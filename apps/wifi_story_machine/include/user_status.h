#ifndef USER_STATUS_H
#define USER_STATUS_H


#include <stdint.h>

/*******************************************************************************
**************************空间定义 ********************************
******************************************************************************/

#define RET_STATUS_SPACE_MASK              ((ret_status_t)0xFF00)

#define RET_STATUS_GENERIC_SPACE           ((ret_status_t)0x0000)
#define RET_STATUS_WIFI_SPACE              ((ret_status_t)0x0B00)

/*******************************************************************************
**************************状态定义 ********************************
******************************************************************************/
/*******************************************************************************
**************************一般错误 ********************************
******************************************************************************/

#define RET_STATUS_OK    ((ret_status_t)0x0000)///< 没有错误。
#define RET_STATUS_FAIL  ((ret_status_t)0x0001)///< 一般错误。

//状态错误
#define RET_STATUS_INVALID_STATE         ((ret_status_t)0x0002)///< 一般无效状态错误。
#define RET_STATUS_NOT_READY             ((ret_status_t)0x0003)///< 模块尚未准备好执行请求的操作。
#define RET_STATUS_BUSY                  ((ret_status_t)0x0004)///< 模块正忙，无法执行请求的操作。
#define RET_STATUS_IN_PROGRESS           ((ret_status_t)0x0005)///< 操作正在进行中且尚未完成（通过或失败）。
#define RET_STATUS_ABORT                 ((ret_status_t)0x0006)///< 操作已中止。
#define RET_STATUS_TIMEOUT               ((ret_status_t)0x0007)///< 操作超时。
#define RET_STATUS_PERMISSION            ((ret_status_t)0x0008)///< 每个权限不允许操作。
#define RET_STATUS_WOULD_BLOCK           ((ret_status_t)0x0009)///< 非阻塞操作会阻塞。
#define RET_STATUS_IDLE                  ((ret_status_t)0x000A)///< 操作/模块空闲，无法进行请求的操作。
#define RET_STATUS_IS_WAITING            ((ret_status_t)0x000B)///< 构造等待时无法完成操作。
#define RET_STATUS_NONE_WAITING          ((ret_status_t)0x000C)///< 没有任务/构造正在等待/挂起该操作/事件。
#define RET_STATUS_SUSPENDED             ((ret_status_t)0x000D)///< 构造挂起时无法执行操作。
#define RET_STATUS_NOT_AVAILABLE         ((ret_status_t)0x000E)///< 由于软件配置原因，功能不可用。
#define RET_STATUS_NOT_SUPPORTED         ((ret_status_t)0x000F)///< 不支持该功能。
#define RET_STATUS_INITIALIZATION        ((ret_status_t)0x0010)///< 初始化失败。
#define RET_STATUS_NOT_INITIALIZED       ((ret_status_t)0x0011)///< 模块尚未初始化。
#define RET_STATUS_ALREADY_INITIALIZED   ((ret_status_t)0x0012)///< 模块已经初始化。
#define RET_STATUS_DELETED               ((ret_status_t)0x0013)///< 对象/构造已被删除。
#define RET_STATUS_ISR                   ((ret_status_t)0x0014)///< 来自 ISR 的非法呼叫。
#define RET_STATUS_NETWORK_UP            ((ret_status_t)0x0015)///< 非法调用，因为网络已启动。
#define RET_STATUS_NETWORK_DOWN          ((ret_status_t)0x0016)///< 非法调用，因为网络已关闭。
#define RET_STATUS_NOT_JOINED            ((ret_status_t)0x0017)///< 由于未加入网络而失败。
#define RET_STATUS_NO_BEACONS            ((ret_status_t)0x0018)///< 无效操作，因为没有信标。

//分配/所有权错误
#define RET_STATUS_ALLOCATION_FAILED   ((ret_status_t)0x0019)///< 一般分配错误。
#define RET_STATUS_NO_MORE_RESOURCE    ((ret_status_t)0x001A)///< 没有更多资源可用于执行该操作。
#define RET_STATUS_EMPTY               ((ret_status_t)0x001B)///< 项目/列表/队列为空。
#define RET_STATUS_FULL                ((ret_status_t)0x001C)///< 项目/列表/队列已满。
#define RET_STATUS_WOULD_OVERFLOW      ((ret_status_t)0x001D)///< 项目会溢出。
#define RET_STATUS_HAS_OVERFLOWED      ((ret_status_t)0x001E)///< 项目/列表/队列已溢出。
#define RET_STATUS_OWNERSHIP           ((ret_status_t)0x001F)///< 一般所有权错误。
#define RET_STATUS_IS_OWNER            ((ret_status_t)0x0020)///< 已经/仍然拥有资源。

//无效参数错误
#define RET_STATUS_INVALID_PARAMETER       ((ret_status_t)0x0021)///< 通用无效参数或无效参数的结果。
#define RET_STATUS_NULL_POINTER            ((ret_status_t)0x0022)///< 作为参数接收的无效空指针。
#define RET_STATUS_INVALID_CONFIGURATION   ((ret_status_t)0x0023)///< 提供的配置无效。
#define RET_STATUS_INVALID_MODE            ((ret_status_t)0x0024)///< 无效模式。
#define RET_STATUS_INVALID_HANDLE          ((ret_status_t)0x0025)///< 无效句柄。
#define RET_STATUS_INVALID_TYPE            ((ret_status_t)0x0026)///< 操作类型无效。
#define RET_STATUS_INVALID_INDEX           ((ret_status_t)0x0027)///< 无效索引。
#define RET_STATUS_INVALID_RANGE           ((ret_status_t)0x0028)///< 无效范围。
#define RET_STATUS_INVALID_KEY             ((ret_status_t)0x0029)///< 无效密钥。
#define RET_STATUS_INVALID_CREDENTIALS     ((ret_status_t)0x002A)///< 凭证无效。
#define RET_STATUS_INVALID_COUNT           ((ret_status_t)0x002B)///< 无效计数。
#define RET_STATUS_NOT_FOUND               ((ret_status_t)0x002C)///< 找不到项目。
#define RET_STATUS_ALREADY_EXISTS          ((ret_status_t)0x002D)///< 项目已存在。

//IO/通信错误
#define RET_STATUS_IO                    ((ret_status_t)0x002E)///< 一般 I/O 故障。
#define RET_STATUS_IO_TIMEOUT            ((ret_status_t)0x002F)///< 由于超时导致 I/O 失败。
#define RET_STATUS_TRANSMIT              ((ret_status_t)0x0030)///< 一般传输错误。
#define RET_STATUS_TRANSMIT_UNDERFLOW    ((ret_status_t)0x0031)///< 传输下溢。
#define RET_STATUS_TRANSMIT_INCOMPLETE   ((ret_status_t)0x0032)///< 传输不完整。
#define RET_STATUS_TRANSMIT_BUSY         ((ret_status_t)0x0033)///< 传输正忙。
#define RET_STATUS_RECEIVE               ((ret_status_t)0x0034)///< 一般接收错误。
#define RET_STATUS_OBJECT_READ           ((ret_status_t)0x0035)///< 无法通过给定对象读取。
#define RET_STATUS_OBJECT_WRITE          ((ret_status_t)0x0036)///< 无法通过给定对象写入。
#define RET_STATUS_MESSAGE_TOO_LONG      ((ret_status_t)0x0037)///< 消息太长。

//EEPROM/闪存错误
#define RET_STATUS_EEPROM_MFG_VERSION_MISMATCH     ((ret_status_t)0x0038)///<
#define RET_STATUS_EEPROM_STACK_VERSION_MISMATCH   ((ret_status_t)0x0039)///<
#define RET_STATUS_FLASH_WRITE_INHIBITED           ((ret_status_t)0x003A)///< 闪存写入被禁止。
#define RET_STATUS_FLASH_VERIFY_FAILED             ((ret_status_t)0x003B)///< 闪存验证失败。
#define RET_STATUS_FLASH_PROGRAM_FAILED            ((ret_status_t)0x003C)///< 闪存编程失败。
#define RET_STATUS_FLASH_ERASE_FAILED              ((ret_status_t)0x003D)///< 闪存擦除失败。

//MAC错误
#define RET_STATUS_MAC_NO_DATA                   ((ret_status_t)0x003E)///<
#define RET_STATUS_MAC_NO_ACK_RECEIVED           ((ret_status_t)0x003F)///<
#define RET_STATUS_MAC_INDIRECT_TIMEOUT          ((ret_status_t)0x0040)///<
#define RET_STATUS_MAC_UNKNOWN_HEADER_TYPE       ((ret_status_t)0x0041)///<
#define RET_STATUS_MAC_ACK_HEADER_TYPE           ((ret_status_t)0x0042)///<
#define RET_STATUS_MAC_COMMAND_TRANSMIT_FAILURE  ((ret_status_t)0x0043)///<

//CLI_STORAGE 错误
#define RET_STATUS_CLI_STORAGE_NVM_OPEN_ERROR    ((ret_status_t)0x0044)///< 打开 NVM 时出错

//安全状态代码
#define RET_STATUS_SECURITY_IMAGE_CHECKSUM_ERROR ((ret_status_t)0x0045)///< 图像校验和无效。
#define RET_STATUS_SECURITY_DECRYPT_ERROR        ((ret_status_t)0x0046)///< 解密失败

//命令状态码
#define RET_STATUS_COMMAND_IS_INVALID            ((ret_status_t)0x0047)///< 命令未被识别
#define RET_STATUS_COMMAND_TOO_LONG              ((ret_status_t)0x0048)///< 超出命令最大长度
#define RET_STATUS_COMMAND_INCOMPLETE            ((ret_status_t)0x0049)///< 接收到的数据不构成完整的命令

/*******************************************************************************
******************************无线网络错误 ******************************
******************************************************************************/

#define RET_STATUS_WIFI_INVALID_KEY                         ((ret_status_t)0x0B01)///< 无效的固件密钥集
#define RET_STATUS_WIFI_FIRMWARE_DOWNLOAD_TIMEOUT           ((ret_status_t)0x0B02)///< 固件下载时间太长
#define RET_STATUS_WIFI_UNSUPPORTED_MESSAGE_ID              ((ret_status_t)0x0B03)///< 未知的请求 ID 或使用了错误的接口 ID
#define RET_STATUS_WIFI_WARNING                             ((ret_status_t)0x0B04)///< 请求成功但部分参数被忽略
#define RET_STATUS_WIFI_NO_PACKET_TO_RECEIVE                ((ret_status_t)0x0B05)///< 没有等待接收的数据包
#define RET_STATUS_WIFI_RETEEP_GRANTED                       ((ret_status_t)0x0B08)///< 授予睡眠模式
#define RET_STATUS_WIFI_RETEEP_NOT_GRANTED                   ((ret_status_t)0x0B09)///< WFx 不会返回休眠状态
#define RET_STATUS_WIFI_SECURE_LINK_MAC_KEY_ERROR           ((ret_status_t)0x0B10)///< 未找到 SecureLink MAC 密钥
#define RET_STATUS_WIFI_SECURE_LINK_MAC_KEY_ALREADY_BURNED  ((ret_status_t)0x0B11)///< SecureLink MAC 密钥已安装在 OTP 中
#define RET_STATUS_WIFI_SECURE_LINK_RAM_MODE_NOT_ALLOWED    ((ret_status_t)0x0B12)///< SecureLink MAC 密钥无法安装在 RAM 中
#define RET_STATUS_WIFI_SECURE_LINK_FAILED_UNKNOWN_MODE     ((ret_status_t)0x0B13)///< SecureLink MAC 密钥安装失败
#define RET_STATUS_WIFI_SECURE_LINK_EXCHANGE_FAILED         ((ret_status_t)0x0B14)///< SecureLink 密钥（重新）协商失败
#define RET_STATUS_WIFI_WRONG_STATE                         ((ret_status_t)0x0B18)///< 设备处于不适合执行请求的状态
#define RET_STATUS_WIFI_CHANNEL_NOT_ALLOWED                 ((ret_status_t)0x0B19)///< 由于监管限制，请求失败
#define RET_STATUS_WIFI_NO_MATCHING_AP                      ((ret_status_t)0x0B1A)///< 连接请求失败，因为没有找到合适的AP
#define RET_STATUS_WIFI_CONNECTION_ABORTED                  ((ret_status_t)0x0B1B)///< 连接请求被主机中止
#define RET_STATUS_WIFI_CONNECTION_TIMEOUT                  ((ret_status_t)0x0B1C)///< 由于超时，连接请求失败
#define RET_STATUS_WIFI_CONNECTION_REJECTED_BY_AP           ((ret_status_t)0x0B1D)///< 连接请求失败，因为 AP 拒绝了设备
#define RET_STATUS_WIFI_CONNECTION_AUTH_FAILURE             ((ret_status_t)0x0B1E)///< 连接请求失败，因为 WPA 握手未成功完成
#define RET_STATUS_WIFI_RETRY_EXCEEDED                      ((ret_status_t)0x0B1F)///< 请求失败，因为超出了重试限制
#define RET_STATUS_WIFI_TX_LIFETIME_EXCEEDED                ((ret_status_t)0x0B20)///< 请求失败，因为超出了 MSDU 生存时间

/*******************************************************************************
******************************数据类型 ******************************
******************************************************************************/

typedef uint32_t ret_status_t;

/*******************************************************************************
********************************  功能   *******************************
******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

//未来字符串函数的占位符。

#ifdef __cplusplus
}
#endif


#endif/*USER_STATUS_H*/
