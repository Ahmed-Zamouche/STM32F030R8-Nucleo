/*
 * console.h
 *
 *  Created on: 12 Nov 2017
 *      Author: ahmed
 */

#ifndef INC_CONSOLE_H_
#define INC_CONSOLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define CONSOLE_EOL	(10)

enum Console_e {
	CONSOLE_1,

	CONSOLE_NUM
};

typedef enum Console_Status_e {

	CONSOLE_STATUS_OK = 0,
	CONSOLE_STATUS_ERROR,
	CONSOLE_STATUS_BUSY,
	CONSOLE_STATUS_TIMEOUT,

	CONSOLE_STATUS_NUM
}Console_Status_t;


enum ConsoleEvent_e {


	CONSOLE_EVENT_RD_DONE,

	CONSOLE_EVENT_WR_DONE,

	CONSOLE_EVENT_NUM
};

typedef void (*Console_CallbackRead_t)(enum Console_e, uint16_t Size);
typedef void (*Console_CallbackWrite_t)(enum Console_e);

void Console_CallbackReadRegister(enum Console_e idx, Console_CallbackRead_t);
void Console_CallbackWriteRegister(enum Console_e idx, Console_CallbackWrite_t);

Console_Status_t Console_ReadLine(enum Console_e, uint8_t *pData, uint16_t Size);

Console_Status_t Console_Write(enum Console_e, uint8_t *pData, uint16_t Size);

void Console_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_CONSOLE_H_ */
