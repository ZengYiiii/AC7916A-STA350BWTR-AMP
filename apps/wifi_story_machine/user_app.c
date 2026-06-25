#include "user_app.h"
#include "sta350bw.h"
#include "le_trans_data.h"
#include "eq_protocol.h"
#include <stdlib.h>
#include <string.h>

#define LOG_TAG "USER_APP"
#define USER_AUDIODEVICE_TASK_STACK_SIZE 2048
#define USER_AUDIODEVICE_TASK_PRIO 6
#define USER_AUDIODEVICE_TASK_Q 0
#define STA350BW_INIT_VOLUME 80
#define STA350BW_MUTE_ALL_MASK 0x0F

/* 开机 USB 烧录窗口: 上电后先挂起 USB(不枚举成声卡), 延迟一段时间给烧录工具
 * 抢占 USB 下载口的机会, 之后再恢复 USB 声卡功能。0 可关闭此功能。 */
#define USB_DOWNLOAD_WINDOW_MS 3000

void *AudioDrvI2C_Handle = NULL;

/* 主动点亮IIS0 MCLK,供STA350BW(I2S从机)锁PLL,定义见board_7916A.c */
extern void board_iis0_clk_keep_on(void);

static STA350BW_ctx_t STA350BW = {0};
extern uint32_t USER_1_EQ_PRESET[];
extern uint32_t USER_2_EQ_PRESET[];
extern uint32_t USER_3_EQ_PRESET[];

#define USER_EQ_BAND_COUNT 4
#define BLE_CMD_MAX_LEN 96
#define USER_EQ_GAIN_MIN_TENTH_DB (-120)
#define USER_EQ_GAIN_MAX_TENTH_DB (120)

static const uint16_t user_eq_freqs[USER_EQ_BAND_COUNT] = {125, 500, 2000, 8000};
static const float user_eq_q = 1.0f;
static const uint32_t user_eq_flat_bq[5] = {0x000000, 0x000000, 0x000000, 0x000000, 0x400000};
static uint32_t user_eq_coeffs[USER_EQ_BAND_COUNT][5];
static uint8_t user_eq_ready = 0;
static uint32_t user_eq_fs = STA350BW_Fs_44100;
/* 当前 EQ 状态(供 QUERY 回传): 4 段增益(0.1dB) + 当前预设 id */
static int8_t user_eq_cur_gains[USER_EQ_BAND_COUNT] = {0, 0, 0, 0};
static uint8_t user_eq_cur_preset = BIQUAD_TYPE_FLAT;
/* 经 ae3c 通知回传 EQ 状态, 定义见 le_trans_data.c */
extern int eq_notify_send(const unsigned char *data, unsigned short len);
/*******************************************************************************
Static Functions
*******************************************************************************/

static int user_eq_clamp_gain(int gain_tenths)
{
    if (gain_tenths < USER_EQ_GAIN_MIN_TENTH_DB)
    {
        return USER_EQ_GAIN_MIN_TENTH_DB;
    }
    if (gain_tenths > USER_EQ_GAIN_MAX_TENTH_DB)
    {
        return USER_EQ_GAIN_MAX_TENTH_DB;
    }
    return gain_tenths;
}

static void user_eq_update_band(uint8_t band, float gain_db)
{
    BIQUAD_Filter_t filter;

    if (!STA350BW.initialized || band >= USER_EQ_BAND_COUNT)
    {
        return;
    }

    memset(&filter, 0, sizeof(filter));
    filter.Type = BIQUAD_CALCULATOR_PEAK;
    filter.Fs = user_eq_fs;
    filter.Fc = user_eq_freqs[band];
    filter.Q = user_eq_q;
    filter.Slope = 0.0f;
    filter.Gain = gain_db;

    if (BQ_CALC_ComputeFilter(&filter) < 0)
    {
        LOGE("user_eq_update_band: calc fail band=%d gain=%.1f", band, gain_db);
        return;
    }

    memcpy(user_eq_coeffs[band], filter.Coefficients, sizeof(filter.Coefficients));

    STA350BW_SetDSPOption(STA350BW_C1EQBP, STA350BW_DISABLE);
    STA350BW_SetDSPOption(STA350BW_C2EQBP, STA350BW_DISABLE);
    STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, (uint8_t)(STA350BW_CH1_BQ1 + band), filter.Coefficients);
    STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, (uint8_t)(STA350BW_CH2_BQ1 + band), filter.Coefficients);

    user_eq_ready = 1;
}

static void user_eq_apply_all(const int *gains_tenths, uint8_t count)
{
    uint8_t i = 0;

    if (!gains_tenths || count != USER_EQ_BAND_COUNT)
    {
        return;
    }

    for (i = 0; i < USER_EQ_BAND_COUNT; i++)
    {
        float gain_db = (float)user_eq_clamp_gain(gains_tenths[i]) / 10.0f;
        user_eq_update_band(i, gain_db);
    }
}

static void user_eq_copy_to_preset(uint32_t *preset)
{
    uint8_t i = 0;

    if (!preset)
    {
        return;
    }

    for (i = 0; i < USER_EQ_BAND_COUNT; i++)
    {
        memcpy(&preset[i * 5], user_eq_coeffs[i], sizeof(user_eq_coeffs[i]));
    }
    memcpy(&preset[USER_EQ_BAND_COUNT * 5], user_eq_flat_bq, sizeof(user_eq_flat_bq));
}

static void ble_apply_preset_id(uint8_t preset_id)
{
    if (preset_id > BIQUAD_TYPE_USER_3)
    {
        LOGE("invalid preset id:%d", preset_id);
        return;
    }
    Switch_Demo((enum BiquadType)preset_id);
}

static void ble_save_user_preset(uint8_t slot)
{
    if (!user_eq_ready)
    {
        int gains[USER_EQ_BAND_COUNT] = {0};
        user_eq_apply_all(gains, USER_EQ_BAND_COUNT);
    }

    switch (slot)
    {
    case EQ_SAVE_SLOT_1:
        user_eq_copy_to_preset(USER_1_EQ_PRESET);
        break;
    case EQ_SAVE_SLOT_2:
        user_eq_copy_to_preset(USER_2_EQ_PRESET);
        break;
    case EQ_SAVE_SLOT_3:
        user_eq_copy_to_preset(USER_3_EQ_PRESET);
        break;
    default:
        LOGE("invalid save slot:%d", slot);
        break;
    }
}

/* 经 ae3c 回传当前 EQ 状态: [MAGIC][CMD=QUERY][LEN=5][g0 g1 g2 g3 preset][SUM] */
static void eq_send_query_response(void)
{
    uint8_t frame[EQ_FRAME_OVERHEAD + EQ_QUERY_RESP_LEN];
    uint8_t i, sum = 0;

    frame[EQ_FRAME_OFF_MAGIC] = EQ_PROTO_MAGIC;
    frame[EQ_FRAME_OFF_CMD] = EQ_CMD_QUERY;
    frame[EQ_FRAME_OFF_LEN] = EQ_QUERY_RESP_LEN;
    for (i = 0; i < USER_EQ_BAND_COUNT; i++)
    {
        frame[EQ_FRAME_OFF_PAYLOAD + i] = (uint8_t)user_eq_cur_gains[i];
    }
    frame[EQ_FRAME_OFF_PAYLOAD + USER_EQ_BAND_COUNT] = user_eq_cur_preset;
    for (i = 0; i < (uint8_t)(EQ_FRAME_OFF_PAYLOAD + EQ_QUERY_RESP_LEN); i++)
    {
        sum ^= frame[i];
    }
    frame[EQ_FRAME_OFF_PAYLOAD + EQ_QUERY_RESP_LEN] = sum;
    eq_notify_send(frame, sizeof(frame));
}

/* BLE EQ 二进制命令解析: [MAGIC][CMD][LEN][PAYLOAD..][SUM], 见 eq_protocol.h */
static void ble_sound_tuner_command_parse(const uint8_t *packet, uint16_t size)
{
    uint8_t cmd, len, sum = 0, i;
    const uint8_t *pl;
    int gains[USER_EQ_BAND_COUNT];

    if (!packet || size < EQ_FRAME_MIN_LEN)
    {
        return;
    }
    if (packet[EQ_FRAME_OFF_MAGIC] != EQ_PROTO_MAGIC)
    {
        return;
    }
    cmd = packet[EQ_FRAME_OFF_CMD];
    len = packet[EQ_FRAME_OFF_LEN];
    if (len > EQ_FRAME_MAX_PAYLOAD || (uint16_t)(EQ_FRAME_OVERHEAD + len) > size)
    {
        LOGE("eq frame len err:%d size:%d", len, size);
        return;
    }
    for (i = 0; i < (uint8_t)(EQ_FRAME_OFF_PAYLOAD + len); i++)
    {
        sum ^= packet[i];
    }
    if (sum != packet[EQ_FRAME_OFF_PAYLOAD + len])
    {
        LOGE("eq frame sum err");
        return;
    }

    pl = &packet[EQ_FRAME_OFF_PAYLOAD];
    switch (cmd)
    {
    case EQ_CMD_SET_BAND:
        if (len >= 2)
        {
            uint8_t band = pl[0];
            int g = user_eq_clamp_gain((int8_t)pl[1]);
            if (band < USER_EQ_BAND_COUNT)
            {
                user_eq_update_band(band, (float)g / 10.0f);
                user_eq_cur_gains[band] = (int8_t)g;
            }
        }
        break;
    case EQ_CMD_SET_ALL:
        if (len >= USER_EQ_BAND_COUNT)
        {
            for (i = 0; i < USER_EQ_BAND_COUNT; i++)
            {
                gains[i] = user_eq_clamp_gain((int8_t)pl[i]);
                user_eq_cur_gains[i] = (int8_t)gains[i];
            }
            user_eq_apply_all(gains, USER_EQ_BAND_COUNT);
        }
        break;
    case EQ_CMD_PRESET:
        if (len >= 1)
        {
            ble_apply_preset_id(pl[0]);
            user_eq_cur_preset = pl[0];
        }
        break;
    case EQ_CMD_SAVE:
        if (len >= 1)
        {
            ble_save_user_preset(pl[0]);
        }
        break;
    case EQ_CMD_QUERY:
        eq_send_query_response();
        break;
    default:
        LOGE("unknown eq cmd:%d", cmd);
        break;
    }
}

/* 音频输出走 iis0 -> 外置功放 STA350BW, 不经过芯片 DAC, 因此 SDK 的 DAC/数字音量
 * 对最终响度无效。最终响度的唯一旋钮是功放 MVOL 主音量, 故手机音量(0~100)直接
 * 映射到功放 MVOL。兼容两类手机: 支持 AVRCP 绝对音量的手机滑条精准对应; 不支持的
 * 手机由协议栈按步进逻辑给出递增/递减后的 vol, 走同一入口, 无需两套逻辑。
 * user_amp_volume 记录最近一次设置的功放音量, 供连接时与手机滑条同步。 */
static uint8_t user_amp_volume = STA350BW_INIT_VOLUME;

/* 统一的功放音量落地: 钳位到 0~100, 写 MVOL, 并记录当前值供同步查询。
 * vol=0 时 STA350BW_SetVolume 内部会写 0xFF 真静音。 */
static void user_amp_set_volume(int volume)
{
    if (volume < 0)
    {
        volume = 0;
    }
    if (volume > 100)
    {
        volume = 100;
    }

    if (!STA350BW.initialized)
    {
        /* 功放还没初始化好: 只记录目标值, 等 probe 成功后由落地函数写入 */
        user_amp_volume = (uint8_t)volume;
        LOGD("amp not ready, cache volume:%d", volume);
        return;
    }

    if (STA350BW_SetVolume(STA350BW_CHANNEL_MASTER, (uint8_t)volume) != RET_STATUS_OK)
    {
        LOGE("功放音量设置失败:%d", volume);
        return;
    }
    user_amp_volume = (uint8_t)volume;
    LOGI("功放音量设置成功:%d", volume);
}

/* 供外部(如连接同步)查询当前功放音量(0~100) */
int user_amp_get_volume(void)
{
    return user_amp_volume;
}

void BT_MUSIC_VOLUME_Event(int volume)
{
    LOGD("BT_MUSIC_VOLUME_Event:%d", volume);
    user_amp_set_volume(volume);
}

void USB_MUSIC_VOLUME_Event(int volume)
{
    LOGD("USB_MUSIC_VOLUME_Event:%d", volume);
    user_amp_set_volume(volume);
}

/* ----------------------------------------------------------------------------*/
/**
 * @brief BLE RX事件 提供给用户使用
 */
/* ----------------------------------------------------------------------------*/
void BLE_RX_Event(uint16_t att_handle, uint16_t transaction_mode, uint16_t offset, uint8_t *buffer, uint16_t buffer_size)
{
    switch (att_handle)
    {
    case ATT_CHARACTERISTIC_ae3b_01_VALUE_HANDLE:
        ble_sound_tuner_command_parse(buffer, buffer_size);
        break;

    default:
        break;
    }
}

/********************************************************************************/

static int32_t User_I2C_Init(void)
{
    int32_t ret = RET_STATUS_OK;
    LOGD("User_I2C_Init");
#if (CONFIG_APP_I2C_BUS_ID == 0)
    AudioDrvI2C_Handle = dev_open("iic0", NULL);
#else
    AudioDrvI2C_Handle = dev_open("iic1", NULL);
#endif
    if (!AudioDrvI2C_Handle)
    {
        LOGE("AudioDrvI2C_Handle open err \n");
        ret = RET_STATUS_INITIALIZATION;
    }
    else
    {
        ret = RET_STATUS_OK;
    }
    LOGI("User I2C Init OK , AudioDrvI2C_Handle = %p", AudioDrvI2C_Handle);
    return ret;
}

static int32_t User_I2C_DeInit(void)
{
    int32_t ret = RET_STATUS_OK;

    ret = dev_close(AudioDrvI2C_Handle);
    if (ret)
    {
        LOGE("AudioDrvI2C_Handle close err \n");
        ret = RET_STATUS_IN_PROGRESS;
    }
    else
    {
        ret = RET_STATUS_OK;
    }
    return ret;
}

static ret_status_t iic_write_one_byte(uint8_t DevAddress, unsigned char addr, unsigned int data) // 返回值为0成功，非0失败
{
    ret_status_t ret = RET_STATUS_OK;

    dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_START, 0);                          // IIC锁定
    if (dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_TX_WITH_START_BIT, DevAddress)) // 起始信号 + 写地址命令
    {
        ret = RET_STATUS_TRANSMIT;
        LOGE("AudioDrvI2C_Handle write err in IIC_IOCTL_TX_WITH_START_BIT @%d", __LINE__);
        goto exit;
    }
    delay_us(100);
    if (dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_TX, addr)) // 写地址
    {
        ret = RET_STATUS_TRANSMIT;
        LOGE("AudioDrvI2C_Handle write err in IIC_IOCTL_TX @%d", __LINE__);
        goto exit;
    }
    delay_us(100);
    if (dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_TX_WITH_STOP_BIT, data)) // 写数据 + 结束信号
    {
        ret = RET_STATUS_TRANSMIT;
        LOGE("AudioDrvI2C_Handle write err in IIC_IOCTL_TX_WITH_STOP_BIT @%d", __LINE__);
        goto exit;
    }
    delay_us(100);

exit:
    dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_STOP, 0); // IIC解锁
    return ret;
}

static ret_status_t iic_read_one_byte(uint8_t DevAddress, unsigned char addr, unsigned char *data) // 返回值为0成功，非0失败
{
    ret_status_t ret = RET_STATUS_OK;

    dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_START, 0);                          // IIC锁定
    if (dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_TX_WITH_START_BIT, DevAddress)) // 起始信号 + 读地址命令
    {
        ret = RET_STATUS_TRANSMIT;
        LOGE("AudioDrvI2C_Handle write err in IIC_IOCTL_TX_WITH_START_BIT @%d", __LINE__);
        goto exit;
    }
    delay_us(100);
    if (dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_TX_WITH_STOP_BIT, addr)) // 读地址 + 结束信号
    {
        ret = RET_STATUS_TRANSMIT;
        LOGE("AudioDrvI2C_Handle write err IIC_IOCTL_TX_WITH_STOP_BIT @%d", __LINE__);
        goto exit;
    }
    delay_us(100);
    if (dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_TX_WITH_START_BIT, (DevAddress) | BIT(0))) // 起始信号 + 读数据命令
    {
        ret = RET_STATUS_TRANSMIT;
        LOGE("AudioDrvI2C_Handle write err IIC_IOCTL_TX_WITH_START_BIT @%d", __LINE__);
        goto exit;
    }
    delay_us(100);

#if 1
    // 接收没有ACK：IIC_IOCTL_RX_WITH_STOP_BIT，读数据 + 结束信号
    dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_RX_WITH_STOP_BIT, (u32)data); // 读数据 + 结束信号
#else
    // 接收需要ACK，则命令为 IIC_IOCTL_RX_WITH_ACK，如下：
    dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_RX_WITH_ACK, (u32)data); // 读数据 + ACK
    dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_TX_STOP_BIT, 0);         // 结束信号
#endif

exit:
    dev_ioctl(AudioDrvI2C_Handle, IIC_IOCTL_STOP, 0); // IIC解锁
    return ret;
}

/**
 * @brief  Read a register of the device through BUS
 * @param  DevAddr Device address on Bus.
 * @param  Reg    The target register address to read
 * @param  pData  Pointer to data buffer to read
 * @param  Length Data Length
 * @retval USER status
 */

int32_t User_I2C_ReadReg(uint8_t DevAddr, uint8_t Reg, uint8_t *pData, uint8_t Length)
{
    // LOGD("User_I2C_ReadReg DevAddr=0x%X Reg=0x%X Length=%d", DevAddr, Reg, Length);
    for (int i = 0; i < Length; i++)
    {
        if (iic_read_one_byte(DevAddr, Reg++, &pData[i]) != RET_STATUS_OK)
        {
            LOGE("User_I2C_ReadReg ERROR");
            return RET_STATUS_TRANSMIT;
        }
    }
    return RET_STATUS_OK;
}

/**

  * @brief  Write a value in a register of the device through BUS.
  * @param  DevAddr Device address on Bus.
  * @param  Reg    The target register address to write

  * @param  pData  Pointer to data buffer to write
  * @param  Length Data Length
  * @retval USER statu
  */
int32_t User_I2C_WriteReg(uint8_t DevAddr, uint8_t Reg, uint8_t *pData, uint8_t Length)
{
    // LOGD("User_I2C_WriteReg DevAddr=0x%X Reg=0x%X Length=%d", DevAddr, Reg, Length);
    for (int i = 0; i < Length; i++)
    {
        if (iic_write_one_byte(DevAddr, Reg++, pData[i]) != 0)
        {
            LOGE("User_I2C_WriteReg ERROR");
            return RET_STATUS_TRANSMIT;
        }
    }

    return RET_STATUS_OK;
}

int32_t User_GetTick(void)
{
    return xTaskGetTickCount();
}

/**
 * @brief  I2C/STA350BW 上电自检: 不依赖示波器, 仅靠串口判断
 *         I2C 是否物理通讯, 以及 PLL 是否锁定(MCLK 是否正常)。
 */
static void STA350BW_I2C_SelfCheck(void)
{
    const uint8_t addr_list[] = {STA350BW_ADDRESS_1, STA350BW_ADDRESS_2};
    uint8_t status = 0, rega = 0;
    int32_t r1, r2;

    /* 临时挂上回调以便用 STA350BW_ReadReg 读寄存器 */
    STA350BW.read_reg = User_I2C_ReadReg;
    STA350BW.write_reg = User_I2C_WriteReg;

    for (size_t i = 0; i < sizeof(addr_list) / sizeof(addr_list[0]); i++)
    {
        STA350BW.i2c_address = addr_list[i];
        status = 0xA5;
        rega = 0xA5;
        r1 = User_I2C_ReadReg(addr_list[i], STA350BW_STATUS, &status, 1);
        r2 = User_I2C_ReadReg(addr_list[i], STA350BW_CONF_REGA, &rega, 1);
        LOGW("[SelfCheck] addr=0x%02X STATUS rd_ret=%d val=0x%02X | REGA rd_ret=%d val=0x%02X",
             addr_list[i], (int)r1, status, (int)r2, rega);
        if (r1 == RET_STATUS_OK)
        {
            if (status == 0x7F)
            {
                LOGW("[SelfCheck] addr=0x%02X OK: I2C通 且 PLL已锁(STATUS=0x7F)", addr_list[i]);
            }
            else
            {
                /* STATUS bit7 = PLLUL (PLL unlock) */
                LOGW("[SelfCheck] addr=0x%02X I2C通 但 PLL未锁(STATUS=0x%02X, bit7 PLLUL=%d) -> 查MCLK",
                     addr_list[i], status, (status >> 7) & 1);
            }
        }
        else
        {
            LOGE("[SelfCheck] addr=0x%02X I2C读失败 -> 查I2C(baudrate/上拉/接线/地址)", addr_list[i]);
        }
    }
}

/**
 * @brief  功放 init 成功后的统一"落地"动作: 解除静音 + 写入功放默认音量 + 恢复 EQ。
 *         无论是开机首次 probe 成功, 还是后来(播放时 MCLK 稳定才)重试成功, 都必须
 *         调用本函数, 否则会出现"PLL 锁上了但音量/unmute 没写进芯片 -> 依然没声"。
 *         设计约定: 音频走 iis0 外接功放, 不经 DAC, 最终响度只由功放 MVOL 决定。
 *         手机音量直接映射到功放 MVOL(见 BT_MUSIC_VOLUME_Event), 这里用 user_amp_volume
 *         (最近一次的目标音量, 默认 STA350BW_INIT_VOLUME)落地, 保证 probe 成功瞬间
 *         功放音量与已知目标一致, 不会出现"刚出声就满音量"。
 */
static void user_amp_apply_after_init(void)
{
    if (!STA350BW.initialized)
    {
        return;
    }

    /* 1) 解除全通道静音 */
    STA350BW_SetMute(STA350BW_MUTE_ALL_MASK, STA350BW_DISABLE);

    /* 2) 写入当前目标音量(开机=默认档, 若手机已调过则为最新值) */
    if (STA350BW_SetVolume(STA350BW_CHANNEL_MASTER, user_amp_volume) != RET_STATUS_OK)
    {
        LOGE("user_amp_apply_after_init: set volume %d 失败", user_amp_volume);
    }
    else
    {
        LOGI("user_amp_apply_after_init: unmute + volume=%d OK", user_amp_volume);
    }

    /* 3) 应用默认 EQ 预设: 低音增强3(BASS_BOOST3) */
    Switch_Demo(BIQUAD_TYPE_BASS_BOOST3);
}

/**
 * @brief  Register Bus IOs if component ID is OK
 * @retval error status
 */
static int32_t STA350BW_Probe(void)
{
    int32_t ret = RET_STATUS_OK;
    uint32_t init_fs = 0;
    const uint8_t addr_list[] = {STA350BW_ADDRESS_1, STA350BW_ADDRESS_2};

    /* 先点亮IIS0 MCLK,STA350BW从机需靠它锁PLL,否则STATUS读不到0x7F */
    board_iis0_clk_keep_on();

    AUDIO_DEVICE_ON();
    AUDIO_DEVICE_RESET();
    delay_us(1000);
    AUDIO_DEVICE_UNRESET();
    delay_us(5000);

    /* 上电自检: 串口直接看出 I2C 通不通 / PLL 锁没锁 */
    STA350BW_I2C_SelfCheck();

    STA350BW.read_reg = User_I2C_ReadReg;      // i2c read callback
    STA350BW.write_reg = User_I2C_WriteReg;    // i2c write callback

    for (size_t i = 0; i < sizeof(addr_list) / sizeof(addr_list[0]); i++)
    {
        STA350BW.i2c_address = addr_list[i];
        ret = STA350BW_Init(&STA350BW, STA350BW_INIT_VOLUME, STA350BW_Fs_44100);
        if (ret == STA350BW_OK)
        {
            init_fs = STA350BW_Fs_44100;
            break;
        }
        ret = STA350BW_Init(&STA350BW, STA350BW_INIT_VOLUME, STA350BW_Fs_48000);
        if (ret == STA350BW_OK)
        {
            init_fs = STA350BW_Fs_48000;
            break;
        }
    }

    if (ret != STA350BW_OK)
    {
        for (size_t i = 0; i < sizeof(addr_list) / sizeof(addr_list[0]); i++)
        {
            STA350BW.i2c_address = (uint8_t)(addr_list[i] << 1);
            ret = STA350BW_Init(&STA350BW, STA350BW_INIT_VOLUME, STA350BW_Fs_44100);
            if (ret == STA350BW_OK)
            {
                init_fs = STA350BW_Fs_44100;
                break;
            }
            ret = STA350BW_Init(&STA350BW, STA350BW_INIT_VOLUME, STA350BW_Fs_48000);
            if (ret == STA350BW_OK)
            {
                init_fs = STA350BW_Fs_48000;
                break;
            }
        }
    }

    if (ret != STA350BW_OK)
    {
        LOGE("AudioDrv->Init ERROR:0x%X", ret);
        ret = RET_STATUS_INVALID_HANDLE;
        STA350BW.initialized = 0;
    }
    else
    {
        LOGI("STA350BW init OK addr=0x%X fs=%u", STA350BW.i2c_address, init_fs);
        if (init_fs != 0)
        {
            user_eq_fs = init_fs;
        }
        ret = RET_STATUS_OK;
        STA350BW.initialized = 1;
        /* PLL 锁定、init 成功的瞬间立即落地: 解除静音 + 写当前音量 + 恢复 EQ。
         * 关键: 无论开机首次成功还是播放时重试成功, 都在这里把声音配置写进芯片。 */
        user_amp_apply_after_init();
    }
    return ret;
}

/**
 * @brief UserAudioDeviceTaskEntrance task
 */
static void UserAudioDeviceTaskEntrance(void *pvParameter)
{
    int32_t ret = RET_STATUS_OK;

    // os_time_dly(100);
    LOGW("UserAudioDeviceTaskEntrance");

#if (USB_DOWNLOAD_WINDOW_MS > 0)
    /* 开机先挂起 USB, 留出烧录窗口, 期间顺便完成功放初始化, 窗口结束再恢复 USB 声卡 */
    extern void usb_otg_suspend(unsigned char usb_id, unsigned char op_mode);
    extern void usb_otg_resume(unsigned char usb_id);
    usb_otg_suspend(0, 1 /* OTG_UNINSTALL, 见 usb/otg.h */);
    LOGW("USB suspended for download window %dms", USB_DOWNLOAD_WINDOW_MS);
#endif

    ret = User_I2C_Init();
    if (ret != RET_STATUS_OK)
    {
        LOGE("User_I2C_Init ERROR:0x%X", ret);
    }
    else
        LOGI("User_I2C_Init OK");

    ret = STA350BW_Probe();
    if (ret != RET_STATUS_OK)
    {
        LOGE("STA350BW_Probe ERROR:0x%X", ret);
    }
    else
        LOGI("STA350BW_Probe OK");

#if (USB_DOWNLOAD_WINDOW_MS > 0)
    /* 等满烧录窗口(扣除已耗时), 再恢复 USB */
    os_time_dly(USB_DOWNLOAD_WINDOW_MS / 10);
    usb_otg_resume(0);
    LOGW("USB resumed, sound card enabled");
#endif

    /* 开机首次 probe 若已成功, user_amp_apply_after_init() 已在 probe 内完成落地,
     * 这里无需重复处理。下面的 while 负责"开机没锁上 PLL"时持续重试。 */
    while (1)
    {
        if (!STA350BW.initialized)
        {
            /* 方案A: 开机阶段 IIS0 时钟刚常驻、PLL 可能还没稳, 此时 probe 易失败。
             * 真正播放音乐后 IIS0 数据流在跑、MCLK 绝对稳定, 这里持续重试必能锁上;
             * 一旦成功, probe 内部的 user_amp_apply_after_init() 会立即把音量/unmute/EQ
             * 写进芯片, 声音随即出来。重试间隔收紧到 0.5s, 让播放后尽快补声。 */
            ret = STA350BW_Probe();
            if (ret != RET_STATUS_OK)
            {
                LOGE("STA350BW_Probe retry ERROR:0x%X", ret);
            }
            else
            {
                LOGI("STA350BW_Probe retry OK (PLL locked, sound applied)");
            }
        }
        /* 0.5s 一轮: 未初始化时快速重试补声; 已初始化后这只是低频空转, 开销可忽略 */
        os_time_dly(50);
    }
}

static int UserAudioDeviceTaskStart(void)
{

    LOGW("UserAudioDeviceTaskStart");
    if (thread_fork("UserAudioDevice", USER_AUDIODEVICE_TASK_PRIO, USER_AUDIODEVICE_TASK_STACK_SIZE, USER_AUDIODEVICE_TASK_Q, NULL, UserAudioDeviceTaskEntrance, NULL) != 0)
    {
        // 创建任务失败
        LOGE("Failed to create UserAudioDevice task\n");
    }
    return 0;
}
late_initcall(UserAudioDeviceTaskStart);
