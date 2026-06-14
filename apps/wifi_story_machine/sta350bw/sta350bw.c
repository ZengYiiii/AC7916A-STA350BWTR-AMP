/**
****************************************************************************************
*@文件sta350bw.c
*@author SRA -中央实验室
*@版本v3.0.0
*@日期 2019 年 5 月 6 日
*@brief文件提供该STA350BW SOUND TERMINAL音频驱动程序。
****************************************************************************************
*@注意力
*
*<h2><center>© COPYRIGHT(c) 2019 意法半导体</center></h2>
*
*以源代码和二进制形式重新分发和使用，无论是否经过修改，
*是允许的，前提是满足以下条件：
*1.来源代码的再分发必须保留上述版权声明，
*此条件列表和以下免责声明。
*2.以二进制形式重新分发必须复制上述版权声明，
*文档中的条件列表和以下免责声明
*和/或随机分发一起提供其他材料。
*3.既不是意法半导体的名称，也不是其贡献者的姓名
*可用于认可或推广源自软件衍生的产品
*事先事先征得同意。
*
*本软件由版权所有者和贡献者“按原样”提供
*以及任何明示或暗示的保证，包括但不限于
*对适销性和特定用途适用性的默示保证是
*免责声明。在任何情况下，版权所有者或贡献者均不承担任何责任
*对于任何直接、间接、偶然、特殊、示范性或后果性的
*损害（包括但不限于采购替代品或
*服务；使用、数据或利润的损失；或业务中断）但是
*造成的和基于任何责任理论，无论是合同责任、严格责任，
*或因使用而产生的任何目标行为（包括疏忽或其他原因）
*本软件，即使被告知也可能发生此类损坏。
*
****************************************************************************************
*/
/*包括 ------------------------------------------------------------------*/
#include "sta350bw.h"

#define LOG_TAG "STA350BW"

/**@addtogroup BSP
 *@{
 */
/**@addtogroup 组件
 *@{
 */
/**@addtogroup STA350BW
 *@{
 */
/**@defgroup STA350BW_Private_Types
 *@{
 */
/**
 *@}
 */
/**@defgroup STA350BW_Private_Defines
 *@{
 */
/**
 *@}
 */
/**@defgroup STA350BW_Private_Macros
 *@{
 */
/**
 *@}
 */
/**@defgroup STA350BW_Private_Variables
 *@{
 */
/**
 *@}
 */
/**@defgroup STA350BW_Private_FunctionPrototypes
 *@{
 */

static STA350BW_ctx_t ctx = {0};

static int32_t writeRAMSet(uint8_t RAM_block,
                           uint8_t RAM_address, uint8_t *pIn);

int32_t STA350BW_ReadReg(uint8_t RegAddr, uint16_t NumByteToRead, uint8_t *Data);
int32_t STA350BW_WriteReg(uint8_t RegAddr, uint16_t NumByteToRead, uint8_t *Data);

/**
 *@}
 */
/**@defgroup STA350BW_Private_Functions
 *@{
 */
/**
 *@brief 初始化 STA350BW 和控制接口。
 *@param handle：与当前设备实例相关的对象。
 *@paramvolume：要设置的主音量。
 *@param SampleFreq：采样频率。
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_Init(STA350BW_ctx_t *dev, uint16_t volume,
                      uint32_t samplingFreq)
{
  uint8_t tmp = 0x00;

  ctx.read_reg = dev->read_reg;
  ctx.write_reg = dev->write_reg;
  ctx.i2c_address = dev->i2c_address;
  ctx.initialized = 0;
  /*根据采样频率设置主时钟*/
  if (STA350BW_SetFrequency(samplingFreq) != 0)
  {
    return STA350BW_ERROR;
  }

  /*读取状态注册*/
  /* PLL锁定需要时间(MCLK稳定后),轮询等待STATUS==0x7F,最多约100ms */
  {
    uint8_t retry = 0;
    for (retry = 0; retry < 20; retry++)
    {
      if (STA350BW_ReadReg(STA350BW_STATUS, 1, &tmp) == 0 && tmp == 0x7F)
      {
        break;
      }
      delay_us(5000);
    }
  }
  if (tmp != 0x7F)
  {
    /*状态已明显显示不良行为
    （PLL未锁定，...）*/
    // LOGD("运行：%s 函数：%s 行：%d ", __FILE__, __func__, __LINE__);
    LOGE("Status register highlights undesired behaviour PLL not locked tmp:%X", tmp);
    return STA350BW_ERROR;
  }
  LOGI("STA350BW_Init Status:%X", tmp);
  /*设置主音量(MVOL: 0x00=0dB, 越大越衰减, 整机音量靠它控制)*/
  if (STA350BW_SetVolume(STA350BW_CHANNEL_MASTER, volume) != 0)
  {
    return STA350BW_ERROR;
  }
  /*
   * 通道音量 C1V/C2V 固定为 0dB(0x60)。
   * 注意: 通道音量寄存器映射与主音量不同 —— CxV=0x00 是 +48dB, 0x60 才是 0dB,
   * 总增益 = 通道音量 + 主音量偏移(datasheet 8.7.2)。若通道也套用主音量公式会
   * 变成大幅增益, 抵消主音量衰减(表现为"音量调到很小仍很大声")。
   * 这里把两个通道钉在 0dB, 让整机音量完全由 MVOL 决定。
   */
  {
    uint8_t ch0db = 0x60; /* CxV = 0x60 -> 0 dB */
    if (STA350BW_WriteReg(STA350BW_C1VOL, 1, &ch0db) != 0)
    {
      return STA350BW_ERROR;
    }
    if (STA350BW_WriteReg(STA350BW_C2VOL, 1, &ch0db) != 0)
    {
      return STA350BW_ERROR;
    }
  }

  if (STA350BW_ReadReg(STA350BW_CONF_REGF, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }

  LOGI("STA350BW_Init Conf_RegF:%X", tmp);

  tmp &= ~0x80;
  tmp |= 0x80;

  LOGI("STA350BW_Init 写入 Conf_RegF:%X", tmp);

  /*启用断电阶段*/
  if (STA350BW_WriteReg(STA350BW_CONF_REGF, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }


  // 打开功率提升 不打开F3X模式
  // tmp = 0x65;
  // if (STA350BW_WriteReg(0x4B, 1, &tmp) != 0)
  // {
  //   return STA350BW_ERROR;
  // }

  /*更改音调设置*/
  // STA350BW_SetTone(0x8D);

  LOGI("STA350BW_Init Tone:%X", tmp);

  Switch_Demo(BIQUAD_TYPE_FLAT);

  ctx.initialized = 1;
  dev->initialized = 1;
  return STA350BW_OK;
}

/**
 *@brief 取消初始化 STA350BW 和控制接口。
 *@param handle：与当前设备实例相关的对象。
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_DeInit(void)
{
  uint8_t tmp;
  if (STA350BW_ReadReg(STA350BW_CONF_REGF, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  tmp &= ~0xC0;
  if (STA350BW_WriteReg(STA350BW_CONF_REGF, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  return STA350BW_OK;
}

/**
 *@brief读取设备ID。
 *@param handle：与当前设备实例相关的对象。
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_ReadID(void)
{
  LOGE("Runing:%s Line:%d (未实现)", __FILE__, __LINE__);
  return STA350BW_NOT_IMPLEMENTED;
}

/**
 *@brief 开始音频播放。
 *@param handle：与当前设备实例相关的对象。
 *@param *pData：指向音频数据的指针。
 *@param *p：指向可选附加函数的指针。
 *@param Size：数据坐标的大小。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_Play(uint16_t *pBuffer, uint16_t Size)
{
  LOGE("Runing:%s Line:%d (未实现)", __FILE__, __LINE__);
  return STA350BW_NOT_IMPLEMENTED;
}

/**
 *@brief暂停音频播放。
 *@param handle：与当前设备实例相关的对象。
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_Pause(void)
{
  /*静音输出*/
  if (STA350BW_SetMute(STA350BW_CHANNEL_MASTER, STA350BW_ENABLE) != 0)
  {
    return STA350BW_ERROR;
  }
  return STA350BW_OK;
}

/**
 *@brief音频恢复播放。
 *@param pObj：与当前设备实例相关的对象。
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_Resume(void)
{
  /*取消作业静音*/
  if (STA350BW_SetMute(STA350BW_CHANNEL_MASTER, STA350BW_DISABLE) != 0)
  {
    return STA350BW_ERROR;
  }
  return STA350BW_OK;
}

/**
 *@brief控制STA350BW的静音功能。
 *@param handle：与当前设备实例相关的对象。
 *@param channel：要静音的通道。
 *该参数可以是@ref STA350BW_channel_define的值
 *@param state: 启用禁用参数
 *该参数可以是@ref STA350BW_state_define的值
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_SetMute(uint8_t channel, uint8_t state)
{
  uint8_t tmp;

  if (STA350BW_ReadReg(STA350BW_MUTE, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  if (state == STA350BW_ENABLE)
  {
    tmp |= channel;
  }
  else
  {
    tmp &= ~channel;
  }

  if (STA350BW_WriteReg(STA350BW_MUTE, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  return STA350BW_OK;
}

/**
 *@brief控制STA350BW的音量功能。
 *@param handle：与当前设备实例相关的对象。
 *@param channel：要控制的通道。
 *该参数可以是@ref STA350BW_channel_define的值
 *@paramvolume：要设置的音量
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_SetVolume(uint32_t channel,
                           uint8_t Volume)
{
  /*
   * 音量映射: 手机/USB 音量 0~100 -> STA350BW MVOL 寄存器(每LSB -0.5dB, 0=0dB, 越大越衰减)
   *  - Volume == 0      : 写 0xFF, 真静音
   *  - Volume == 1..100 : 线性映射到衰减 -60dB ~ 0dB (寄存器 120 ~ 0)
   * 比原来的 (100-vol) 范围更宽(到-60dB)、低音量更柔和、最低档真静音、最大不限幅。
   */
  uint8_t tmp;
  if (Volume == 0)
  {
    tmp = 0xFF; /* mute */
  }
  else
  {
    if (Volume > 100)
    {
      Volume = 100;
    }
    /* reg = 120 * (100 - Volume) / 100, Volume=100->0(0dB), Volume=1->~119(-59.5dB) */
    tmp = (uint8_t)(120 * (100 - Volume) / 100);
  }
  LOGD("写入音量：vol=%d reg=%d", Volume, tmp);
  if (STA350BW_WriteReg(STA350BW_MVOL + channel, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  return STA350BW_OK;
}

/**
 *@brief 设置 STA350BW 的采样频率。
 *@param handle：与当前设备实例相关的对象。
 *@param AudioFreq：要设置的音频频率
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_SetFrequency(uint32_t AudioFreq)
{
  uint8_t tmp;

  if (STA350BW_ReadReg(STA350BW_CONF_REGA, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }

  tmp &= ~0x1F;

  if (AudioFreq == STA350BW_Fs_32000 || AudioFreq == STA350BW_Fs_44100 || AudioFreq == STA350BW_Fs_48000)
  {
    tmp |= STA350BW_MCLK_256_LR_48K;
  }
  else if (AudioFreq == STA350BW_Fs_88200 || AudioFreq == STA350BW_Fs_96000)
  {
    tmp |= STA350BW_MCLK_256_LR_96K;
  }
  else
  {
    return STA350BW_ERROR;
  }

  if (STA350BW_WriteReg(STA350BW_CONF_REGA, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  return STA350BW_OK;
}

/**
 *@brief停止音频。
 *@param handle：与当前设备实例相关的对象。
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_Stop(void)
{
  LOGE("Runing:%s Line:%d (未实现)", __FILE__, __LINE__);
  return STA350BW_NOT_IMPLEMENTED;
}

/**
 *@brief设置STA350BW双二阶部分的均衡参数。
 *@param handle：与当前设备实例相关的对象。
 *@param ramBlock：要设置的ram块
 *@param filterNumber: 过滤器编号
 *@param *filterValues：指向包含参数的uint32_t 内存的指针
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_SetEq(uint8_t ramBlock,
                       uint8_t filterNumber, uint32_t *filterValues)
{
  /*5 是由于 ram 寻址：第一个过滤器位于地址 0x00 到 0x04 上；第二个是在 0x05 到 0x09 上...*/
  if (writeRAMSet(ramBlock, filterNumber * 5, (uint8_t *)filterValues) != 0)
  {
    return STA350BW_ERROR;
  }
  return STA350BW_OK;
}

/**
 *@brief 重置设备。
 *@param pObj：与当前设备实例相关的对象。
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_Reset(void)
{
  LOGE("Runing:%s Line:%d (未实现)", __FILE__, __LINE__);
  return STA350BW_NOT_IMPLEMENTED;
}

/**
 *@brief 在 STA350BW 音调寄存器中设置音调值。
 *@param handle：与当前设备实例相关的对象。
 *@paramtoneGain：音调控制的增益
 *@param *p：指向可选附加函数的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_SetTone(uint8_t toneGain)
{
  uint8_t tmp = toneGain;

  if (STA350BW_WriteReg(STA350BW_TONE, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  return STA350BW_OK;
}

/**
 *@brief此功能可用于设置高级DSP选项，方便
 *使用STA350BW设备上的高级功能。
 *@param handle：与当前设备实例相关的对象。
 *@param option: 要设置的具体选项
 *该参数可以是@ref STA350BW_DSP_option_selection的值
 *@param state：要控制选项的状态。根据所选的
 *要控制的DSP功能，该值可以是ENABLE/DISABLE
 *或与特定DSP功能相关的特定数值参数。
 *该参数可以是@ref STA350BW_state_define的值
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_SetDSPOption(uint8_t option, uint8_t state)
{
  uint8_t tmp = 0;

  switch (option)
  {
  case STA350BW_DSPB:
  {
    if (STA350BW_ReadReg(STA350BW_CONF_REGD, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x04;
    tmp |= state << 0x02;

    if (STA350BW_WriteReg(STA350BW_CONF_REGD, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_HPB:
  {
    if (STA350BW_ReadReg(STA350BW_CONF_REGD, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x01;
    tmp |= state << 0x00;

    if (STA350BW_WriteReg(STA350BW_CONF_REGD, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_DEMP:
  {
    if (STA350BW_ReadReg(STA350BW_CONF_REGD, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x02;
    tmp |= state << 0x01;

    if (STA350BW_WriteReg(STA350BW_CONF_REGD, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_BQL:
  {
    if (STA350BW_ReadReg(STA350BW_CONF_REGD, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x08;
    tmp |= state << 0x04;

    if (STA350BW_WriteReg(STA350BW_CONF_REGD, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_BQ5:
  {
    if (STA350BW_ReadReg(STA350BW_CONFX, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x04;
    tmp |= state << 0x02;

    if (STA350BW_WriteReg(STA350BW_CONFX, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_BQ6:
  {
    if (STA350BW_ReadReg(STA350BW_CONFX, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x02;
    tmp |= state << 0x01;

    if (STA350BW_WriteReg(STA350BW_CONFX, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_BQ7:
  {
    if (STA350BW_ReadReg(STA350BW_CONFX, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x01;
    tmp |= state << 0x00;

    if (STA350BW_WriteReg(STA350BW_CONFX, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_C1EQBP:
  {
    if (STA350BW_ReadReg(STA350BW_C1CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x02;
    tmp |= state << 0x01;

    if (STA350BW_WriteReg(STA350BW_C1CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_C2EQBP:
  {
    if (STA350BW_ReadReg(STA350BW_C2CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x02;
    tmp |= state << 0x01;

    if (STA350BW_WriteReg(STA350BW_C2CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_C1TCB:
  {
    if (STA350BW_ReadReg(STA350BW_C1CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x01;
    tmp |= state << 0x00;

    if (STA350BW_WriteReg(STA350BW_C1CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_C2TCB:
  {
    if (STA350BW_ReadReg(STA350BW_C2CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x01;
    tmp |= state << 0x00;

    if (STA350BW_WriteReg(STA350BW_C2CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_C1VBP:
  {
    if (STA350BW_ReadReg(STA350BW_C1CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x04;
    tmp |= state << 0x02;

    if (STA350BW_WriteReg(STA350BW_C1CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_C2VBP:
  {
    if (STA350BW_ReadReg(STA350BW_C2CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x04;
    tmp |= state << 0x02;

    if (STA350BW_WriteReg(STA350BW_C2CFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_EXT_RANGE_BQ1:
  {
    if (STA350BW_ReadReg(STA350BW_CXT_B4B1, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x03;
    tmp |= (state >> 1);

    if (STA350BW_WriteReg(STA350BW_CXT_B4B1, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_EXT_RANGE_BQ2:
  {
    if (STA350BW_ReadReg(STA350BW_CXT_B4B1, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x0C;
    tmp |= (state >> 1) << 2;

    if (STA350BW_WriteReg(STA350BW_CXT_B4B1, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_EXT_RANGE_BQ3:
  {
    if (STA350BW_ReadReg(STA350BW_CXT_B4B1, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x30;
    tmp |= (state >> 1) << 4;

    if (STA350BW_WriteReg(STA350BW_CXT_B4B1, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_EXT_RANGE_BQ4:
  {
    if (STA350BW_ReadReg(STA350BW_CXT_B4B1, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0xC0;
    tmp |= (state >> 1) << 6;

    if (STA350BW_WriteReg(STA350BW_CXT_B4B1, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_EXT_RANGE_BQ5:
  {
    if (STA350BW_ReadReg(STA350BW_CXT_B7B5, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x03;
    tmp |= (state >> 1);

    if (STA350BW_WriteReg(STA350BW_CXT_B7B5, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_EXT_RANGE_BQ6:
  {
    if (STA350BW_ReadReg(STA350BW_CXT_B7B5, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x0C;
    tmp |= (state >> 1) << 2;

    if (STA350BW_WriteReg(STA350BW_CXT_B7B5, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_EXT_RANGE_BQ7:
  {
    if (STA350BW_ReadReg(STA350BW_CXT_B7B5, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x30;
    tmp |= (state >> 1) << 4;

    if (STA350BW_WriteReg(STA350BW_CXT_B7B5, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  case STA350BW_RAM_BANK_SELECT:
  {
    if (STA350BW_ReadReg(STA350BW_EQCFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    tmp &= ~0x03;
    tmp |= state;

    if (STA350BW_WriteReg(STA350BW_EQCFG, 1, &tmp) != 0)
    {
      return STA350BW_ERROR;
    }
    break;
  }
  }
  return STA350BW_OK;
}

/**
 *@brief用于写入RAM集的初始化函数。
 *@param handle：与当前设备实例相关的对象。
 *@param RAM_block：要写入的RAM块。
 *@param RAM_address：要写入的RAM地址。
 *@param *pIn：指向要读取的所需值的指针。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
static int32_t writeRAMSet(uint8_t RAM_block,
                           uint8_t RAM_address, uint8_t *pIn)
{
  uint8_t tmp = 0x00;
  /*选择区块*/
  if (STA350BW_ReadReg(STA350BW_EQCFG, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  tmp &= ~0x03;
  RAM_block &= 0x03;
  tmp |= RAM_block;
  if (STA350BW_WriteReg(STA350BW_EQCFG, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  /*设置地址*/
  if (STA350BW_ReadReg(STA350BW_CFADDR, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  tmp &= ~0x3F;
  RAM_address &= 0x3F;
  tmp |= RAM_address;
  if (STA350BW_WriteReg(STA350BW_CFADDR, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  /*写*/
  if (STA350BW_WriteReg(STA350BW_B1CF1, 1, &pIn[2]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_B1CF2, 1, &pIn[1]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_B1CF3, 1, &pIn[0]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_B2CF1, 1, &pIn[6]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_B2CF2, 1, &pIn[5]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_B2CF3, 1, &pIn[4]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_A1CF1, 1, &pIn[10]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_A1CF2, 1, &pIn[9]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_A1CF3, 1, &pIn[8]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_A2CF1, 1, &pIn[14]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_A2CF2, 1, &pIn[13]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_A2CF3, 1, &pIn[12]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_B0CF1, 1, &pIn[18]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_B0CF2, 1, &pIn[17]) != 0)
  {
    return STA350BW_ERROR;
  }
  if (STA350BW_WriteReg(STA350BW_B0CF3, 1, &pIn[16]) != 0)
  {
    return STA350BW_ERROR;
  }
  /*设置WA PIN*/
  if (STA350BW_ReadReg(STA350BW_CFUD, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  tmp &= ~0x02;
  tmp = 0x02;

  if (STA350BW_WriteReg(STA350BW_CFUD, 1, &tmp) != 0)
  {
    return STA350BW_ERROR;
  }
  return STA350BW_OK;
}

/**
 *@brief 用于演示目的的开关过滤器配置。
 *@参数无
 *@retval 如果初始化过程中没有问题则为 AUDIO_OK，否则为 AUDIO_ERROR
 */
uint32_t Switch_Demo(enum BiquadType current_demo)
{
  BIQUAD_Filter_t Biquad_filter;
  uint8_t ret = 0;

  switch (current_demo)
  {
  case BIQUAD_TYPE_CLEAR:
  {

    /*使用每个通道的第一个 biq 滤波器设置 Fc = 1 KHz 的二阶高通。系数存储在 BANK 1 中*/
    /*当系数写入RAM时，EQ自动激活
    可以使用 SetDSPOptions 和 STA350BW_RAM_BANK_SELECT 在不同的预存储预设之间切换 RAM 组
    参数，例如：
    STA350BW_SetDSPOption( STA350BW_RAM_BANK_SELECT,STA350BW_RAM_BANK_FIRST);*/

    Biquad_filter.Type = BIQUAD_CALCULATOR_SO_HPF;
    Biquad_filter.Fs = STA350BW_Fs_44100;
    Biquad_filter.Fc = 1000;
    Biquad_filter.Q = 0.80;
    Biquad_filter.Slope = 0; /*不用于此类过滤器*/
    Biquad_filter.Gain = 0;  /*不用于此类过滤器*/
    BQ_CALC_ComputeFilter(&Biquad_filter);
    STA350BW_SetEq(STA350BW_RAM_BANK_FIRST, STA350BW_CH1_BQ1,
                   Biquad_filter.Coefficients);
    STA350BW_SetEq(STA350BW_RAM_BANK_FIRST, STA350BW_CH2_BQ1,
                   Biquad_filter.Coefficients);

    /*删除 EQ 和音调旁路（以防在演示过程中更改）*/
    STA350BW_SetDSPOption(STA350BW_C1EQBP, STA350BW_DISABLE);
    STA350BW_SetDSPOption(STA350BW_C2EQBP, STA350BW_DISABLE);
    STA350BW_SetDSPOption(STA350BW_C1TCB, STA350BW_DISABLE);
    STA350BW_SetDSPOption(STA350BW_C2TCB, STA350BW_DISABLE);

    break;
  }
  case BIQUAD_TYPE_FLAT:
  {
    /*为每个通道使用 4 个双二阶设置 平坦 预设。系数存储在 BANK 2 中*/
    /*当系数写入RAM时，EQ自动激活
    可以使用 SetDSPOptions 和 STA350BW_RAM_BANK_SELECT 在不同的预存储预设之间切换 RAM 组
    参数，例如：
    STA350BW_SetDSPOption( STA350BW_RAM_BANK_SELECT,STA350BW_RAM_BANK_FIRST);*/

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&FLAT_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&FLAT_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&FLAT_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&FLAT_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&FLAT_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&FLAT_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&FLAT_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&FLAT_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_ROCK:
  {
    /*为每个通道使用 4 个双二阶设置摇滚 预设。系数存储在 BANK 2 中*/

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&ROCK_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&ROCK_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&ROCK_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&ROCK_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&ROCK_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&ROCK_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&ROCK_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&ROCK_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_SOFT:
  {

    /*为每个通道使用 4 个双二阶设置 软 预设。系数存储在 BANK 2 中*/

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&SOFT_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&SOFT_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&SOFT_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&SOFT_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&SOFT_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&SOFT_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&SOFT_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&SOFT_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_JAZZ:
  {
    /*为每个通道使用 4 个双二阶设置 爵士 预设。系数存储在 BANK 2 中*/

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&JAZZ_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&JAZZ_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&JAZZ_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&JAZZ_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&JAZZ_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&JAZZ_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&JAZZ_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&JAZZ_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_CLASSICAL:
  {
    /*为每个通道使用 4 个双二阶设置 古典 预设。系数存储在 BANK 2 中*/

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&CLASSICAL_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&CLASSICAL_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&CLASSICAL_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&CLASSICAL_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&CLASSICAL_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&CLASSICAL_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&CLASSICAL_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&CLASSICAL_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_DANCE:
  {
    /*为每个通道使用 4 个双二阶设置 舞蹈 预设。系数存储在 BANK 2 中*/

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&DANCE_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&DANCE_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&DANCE_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&DANCE_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&DANCE_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&DANCE_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&DANCE_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&DANCE_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_POP:
  {
    /*为每个通道使用 4 个双二阶设置 爵士 预设。系数存储在 BANK 2 中*/

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&POP_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&POP_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&POP_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&POP_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&POP_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&POP_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&POP_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&POP_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_SOFT_ROCK:
  {
    /*为每个通道使用 4 个双二阶设置 软爵士 预设。系数存储在 BANK 2 中*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&SOFT_ROCK_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&SOFT_ROCK_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&SOFT_ROCK_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&SOFT_ROCK_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&SOFT_ROCK_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&SOFT_ROCK_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&SOFT_ROCK_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&SOFT_ROCK_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_HARD:
  {
    /*为每个通道使用 4 个双二阶设置 硬 预设。系数存储在 BANK 2 中*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&HARD_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&HARD_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&HARD_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&HARD_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&HARD_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&HARD_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&HARD_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&HARD_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_PARTY:
  {
    /*为每个通道使用 4 个双二阶设置 派对 预设。系数存储在 BANK 2 中*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&PARTY_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&PARTY_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&PARTY_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&PARTY_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&PARTY_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&PARTY_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&PARTY_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&PARTY_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_VOCAL:
  {
    /*为每个通道使用 4 个双二阶设置 声音 预设。系数存储在 BANK 2 中*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&VOCAL_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&VOCAL_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&VOCAL_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&VOCAL_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&VOCAL_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&VOCAL_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&VOCAL_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&VOCAL_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_HIPHOP:
  {
    /*为每个通道使用 4 个双二阶设置 嘻哈 预设。系数存储在 BANK 2 中*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&HIPHOP_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&HIPHOP_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&HIPHOP_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&HIPHOP_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&HIPHOP_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&HIPHOP_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&HIPHOP_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&HIPHOP_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_DIALOG:
  {
    /*为每个通道使用 4 个双二阶设置 对话 预设。系数存储在 BANK 2 中*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&DIALOG_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&DIALOG_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&DIALOG_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&DIALOG_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&DIALOG_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&DIALOG_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&DIALOG_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&DIALOG_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_BASS_BOOST1:
  {
    /*为每个通道使用 4 个双二阶设置 低音增强1 预设。系数存储在 BANK 2 中*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&BASS_BOOST1_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&BASS_BOOST1_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&BASS_BOOST1_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&BASS_BOOST1_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&BASS_BOOST1_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&BASS_BOOST1_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&BASS_BOOST1_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&BASS_BOOST1_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_BASS_BOOST2:
  {
    /*为每个通道使用 4 个双二阶设置 低音增强2 预设。系数存储在 BANK 2 中*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&BASS_BOOST2_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&BASS_BOOST2_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&BASS_BOOST2_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&BASS_BOOST2_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&BASS_BOOST2_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&BASS_BOOST2_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&BASS_BOOST2_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&BASS_BOOST2_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_BASS_BOOST3:
  {
    /*为每个通道使用 4 个双二阶设置 低音增强3 预设。系数存储在 BANK 2 中*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&BASS_BOOST3_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&BASS_BOOST3_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&BASS_BOOST3_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&BASS_BOOST3_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&BASS_BOOST3_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&BASS_BOOST3_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&BASS_BOOST3_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&BASS_BOOST3_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_BYPASS_BIQ:
  {
    /*绕过两个通道的 BIQ 过滤器*/
    STA350BW_SetDSPOption(STA350BW_C1EQBP, STA350BW_ENABLE);
    STA350BW_SetDSPOption(STA350BW_C2EQBP, STA350BW_ENABLE);

    /*更改音调设置*/
    STA350BW_SetTone(0xF0);

    break;
  }
  case BIQUAD_TYPE_BYPASS_TONE:
  {
    /*旁路两个通道的音调控制*/
    STA350BW_SetDSPOption(STA350BW_C1TCB, STA350BW_ENABLE);
    STA350BW_SetDSPOption(STA350BW_C2TCB, STA350BW_ENABLE);
    break;
  }
  case BIQUAD_TYPE_USER_1:
  {
    /*用户自定义设置1*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&USER_1_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&USER_1_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&USER_1_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&USER_1_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&USER_1_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&USER_1_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&USER_1_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&USER_1_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_USER_2:
  {
    /*用户自定义设置2*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&USER_2_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&USER_2_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&USER_2_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&USER_2_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&USER_2_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&USER_2_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&USER_2_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&USER_2_EQ_PRESET[15]);
    break;
  }
  case BIQUAD_TYPE_USER_3:
  {
    /*用户自定义设置3*/
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&USER_3_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&USER_3_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&USER_3_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&USER_3_EQ_PRESET[15]);

    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&USER_3_EQ_PRESET[0]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&USER_3_EQ_PRESET[5]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&USER_3_EQ_PRESET[10]);
    ret = STA350BW_SetEq(STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&USER_3_EQ_PRESET[15]);
    break;
  }
  }
  return ret;
}

/**
 *@brief 通用阅读功能。它必须由 I2C 填充
 *或SPI写入功能。
 *@param RegAddr 注册的地址。
 *@param NumByteToRead 要读取的大小。
 *@param *数据坐标将填充读取数据。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_ReadReg(uint8_t RegAddr, uint16_t NumByteToRead, uint8_t *Data)
{
  int32_t ret;
  ret = ctx.read_reg(ctx.i2c_address, RegAddr, Data, NumByteToRead);
  return ret;
}

/**
 *@brief 通用编程功能。它必须由 I2C 填充
 *或SPI写入功能。
 *@param RegAddr 注册的地址。
 *@param NumByteToWrite 要读取的大小。
 *@param *要写入的数据流程图。
 *如果设置正确则@retval STA350BW_OK，否则为STA350BW_ERROR
 */
int32_t STA350BW_WriteReg(uint8_t RegAddr, uint16_t NumByteToWrite, uint8_t *Data)
{
  int32_t ret;
  ret = ctx.write_reg(ctx.i2c_address, RegAddr, Data, NumByteToWrite);
  return ret;
}

/**
 *@}
 */
/**
 *@}
 */
/**
 *@}
 */
/**
//0
Speaker_EQ_Table_1_48000[] = {
	0x80475D,0x7F7155,0x7FB8A3,0x808EAB,0x400000    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.9995)
};

//1
Speaker_EQ_Table_2_48000[] = {
	0x80475D,0x7F68A1,0x7FB8A3,0x808EAB,0x40045A    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.9995)
};

//2
Speaker_EQ_Table_3_48000[] = {
	0x80475D,0x7F5EDD,0x7FB8A3,0x808EAB,0x40093C    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.9995)
};

//3
Speaker_EQ_Table_4_48000[] = {
	0x80475D,0x7F53E8,0x7FB8A3,0x808EAB,0x400EB6    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.9995)
};

//3.5
Speaker_EQ_Table_5_48000[] = {
	0x80475D,0x7F4DEF,0x7FB8A3,0x808EAB,0x4011B2    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.9995)
};

//4
Speaker_EQ_Table_6_48000[] = {
	0x80475D,0x7F479C,0x7FB8A3,0x808EAB,0x4014DC    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.9995)
};

//-1
Speaker_EQ_Table_48000[] = {
	0x80500C,0x7F68AB,0x7FAFF4,0x80A009,0x3FFBA6    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.9996)
};

//-2
Speaker_EQ_Table_48000[] = {
	0x8059C8,0x7F5EF4,0x7FA638,0x80B382,0x3FF6C5    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.9997)
};

输入内容有：{0.00,20.00,0.30} ,{1.00,20.00,0.30},{2.00,20.00,0.30},{3.00,20.00,0.30},{3.50,20.00,0.30},{4.00,20.00,0.30},{-1.00,20.00,0.30},{-2.00,20.00,0.30}
得到的输出内容是:
输入：{0.00,20.00,0.30} 得到： Table_1_48000[] = {0x80475D,0x7F7155,0x7FB8A3,0x808EAB,0x400000};
输入：{1.00,20.00,0.30} 得到： Table_2_48000[] = {0x80475D,0x7F68A1,0x7FB8A3,0x808EAB,0x40045A};
输入：{2.00,20.00,0.30} 得到： Table_3_48000[] = {0x80475D,0x7F5EDD,0x7FB8A3,0x808EAB,0x40093C};
输入：{3.00,20.00,0.30} 得到： Table_4_48000[] = {0x80475D,0x7F53E8,0x7FB8A3,0x808EAB,0x400EB6};
输入：{3.50,20.00,0.30} 得到： Table_5_48000[] = {0x80475D,0x7F4DEF,0x7FB8A3,0x808EAB,0x4011B2};
输入：{4.00,20.00,0.30} 得到： Table_6_48000[] = {0x80475D,0x7F479C,0x7FB8A3,0x808EAB,0x4014DC};
输入：{-1.00,20.00,0.30} 得到： Table_48000[] = {0x80500C,0x7F68AB,0x7FAFF4,0x80A009,0x3FFBA6};
输入：{-2.00,20.00,0.30} 得到： Table_48000[] = {0x8059C8,0x7F5EF4,0x7FA638,0x80B382,0x3FF6C5};

请找出规律，并写出转换代码。


Speaker_EQ_Table_3_48000[] = {0x80475D,0x7F5EDD,0x7FB8A3,0x808EAB,0x40093C};
Speaker_EQ_Table_4_48000[] = {0x80475D,0x7F53E8,0x7FB8A3,0x808EAB,0x400EB6};
Speaker_EQ_Table_5_48000[] = {0x80475D,0x7F4DEF,0x7FB8A3,0x808EAB,0x4011B2};
Speaker_EQ_Table_6_48000[] = {0x80475D,0x7F479C,0x7FB8A3,0x808EAB,0x4014DC};

请找出规律


 */
/***********************(C) 版权所有意法半导体 *****文件结束****/

