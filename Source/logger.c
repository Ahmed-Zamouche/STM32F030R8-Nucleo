/*
 * logger.c
 *
 *  Created on: 6 Dec 2017
 *      Author: ahmed
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include <console.h>
#include <logger.h>

#define LOGGER_BUFFER_SIZE	(256)

static char s_buffer[LOGGER_BUFFER_SIZE];
static enum LoggerLevel_e s_level;


static const char *Logger_Level2Str(enum LoggerLevel_e level) {

	static const char *levels_str[] = { "DEBUG", "INFO", "WARNING", "ERROR",
			"FATAL", };

	return levels_str[level];

}

void Logger_SetLevel(const enum LoggerLevel_e level)
{
	s_level = level;
}

void Logger_printf(const enum LoggerLevel_e level, const char *func,
		const char *format, ...) {

	if (level > s_level) {
		return;
	}
	//FIXME: blocking write
	while (Console_Write(CONSOLE_1, NULL, 0) == CONSOLE_STATUS_BUSY) {
		;
	}

	int n = snprintf(s_buffer, LOGGER_BUFFER_SIZE, "L:[%s] %s() ",
			Logger_Level2Str(level), func);

	assert(n >= 0);
	va_list argptr;
	va_start(argptr, format);
	n += vsnprintf(&s_buffer[n], (LOGGER_BUFFER_SIZE - n), format, argptr);
	va_end(argptr);
	assert(n >= 0);

	n += snprintf(&s_buffer[n], (LOGGER_BUFFER_SIZE - n), "\r\n");

	assert(n >= 0);

	//FIXME: blocking write
	while (Console_Write(CONSOLE_1, (uint8_t *) s_buffer, n)
			== CONSOLE_STATUS_BUSY) {
		;
	}

}


void Logger_Init(void) {
	s_level = LOGGER_LEVEL_INFO;
}
