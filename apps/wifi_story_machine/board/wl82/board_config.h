#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

/*
 *  板级配置选择，需要删去app_config.h中前面跟此头文件重复的宏定义，不然此头文件宏定义无效,只能打开一个, 不然会报错
 */

#define CONFIG_BOARD_7916AB


/*
 *  工程配置选择,只能打开一个, 不然会报错
 */
// #define CONFIG_BOARD_DUI
// #define CONFIG_BOARD_DEMO
#define CONFIG_BOARD_DEV_KIT
// #define CONFIG_BOARD_DEVELOP

//7916A
#define CONFIG_BOARD_7916A



//7916A
#include "board_7916AB_cfg.h"


#endif
