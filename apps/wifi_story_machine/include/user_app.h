#ifndef USER_APP_H_
#define USER_APP_H_

#include <string.h>
#include <stdlib.h>

#include "user_status.h"

#include "system/includes.h"
#include "os/os_api.h"
#include "system/task.h"
#include "system/init.h"

#include "asm/cpu.h"

#include "spp_user.h"
#include "bt_common.h"
#include "btstack/avctp_user.h"
#include "system/timer.h"
#include "system/sys_time.h"
#include "app_config.h"
#include "debug.h"
#include "timer.h"
#include "device/device.h"
#include "asm/spi.h"
#include "device/gpio.h"
#include "asm/pwm.h"
#include "device/iic.h"
#include "asm/iic.h"
#include "asm/clock.h"
#include "fs/fs.h"
#include "asm/sfc_norflash_api.h"
#include "syscfg/syscfg_id.h"

#define USER_APP_VERSION "1.0.0"

#define CONFIG_APP_I2C_BUS_ID (1)

#define AUDIO_DEVICE_PWRDN_PIN IO_PORTH_04
#define AUDIO_DEVICE_RESET_PIN IO_PORTH_02

static inline void AUDIO_DEVICE_ON(void)
{
    gpio_direction_output(AUDIO_DEVICE_PWRDN_PIN, 1);
}
static inline void AUDIO_DEVICE_OFF(void)
{
    gpio_direction_output(AUDIO_DEVICE_PWRDN_PIN, 0);
}

static inline void AUDIO_DEVICE_RESET(void)
{
    gpio_direction_output(AUDIO_DEVICE_RESET_PIN, 0);
}
static inline void AUDIO_DEVICE_UNRESET(void)
{
    gpio_direction_output(AUDIO_DEVICE_RESET_PIN, 1);
}

/**
 * Get the mapped of a number given an input and output range
 * @param x integer which mapped value should be calculated
 * @param min_in min input range
 * @param max_in max input range
 * @param min_out max output range
 * @param max_out max output range
 * @return the mapped number
 */
static inline int32_t map(int32_t x, int32_t min_in, int32_t max_in, int32_t min_out,
                          int32_t max_out)
{
    if (x >= max_in)
        return max_out;
    if (x <= min_in)
        return min_out;

    return (x - min_in) * (max_out - min_out) / (max_in - min_in) + min_out;
}

#endif /* USER_APP_H_ */