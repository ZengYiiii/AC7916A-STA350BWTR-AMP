#ifndef __LOG_H
#define __LOG_H

#include "generic/typedef.h"
#include "generic/printf.h"

#if !defined(LOG_TAG)
#define LOG_TAG "NO_TAG"
#endif /* !defined(LOG_TAG) */

#define CTRL_TEXT_BRIGHT_BLACK "[1;30m"
#define CTRL_TEXT_BRIGHT_RED "[1;31m"
#define CTRL_TEXT_BRIGHT_GREEN "[1;32m"
#define CTRL_TEXT_BRIGHT_YELLOW "[1;33m"
#define CTRL_TEXT_BRIGHT_BLUE "[1;34m"
#define CTRL_TEXT_BRIGHT_MAGENTA "[1;35m"
#define CTRL_TEXT_BRIGHT_CYAN "[1;36m"
#define CTRL_TEXT_BRIGHT_WHITE "[1;37m"

#define CTRL_TEXT_END "[0m"

#define plog_d(TAG, ...)                                                      \
	do                                                                        \
	{                                                                         \
		printf("\r\n" CTRL_TEXT_BRIGHT_MAGENTA "[D] [" TAG "]:" __VA_ARGS__); \
		printf("" CTRL_TEXT_END "\r\n");                                      \
	} while (0)
#define plog_i(TAG, ...)                                                    \
	do                                                                      \
	{                                                                       \
		printf("\r\n" CTRL_TEXT_BRIGHT_GREEN "[I] [" TAG "]:" __VA_ARGS__); \
		printf("" CTRL_TEXT_END "\r\n");                                    \
	} while (0)
#define plog_w(TAG, ...)                                                     \
	do                                                                       \
	{                                                                        \
		printf("\r\n" CTRL_TEXT_BRIGHT_YELLOW "[W] [" TAG "]:" __VA_ARGS__); \
		printf("" CTRL_TEXT_END "\r\n");                                     \
	} while (0)
#define plog_e(TAG, ...)                                                  \
	do                                                                    \
	{                                                                     \
		printf("\r\n" CTRL_TEXT_BRIGHT_RED "[E] [" TAG "]:" __VA_ARGS__); \
		printf("" CTRL_TEXT_END "\r\n");                                  \
	} while (0)
#define plog_v(TAG, ...)                                                   \
	do                                                                     \
	{                                                                      \
		printf("\r\n" CTRL_TEXT_BRIGHT_CYAN "[V] [" TAG "]:" __VA_ARGS__); \
		printf("" CTRL_TEXT_END "\r\n");                                   \
	} while (0)

#define LOGD(...) plog_d(LOG_TAG, __VA_ARGS__)
#define LOGI(...) plog_i(LOG_TAG, __VA_ARGS__)
#define LOGW(...) plog_w(LOG_TAG, __VA_ARGS__)
#define LOGE(...) plog_e(LOG_TAG, __VA_ARGS__)
#define LOGV(...) plog_v(LOG_TAG, __VA_ARGS__)

#define __LOG_VERB 0
#define __LOG_DEBUG 1
#define __LOG_INFO 2
#define __LOG_WARN 3
#define __LOG_ERROR 4
#define __LOG_CHAR 5

struct logbuf
{
	u16 len;
	u16 buf_len;
	char buf[0];
};

#define __LOG_ENABLE

#ifndef __LOG_LEVEL
#define __LOG_LEVEL 0
#endif

#ifdef CONFIG_RELEASE_ENABLE
#undef __LOG_LEVEL
#define __LOG_LEVEL 0xff
#endif

#if __LOG_LEVEL > __LOG_VERB
#define log_v(...) \
	do             \
	{              \
	} while (0)
#elif defined __LOG_ENABLE
#define log_v(...) log_print(__LOG_VERB, NULL, __VA_ARGS__)
#else
#define log_v(...) printf(__VA_ARGS__)
#endif

#if __LOG_LEVEL > __LOG_DEBUG
#define log_d(...) \
	do             \
	{              \
	} while (0)
#elif defined __LOG_ENABLE
#define log_d(...) log_print(__LOG_DEBUG, NULL, __VA_ARGS__);
#else
#define log_d(...) printf(__VA_ARGS__)
#endif

#if __LOG_LEVEL > __LOG_INFO
#define log_i(...) \
	do             \
	{              \
	} while (0)
#elif defined __LOG_ENABLE
#define log_i(...) log_print(__LOG_INFO, NULL, __VA_ARGS__);
#else
#define log_i(...) printf(__VA_ARGS__)
#endif

#if __LOG_LEVEL > __LOG_WARN
#define log_w(...) \
	do             \
	{              \
	} while (0)
#elif defined __LOG_ENABLE
#define log_w(...) log_print(__LOG_WARN, NULL, __VA_ARGS__);
#else
#define log_w(...) printf(__VA_ARGS__)
#endif

#if __LOG_LEVEL > __LOG_ERROR
#define log_e(...) \
	do             \
	{              \
	} while (0)
#elif defined __LOG_ENABLE
#define log_e(...) log_print(__LOG_ERROR, NULL, __VA_ARGS__);
#else
#define log_e(...) printf(__VA_ARGS__)
#endif

#if __LOG_LEVEL > __LOG_CHAR
#define log_c(x) \
	do           \
	{            \
	} while (0)
#elif defined __LOG_ENABLE
#define log_c(x) putchar(x)
#else
#define log_c(x)
#endif

#define r_printf(x, ...) log_i("\e[31m\e[1m" x "\e[0m", ##__VA_ARGS__)
#define g_printf(x, ...) log_i("\e[32m\e[1m" x "\e[0m", ##__VA_ARGS__)
#define y_printf(x, ...) log_i("\e[33m\e[1m" x "\e[0m", ##__VA_ARGS__)
#define r_f_printf(x, ...) log_i("\e[31m\e[5m\e[1m" x "\e[0m", ##__VA_ARGS__)
#define g_f_printf(x, ...) log_i("\e[32m\e[5m\e[1m" x "\e[0m", ##__VA_ARGS__)
#define y_f_printf(x, ...) log_i("\e[33m\e[5m\e[1m" x "\e[0m", ##__VA_ARGS__)

#ifndef __LOG_ENABLE

#define log_dump(a, b) \
	do                 \
	{                  \
	} while (0)
#define log_putchar() \
	do                \
	{                 \
	} while (0)
#define log_early_init(a) \
	do                    \
	{                     \
	} while (0)
#define log_level(a) \
	do               \
	{                \
	} while (0)
#define log_output_lock() 0
#define log_output_unlock() \
	do                      \
	{                       \
	} while (0)
#define log_output_start(...) NULL
#define log_output_end(...) \
	do                      \
	{                       \
	} while (0)

#else

extern int config_debug_enable;

int log_output_lock();

void log_output_unlock();

void log_print_time();

void log_early_init(int buf_size);

void log_level(int level);

void log_dump(const u8 *buf, int len);

struct logbuf *log_output_start(int len);

void log_output_end(struct logbuf *);

void log_putchar(struct logbuf *lb, char c);

void log_put_u8hex(struct logbuf *lb, unsigned char dat);

void log_set_time_offset(int offset);

int log_get_time_offset();

#endif

void log_putbyte(char);

void log_flush();

void log_print(int level, const char *tag, const char *format, ...);

#endif
