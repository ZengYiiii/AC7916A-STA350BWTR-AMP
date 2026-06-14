#ifndef _EQ_PROTOCOL_H_
#define _EQ_PROTOCOL_H_

/*
 * BLE EQ 二进制调音协议 (通过特征 ae3b 写入, ae3c 通知回传)
 *
 * 帧格式: [MAGIC][CMD][LEN][PAYLOAD...][SUM]
 *   MAGIC : 固定 0xEB, 帧起始标识
 *   CMD   : 命令字, 见 EQ_CMD_*
 *   LEN   : PAYLOAD 字节数 (不含 MAGIC/CMD/LEN/SUM)
 *   SUM   : 校验字节 = MAGIC ^ CMD ^ LEN ^ payload[0] ^ ... ^ payload[LEN-1]
 *
 * 增益单位统一为 0.1dB (tenths), 用 int8 表示, 范围 -120..+120 (= ±12.0dB),
 * 与固件内部 user_eq_clamp_gain 的单位一致, 无需换算。
 */

#define EQ_PROTO_MAGIC          0xEB

/* 命令字 */
#define EQ_CMD_SET_BAND         0x01  /* payload: band(u8) gain(s8, 0.1dB)        单段设置 */
#define EQ_CMD_SET_ALL          0x02  /* payload: g0 g1 g2 g3 (4×s8, 0.1dB)       四段一次性设置 */
#define EQ_CMD_PRESET           0x03  /* payload: preset_id(u8) = enum BiquadType  切换预设 */
#define EQ_CMD_SAVE             0x04  /* payload: slot(u8) 1/2/3                   存当前EQ到USER_n */
#define EQ_CMD_QUERY            0x05  /* payload: 无                               请求回传当前状态 */

/* QUERY 响应 (经 ae3c notify 回传), 帧格式同上, CMD=EQ_CMD_QUERY:
 *   payload: g0 g1 g2 g3 (4×s8, 0.1dB) preset_id(u8)
 */
#define EQ_QUERY_RESP_LEN       5

/* 帧字段偏移与长度 */
#define EQ_FRAME_OFF_MAGIC      0
#define EQ_FRAME_OFF_CMD        1
#define EQ_FRAME_OFF_LEN        2
#define EQ_FRAME_OFF_PAYLOAD    3
#define EQ_FRAME_OVERHEAD       4   /* MAGIC + CMD + LEN + SUM */
#define EQ_FRAME_MIN_LEN        EQ_FRAME_OVERHEAD  /* 空 payload 的最小帧长 */
#define EQ_FRAME_MAX_PAYLOAD    16

/* EQ 段与增益范围 (与 user_app.c 中 USER_EQ_* 一致) */
#define EQ_BAND_COUNT           4
#define EQ_GAIN_MIN_TENTH       (-120)
#define EQ_GAIN_MAX_TENTH       (120)

/* USER 预设槽位 */
#define EQ_SAVE_SLOT_1          1
#define EQ_SAVE_SLOT_2          2
#define EQ_SAVE_SLOT_3          3

#endif /* _EQ_PROTOCOL_H_ */
