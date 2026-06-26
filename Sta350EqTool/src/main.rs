#![windows_subsystem = "windows"]

//! STA350BW EQ 调音工具
//! 通过 USB HID(vendor 0xFF00) 与设备通信, 实时调节 7 段均衡器。
//! 协议与固件 eq_usb_hid.h 一致。

use eframe::egui;
use std::sync::mpsc::{self, Receiver, Sender};
use std::thread;
use std::time::{Duration, Instant};

// ---- 设备标识(与固件 descriptor.c 一致) ----
// 实测 Windows 枚举出的 PID 为 0x4955(由芯片 chip id 决定), VID 0x3654(杰理)。
const USB_VID: u16 = 0x3654; // 珠海杰理
const USB_PID: u16 = 0x4955; // 实测枚举值
const USAGE_PAGE: u16 = 0xFF00; // vendor-defined

// ---- 协议(与 eq_usb_hid.h 一致) ----
const HID_REPORT_LEN: usize = 64;
const MAGIC: u8 = 0xE9;
const OFF_MAGIC: usize = 0;
const OFF_CMD: usize = 1;
const OFF_LEN: usize = 2;
const OFF_PAYLOAD: usize = 3;

const CMD_SET_BAND: u8 = 0x01;
const CMD_PRESET: u8 = 0x03;
const CMD_SAVE: u8 = 0x04;
const CMD_QUERY: u8 = 0x05;
const CMD_FLAT: u8 = 0x06;
const CMD_STATE: u8 = 0x81;

const BAND_COUNT: usize = 4;

// 预设: PC 端定义每个预设的 4 段增益(0.1dB)。频率固定用 DEFAULT_FREQS, Q=1.0。
// 点击预设时把这组参数加载到滑块并逐段下发, 用户可在此基础继续微调并保存。
struct Preset {
    name: &'static str,
    gains: [i16; BAND_COUNT], // 0.1 dB, 对应 125/500/2000/8000 Hz
}

const PRESETS: &[Preset] = &[
    Preset { name: "平坦 Flat",      gains: [0, 0, 0, 0] },
    Preset { name: "摇滚 Rock",      gains: [40, -10, 20, 40] },
    Preset { name: "爵士 Jazz",      gains: [30, 10, 20, 30] },
    Preset { name: "古典 Classical", gains: [30, 0, 10, 30] },
    Preset { name: "舞曲 Dance",     gains: [50, 0, 20, 40] },
    Preset { name: "流行 Pop",       gains: [-10, 30, 10, -10] },
    Preset { name: "人声 Vocal",     gains: [-10, 30, 30, 0] },
    Preset { name: "低音增强",       gains: [70, 30, 0, 0] },
];

// PLACEHOLDER_TYPES

/// 单段 EQ 参数
#[derive(Clone, Copy)]
struct Band {
    freq: u16,    // 中心频率 Hz
    gain: i16,    // 增益 0.1dB (-120~120)
    q: u16,       // Q值 *100
}

impl Default for Band {
    fn default() -> Self {
        Band { freq: 1000, gain: 0, q: 100 }
    }
}

/// 默认 7 段中心频率(与固件一致)
const DEFAULT_FREQS: [u16; BAND_COUNT] = [125, 500, 2000, 8000];

/// 主->工作线程 指令
enum Cmd {
    Connect,
    Disconnect,
    SetBand(u8, Band),
    #[allow(dead_code)] // 备用: 直接切固件内置预设系数表(当前 PC 改为逐段下发参数)
    Preset(u8),
    Flat,
    Save(u8),
    Query,
}

/// 工作线程->主 消息
enum Evt {
    Log(String),
    Connected(bool),
    State { bands: [Band; BAND_COUNT] },
}

// PLACEHOLDER_HID

/// 组一帧 HID OUT report(64B), 返回带前导 report-id 0 的 65B(Windows HID write 约定)
fn build_frame(cmd: u8, payload: &[u8]) -> Vec<u8> {
    let mut f = vec![0u8; HID_REPORT_LEN];
    f[OFF_MAGIC] = MAGIC;
    f[OFF_CMD] = cmd;
    f[OFF_LEN] = payload.len() as u8;
    for (i, b) in payload.iter().enumerate() {
        f[OFF_PAYLOAD + i] = *b;
    }
    let mut sum = 0u8;
    for i in 0..(OFF_PAYLOAD + payload.len()) {
        sum ^= f[i];
    }
    f[OFF_PAYLOAD + payload.len()] = sum;
    // hidapi write: 首字节为 report id(0)
    let mut out = vec![0u8];
    out.extend_from_slice(&f);
    out
}

fn payload_set_band(band: u8, b: Band) -> Vec<u8> {
    vec![
        band,
        (b.freq & 0xFF) as u8, (b.freq >> 8) as u8,
        (b.gain & 0xFF) as u8, ((b.gain >> 8) & 0xFF) as u8,
        (b.q & 0xFF) as u8, (b.q >> 8) as u8,
    ]
}

/// 解析设备回传的 STATE 帧
fn parse_state(buf: &[u8]) -> Option<(u8, [Band; BAND_COUNT])> {
    if buf.len() < HID_REPORT_LEN || buf[OFF_MAGIC] != MAGIC || buf[OFF_CMD] != CMD_STATE {
        return None;
    }
    let mut p = OFF_PAYLOAD;
    let preset = buf[p]; p += 1;
    let mut bands = [Band::default(); BAND_COUNT];
    for i in 0..BAND_COUNT {
        if p + 6 > buf.len() { return None; }
        bands[i].freq = buf[p] as u16 | ((buf[p+1] as u16) << 8);
        bands[i].gain = buf[p+2] as i16 | ((buf[p+3] as i16) << 8);
        bands[i].q = buf[p+4] as u16 | ((buf[p+5] as u16) << 8);
        p += 6;
    }
    Some((preset, bands))
}

// PLACEHOLDER_WORKER

/// 后台 HID 工作线程: 管理连接、发送指令、轮询读取设备回传。
fn worker_thread(cmd_rx: Receiver<Cmd>, evt_tx: Sender<Evt>) {
    let api = match hidapi::HidApi::new() {
        Ok(a) => a,
        Err(e) => {
            let _ = evt_tx.send(Evt::Log(format!("hidapi 初始化失败: {}", e)));
            return;
        }
    };
    let mut device: Option<hidapi::HidDevice> = None;

    loop {
        // 处理主线程指令(非阻塞)
        match cmd_rx.recv_timeout(Duration::from_millis(20)) {
            Ok(cmd) => match cmd {
                Cmd::Connect => {
                    device = open_device(&api, &evt_tx);
                    let _ = evt_tx.send(Evt::Connected(device.is_some()));
                    if device.is_some() {
                        // 连接后查询设备当前状态
                        if let Some(d) = &device {
                            let _ = d.write(&build_frame(CMD_QUERY, &[]));
                        }
                    }
                }
                Cmd::Disconnect => {
                    device = None;
                    let _ = evt_tx.send(Evt::Connected(false));
                }
                other => {
                    if let Some(d) = &device {
                        let frame = match other {
                            Cmd::SetBand(b, band) => build_frame(CMD_SET_BAND, &payload_set_band(b, band)),
                            Cmd::Preset(id) => build_frame(CMD_PRESET, &[id]),
                            Cmd::Flat => build_frame(CMD_FLAT, &[]),
                            Cmd::Save(slot) => build_frame(CMD_SAVE, &[slot]),
                            Cmd::Query => build_frame(CMD_QUERY, &[]),
                            _ => continue,
                        };
                        if let Err(e) = d.write(&frame) {
                            let _ = evt_tx.send(Evt::Log(format!("发送失败: {}", e)));
                            device = None;
                            let _ = evt_tx.send(Evt::Connected(false));
                        }
                    }
                }
            },
            Err(mpsc::RecvTimeoutError::Timeout) => {}
            Err(mpsc::RecvTimeoutError::Disconnected) => break,
        }

        // 轮询读取设备回传(STATE)
        if let Some(d) = &device {
            let mut buf = [0u8; HID_REPORT_LEN];
            match d.read_timeout(&mut buf, 1) {
                Ok(n) if n > 0 => {
                    if let Some((_preset, bands)) = parse_state(&buf) {
                        let _ = evt_tx.send(Evt::State { bands });
                    }
                }
                Ok(_) => {}
                Err(_) => {}
            }
        }
    }
}

/// 按 VID/PID 匹配并打开设备(优先选 usage_page=0xFF00 的 vendor 接口)。
fn open_device(api: &hidapi::HidApi, evt_tx: &Sender<Evt>) -> Option<hidapi::HidDevice> {
    // 第一轮: 严格匹配 VID+PID+usage_page(0xFF00)
    for info in api.device_list() {
        if info.vendor_id() == USB_VID
            && info.product_id() == USB_PID
            && info.usage_page() == USAGE_PAGE
        {
            if let Ok(d) = info.open_device(api) {
                let _ = evt_tx.send(Evt::Log(format!(
                    "已连接(vendor): VID={:04X} PID={:04X} usage_page=FF00",
                    USB_VID, USB_PID
                )));
                return Some(d);
            }
        }
    }
    // 第二轮: 放宽到 VID+PID(某些系统 usage_page 读不到/为0)
    for info in api.device_list() {
        if info.vendor_id() == USB_VID && info.product_id() == USB_PID {
            let up = info.usage_page();
            if let Ok(d) = info.open_device(api) {
                let _ = evt_tx.send(Evt::Log(format!(
                    "已连接: VID={:04X} PID={:04X} (usage_page={:04X})",
                    USB_VID, USB_PID, up
                )));
                return Some(d);
            }
        }
    }
    let _ = evt_tx.send(Evt::Log(format!(
        "未找到设备(VID={:04X} PID={:04X})。请确认已插USB并烧录新固件。",
        USB_VID, USB_PID
    )));
    None
}

// PLACEHOLDER_APP

struct EqApp {
    cmd_tx: Sender<Cmd>,
    evt_rx: Receiver<Evt>,
    connected: bool,
    bands: [Band; BAND_COUNT],
    cur_preset: i32, // -1=自定义, >=0=PRESETS 索引
    logs: Vec<String>,
    last_send: [Instant; BAND_COUNT], // 各段去抖计时
    save_slot: u8,
}

impl EqApp {
    fn new(cmd_tx: Sender<Cmd>, evt_rx: Receiver<Evt>) -> Self {
        let mut bands = [Band::default(); BAND_COUNT];
        for i in 0..BAND_COUNT {
            bands[i].freq = DEFAULT_FREQS[i];
            bands[i].gain = 0;
            bands[i].q = 100;
        }
        EqApp {
            cmd_tx,
            evt_rx,
            connected: false,
            bands,
            cur_preset: -1,
            logs: vec!["就绪。请点击\"连接设备\"。".into()],
            last_send: [Instant::now(); BAND_COUNT],
            save_slot: 1,
        }
    }

    fn log(&mut self, s: impl Into<String>) {
        self.logs.push(s.into());
        if self.logs.len() > 200 {
            self.logs.remove(0);
        }
    }

    fn drain_events(&mut self) {
        while let Ok(evt) = self.evt_rx.try_recv() {
            match evt {
                Evt::Log(s) => self.log(s),
                Evt::Connected(c) => {
                    self.connected = c;
                    self.log(if c { "设备已连接" } else { "设备已断开" });
                }
                Evt::State { bands } => {
                    // 设备回传 7 段参数直接载入滑块; 预设归为"自定义"
                    // (PC 无法从设备系数反推是哪个预设)。
                    self.cur_preset = -1;
                    self.bands = bands;
                    self.log("已同步设备当前 EQ 状态");
                }
            }
        }
    }
}

fn setup_fonts(ctx: &egui::Context) {
    let mut fonts = egui::FontDefinitions::default();
    fonts.font_data.insert(
        "OPPOSans".to_owned(),
        egui::FontData::from_static(include_bytes!("../fonts/OPPOSans-Regular.ttf")),
    );
    fonts.families.entry(egui::FontFamily::Proportional).or_default().insert(0, "OPPOSans".to_owned());
    fonts.families.entry(egui::FontFamily::Monospace).or_default().insert(0, "OPPOSans".to_owned());
    ctx.set_fonts(fonts);
}

fn main() -> eframe::Result<()> {
    let (cmd_tx, cmd_rx) = mpsc::channel::<Cmd>();
    let (evt_tx, evt_rx) = mpsc::channel::<Evt>();
    thread::spawn(move || worker_thread(cmd_rx, evt_tx));

    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default().with_inner_size([960.0, 680.0]),
        ..Default::default()
    };
    eframe::run_native(
        "STA350BW 均衡器调音工具",
        options,
        Box::new(move |cc| {
            setup_fonts(&cc.egui_ctx);
            Box::new(EqApp::new(cmd_tx, evt_rx))
        }),
    )
}

// PLACEHOLDER_UI

impl eframe::App for EqApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        self.drain_events();
        ctx.request_repaint_after(Duration::from_millis(50));

        // ===== 顶部: 连接 =====
        egui::TopBottomPanel::top("top").show(ctx, |ui| {
            ui.add_space(6.0);
            ui.horizontal(|ui| {
                ui.heading("STA350BW 均衡器");
                ui.separator();
                let status = if self.connected { "● 已连接" } else { "○ 未连接" };
                let color = if self.connected {
                    egui::Color32::from_rgb(80, 200, 120)
                } else {
                    egui::Color32::GRAY
                };
                ui.colored_label(color, status);
                ui.with_layout(egui::Layout::right_to_left(egui::Align::Center), |ui| {
                    if self.connected {
                        if ui.button("断开").clicked() {
                            let _ = self.cmd_tx.send(Cmd::Disconnect);
                        }
                        if ui.button("读取设备状态").clicked() {
                            let _ = self.cmd_tx.send(Cmd::Query);
                        }
                    } else if ui.button("连接设备").clicked() {
                        let _ = self.cmd_tx.send(Cmd::Connect);
                    }
                });
            });
            ui.add_space(6.0);
        });

        // ===== 底部: 日志 =====
        egui::TopBottomPanel::bottom("log").resizable(true).default_height(120.0).show(ctx, |ui| {
            ui.add_space(4.0);
            ui.label("日志");
            egui::ScrollArea::vertical().stick_to_bottom(true).show(ui, |ui| {
                for l in &self.logs {
                    ui.monospace(l);
                }
            });
        });

        // ===== 中央: 预设 + 7 段 EQ =====
        egui::CentralPanel::default().show(ctx, |ui| {
            self.ui_presets(ui);
            ui.separator();
            self.ui_bands(ui);
        });
    }
}

// PLACEHOLDER_UI2

impl EqApp {
    fn ui_presets(&mut self, ui: &mut egui::Ui) {
        ui.add_space(6.0);
        ui.horizontal_wrapped(|ui| {
            ui.label("预设:");
            for (idx, p) in PRESETS.iter().enumerate() {
                let selected = self.cur_preset == idx as i32;
                if ui.selectable_label(selected, p.name).clicked() {
                    self.apply_preset(idx);
                }
            }
        });
        ui.add_space(4.0);
        ui.horizontal(|ui| {
            if ui.button("全部清平 (0dB)").clicked() {
                for b in self.bands.iter_mut() {
                    b.gain = 0;
                }
                self.cur_preset = -1;
                let _ = self.cmd_tx.send(Cmd::Flat);
                self.log("EQ 全部清平");
            }
            ui.separator();
            ui.label("保存到槽位:");
            ui.add(egui::DragValue::new(&mut self.save_slot).clamp_range(1..=3));
            if ui.button("保存").clicked() {
                let _ = self.cmd_tx.send(Cmd::Save(self.save_slot));
                self.log(format!("保存当前 EQ 到 USER{}", self.save_slot));
            }
        });
    }

    /// 点击预设: 把该预设的 7 段参数加载到本地滑块(曲线/数字随之更新),
    /// 并逐段下发给设备。之后用户可在此基础继续微调、再保存。
    fn apply_preset(&mut self, idx: usize) {
        if idx >= PRESETS.len() {
            return;
        }
        let p = &PRESETS[idx];
        for i in 0..BAND_COUNT {
            self.bands[i].freq = DEFAULT_FREQS[i];
            self.bands[i].gain = p.gains[i];
            self.bands[i].q = 100; // Q=1.0
        }
        self.cur_preset = idx as i32;
        // 逐段下发(逐段 SET_BAND, 设备侧去抖合并)
        for i in 0..BAND_COUNT {
            let _ = self.cmd_tx.send(Cmd::SetBand(i as u8, self.bands[i]));
        }
        self.log(format!("加载预设: {} (可继续微调)", p.name));
    }

    // PLACEHOLDER_BANDS

    fn ui_bands(&mut self, ui: &mut egui::Ui) {
        ui.add_space(4.0);
        ui.label(egui::RichText::new("4 段参数均衡器").strong());
        ui.label(
            egui::RichText::new("左右声道独立, 每段可调 频率 / 增益 / Q 值")
                .small()
                .color(egui::Color32::GRAY),
        );
        ui.add_space(4.0);

        // 频响曲线
        self.ui_curve(ui);
        ui.add_space(8.0);

        // 7 段竖直滑块
        ui.horizontal(|ui| {
            for i in 0..BAND_COUNT {
                let mut changed = false;
                ui.vertical(|ui| {
                    ui.set_width(118.0);
                    // 频段标题
                    let fl = if self.bands[i].freq >= 1000 {
                        format!("{:.1}k", self.bands[i].freq as f32 / 1000.0)
                    } else {
                        format!("{}Hz", self.bands[i].freq)
                    };
                    ui.label(egui::RichText::new(format!("段{} {}", i + 1, fl)).strong());

                    // 增益竖直滑块 (-12 ~ +12 dB)
                    let mut gain_db = self.bands[i].gain as f32 / 10.0;
                    if ui
                        .add(
                            egui::Slider::new(&mut gain_db, -12.0..=12.0)
                                .vertical()
                                .text("dB")
                                .fixed_decimals(1),
                        )
                        .changed()
                    {
                        self.bands[i].gain = (gain_db * 10.0) as i16;
                        changed = true;
                    }

                    // 频率
                    let mut f = self.bands[i].freq as f32;
                    if ui
                        .add(egui::Slider::new(&mut f, 20.0..=20000.0).logarithmic(true).text("Hz"))
                        .changed()
                    {
                        self.bands[i].freq = f as u16;
                        changed = true;
                    }
                    // Q
                    let mut q = self.bands[i].q as f32 / 100.0;
                    if ui
                        .add(egui::Slider::new(&mut q, 0.3..=8.0).text("Q").fixed_decimals(2))
                        .changed()
                    {
                        self.bands[i].q = (q * 100.0) as u16;
                        changed = true;
                    }
                });

                // 去抖发送: 同段 30ms 内多次拖动只发最新
                if changed {
                    self.cur_preset = -1; // 手动调过即变为自定义
                    if self.last_send[i].elapsed() >= Duration::from_millis(30) {
                        let _ = self.cmd_tx.send(Cmd::SetBand(i as u8, self.bands[i]));
                        self.last_send[i] = Instant::now();
                    }
                }
                // 拖动结束(松手)补发一帧, 保证最终值送达
                if ui.input(|inp| inp.pointer.any_released()) {
                    let _ = self.cmd_tx.send(Cmd::SetBand(i as u8, self.bands[i]));
                }
            }
        });
    }

    // PLACEHOLDER_CURVE

    /// 绘制 7 段叠加的频响曲线(20Hz~20kHz 对数横轴, ±15dB 纵轴)
    fn ui_curve(&self, ui: &mut egui::Ui) {
        let desired = egui::vec2(ui.available_width(), 160.0);
        let (rect, _resp) = ui.allocate_exact_size(desired, egui::Sense::hover());
        let painter = ui.painter().with_clip_rect(rect);

        // 背景
        painter.rect_filled(rect, 4.0, egui::Color32::from_rgb(28, 30, 36));

        let fmin = 20.0_f32.ln();
        let fmax = 20000.0_f32.ln();
        let db_range = 15.0_f32;

        let x_of = |f: f32| -> f32 {
            let t = (f.ln() - fmin) / (fmax - fmin);
            rect.left() + t * rect.width()
        };
        let y_of = |db: f32| -> f32 {
            let t = (db + db_range) / (2.0 * db_range);
            rect.bottom() - t * rect.height()
        };

        // 网格: 0dB 中线 + 频率刻度
        let zero = y_of(0.0);
        painter.line_segment(
            [egui::pos2(rect.left(), zero), egui::pos2(rect.right(), zero)],
            egui::Stroke::new(1.0, egui::Color32::from_gray(70)),
        );
        for &f in &[100.0, 1000.0, 10000.0] {
            let x = x_of(f);
            painter.line_segment(
                [egui::pos2(x, rect.top()), egui::pos2(x, rect.bottom())],
                egui::Stroke::new(1.0, egui::Color32::from_gray(55)),
            );
            let lbl = if f >= 1000.0 { format!("{}k", f as i32 / 1000) } else { format!("{}", f as i32) };
            painter.text(
                egui::pos2(x + 2.0, rect.bottom() - 14.0),
                egui::Align2::LEFT_BOTTOM,
                lbl,
                egui::FontId::monospace(11.0),
                egui::Color32::GRAY,
            );
        }

        // 计算合成频响曲线
        let n = 160usize;
        let mut pts = Vec::with_capacity(n);
        for i in 0..n {
            let t = i as f32 / (n - 1) as f32;
            let f = (fmin + t * (fmax - fmin)).exp();
            let mut db = 0.0f32;
            for b in &self.bands {
                db += peak_gain_db(f, b.freq as f32, b.gain as f32 / 10.0, b.q as f32 / 100.0);
            }
            db = db.clamp(-db_range, db_range);
            pts.push(egui::pos2(x_of(f), y_of(db)));
        }
        painter.add(egui::Shape::line(pts, egui::Stroke::new(2.0, egui::Color32::from_rgb(100, 180, 255))));
    }
}

/// 单段 peak 滤波器在频率 f 处的增益(dB), 近似 RBJ peaking EQ 幅频响应
fn peak_gain_db(f: f32, fc: f32, gain_db: f32, q: f32) -> f32 {
    if gain_db.abs() < 0.01 {
        return 0.0;
    }
    let a = 10f32.powf(gain_db / 40.0); // sqrt(A)
    let w = f / fc;
    // 简化的对称 bell 形状: 在 fc 处=gain_db, 远离按 Q 衰减
    let bw = (w.ln()).abs() * q;
    let shape = 1.0 / (1.0 + bw * bw);
    let g = 20.0 * (a * a).log10() * shape;
    let _ = a;
    g
}






