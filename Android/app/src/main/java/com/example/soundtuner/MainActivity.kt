package com.example.soundtuner

import android.Manifest
import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothGatt
import android.bluetooth.BluetoothGattCallback
import android.bluetooth.BluetoothGattCharacteristic
import android.bluetooth.BluetoothGattDescriptor
import android.bluetooth.BluetoothManager
import android.bluetooth.BluetoothProfile
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanResult
import android.content.Context
import android.os.Build
import android.os.Bundle
import android.os.SystemClock
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Slider
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.DisposableEffect
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.google.accompanist.permissions.ExperimentalPermissionsApi
import com.google.accompanist.permissions.rememberMultiplePermissionsState
import java.util.UUID
import kotlin.math.roundToInt

private const val TARGET_DEVICE_NAME = "NiShuGong_AMP(BLE)"
private const val TARGET_DEVICE_NAME_FALLBACK = "NiShuGong_AMP_BLE"
private val TARGET_DEVICE_NAMES = setOf(TARGET_DEVICE_NAME, TARGET_DEVICE_NAME_FALLBACK)

private fun uuidFrom16Bit(uuid16: String): UUID {
    val clean = uuid16.lowercase().padStart(4, '0')
    return UUID.fromString("0000$clean-0000-1000-8000-00805f9b34fb")
}

private val SOUND_TUNER_SERVICE_UUID = uuidFrom16Bit("ae3a")
private val EQ_COMMAND_CHARACTERISTIC_UUID = uuidFrom16Bit("ae3b")
private val EQ_NOTIFY_CHARACTERISTIC_UUID = uuidFrom16Bit("ae3c")
private val CCC_DESCRIPTOR_UUID = UUID.fromString("00002902-0000-1000-8000-00805f9b34fb")

@SuppressLint("MissingPermission")
@ExperimentalPermissionsApi
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            SoundTunerTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    RequestBluetoothPermissions {
                        SoundTunerApp()
                    }
                }
            }
        }
    }
}

@SuppressLint("MissingPermission")
@Composable
fun SoundTunerApp() {
    val context = LocalContext.current
    val bluetoothAdapter: BluetoothAdapter? by lazy {
        val bluetoothManager = context.getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        bluetoothManager.adapter
    }

    var isScanning by remember { mutableStateOf(false) }
    var isConnecting by remember { mutableStateOf(false) }
    var discoveredDevices by remember { mutableStateOf<List<BluetoothDevice>>(emptyList()) }
    var connectedGatt by remember { mutableStateOf<BluetoothGatt?>(null) }
    var commandCharacteristic by remember { mutableStateOf<BluetoothGattCharacteristic?>(null) }
    // ae3c notify 回传的最新查询结果, 用于同步 UI 滑块
    var lastQueryResult by remember { mutableStateOf<EqProtocol.QueryResult?>(null) }

    fun isTargetDeviceName(name: String?): Boolean {
        val trimmed = name?.trim() ?: return false
        return TARGET_DEVICE_NAMES.contains(trimmed)
    }

    // 统一字节写入 (Android 13+ 新 API 与旧 API 两条分支)
    fun writeBytes(
        gatt: BluetoothGatt,
        characteristic: BluetoothGattCharacteristic,
        bytes: ByteArray
    ) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
            gatt.writeCharacteristic(
                characteristic,
                bytes,
                BluetoothGattCharacteristic.WRITE_TYPE_NO_RESPONSE
            )
        } else {
            @Suppress("DEPRECATION")
            characteristic.writeType = BluetoothGattCharacteristic.WRITE_TYPE_NO_RESPONSE
            @Suppress("DEPRECATION")
            characteristic.value = bytes
            @Suppress("DEPRECATION")
            gatt.writeCharacteristic(characteristic)
        }
    }

    val gattCallback = remember {
        object : BluetoothGattCallback() {
            override fun onConnectionStateChange(gatt: BluetoothGatt, status: Int, newState: Int) {
                if (newState == BluetoothProfile.STATE_CONNECTED) {
                    Log.i("BLE", "Connected to GATT server.")
                    connectedGatt = gatt
                    isConnecting = false
                    isScanning = false
                    gatt.discoverServices()
                } else if (newState == BluetoothProfile.STATE_DISCONNECTED) {
                    Log.i("BLE", "Disconnected from GATT server.")
                    connectedGatt = null
                    commandCharacteristic = null
                    isConnecting = false
                }
            }

            override fun onServicesDiscovered(gatt: BluetoothGatt, status: Int) {
                if (status == BluetoothGatt.GATT_SUCCESS) {
                    val service = gatt.getService(SOUND_TUNER_SERVICE_UUID)
                    if (service == null) {
                        Log.e("BLE", "Sound Tuner service not found")
                        return
                    }
                    val characteristic = service.getCharacteristic(EQ_COMMAND_CHARACTERISTIC_UUID)
                    if (characteristic == null) {
                        Log.e("BLE", "EQ Command characteristic not found")
                    } else {
                        Log.i("BLE", "Service and characteristic found!")
                        commandCharacteristic = characteristic
                    }

                    // 订阅 ae3c 通知: setCharacteristicNotification + 写 CCC descriptor
                    val notifyChar = service.getCharacteristic(EQ_NOTIFY_CHARACTERISTIC_UUID)
                    if (notifyChar == null) {
                        Log.w("BLE", "EQ Notify characteristic (ae3c) not found")
                    } else {
                        gatt.setCharacteristicNotification(notifyChar, true)
                        val ccc = notifyChar.getDescriptor(CCC_DESCRIPTOR_UUID)
                        if (ccc != null) {
                            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
                                gatt.writeDescriptor(
                                    ccc,
                                    BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE
                                )
                            } else {
                                @Suppress("DEPRECATION")
                                run {
                                    ccc.value = BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE
                                    gatt.writeDescriptor(ccc)
                                }
                            }
                        } else {
                            Log.w("BLE", "CCC descriptor not found on ae3c")
                        }
                    }
                } else {
                    Log.w("BLE", "onServicesDiscovered received: $status")
                }
            }

            // 通知回传后, 主动发一次 QUERY 拉取当前状态 (确保 descriptor 已使能)
            override fun onDescriptorWrite(
                gatt: BluetoothGatt,
                descriptor: BluetoothGattDescriptor,
                status: Int
            ) {
                if (descriptor.uuid == CCC_DESCRIPTOR_UUID) {
                    commandCharacteristic?.let { writeBytes(gatt, it, EqProtocol.buildQuery()) }
                }
            }

            // Android 13+ 新回调
            override fun onCharacteristicChanged(
                gatt: BluetoothGatt,
                characteristic: BluetoothGattCharacteristic,
                value: ByteArray
            ) {
                if (characteristic.uuid == EQ_NOTIFY_CHARACTERISTIC_UUID) {
                    EqProtocol.parseQueryResponse(value)?.let { lastQueryResult = it }
                }
            }

            // 旧 API 回调
            @Deprecated("Deprecated in Java")
            @Suppress("DEPRECATION")
            override fun onCharacteristicChanged(
                gatt: BluetoothGatt,
                characteristic: BluetoothGattCharacteristic
            ) {
                if (characteristic.uuid == EQ_NOTIFY_CHARACTERISTIC_UUID) {
                    val value = characteristic.value ?: return
                    EqProtocol.parseQueryResponse(value)?.let { lastQueryResult = it }
                }
            }
        }
    }

    val scanCallback = remember {
        object : ScanCallback() {
            override fun onScanResult(callbackType: Int, result: ScanResult) {
                val deviceName = result.device.name ?: result.scanRecord?.deviceName
                if (!isTargetDeviceName(deviceName)) {
                    return
                }

                if (!discoveredDevices.any { it.address == result.device.address }) {
                    discoveredDevices = discoveredDevices + result.device
                }

                if (commandCharacteristic == null && !isConnecting) {
                    isConnecting = true
                    bluetoothAdapter?.bluetoothLeScanner?.stopScan(this)
                    result.device.connectGatt(context, false, gattCallback)
                }
            }

            override fun onScanFailed(errorCode: Int) {
                Log.e("BLE", "Scan failed with error code: $errorCode")
                isScanning = false
                isConnecting = false
            }
        }
    }

    DisposableEffect(Unit) {
        onDispose {
            bluetoothAdapter?.bluetoothLeScanner?.stopScan(scanCallback)
            connectedGatt?.close()
        }
    }

    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(16.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        if (commandCharacteristic == null) {
            Text(text = "Target: $TARGET_DEVICE_NAME", style = MaterialTheme.typography.titleMedium)
            Spacer(modifier = Modifier.height(8.dp))
            Text(
                text = if (isConnecting) "Connecting..." else "Not connected",
                style = MaterialTheme.typography.bodyMedium
            )

            Spacer(modifier = Modifier.height(16.dp))

            Button(
                onClick = {
                    if (!isScanning) {
                        discoveredDevices = emptyList()
                        bluetoothAdapter?.bluetoothLeScanner?.startScan(scanCallback)
                    } else {
                        bluetoothAdapter?.bluetoothLeScanner?.stopScan(scanCallback)
                    }
                    isScanning = !isScanning
                },
                modifier = Modifier.fillMaxWidth()
            ) {
                Text(if (isScanning) "Stop Scan" else "Start Scan")
            }

            Spacer(modifier = Modifier.height(16.dp))

            LazyColumn(modifier = Modifier.fillMaxWidth()) {
                items(discoveredDevices) { device ->
                    DeviceListItem(device = device) {
                        bluetoothAdapter?.bluetoothLeScanner?.stopScan(scanCallback)
                        isScanning = false
                        isConnecting = true
                        device.connectGatt(context, false, gattCallback)
                    }
                }
            }
        } else {
            ControlPanel(
                deviceName = connectedGatt?.device?.name ?: "Unknown Device",
                queryResult = lastQueryResult,
                onSendCommand = { command ->
                    val characteristic = commandCharacteristic
                    val gatt = connectedGatt
                    if (characteristic != null && gatt != null) {
                        Log.d("BLE_COMMAND", "Sending ${command.size} bytes: " +
                                command.joinToString(" ") { "%02X".format(it.toInt() and 0xFF) })
                        writeBytes(gatt, characteristic, command)
                    }
                },
                onDisconnect = {
                    connectedGatt?.disconnect()
                }
            )
        }
    }
}

@SuppressLint("MissingPermission")
@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun DeviceListItem(device: BluetoothDevice, onClick: () -> Unit) {
    Card(
        modifier = Modifier
            .fillMaxWidth()
            .padding(vertical = 4.dp),
        onClick = onClick
    ) {
        Column(modifier = Modifier.padding(16.dp)) {
            Text(text = device.name ?: "Unknown Device", style = MaterialTheme.typography.titleMedium)
            Text(text = device.address, style = MaterialTheme.typography.bodySmall)
        }
    }
}

@Composable
fun ControlPanel(
    deviceName: String,
    queryResult: EqProtocol.QueryResult?,
    onSendCommand: (ByteArray) -> Unit,
    onDisconnect: () -> Unit
) {
    val presetNames = listOf(
        "FLAT", "ROCK", "SOFT", "JAZZ", "CLASSICAL", "DANCE", "POP", "SOFT_ROCK",
        "HARD", "PARTY", "VOCAL", "HIPHOP", "DIALOG", "BASS_BOOST1", "BASS_BOOST2", "BASS_BOOST3"
    )
    val userPresetNames = listOf("USER_1", "USER_2", "USER_3")
    val bypassNames = listOf("BYPASS_BIQ", "BYPASS_TONE")
    val bandLabels = listOf("125 Hz", "500 Hz", "2 kHz", "8 kHz")
    val bandGains = remember { mutableStateListOf(0f, 0f, 0f, 0f) }
    val scrollState = rememberScrollState()

    // 每段独立的节流时间戳, 实时拖动时 ~80ms 发一次 SET_BAND
    val lastSentAt = remember { LongArray(EqProtocol.BAND_COUNT) }
    val throttleMs = 80L

    fun presetIdOf(name: String): Int = EqProtocol.PRESET_IDS[name] ?: EqProtocol.PRESET_IDS["FLAT"]!!

    // ae3c notify 回传后, 把固件当前增益同步到 UI 滑块 (tenths -> dB)
    LaunchedEffect(queryResult) {
        queryResult?.let { result ->
            for (i in 0 until EqProtocol.BAND_COUNT) {
                if (i < bandGains.size) {
                    bandGains[i] = result.gainsTenths[i] / 10f
                }
            }
        }
    }

    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(scrollState),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(text = "Connected to: $deviceName", style = MaterialTheme.typography.titleLarge)
        Spacer(modifier = Modifier.height(16.dp))

        PresetGrid(title = "Factory Presets", presets = presetNames) {
            onSendCommand(EqProtocol.buildPreset(presetIdOf(it)))
        }

        PresetGrid(title = "User Presets", presets = userPresetNames) {
            onSendCommand(EqProtocol.buildPreset(presetIdOf(it)))
        }

        PresetGrid(title = "Bypass", presets = bypassNames) {
            onSendCommand(EqProtocol.buildPreset(presetIdOf(it)))
        }

        Spacer(modifier = Modifier.height(8.dp))
        Text(text = "Parametric EQ", style = MaterialTheme.typography.titleMedium)
        Spacer(modifier = Modifier.height(8.dp))

        bandGains.forEachIndexed { index, gain ->
            EqBandSlider(
                label = bandLabels[index],
                gainDb = gain,
                onGainChange = { newGain ->
                    bandGains[index] = newGain
                    // 实时拖动节流: 单段发送 SET_BAND
                    val now = SystemClock.uptimeMillis()
                    if (now - lastSentAt[index] >= throttleMs) {
                        lastSentAt[index] = now
                        onSendCommand(
                            EqProtocol.buildSetBand(index, (newGain * 10).roundToInt())
                        )
                    }
                },
                onGainChangeFinished = {
                    // 拖动结束补发一帧, 确保最终值落地
                    onSendCommand(
                        EqProtocol.buildSetBand(index, (bandGains[index] * 10).roundToInt())
                    )
                }
            )
        }

        Row(modifier = Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.SpaceBetween) {
            Button(
                modifier = Modifier.weight(1f),
                onClick = {
                    val gains = IntArray(EqProtocol.BAND_COUNT) {
                        if (it < bandGains.size) (bandGains[it] * 10).roundToInt() else 0
                    }
                    onSendCommand(EqProtocol.buildSetAll(gains))
                }
            ) {
                Text("Apply EQ")
            }
            Spacer(modifier = Modifier.width(8.dp))
            Button(
                modifier = Modifier.weight(1f),
                onClick = {
                    for (i in bandGains.indices) {
                        bandGains[i] = 0f
                    }
                    onSendCommand(EqProtocol.buildSetAll(intArrayOf(0, 0, 0, 0)))
                }
            ) {
                Text("Reset")
            }
        }

        Spacer(modifier = Modifier.height(12.dp))
        Text(text = "Save EQ to User Preset", style = MaterialTheme.typography.titleMedium)
        Spacer(modifier = Modifier.height(8.dp))

        Row(modifier = Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.SpaceBetween) {
            userPresetNames.forEachIndexed { idx, slot ->
                Button(
                    modifier = Modifier.weight(1f),
                    onClick = { onSendCommand(EqProtocol.buildSave(idx + 1)) }
                ) {
                    Text(slot)
                }
                if (slot != userPresetNames.last()) {
                    Spacer(modifier = Modifier.width(8.dp))
                }
            }
        }

        Spacer(modifier = Modifier.height(16.dp))
        Button(onClick = onDisconnect) {
            Text("Disconnect")
        }
    }
}

@Composable
private fun PresetGrid(title: String, presets: List<String>, onSelect: (String) -> Unit) {
    Text(text = title, style = MaterialTheme.typography.titleMedium)
    Spacer(modifier = Modifier.height(8.dp))

    val rows = presets.chunked(2)
    rows.forEach { rowItems ->
        Row(
            modifier = Modifier.fillMaxWidth(),
            horizontalArrangement = Arrangement.SpaceEvenly
        ) {
            rowItems.forEach { preset ->
                Button(
                    modifier = Modifier.padding(4.dp).weight(1f),
                    onClick = { onSelect(preset) }
                ) {
                    Text(text = preset)
                }
            }
            if (rowItems.size < 2) {
                Spacer(Modifier.weight(2f - rowItems.size))
            }
        }
    }
    Spacer(modifier = Modifier.height(12.dp))
}

@Composable
private fun EqBandSlider(
    label: String,
    gainDb: Float,
    onGainChange: (Float) -> Unit,
    onGainChangeFinished: () -> Unit = {}
) {
    Text(text = "$label  ${String.format("%.1f", gainDb)} dB", style = MaterialTheme.typography.bodyMedium)
    Slider(
        value = gainDb,
        onValueChange = onGainChange,
        onValueChangeFinished = onGainChangeFinished,
        valueRange = -12f..12f,
        steps = 47
    )
    Spacer(modifier = Modifier.height(4.dp))
}

@OptIn(ExperimentalPermissionsApi::class)
@Composable
fun RequestBluetoothPermissions(content: @Composable () -> Unit) {
    val context = LocalContext.current
    val isBleSupported = remember { context.packageManager.hasSystemFeature(android.content.pm.PackageManager.FEATURE_BLUETOOTH_LE) }

    if (!isBleSupported) {
        Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
            Text("BLE is not supported on this device.")
        }
        return
    }

    val permissions = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
        listOf(
            Manifest.permission.BLUETOOTH_SCAN,
            Manifest.permission.BLUETOOTH_CONNECT,
        )
    } else {
        listOf(
            Manifest.permission.BLUETOOTH,
            Manifest.permission.BLUETOOTH_ADMIN,
            Manifest.permission.ACCESS_FINE_LOCATION
        )
    }
    val permissionState = rememberMultiplePermissionsState(permissions = permissions)

    if (permissionState.allPermissionsGranted) {
        content()
    } else {
        LaunchedEffect(key1 = permissionState) {
            permissionState.launchMultiplePermissionRequest()
        }
        Column(
            modifier = Modifier.fillMaxSize(),
            verticalArrangement = Arrangement.Center,
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            Text("Bluetooth permissions are required to use this app.")
            Spacer(modifier = Modifier.height(8.dp))
            Button(onClick = { permissionState.launchMultiplePermissionRequest() }) {
                Text("Grant Permissions")
            }
        }
    }
}

@Composable
fun SoundTunerTheme(content: @Composable () -> Unit) {
    MaterialTheme {
        content()
    }
}

@Preview(showBackground = true)
@Composable
fun DefaultPreview() {
    SoundTunerTheme {
        ControlPanel("Test Device", null, {}, {})
    }
}
