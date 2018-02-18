/*
 * logger.h
 *
 *  Created on: 6 Dec 2017
 *      Author: ahmed
 */

#ifndef INCLUDE_LOGGER_H_
#define INCLUDE_LOGGER_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef enum LoggerLevel_e
{
	LOGGER_LEVEL_DEBUG = 0,
	LOGGER_LEVEL_INFO,
	LOGGER_LEVEL_WARNING,
	LOGGER_LEVEL_ERROR,
	LOGGER_LEVEL_FATAL,

	LOGGER_LEVEL_NUM,
}LoggerLevel_t;

void Logger_SetLevel(const enum LoggerLevel_e);

void Logger_printf(const enum LoggerLevel_e, const char *fun, const char* format, ...)
#ifdef __GNUC__
    __attribute__((format(printf, 3, 4)))
#endif
;

#define Logger_Printf(level, format, ...) \
	do{\
		Logger_printf(level, __FUNCTION__, format,  ##__VA_ARGS__);\
	}while(0)


void Logger_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_LOGGER_H_ */
