# 功放固件清洁 + 二进制 EQ 协议 + 安卓 App 完善

## 背景澄清（探查中发现的关键事实，纠正最初设想）

1. **WiFi/UI(LCD)/视频当前已全部关闭**：预处理确认 `CONFIG_NET_ENABLE`/`CONFIG_WIFI_ENABLE`/`CONFIG_UI_ENABLE`/`CONFIG_VIDEO_ENABLE` 均未定义；当前 elf 里查无 WiFi(RtmpMlme/tcpip)、LCD、camera 符号。之前满屏 WiFi 的日志来自 `Dec 22 2025` 旧固件，非当前代码。
2. **安卓 App 已基本可用**：`Android/app` 的 `MainActivity.kt` 已实现扫描连接 `NiShuGong_AMP(BLE)`、4 段 EQ 滑块、16 工厂预设+3 用户预设+旁路、Apply/Reset/Save，当前用 ASCII 文本协议。
3. **蓝牙走纯蓝牙路径**：app_main 已有 `#if CONFIG_BT_ENABLE && !CONFIG_WIFI_ENABLE → bt_ble_module_init()`。
4. **BLE EQ 通道**：service `ae3a` / 写特征 `ae3b`(WRITE_WITHOUT_RESPONSE, handle 0x0042) / 通知 `ae3c`(0x0044)。
5. **USB 声卡**：`TCFG_PC_ENABLE=1`，`SPEAKER_CLASS|CDC_CLASS`，由 board 的 `otg` 设备(slave_online_cnt 消抖)驱动枚举。

## 用户决策
- EQ 协议：**改二进制**（命令字+参数）
- 固件：**清理残留死代码**（Makefile 源列表、任务表、app_music 网络死代码）
- USB：**开机延迟起 USB**，留烧录窗口

---

## 第一部分：固件二进制 EQ 协议

### 1.1 协议设计（新增 `apps/wifi_story_machine/include/eq_protocol.h`）
所有命令经 `ae3b` 写入，格式：`[MAGIC(1)=0xEB][CMD(1)][LEN(1)][PAYLOAD...][SUM(1)]`，SUM 为前面字节异或校验。

命令字：
- `0x01 SET_BAND`    payload: `band(1) gain_s8(1)`  单段增益，gain 单位 0.5dB，范围 -24..+24 (= ±12dB)
- `0x02 SET_ALL`     payload: `g0 g1 g2 g3`(4×s8)   四段一次性
- `0x03 PRESET`      payload: `preset_id(1)`         对应 enum BiquadType
- `0x04 SAVE`        payload: `slot(1)` (1/2/3)      存当前 EQ 到 USER_n
- `0x05 QUERY`       payload: 无                     固件经 `ae3c` notify 回当前 4 段增益+当前预设

### 1.2 固件改动
- **新增** `eq_protocol.h`：宏定义命令字、MAGIC、band/gain 范围。
- **改** `user_app.c` 的 `ble_sound_tuner_command_parse()`：
  - 替换现有 ASCII `strncmp` 分支为二进制解析（校验 MAGIC/SUM/LEN，再按 CMD 分发）。
  - 复用现有 `user_eq_update_band()` / `user_eq_apply_all()` / `ble_save_user_preset()` / `Switch_Demo()`，仅改入口解析层。
  - QUERY 命令通过 `ae3c` notify 回传（需引用现有 notify 发送接口，见 le_trans_data.c）。
- **保留** EQ 计算/预设/flash 存储逻辑不动。

### 1.3 兼容性
ASCII 与二进制不能并存（首字节冲突）。改为纯二进制后，旧的串口直接发 ASCII 测试方式失效，但安卓端同步改即可。

---

## 第二部分：USB 声卡开机延迟窗口

### 方案：延迟注册/启动 OTG，给烧录留 2-3 秒
- 在 `board_7916A.c` 的 OTG 初始化路径（`otg` 设备注册/`usb_otg_init` 调用处）前加开机延迟，或把 `slave_online_cnt` 配合一个上电后计时门控：开机后先 delay ~2.5s 再允许 USB 进入 device 模式。
- 具体落点：定位 board 中实际触发 USB device 枚举的初始化函数（OTG online 检测启动处），在其前插入一次性延迟（仅上电首次）。
- LED 可选提示（当前无 UI，靠延迟即可）。
- 风险：延迟期间插 USB 不会立刻出声卡，2.5s 后正常。可调。

---

## 第三部分：固件清洁（清理残留死代码）

### 3.1 Makefile 源文件列表瘦身（`board/wl82/Makefile` c_SRC_FILES）
移除已不参与功能的源文件引用（总开关已关，编译进来纯属浪费）：
- 视频相关：`video/camera_lcd_demo.c`、`get_yuv_data.c`、`jpeg2yuv.c`、`network_mssdp.c`、`spi_data_deal.c`、`spi_recv.c`、`video/stream/*`、`stream_protocol.c`、`strm_video_rec.c`、`user_video_rec.c`
- 相机驱动：`apps/common/camera/*`（一大批 gc/byd/ov 传感器）
- WiFi/网络：`wifi_app_task.c`、`multiple_ethernetif.c`、`apps/common/net/*`
- UI/LCD：`ui/led_ui_gr202.c`、`apps/common/ui/lcd_driver/*`、`touch_panel/*`
- 注：仅移源文件列表项，不删文件本体（可回退）。每移一批就编译验证。

### 3.2 任务表瘦身（`app_main.c` task_info_table）
移除 video_server/vpkg_server/video*_rec/net_avi/jpg_dec/video_dec_server/ui/lcd_task/te_task 等条目（这些功能已关，任务白占）。

### 3.3 app_music.c 网络死代码
`#ifdef CONFIG_NET_ENABLE` 包裹的网络音乐分支已不编译，**保留不动**（删除风险高、收益低），仅在确有必要时清理。

### 3.4 安全策略
- 每改一类就 `make` 验证链接通过（用 `tools/utils/make.exe`）。
- 任一步骤编译失败立即回退该步。
- 保留 BT(A2DP/AVRCP)、USB 声卡、IIS/STA350BW、BLE EQ 全链路。

---

## 第四部分：安卓 App 改造（`Android/app`）

### 4.1 协议层（新增 `EqProtocol.kt`）
- 实现二进制编码：`buildSetBand/buildSetAll/buildPreset/buildSave/buildQuery`，输出 ByteArray（MAGIC+CMD+LEN+PAYLOAD+SUM）。
- 解析 `ae3c` notify 回传的 QUERY 响应。

### 4.2 MainActivity.kt 改造
- 把现有 `onSendCommand(String)` 文本发送改为发送 ByteArray（调 EqProtocol）。
- 预设按钮：`PRESET:<name>` → `buildPreset(presetId)`。需建立预设名→id 映射（对应 enum BiquadType 顺序）。
- EQ 滑块 Apply：`PEQALL:` → `buildSetAll(gains)`。
- 实时拖动（可选增强）：滑块拖动时节流发送 `buildSetBand`。
- SAVE：`SAVE:<slot>` → `buildSave(slotId)`。
- 订阅 `ae3c` 通知，连接后发 QUERY 同步当前 EQ 状态到 UI。

### 4.3 依赖
现有 build.gradle.kts 已含 Compose + accompanist permissions，无需加依赖。

---

## 执行顺序（每步可独立验证）
1. 固件：新增 `eq_protocol.h` + 改 `user_app.c` 二进制解析 → 编译验证。
2. 固件：USB 开机延迟窗口 → 编译验证。
3. 固件：Makefile/任务表清洁（分批） → 每批编译验证。
4. 安卓：`EqProtocol.kt` + 改 `MainActivity.kt` → Gradle 编译（若环境可用）。
5. 联调建议：先烧录固件（用开机延迟窗口救烧录），再装 App 实测 EQ。

## 风险
- 二进制协议改完，旧 ASCII 测试方式失效（已与用户确认改二进制）。
- USB 延迟窗口时长需实测调优。
- Makefile 清理可能牵出隐藏依赖（某个保留文件 include 了被移文件的符号）→ 分批编译可快速定位回退。
- 安卓 Gradle 构建依赖本机 JDK/SDK 环境，若不可用则只交付代码、由你在 Android Studio 编译。
