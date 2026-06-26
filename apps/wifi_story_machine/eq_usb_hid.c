#include "eq_usb_hid.h"
#include "user_app.h"
#include "sta350bw.h"
#include <string.h>

#define LOG_TAG "EQ_USB"

/* 功放上下文(定义在 user_app.c), 用于判断 initialized 与写 EQ */
extern STA350BW_ctx_t *user_amp_get_ctx(void);
/* USB HID 发送(设备->PC), 定义在 SDK hid.c */
extern unsigned int hid_send_buf_async(const unsigned char usb_id, const unsigned char *buf, unsigned int len);

#define EQ_MUTE_ALL_MASK 0x0F

/* -----------------------------------------------------------------------------
 * 4 段 EQ 当前状态(每段: 频率Hz / 增益0.1dB / Q值*100), 对应 BQ1~BQ4(双声道独立)
 * 默认频段为常见 4 段中心频率, 增益 0(平), Q=1.0(=100)。
 * ---------------------------------------------------------------------------*/
static uint16_t eq_freq[EQ_BAND_COUNT]  = {125, 500, 2000, 8000};
static int16_t  eq_gain[EQ_BAND_COUNT]  = {0, 0, 0, 0}; /* 0.1dB */
static uint16_t eq_q[EQ_BAND_COUNT]     = {100, 100, 100, 100}; /* *100 */
static uint8_t  eq_cur_preset = 0xFF; /* 0xFF=自定义(非预设) */
static uint8_t  eq_custom_dirty = 0;  /* PC 是否下发过自定义段参数(决定开机是否写自定义EQ) */
static uint32_t eq_fs = STA350BW_Fs_44100;

/* -----------------------------------------------------------------------------
 * pending 去抖结构: HID 回调只更新这里并置位, 任务侧批量消费最新一帧
 * ---------------------------------------------------------------------------*/
enum eq_pending_kind {
    EQ_PENDING_NONE = 0,
    EQ_PENDING_BANDS,  /* 7 段参数有更新, 需重算并整体写入 */
    EQ_PENDING_PRESET, /* 切预设 */
    EQ_PENDING_SAVE,   /* 保存到 USER 槽位 */
    EQ_PENDING_FLAT,   /* 全部清平 */
};

static volatile uint8_t eq_pending_kind = EQ_PENDING_NONE;
static volatile uint8_t eq_pending_query = 0;
static volatile uint8_t eq_pending_preset_id = 0;
static volatile uint8_t eq_pending_save_slot = 0;

/* PLACEHOLDER_BODY */

/* =============================================================================
 * 自定义 vendor-defined HID report descriptor (裸字节, 不依赖 SDK 宏避免包含歧义)
 * usage page 0xFF00, IN(设备->PC) 64B + OUT(PC->设备) 64B
 * ===========================================================================*/
static const uint8_t s_eq_hid_report_desc[] = {
    0x06, 0x00, 0xFF,             /* USAGE_PAGE (Vendor-defined 0xFF00) */
    0x09, 0x01,                   /* USAGE (Vendor Usage 1) */
    0xA1, 0x01,                   /* COLLECTION (Application) */
    0x15, 0x00,                   /*   LOGICAL_MINIMUM (0) */
    0x26, 0xFF, 0x00,             /*   LOGICAL_MAXIMUM (255) */
    0x75, 0x08,                   /*   REPORT_SIZE (8) */
    0x09, 0x01,                   /*   USAGE (Vendor Usage 1) - IN */
    0x95, EQ_HID_REPORT_LEN,      /*   REPORT_COUNT (64) */
    0x81, 0x02,                   /*   INPUT (Data,Var,Abs) 设备->PC */
    0x09, 0x02,                   /*   USAGE (Vendor Usage 2) - OUT */
    0x95, EQ_HID_REPORT_LEN,      /*   REPORT_COUNT (64) */
    0x91, 0x02,                   /*   OUTPUT (Data,Var,Abs) PC->设备 */
    0xC0                          /* END_COLLECTION */
};

const uint8_t *eq_usb_hid_report_desc(uint32_t *out_len)
{
    if (out_len) {
        *out_len = sizeof(s_eq_hid_report_desc);
    }
    return s_eq_hid_report_desc;
}

/* =============================================================================
 * 内部工具: 钳位 / 计算单段 biquad 系数
 * ===========================================================================*/
static int16_t eq_clamp_gain(int16_t g)
{
    if (g < EQ_BAND_GAIN_MIN_TENTH) return EQ_BAND_GAIN_MIN_TENTH;
    if (g > EQ_BAND_GAIN_MAX_TENTH) return EQ_BAND_GAIN_MAX_TENTH;
    return g;
}

/* PLACEHOLDER_CALC */

/* 计算第 band 段的 biquad 系数到 coeffs[5]。成功返回 0。 */
static int eq_calc_band(uint8_t band, uint32_t *coeffs)
{
    BIQUAD_Filter_t filter;

    memset(&filter, 0, sizeof(filter));
    filter.Type = BIQUAD_CALCULATOR_PEAK;
    filter.Fs = eq_fs;
    filter.Fc = eq_freq[band];
    filter.Q = (float)eq_q[band] / 100.0f;
    filter.Slope = 0.0f;
    filter.Gain = (float)eq_clamp_gain(eq_gain[band]) / 10.0f;

    if (BQ_CALC_ComputeFilter(&filter) < 0) {
        LOGE("eq_calc_band fail band=%d fc=%d", band, eq_freq[band]);
        return -1;
    }
    memcpy(coeffs, filter.Coefficients, sizeof(filter.Coefficients));
    return 0;
}

/* 把单段写进功放 RAM: band 0~3 -> BQ1~BQ4, 双声道各写一份(地址不冲突) */
static void eq_write_band(uint8_t band, uint32_t *coeffs)
{
    if (band < EQ_BAND_COUNT) {
        STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, (uint8_t)(STA350BW_CH1_BQ1 + band), coeffs);
        STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, (uint8_t)(STA350BW_CH2_BQ1 + band), coeffs);
    }
}

/* 整体重算并热写入 4 段(无 mute, 真正无感实时)。要求功放已 initialized。 */
static void eq_apply_all(void)
{
    STA350BW_ctx_t *amp = user_amp_get_ctx();
    uint8_t band;
    uint32_t coeffs[5];

    if (!amp || !amp->initialized) {
        return;
    }

    /* BQ1~BQ4 直接激活: 关 EQ 旁路即可(不动 BQL/DEMP/TCB, 避免破坏音频通路)。
     * 不做 mute 包裹: STA350BW 的 biquad 系数 RAM 支持热更新, 逐段写不会炸音;
     * 而 SetMute 自带 soft-mute 渐变(淡出+淡入数百ms), 才是"调一下停很久"的主因。
     * 去掉 mute 后即为真正无感实时调节。 */
    STA350BW_SetDSPOption(STA350BW_C1EQBP, STA350BW_DISABLE);
    STA350BW_SetDSPOption(STA350BW_C2EQBP, STA350BW_DISABLE);

    for (band = 0; band < EQ_BAND_COUNT; band++) {
        if (eq_calc_band(band, coeffs) == 0) {
            eq_write_band(band, coeffs);
        }
    }

    LOGI("eq_apply_all: 4 bands written (no-mute, realtime)");
}

/* PLACEHOLDER_PROTO */

/* 组帧并经 HID IN 回传当前 7 段状态给 PC */
static void eq_send_state(void)
{
    uint8_t frame[EQ_HID_REPORT_LEN];
    uint8_t i, sum = 0, p;

    memset(frame, 0, sizeof(frame));
    frame[EQ_HID_OFF_MAGIC] = EQ_HID_MAGIC;
    frame[EQ_HID_OFF_CMD] = EQ_HID_CMD_STATE;
    /* payload: preset(1) + 每段[freq(2)+gain(2)+q(2)] = 1 + 7*6 = 43 字节 */
    p = EQ_HID_OFF_PAYLOAD;
    frame[p++] = eq_cur_preset;
    for (i = 0; i < EQ_BAND_COUNT; i++) {
        frame[p++] = (uint8_t)(eq_freq[i] & 0xFF);
        frame[p++] = (uint8_t)(eq_freq[i] >> 8);
        frame[p++] = (uint8_t)(eq_gain[i] & 0xFF);
        frame[p++] = (uint8_t)(eq_gain[i] >> 8);
        frame[p++] = (uint8_t)(eq_q[i] & 0xFF);
        frame[p++] = (uint8_t)(eq_q[i] >> 8);
    }
    frame[EQ_HID_OFF_LEN] = (uint8_t)(p - EQ_HID_OFF_PAYLOAD);
    for (i = 0; i < p; i++) {
        sum ^= frame[i];
    }
    frame[p] = sum;
    hid_send_buf_async(0, frame, EQ_HID_REPORT_LEN);
}

/* HID 输出回调(PC -> 设备), 运行在 USB 任务上下文。
 * 只校验帧并把目标状态记入 pending, 不做 I2C(解耦关键)。 */
int eq_usb_hid_output(uint8_t *buf, uint32_t len)
{
    uint8_t cmd, plen, sum = 0, i;
    const uint8_t *pl;

    if (!buf || len < EQ_HID_OVERHEAD) {
        return 0;
    }
    if (buf[EQ_HID_OFF_MAGIC] != EQ_HID_MAGIC) {
        return 0;
    }
    cmd = buf[EQ_HID_OFF_CMD];
    plen = buf[EQ_HID_OFF_LEN];
    if (plen > EQ_HID_MAX_PAYLOAD || (uint32_t)(EQ_HID_OVERHEAD + plen) > len) {
        LOGE("hid frame len err:%d", plen);
        return 0;
    }
    for (i = 0; i < (uint8_t)(EQ_HID_OFF_PAYLOAD + plen); i++) {
        sum ^= buf[i];
    }
    if (sum != buf[EQ_HID_OFF_PAYLOAD + plen]) {
        LOGE("hid frame sum err");
        return 0;
    }

    pl = &buf[EQ_HID_OFF_PAYLOAD];
    switch (cmd) {
    case EQ_HID_CMD_SET_BAND:
        /* band(1)+freq(2)+gain(2)+q(2) = 7 字节 */
        if (plen >= 7) {
            uint8_t band = pl[0];
            if (band < EQ_BAND_COUNT) {
                eq_freq[band] = (uint16_t)(pl[1] | (pl[2] << 8));
                eq_gain[band] = (int16_t)(pl[3] | (pl[4] << 8));
                eq_q[band] = (uint16_t)(pl[5] | (pl[6] << 8));
                eq_cur_preset = 0xFF; /* 改成自定义 */
                eq_custom_dirty = 1;  /* 标记 PC 已下发自定义参数 */
                eq_pending_kind = EQ_PENDING_BANDS;
            }
        }
        break;
    case EQ_HID_CMD_PRESET:
        if (plen >= 1) {
            eq_pending_preset_id = pl[0];
            eq_pending_kind = EQ_PENDING_PRESET;
        }
        break;
    case EQ_HID_CMD_SAVE:
        if (plen >= 1) {
            eq_pending_save_slot = pl[0];
            eq_pending_kind = EQ_PENDING_SAVE;
        }
        break;
    case EQ_HID_CMD_FLAT:
        eq_pending_kind = EQ_PENDING_FLAT;
        break;
    case EQ_HID_CMD_QUERY:
        eq_pending_query = 1;
        break;
    default:
        LOGE("unknown hid eq cmd:%d", cmd);
        break;
    }
    return 0;
}

/* PLACEHOLDER_API */

void eq_usb_set_fs(uint32_t fs)
{
    if (fs != 0) {
        eq_fs = fs;
    }
}

/* 应用当前 EQ 状态。功放 init 成功后(user_amp_apply_after_init)调用。
 * 开机默认走驱动内置预设 BASS_BOOST3(经验证可正常出声的安全路径);
 * 只有 PC 下发过自定义参数(eq_cur_preset=0xFF 且被标记 dirty)后才写自定义 4 段。 */
void eq_usb_apply_current(void)
{
    STA350BW_ctx_t *amp = user_amp_get_ctx();

    if (!amp || !amp->initialized) {
        return;
    }

    if (eq_cur_preset != 0xFF) {
        /* 预设模式: 直接用驱动预设(内部已写好 RAM) */
        Switch_Demo((enum BiquadType)eq_cur_preset);
    } else if (eq_custom_dirty) {
        /* PC 调过自定义参数才写, 否则不碰(避免开机用空参数破坏音频) */
        eq_apply_all();
    } else {
        /* 开机默认: 用经验证的内置预设, 保证基础音频干净 */
        Switch_Demo(BIQUAD_TYPE_BASS_BOOST3);
    }
}

/* 任务上下文消费 pending(去抖): 只应用最新一帧。 */
void eq_usb_process_pending(void)
{
    STA350BW_ctx_t *amp = user_amp_get_ctx();
    uint8_t kind;

    if (!amp || !amp->initialized) {
        return;
    }

    kind = eq_pending_kind;
    eq_pending_kind = EQ_PENDING_NONE;

    switch (kind) {
    case EQ_PENDING_BANDS:
        eq_apply_all();
        break;
    case EQ_PENDING_PRESET:
        if (eq_pending_preset_id <= BIQUAD_TYPE_USER_3) {
            eq_cur_preset = eq_pending_preset_id;
            Switch_Demo((enum BiquadType)eq_pending_preset_id);
        } else {
            LOGE("invalid preset id:%d", eq_pending_preset_id);
        }
        break;
    case EQ_PENDING_FLAT: {
        uint8_t b;
        for (b = 0; b < EQ_BAND_COUNT; b++) {
            eq_gain[b] = 0;
        }
        eq_cur_preset = 0xFF;
        eq_custom_dirty = 1;
        eq_apply_all();
        break;
    }
    case EQ_PENDING_SAVE:
        /* 当前实现: RAM 已实时生效即视为保存(VM 持久化可后续扩展)。 */
        LOGI("eq save slot:%d (RAM applied)", eq_pending_save_slot);
        break;
    default:
        break;
    }

    if (eq_pending_query) {
        eq_pending_query = 0;
        eq_send_state();
    }
}




