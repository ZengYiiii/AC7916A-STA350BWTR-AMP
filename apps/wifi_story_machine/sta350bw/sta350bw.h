/**
********************************************************************************
*@文件sta350bw.h
*@author SRA -中央实验室
*@版本v3.0.0
*@日期 2019 年 5 月 6 日
*@brief 该文件包含 sta350bw.c 的定义
*固件驱动程序。
********************************************************************************
*@注意力
*
*<h2><center>© COPYRIGHT(c) 2019 意法半导体</center></h2>
*
*以源代码和二进制形式重新分发和使用，无论是否经过修改，
*是允许的，前提是满足以下条件：
*1. 源代码的再分发必须保留上述版权声明，
*此条件列表和以下免责声明。
*2. 以二进制形式重新分发必须复制上述版权声明，
*文档中的条件列表和以下免责声明
*和/或随分发一起提供的其他材料。
*3. 既不是意法半导体的名称，也不是其贡献者的姓名
*可用于认可或推广从此软件衍生的产品
*未经事先书面许可。
*
*本软件由版权所有者和贡献者“按原样”提供
*以及任何明示或暗示的保证，包括但不限于
*对适销性和特定用途适用性的默示保证是
*免责声明。在任何情况下，版权所有者或贡献者均不承担任何责任
*对于任何直接、间接、偶然、特殊、示范性或后果性的
*损害（包括但不限于采购替代品或
*服务;使用、数据或利润的损失；或业务中断）但是
*造成的和基于任何责任理论，无论是合同责任、严格责任，
*或因使用而产生的任何侵权行为（包括疏忽或其他原因）
*本软件，即使已被告知可能发生此类损坏。
*
********************************************************************************
*/
/*定义防止递归包含------------------------------------*/
#ifndef STA350BW_H
#define STA350BW_H

#ifdef __cplusplus
extern "C"
{
#endif

/*包括 -----------------------------------------------------------------------------*/
#include <stdint.h>
#include "debug.h"
#include "user_app.h"

#include "BiquadCalculator.h"
#include "BiquadPresets.h"

/*导出类型 ------------------------------------------------------------------------*/
/**@addtogroup BSP
*@{
*/
/**@addtogroup 组件
*@{
*/
/**@addtogroup STA350BW
*@{
*/
/**@defgroup STA350BW_Exported_Types STA350BW 导出类型
*@{
*/
/**@defgroup STA350BW_adsress_define STA350BW 地址定义
*@brief STA350BW 地址定义
*@{
*/
//TODO：STA350BW 器件有两个可能的地址：0x38 和 0x3A。 Dnt（地址 << 1）
#define STA350BW_ADDRESS_1 ((uint8_t)0x38)
#define STA350BW_ADDRESS_2 ((uint8_t)0x3A)
  /**
*@}
*/

  typedef enum
  {
    STA350BW_OK = (uint8_t)0,
    STA350BW_ERROR = 1,
    STA350BW_NOT_IMPLEMENTED = 2
  } STA350BW_Error_et;

  typedef int32_t (*STA350BW_write_ptr)(uint8_t, uint8_t, uint8_t *, uint8_t);
  typedef int32_t (*STA350BW_read_ptr)(uint8_t, uint8_t, uint8_t *, uint8_t);

  typedef struct
  {
    /**组件必填字段**/
    STA350BW_write_ptr write_reg;
    STA350BW_read_ptr read_reg;
    uint8_t i2c_address;
    uint8_t initialized;
  } STA350BW_ctx_t;

  /**
*@}
*/
  /**@defgroup STA350BW_Exported_Constants
*@{
*/
  /**@defgroup STA350BW_Registers_Mapping
*@brief STA350BW 寄存器映射
*@{
*/

#define STA350BW_MAX_REGISTERS ((uint8_t)0x56)

/**
*@brief 配置寄存器A
*\代码
*读/写
*默认值：0x63
*7 FAULT检测恢复旁路
*6 TWAB 热警告可调旁路
*5 TWRB 热警告恢复旁路
*4,3 IR插值比
*[2:0] MCS 主时钟选择
*\结束码
*/
#define STA350BW_CONF_REGA ((uint8_t)0x00)/*配置寄存器A*/

/**
*@brief 配置寄存器B
*\代码
*读/写
*默认值：0x80
*7 C2IM通道2输入映射
*6个C2IM通道1输入映射
*5 DSCKE 延迟串行时钟使能
*4 SAIFB 串行数据第一位
*[3:0]串行输入接口格式
*\结束码
*/
#define STA350BW_CONF_REGB ((uint8_t)0x01)/*配置寄存器B*/

/**
*@brief 配置寄存器C
*\代码
*读/写
*默认值：0x09F
*7 OCRB 过流警告调节旁路
*[5:2] CSZx：FFX 补偿脉冲大小
*[1:0] OMx：FFX 输出模式
*0 Clk_Out：在 MCO 上启用 HSE。 0：MCO 禁用。 1：MCO使能
*\结束码
*/
#define STA350BW_CONF_REGC ((uint8_t)0x02)/*配置寄存器C*/

/**
*@brief I2C地址配置寄存器D
*\代码
*读/写
*默认值：0x40
*7 SME软静音使能
*6 ZDE 零检测使能
*5 DRC DRC或抗削波模式
*4 BQL 双二阶链接
*3 PSL 后比例链接
*2个DSPB DSP旁路
*1 个 DEMP 去加重滤波器
*0 HPB 高通滤波器旁路
*\结束码
*/
#define STA350BW_CONF_REGD ((uint8_t)0x03)/*配置寄存器D*/

/**
*@brief I2C地址配置寄存器E
*\代码
*读/写
*默认值：0xC2
*7 SVE 软音量启用
*6 ZCE 过零使能
*5 DCCV可变失真补偿
*4个PWMS PWM速度
*3 AME AM降噪使能
*2 NSBW 噪声整形器带宽
*1 MPC 最大功率校正
*0 MPCV 可变轴功率校正
*\结束码
*/
#define STA350BW_CONF_REGE ((uint8_t)0x04)/*配置寄存器E*/

/**
*@brief I2C地址配置寄存器F
*\代码
*读/写
*默认值：0x5C
*7 EAPD 外部放大器断电
*6 PWDN设备掉电
*5 ECLE Auto EAPD 时钟丢失
*4路LDTE LRCK双触发保护
*3 BCLE 二进制输出模式时钟丢失检测
*2 IDE 无效输入检测
*1,0 OCFG 输出配置
*\结束码
*/
#define STA350BW_CONF_REGF ((uint8_t)0x05)/*配置寄存器F*/

/**
*@brief I2C 地址静音/线路输出配置
*\代码
*读/写
*默认值：0x10
*[7:6] LOC线路输出配置
*[5:4] 保留
*3 C3M 通道 3 静音
*2 C2M 通道 2 静音
*1 C1M 通道 1 静音
*0 MMUTE 主静音
*\结束码
*/
#define STA350BW_MUTE ((uint8_t)0x06)/*静音/线路输出配置*/

/**
*@brief I2C地址主卷
*\代码
*读/写
*默认值：0xFF
*[7:0]主音量（默认-127.5dB）
*\结束码
*/
#define STA350BW_MVOL ((uint8_t)0x07)/*主音量*/

/**
*@brief I2C 地址通道 1 音量
*\代码
*读/写
*默认值：0x60
*[7:0]主音量（默认0.0dB）
*\结束码
*/
#define STA350BW_C1VOL ((uint8_t)0x08)/*通道1音量*/

/**
*@brief I2C 地址通道 2 音量
*\代码
*读/写
*默认值：0x60
*[7:0]主音量（默认0.0dB）
*\结束码
*/
#define STA350BW_C2VOL ((uint8_t)0x09)/*通道2音量*/

/**
*@brief I2C 地址通道 3 音量
*\代码
*读/写
*默认值：0x60
*[7:0]主音量（默认0.0dB）
*\结束码
*/
#define STA350BW_C3VOL ((uint8_t)0x0A)/*通道3音量*/

/**
*@brief I2C 地址自动模式 1
*\代码
*读/写
*默认值：0x80
*[7:6] 保留
*[5:4] AMGC 音频预设增益压缩
*[3:0] 保留
*\结束码
*/
#define STA350BW_AUTO1 ((uint8_t)0x0B)/*音频预设1寄存器*/

/**
*@brief I2C 地址自动模式 2
*\代码
*读/写
*默认值：0x00
*[7:4] XO 预设分频滤波器
*[3:1] AMAMx AM 原子模式设置
*0 AMAME AM 自动模式启用
*\结束码
*/
#define STA350BW_AUTO2 ((uint8_t)0x0C)/*音频预设2寄存器*/

/**
*@brief I2C地址通道1配置寄存器
*\代码
*读/写
*默认值：0x00
*7,6 C1OM 通道 1 输出映射
*5,4 C1LS 通道 1 限制器映射
*3 C1BO 通道1 二进制输出
*2 C1VPB 通道 1 音量旁路
*1 C1EQBP 通道 1 均衡旁路
*0 C1TCB 通道 1 音调/控制旁路
*\结束码
*/
#define STA350BW_C1CFG ((uint8_t)0x0E)/*通道1配置寄存器*/

/**
*@brief I2C 地址通道 2 配置寄存器
*\代码
*读/写
*默认值：0x40
*7,6 C2OM 通道 2 输出映射
*5,4 C2LS 通道 2 限制器映射
*3 C2BO 通道 2 二进制输出
*2 C2VPB 通道 2 音量旁路
*1 个 C2EQBP 通道 2 均衡旁路
*0 C2TCB 通道 2 音调/控制旁路
*\结束码
*/
#define STA350BW_C2CFG ((uint8_t)0x0F)/*通道2配置寄存器*/

/**
*@brief I2C 地址通道 3 配置寄存器
*\代码
*读/写
*默认值：0x80
*7,6 C2OM 通道 3 输出映射
*5,4 C2LS 通道 3 限制器映射
*3 C2BO 通道 3 二进制输出
*2 C2VPB 通道 3 音量旁路
*1,0 保留
*\结束码
*/
#define STA350BW_C3CFG ((uint8_t)0x10)/*通道3配置寄存器*/

/**
*@brief I2C 地址音控制寄存器
*\代码
*读/写
*默认值：0x77
*[7:4] 高音
*[3:0] 低音
*\结束码
*/
#define STA350BW_TONE ((uint8_t)0x11)/*音调控制寄存器*/

/**
*@brief I2C 地址限制器 1 启动/释放速率寄存器
*\代码
*读/写
*默认值：0x6A
*[7:4] 限制器 1 攻击率
*[3:0] 限制器 1 释放速率
*\结束码
*/
#define STA350BW_L1AR ((uint8_t)0x12)/*限制器 1 起音/释放速率寄存器*/

/**
*@brief I2C 地址限制器 1 攻击/释放阈值寄存器
*\代码
*读/写
*默认值：0x69
*[7:4] 限制器 1 攻击阈值
*[3:0] 限制器 1 释放阈值
*\结束码
*/
#define STA350BW_L1ATR ((uint8_t)0x13)/*限制器 1 启动/释放阈值寄存器*/

/**
*@brief I2C 地址限制器 2 启动/释放速率寄存器
*\代码
*读/写
*默认值：0x6A
*[7:4] 限制器 2 攻击率
*[3:0] 限制器 2 释放速率
*\结束码
*/
#define STA350BW_L2AR ((uint8_t)0x14)/*限制器 2 起音/释放速率寄存器*/

/**
*@brief I2C 地址限制器 2 攻击/释放阈值寄存器
*\代码
*读/写
*默认值：0x69
*[7:4] 限制器 2 攻击阈值
*[3:0] 限制器 2 释放阈值
*\结束码
*/
#define STA350BW_L2ATR ((uint8_t)0x15)/*限制器 2 启动/释放阈值寄存器*/

/*内存下载*/
/**
*@brief I2C地址系数地址寄存器
*\代码
*读/写
*默认值：0x00
*[7:6] 保留
*[5:0] RAM地址
*\结束码
*/
#define STA350BW_CFADDR ((uint8_t)0x16)/*系数地址寄存器*/

/**
*@brief I2C 地址系数 b1 数据寄存器位 23:16
*\代码
*读/写
*默认值：0x00
*[7:0]系数b1位23:16
*\结束码
*/
#define STA350BW_B1CF1 ((uint8_t)0x17)/*系数 b1 数据寄存器位 23:16*/

/**
*@brief I2C 地址系数 b1 数据寄存器位 15:8
*\代码
*读/写
*默认值：0x00
*[7:0]系数b1位15:8
*\结束码
*/
#define STA350BW_B1CF2 ((uint8_t)0x18)/*系数 b1 数据寄存器位 15:8*/

/**
*@brief I2C 地址系数 b1 数据寄存器位 7:0
*\代码
*读/写
*默认值：0x00
*[7:0]系数b1位7:0
*\结束码
*/
#define STA350BW_B1CF3 ((uint8_t)0x19)/*系数 b1 数据寄存器位 7:0*/

/**
*@brief I2C 地址系数 b2 数据寄存器位 23:16
*\代码
*读/写
*默认值：0x00
*[7:0]系数b2位23:16
*\结束码
*/
#define STA350BW_B2CF1 ((uint8_t)0x1A)/*系数 b2 数据寄存器位 23:16*/

/**
*@brief I2C 地址系数 b2 数据寄存器位 15:8
*\代码
*读/写
*默认值：0x00
*[7:0]系数b2位15:8
*\结束码
*/
#define STA350BW_B2CF2 ((uint8_t)0x1B)/*系数 b2 数据寄存器位 15:8*/

/**
*@brief I2C 地址系数 b2 数据寄存器位 7:0
*\代码
*读/写
*默认值：0x00
*[7:0] 系数b2数据位7:0
*\结束码
*/
#define STA350BW_B2CF3 ((uint8_t)0x1C)/*系数 b2 数据寄存器位 7:0*/

/**
*@brief I2C 地址系数 a1 数据寄存器位 23:16
*\代码
*读/写
*默认值：0x00
*[7:0] 系数a1数据位23:16
*\结束码
*/
#define STA350BW_A1CF1 ((uint8_t)0x1D)/*系数a1数据寄存器位23:16*/

/**
*@brief I2C 地址系数 a1 数据寄存器位 15:8
*\代码
*读/写
*默认值：0x00
*[7:0] 系数a1数据位15:8
*\结束码
*/
#define STA350BW_A1CF2 ((uint8_t)0x1E)/*系数a1数据寄存器位15:8*/

/**
*@brief I2C 地址系数 a1 数据寄存器位 7:0
*\代码
*读/写
*默认值：0x00
*[7:0] 系数a1数据位7:0
*\结束码
*/
#define STA350BW_A1CF3 ((uint8_t)0x1F)/*系数a1数据寄存器位7:0*/

/**
*@brief I2C 地址系数 a2 数据寄存器位 23:16
*\代码
*读/写
*默认值：0x00
*[7:0] 系数a2数据位23:16
*\结束码
*/
#define STA350BW_A2CF1 ((uint8_t)0x20)/*系数a2数据寄存器位23:16*/

/**
*@brief I2C 地址系数 a2 数据寄存器位 15:8
*\代码
*读/写
*默认值：0x00
*[7:0] 系数a2数据位15:8
*\结束码
*/
#define STA350BW_A2CF2 ((uint8_t)0x21)/*系数a2数据寄存器位15:8*/

/**
*@brief I2C 地址系数 a2 数据寄存器位 7:0
*\代码
*读/写
*默认值：0x00
*[7:0] 系数a2数据位7:0
*\结束码
*/
#define STA350BW_A2CF3 ((uint8_t)0x22)/*系数a2数据寄存器位7:0*/

/**
*@brief I2C 地址系数 b0 数据寄存器位 23:16
*\代码
*读/写
*默认值：0x00
*[7:0]系数b0位23:16
*\结束码
*/
#define STA350BW_B0CF1 ((uint8_t)0x23)/*系数 b0 数据寄存器位 23:16*/

/**
*@brief I2C 地址系数 b0 数据寄存器位 15:8
*\代码
*读/写
*默认值：0x00
*[7:0] 系数 b0 数据位 15:8
*\结束码
*/
#define STA350BW_B0CF2 ((uint8_t)0x24)/*系数 b0 数据寄存器位 15:8*/

/**
*@brief I2C 地址系数 b0 数据寄存器位 7:0
*\代码
*读/写
*默认值：0x00
*[7:0] 系数 b0 数据位 7:0
*\结束码
*/
#define STA350BW_B0CF3 ((uint8_t)0x25)/*系数 b0 数据寄存器位 7:0*/

/**
*@brief I2C地址系数写/读控制寄存器
*\代码
*读/写
*默认值：0x00
*[7:4] 保留
*3 RA读取全套系数
*2 R1 只读一个系数
*1 WA写出一套完整的系数
*0 W1 只写入一个系数
*\结束码
*/
#define STA350BW_CFUD ((uint8_t)0x26)/*系数写/读控制寄存器*/

/**
*@brief I2C 地址可变最大功率校正 15:8
*\代码
*读/写
*默认值：0x1A
*[7:0] 可变最大功率校正系数 15:8
*\结束码
*/
#define STA350BW_MPCC1 ((uint8_t)0x27)/*可变最大功率校正15:8寄存器*/

/**
*@brief I2C 地址可变最大功率校正 7:0
*\代码
*读/写
*默认值：0x30
*[7:0] 可变最大功率校正系数 7:0
*\结束码
*/
#define STA350BW_MPCC2 ((uint8_t)0x28)/*可变最大功率校正7:0寄存器*/

/**
*@brief I2C 地址 可变失真补偿 15:8
*\代码
*读/写
*默认值：0xF3
*[7:0] 可变失真补偿系数 15:8
*\结束码
*/
#define STA350BW_DCC1 ((uint8_t)0x29)/*可变失真补偿 15:8*/

/**
*@brief I2C 地址 可变失真补偿 7:0
*\代码
*读/写
*默认值：0x33
*[7:0] 可变失真补偿系数 7:0
*\结束码
*/
#define STA350BW_DCC2 ((uint8_t)0x2A)/*可变失真补偿 7:0*/

/**
*@brief I2C 地址故障检测恢复常量寄存器 15:8
*\代码
*读/写
*默认值：0x00
*[7:0] 故障检测恢复常数 15:8
*\结束码
*/
#define STA350BW_FDRC1 ((uint8_t)0x2B)/*故障检测恢复常量寄存器 15:8*/

/**
*@brief I2C 地址故障检测恢复常量寄存器 7:0
*\代码
*读/写
*默认值：0xC0
*[7:0] 故障检测恢复常数 7:0
*\结束码
*/
#define STA350BW_FDRC2 ((uint8_t)0x2C)/*故障检测恢复常数寄存器 7:0*/

/**
*@brief I2C 地址状态寄存器
*\代码
*读
*默认值：0x7F
*7 PLLUL PLL 解锁
*6 FAULT 桥接器检测到故障
*5 UVFAULT 欠压故障
*4 OVFAULT 过压故障
*3 OCFAULT 过流故障
*2 OCWARN 过流警告
*1 TFAULT 热故障
*0 TWARN 热警告
*\结束码
*/
#define STA350BW_STATUS ((uint8_t)0x2D)/*状态寄存器*/

/**
*@brief I2C地址EQ系数和DRC配置寄存器
*\代码
*读/写
*默认值：0x00
*7 XOB 分频滤波器旁路
*[6:5] 保留
*[4:3] AMGC 防削波和 DRC 预设
*2 保留
*[1:0] EQ RAM 库选择器
*\结束码
*/
#define STA350BW_EQCFG ((uint8_t)0x31)/*EQ系数和DRC配置寄存器*/

/**
*@brief I2C 地址限制器 1 扩展攻击阈值寄存器
*\代码
*读/写
*默认值：0x30
*7 EATHEN1 限制器 1 扩展攻击阈值启用
*[6:0] EATH1 限制器 1 扩展攻击阈值
*\结束码
*/
#define STA350BW_EATH1 ((uint8_t)0x32)/*限制器1扩展攻击阈值寄存器*/

/**
*@brief I2C 地址限制器 1 扩展释放阈值寄存器
*\代码
*读/写
*默认值：0x30
*7 ERTHEN1 限制器 1 延长释放阈值启用
*[6:0] ERTH1 限制器 1 延长释放阈值
*\结束码
*/
#define STA350BW_ERTH1 ((uint8_t)0x33)/*限制器1延长释放阈值寄存器*/

/**
*@brief I2C地址限制器2扩展攻击阈值寄存器
*\代码
*读/写
*默认值：0x30
*7 EATHEN2 限制器 2 扩展攻击阈值启用
*[6:0] EATH2 限制器 2 扩展攻击阈值
*\结束码
*/
#define STA350BW_EATH2 ((uint8_t)0x34)/*限制器2扩展攻击阈值寄存器*/

/**
*@brief I2C 地址限制器 2 扩展释放阈值寄存器
*\代码
*读/写
*默认值：0x30
*7 ERTHEN2 限制器 2 延长释放阈值启用
*[6:0] ERTH2 限制器 2 延长释放阈值
*\结束码
*/
#define STA350BW_ERTH2 ((uint8_t)0x35)/*限制器2延长释放阈值寄存器*/

/**
*@brief I2C地址扩展配置寄存器
*\代码
*读/写
*默认值：0x00
*[7:6] MDRC MDRC 或 EQ DRC 选择器
*5 PS48DB 扩展后缩放范围
*4 扩展攻击率限制器 1
*3 扩展攻击率限制器 2
*2 个 Biquad 5 启用
*1 个双二阶 6 启用
*0 双二阶 7 启用
*\结束码
*/
#define STA350BW_CONFX ((uint8_t)0x36)/*扩展配置寄存器*/

/**
*@brief I2C地址软音量加配置寄存器
*\代码
*读/写
*默认值：0x00
*[7:6] 保留
*5 SVUPE 软音量增大启用
*[4:0] SVUP 软音量增大系数
*\结束码
*/
#define STA350BW_SVCA ((uint8_t)0x37)/*软音量增大配置寄存器*/

/**
*@brief I2C地址软音量下配置寄存器
*\代码
*读/写
*默认值：0x00
*[7:6] 保留
*5 SVDWE 软音量降低启用
*[4:0] SVDW 软音量下降系数
*\结束码
*/
#define STA350BW_SVCB ((uint8_t)0x38)/*软音量减小配置寄存器*/

/**
*@brief I2C地址DRC RMS滤波器系数c0 23:16寄存器
*\代码
*读/写
*默认值：0x01
*[7:0] R_C0 DRC RMS 滤波器系数 c0 23:16
*\结束码
*/
#define STA350BW_RMS0A ((uint8_t)0x39)/*DRC RMS 滤波器系数 c0 23:16 寄存器*/

/**
*@brief I2C地址DRC RMS滤波器系数c0 15:8寄存器
*\代码
*读/写
*默认值：0xEE
*[7:0] R_C0 DRC RMS 滤波器系数 c0 15:8
*\结束码
*/
#define STA350BW_RMS0B ((uint8_t)0x3A)/*DRC RMS 滤波器系数 c0 15:8 寄存器*/

/**
*@brief I2C地址DRC RMS滤波器系数c0 7:0寄存器
*\代码
*读/写
*默认值：0xFF
*[7:0] R_C0 DRC RMS 滤波器系数 c0 7:0
*\结束码
*/
#define STA350BW_RMS0C ((uint8_t)0x3B)/*DRC RMS 滤波器系数 c0 7:0 寄存器*/

/**
*@brief I2C地址DRC RMS滤波器系数c1 23:16寄存器
*\代码
*读/写
*默认值：0x7E
*[7:0] R_C1 DRC RMS 滤波器系数 c0 23:16
*\结束码
*/
#define STA350BW_RMS1A ((uint8_t)0x3C)/*DRC RMS 滤波器系数 c1 23:16 寄存器*/

/**
*@brief I2C地址DRC RMS滤波器系数c1 15:8寄存器
*\代码
*读/写
*默认值：0xC0
*[7:0] R_C1 DRC RMS 滤波器系数 c1 15:8
*\结束码
*/
#define STA350BW_RMS1B ((uint8_t)0x3D)/*DRC RMS 滤波器系数 c1 15:8 寄存器*/

/**
*@brief I2C地址DRC RMS滤波器系数c1 7:0寄存器
*\代码
*读/写
*默认值：0x26
*[7:0] R_C0 DRC RMS 滤波器系数 c1 7:0
*\结束码
*/
#define STA350BW_RMS1C ((uint8_t)0x3E)/*DRC RMS 滤波器系数 c1 7:0 寄存器*/

/**
*@brief I2C地址额外卷分辨率配置寄存器
*\代码
*读/写
*默认值：0x00
*7 VRESEN 额外体积分辨率启用
*6 VRESTG 额外体积分辨率更新
*[5:4] C3VR 通道 3 额外音量值
*[3:2] C2VR 通道 2 额外音量值
*[1:0] C1VR通道1额外音量值
*\结束码
*/
#define STA350BW_EVOLRES ((uint8_t)0x3F)/*额外卷分辨率配置寄存器*/

/**
*@brief I2C 地址量化误差噪声校正寄存器
*\代码
*读/写
*默认值：0x00
*7 量化噪声整形使能
*6 双二阶 7 上的量化噪声整形
*5 双二阶 6 上的量化噪声整形
*4 双二阶 5 上的量化噪声整形
*3 双二阶 4 上的量化噪声整形
*2 双二阶 3 上的量化噪声整形
*1 双二阶上的量化噪声整形 2
*0 双二阶 1 上的量化噪声整形
*\结束码
*/
#define STA350BW_NSHAPE ((uint8_t)0x48)/*量化误差噪声校正寄存器*/

/**
*@brief I2C 地址扩展系数范围高达 -4...4 双二阶 1-4 寄存器
*\代码
*读/写
*默认值：0x00
*[7:6] CXTB4 双二阶 4 上的扩展系数
*[5:4] CXTB3 双二阶 3 上的扩展系数
*[3:2] CXTB2 双二阶 2 上的扩展系数
*[1:0] CXTB1 双二阶 1 上的扩展系数
*\结束码
*/
#define STA350BW_CXT_B4B1 ((uint8_t)0x49)/*将系数范围扩展至 -4...4 双二阶 1-4 寄存器*/

/**
*@brief I2C 地址扩展系数范围高达 -4...4 双二阶 5-7 寄存器
*\代码
*读/写
*默认值：0x00
*[7:6] 保留
*[5:4] CXTB7 双二阶 7 上的扩展系数
*[3:2] CXTB6 双二阶 6 上的扩展系数
*[1:0] CXTB5 双二阶 5 上的扩展系数
*\结束码
*/
#define STA350BW_CXT_B7B5 ((uint8_t)0x4A)/*将系数范围扩展至 -4...4 双二阶 5-7 寄存器*/

/**
*@brief I2C地址杂项寄存器1
*\代码
*读/写
*默认值：0x04
*7 RPDNEN 速率掉电使能
*6 NSHHPEN 噪声整形功能启用
*5 BRIDGOFF 桥立即关闭
*[4:3] 保留
*2 CPWMEN 通道 PWM 使能
*[1:0] 保留
*\结束码
*/
#define STA350BW_MISC1 ((uint8_t)0x4B)/*杂项寄存器1*/

/**
*@brief I2C地址杂项寄存器2
*\代码
*读/写
*默认值：0x00
*[7:5] 保留
*[4:2] PNDSLL 掉电延迟选择器
*[1:0] 保留
*\结束码
*/
#define STA350BW_MISC2 ((uint8_t)0x4C)/*杂项寄存器2*/

/**
*@}
*/
/**@defgroup STA350BW_Main_parameter
*@{
*/
#define STA350BW_EAPD_ON ((uint8_t)0x80)
#define STA350BW_EAPD_OFF ((uint8_t)0x00)
#define STA350BW_PWDN_OFF ((uint8_t)0x40)
#define STA350BW_PWDN_ON ((uint8_t)0x00)/*低功耗*/

#define STA350BW_MVOL_0dB ((uint8_t)0x00)
#define STA350BW_MVOL_MUTE ((uint8_t)0xFF)
/**
*@}
*/
/**@defgroup STA350BW_输入_频率_选择
*@{
*/
#define STA350BW_Fs_32000 ((uint32_t)32000)
#define STA350BW_Fs_44100 ((uint32_t)44100)
#define STA350BW_Fs_48000 ((uint32_t)48000)
#define STA350BW_Fs_88200 ((uint32_t)88200)
#define STA350BW_Fs_96000 ((uint32_t)96000)

#define STA350BW_MCLK_256_LR_48K ((uint8_t)0x03)
#define STA350BW_MCLK_128_LR_48K ((uint8_t)0x04)
#define STA350BW_MCLK_256_LR_96K ((uint8_t)0x09)
#define STA350BW_MCLK_128_LR_96K ((uint8_t)0x0B)
/**
*@}
*/
/**@defgroup STA350BW_mode_selection
*@brief STA350BW 模式配置常量
*@{
*/
#define STA350BW_STEREO_CONF ((uint8_t)0x00)
#define STA350BW_2SE_1BTL_CONF ((uint8_t)0x01)
#define STA350BW_STEREO_EXT_BRIDGE_CONF ((uint8_t)0x00)
#define STA350BW_MONOBTL_CONF ((uint8_t)0x11)
#define STA350BW_BINARY_CONF ((uint8_t)0x80)/*在寄存器 0E、0F、10 上*/
/**
*@}
*/
/**@defgroup STA350BW_DSP_option_selection
*@brief STA350BW 与数据路径管理相关的常量
*@{
*/
#define STA350BW_DSPB ((uint8_t)0x00)
#define STA350BW_C1EQBP ((uint8_t)0x01)
#define STA350BW_C2EQBP ((uint8_t)0x02)
#define STA350BW_C1TCB ((uint8_t)0x03)
#define STA350BW_C2TCB ((uint8_t)0x04)
#define STA350BW_C1VBP ((uint8_t)0x05)
#define STA350BW_C2VBP ((uint8_t)0x06)
#define STA350BW_HPB ((uint8_t)0x07)
#define STA350BW_DEMP ((uint8_t)0x08)
#define STA350BW_BQL ((uint8_t)0x09)
#define STA350BW_BQ5 ((uint8_t)0x0A)
#define STA350BW_BQ6 ((uint8_t)0x0B)
#define STA350BW_BQ7 ((uint8_t)0x0C)
#define STA350BW_EXT_RANGE_BQ1 ((uint8_t)0x0D)
#define STA350BW_EXT_RANGE_BQ2 ((uint8_t)0x0E)
#define STA350BW_EXT_RANGE_BQ3 ((uint8_t)0x0F)
#define STA350BW_EXT_RANGE_BQ4 ((uint8_t)0x10)
#define STA350BW_EXT_RANGE_BQ5 ((uint8_t)0x11)
#define STA350BW_EXT_RANGE_BQ6 ((uint8_t)0x12)
#define STA350BW_EXT_RANGE_BQ7 ((uint8_t)0x13)
#define STA350BW_RAM_BANK_SELECT ((uint8_t)0x14)
/**
*@}
*/
/**@defgroup STA350BW_state_define STA350BW 状态定义
*@brief STA350BW 状态定义
*@{
*/
#define STA350BW_ENABLE ((uint8_t)0x01)
#define STA350BW_DISABLE ((uint8_t)0x00)
#define STA350BW_RANGE_ONE ((uint8_t)0x01)
#define STA350BW_RANGE_TWO ((uint8_t)0x02)
#define STA350BW_RANGE_FOUR ((uint8_t)0x04)
/**
*@}
*/
/**@defgroup STA350BW_channel_define STA350BW 通道定义
*@brief STA350BW 通道定义
*@{
*/
#define STA350BW_CHANNEL_MASTER ((uint8_t)0x00)
#define STA350BW_CHANNEL_1 ((uint8_t)0x01)
#define STA350BW_CHANNEL_2 ((uint8_t)0x02)
#define STA350BW_CHANNEL_3 ((uint8_t)0x03)
/**
*@}
*/
/**@defgroup STA350BW_channel_define STA350BW Biq 定义
*@brief STA350BW Biq 定义
*@{
*/
#define STA350BW_RAM_BANK_FIRST ((uint8_t)0x00)
#define STA350BW_RAM_BANK_SECOND ((uint8_t)0x01)
#define STA350BW_RAM_BANK_THIRD ((uint8_t)0x02)
#define STA350BW_CH1_BQ1 ((uint8_t)0x00)
#define STA350BW_CH1_BQ2 ((uint8_t)0x01)
#define STA350BW_CH1_BQ3 ((uint8_t)0x02)
#define STA350BW_CH1_BQ4 ((uint8_t)0x03)
#define STA350BW_CH2_BQ1 ((uint8_t)0x04)
#define STA350BW_CH2_BQ2 ((uint8_t)0x05)
#define STA350BW_CH2_BQ3 ((uint8_t)0x06)
#define STA350BW_CH2_BQ4 ((uint8_t)0x07)

  /**
*@}
*/
  /**@defgroup STA350BW_Exported_Functions
*@{
*/

  int32_t STA350BW_Init(STA350BW_ctx_t *dev, uint16_t volume, uint32_t samplingFreq);
  int32_t STA350BW_DeInit(void);
  int32_t STA350BW_ReadID(void);
  int32_t STA350BW_Play(uint16_t *pBuffer, uint16_t Size);
  int32_t STA350BW_Pause(void);
  int32_t STA350BW_Resume(void);
  int32_t STA350BW_SetMute(uint8_t channel, uint8_t state);
  int32_t STA350BW_SetVolume(uint32_t channel, uint8_t Volume);
  int32_t STA350BW_SetFrequency(uint32_t AudioFreq);
  int32_t STA350BW_Stop(void);
  int32_t STA350BW_Reset(void);
  int32_t STA350BW_SetEq(uint8_t ramBlock, uint8_t filterNumber, uint32_t *filterValues);
  int32_t STA350BW_SetTone(uint8_t toneGain);
  int32_t STA350BW_SetDSPOption(uint8_t option, uint8_t state);


  uint32_t Switch_Demo( enum BiquadType current_demo);

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
*@}
*/

#ifdef __cplusplus
}
#endif

#endif/*STA350BW_H*/
/************************(C) 版权所有意法半导体 *****文件结束****/
