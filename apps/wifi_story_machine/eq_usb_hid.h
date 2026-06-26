#ifndef EQ_USB_HID_H_
#define EQ_USB_HID_H_

#include <stdint.h>

/* =============================================================================
 * STA350BW EQ - USB HID 调节模块
 *
 * 取代原 BLE EQ 通道: PC 工具经 USB HID(vendor-defined, usage page 0xFF00)
 * 下发 EQ 命令, 设备实时调节外置功放 STA350BW 的 biquad 均衡器。
 *
 * EQ 段数: 4 段(STA350BW 真正安全可用的通用 EQ 上限)
 *   段 0~3 = BQ1~BQ4: 双声道独立, 地址 0x00~0x27 互不冲突, 直接写即激活。
 * 注: 数据手册标称"8 biquads/通道", 但 BQ5~BQ7 复用 de-emphasis/bass/treble,
 *     其 RAM 地址(0x20/0x25/0x2A)与 CH2 BQ 区重叠, 实测会破坏正常音频, 故不使用。
 *
 * 解耦: HID 收包回调只把"最新一帧目标"记入 pending, 真正写 I2C 在
 * UserAudioDevice 任务里 eq_usb_process_pending() 执行(去抖, 写前后 mute 消炸音)。
 * ===========================================================================*/

#define EQ_BAND_COUNT 4  /* 4 段 EQ(BQ1~BQ4, 双声道独立, 安全区) */

/* ---- USB HID report ---- */
#define EQ_HID_REPORT_LEN 64 /* HID IN/OUT report 固定 64 字节 */

/* ---- 协议帧: [MAGIC][CMD][LEN][PAYLOAD..][XOR_SUM], 其余补 0 ---- */
#define EQ_HID_MAGIC 0xE9
#define EQ_HID_OFF_MAGIC 0
#define EQ_HID_OFF_CMD 1
#define EQ_HID_OFF_LEN 2
#define EQ_HID_OFF_PAYLOAD 3
#define EQ_HID_OVERHEAD 4 /* MAGIC + CMD + LEN + SUM */
#define EQ_HID_MAX_PAYLOAD (EQ_HID_REPORT_LEN - EQ_HID_OVERHEAD)

/* ---- 命令字(PC -> 设备) ---- */
#define EQ_HID_CMD_SET_BAND 0x01 /* band(u8)+freq(u16 LE)+gain(s16 LE,0.1dB)+q(u16 LE,0.01) */
#define EQ_HID_CMD_PRESET 0x03   /* preset_id(u8) = enum BiquadType */
#define EQ_HID_CMD_SAVE 0x04     /* slot(u8) 1/2/3 */
#define EQ_HID_CMD_QUERY 0x05    /* 无 payload, 请求设备回传状态 */
#define EQ_HID_CMD_FLAT 0x06     /* 无 payload, 7 段全部清平(0dB) */

/* ---- 命令字(设备 -> PC) ---- */
#define EQ_HID_CMD_STATE 0x81 /* 回传: preset(u8) + 每段[freq(u16)+gain(s16)+q(u16)] */

/* ---- 单段参数 ---- */
#define EQ_BAND_GAIN_MIN_TENTH (-120) /* -12.0 dB */
#define EQ_BAND_GAIN_MAX_TENTH (120)  /* +12.0 dB */

/* =============================================================================
 * 对外接口
 * ===========================================================================*/

/* 设备启动时设置当前采样率(probe 成功后由 user_app 调用), 用于 biquad 系数计算 */
void eq_usb_set_fs(uint32_t fs);

/* 功放 init 成功后应用当前 EQ 状态(默认预设或 PC 已调过的最新状态)。
 * 在 user_amp_apply_after_init 中调用。 */
void eq_usb_apply_current(void);

/* 在 UserAudioDevice 任务主循环里周期调用: 消费 HID 投递的 pending 命令,
 * 真正写 STA350BW(去抖, 写前后 mute)。这是解耦的关键。 */
void eq_usb_process_pending(void);

/* HID 输出回调(PC -> 设备), 注册给 hid_set_output_handle。
 * 运行在 USB 任务上下文, 只解析+记 pending, 不做 I2C。 */
int eq_usb_hid_output(uint8_t *buf, uint32_t len);

/* 返回自定义 vendor HID report descriptor 及其长度, 供 task_pc 注册 */
const uint8_t *eq_usb_hid_report_desc(uint32_t *out_len);

#endif /* EQ_USB_HID_H_ */
