package com.example.soundtuner

/**
 * BLE EQ 二进制调音协议 (与固件 apps/wifi_story_machine/include/eq_protocol.h 完全一致)
 *
 * 帧格式: [MAGIC=0xEB][CMD][LEN][PAYLOAD...][SUM]
 *   MAGIC : 固定 0xEB
 *   LEN   : payload 字节数 (不含 MAGIC/CMD/LEN/SUM)
 *   SUM   : MAGIC ^ CMD ^ LEN ^ payload[0] ^ ... ^ payload[LEN-1]
 *
 * 增益单位统一为 0.1dB (tenths), int8 表示, 范围 -120..+120 (= ±12.0dB)。
 */
object EqProtocol {

    const val MAGIC = 0xEB

    // 命令字
    const val CMD_SET_BAND = 0x01
    const val CMD_SET_ALL = 0x02
    const val CMD_PRESET = 0x03
    const val CMD_SAVE = 0x04
    const val CMD_QUERY = 0x05

    const val BAND_COUNT = 4
    const val GAIN_MIN_TENTH = -120
    const val GAIN_MAX_TENTH = 120

    const val QUERY_RESP_LEN = 5
    private const val FRAME_OFF_MAGIC = 0
    private const val FRAME_OFF_CMD = 1
    private const val FRAME_OFF_LEN = 2
    private const val FRAME_OFF_PAYLOAD = 3

    /** 预设名 -> preset_id (对应固件 enum BiquadType) */
    val PRESET_IDS: Map<String, Int> = mapOf(
        "CLEAR" to 0,
        "FLAT" to 1,
        "ROCK" to 2,
        "SOFT" to 3,
        "JAZZ" to 4,
        "CLASSICAL" to 5,
        "DANCE" to 6,
        "POP" to 7,
        "SOFT_ROCK" to 8,
        "HARD" to 9,
        "PARTY" to 10,
        "VOCAL" to 11,
        "HIPHOP" to 12,
        "DIALOG" to 13,
        "BASS_BOOST1" to 14,
        "BASS_BOOST2" to 15,
        "BASS_BOOST3" to 16,
        "BYPASS_BIQ" to 17,
        "BYPASS_TONE" to 18,
        "USER_1" to 19,
        "USER_2" to 20,
        "USER_3" to 21
    )

    private fun clampGain(tenths: Int): Int =
        tenths.coerceIn(GAIN_MIN_TENTH, GAIN_MAX_TENTH)

    /** 组帧: 自动写 MAGIC/CMD/LEN, 并算 SUM */
    private fun buildFrame(cmd: Int, payload: ByteArray): ByteArray {
        val len = payload.size
        val frame = ByteArray(payload.size + 4)
        frame[FRAME_OFF_MAGIC] = MAGIC.toByte()
        frame[FRAME_OFF_CMD] = cmd.toByte()
        frame[FRAME_OFF_LEN] = len.toByte()
        payload.copyInto(frame, FRAME_OFF_PAYLOAD)
        var sum = MAGIC xor cmd xor len
        for (b in payload) {
            sum = sum xor (b.toInt() and 0xFF)
        }
        frame[frame.size - 1] = sum.toByte()
        return frame
    }

    /** 0x01 单段设置: band(0..3) + gain(0.1dB) */
    fun buildSetBand(band: Int, gainTenths: Int): ByteArray {
        val b = band.coerceIn(0, BAND_COUNT - 1)
        val g = clampGain(gainTenths)
        return buildFrame(CMD_SET_BAND, byteArrayOf(b.toByte(), g.toByte()))
    }

    /** 0x02 四段一次性设置: g0 g1 g2 g3 (0.1dB) */
    fun buildSetAll(gainsTenths: IntArray): ByteArray {
        val payload = ByteArray(BAND_COUNT)
        for (i in 0 until BAND_COUNT) {
            val g = if (i < gainsTenths.size) gainsTenths[i] else 0
            payload[i] = clampGain(g).toByte()
        }
        return buildFrame(CMD_SET_ALL, payload)
    }

    /** 0x03 切换预设: preset_id */
    fun buildPreset(presetId: Int): ByteArray =
        buildFrame(CMD_PRESET, byteArrayOf((presetId and 0xFF).toByte()))

    /** 0x04 存当前 EQ 到 USER 槽位: slot 1/2/3 */
    fun buildSave(slot: Int): ByteArray =
        buildFrame(CMD_SAVE, byteArrayOf((slot and 0xFF).toByte()))

    /** 0x05 请求回传当前状态: 空 payload */
    fun buildQuery(): ByteArray = buildFrame(CMD_QUERY, ByteArray(0))

    /** QUERY 响应解析结果 */
    data class QueryResult(val gainsTenths: IntArray, val presetId: Int)

    /**
     * 解析 ae3c notify 回传的 QUERY 响应帧。
     * 帧格式同上, CMD=0x05, payload = g0 g1 g2 g3 preset_id (5 字节)。
     * 校验 MAGIC/SUM/CMD/LEN, 任一失败返回 null。
     */
    fun parseQueryResponse(data: ByteArray): QueryResult? {
        if (data.size < QUERY_RESP_LEN + 4) return null
        if ((data[FRAME_OFF_MAGIC].toInt() and 0xFF) != MAGIC) return null
        if ((data[FRAME_OFF_CMD].toInt() and 0xFF) != CMD_QUERY) return null
        val len = data[FRAME_OFF_LEN].toInt() and 0xFF
        if (len != QUERY_RESP_LEN) return null
        // 整帧长度 = 3 + len + 1
        val frameLen = FRAME_OFF_PAYLOAD + len + 1
        if (data.size < frameLen) return null

        var sum = MAGIC xor CMD_QUERY xor len
        for (i in 0 until len) {
            sum = sum xor (data[FRAME_OFF_PAYLOAD + i].toInt() and 0xFF)
        }
        val expected = data[FRAME_OFF_PAYLOAD + len].toInt() and 0xFF
        if ((sum and 0xFF) != expected) return null

        val gains = IntArray(BAND_COUNT)
        for (i in 0 until BAND_COUNT) {
            // s8 -> Int (保留符号)
            gains[i] = data[FRAME_OFF_PAYLOAD + i].toInt()
        }
        val presetId = data[FRAME_OFF_PAYLOAD + BAND_COUNT].toInt() and 0xFF
        return QueryResult(gains, presetId)
    }
}
