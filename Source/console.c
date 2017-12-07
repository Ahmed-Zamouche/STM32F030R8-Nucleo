/*
 * console.c
 *
 *  Created on: 12 Nov 2017
 *      Author: ahmed
 */

#include <stdbool.h>
#include <string.h>
#include <assert.h>


#include "usart.h"

#include "port.h"


#include "console.h"

struct Console_Def_s {
	UART_HandleTypeDef *huart;
};

struct Console_Read_s{
	Console_CallbackRead_t cb;
	uint8_t *pData;
	uint16_t size;
	uint16_t index;
	volatile bool lock;
};

struct Console_Write_s{
	Console_CallbackWrite_t cb;
	volatile bool lock;
};

struct Console_s {
	struct Console_Write_s write;
	struct Console_Read_s read;

};

static const struct Console_Def_s s_consoleDef[CONSOLE_NUM] = { { .huart =
		&huart1 }, };

static struct Console_s s_console[CONSOLE_NUM];

static inline void Console_Lock(volatile bool *lock) {
	Port_EnterCritical();
	*lock = true;
	Port_ExitCritical();
}

static inline void Console_Unlock(volatile bool *lock)
{
	Port_EnterCritical();
	*lock = false;
	Port_ExitCritical();
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	struct Console_Write_s *cWrite = &s_console[CONSOLE_1].write;

	Console_Unlock(&cWrite->lock);

	cWrite->cb(CONSOLE_1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	struct Console_Read_s *cRead = &s_console[CONSOLE_1].read;

	if ((cRead->index < cRead->size)
			&& (cRead->pData[cRead->index -1] != CONSOLE_EOL)) {
		HAL_StatusTypeDef status = HAL_UART_Receive_IT(
				s_consoleDef[CONSOLE_1].huart, &cRead->pData[cRead->index++],
				1);
		(void) status;
	} else {
		Console_Unlock(&cRead->lock);
		cRead->cb(CONSOLE_1, cRead->index);

	}

}



static void Console_DefaultCallbackRead(enum Console_e idx, uint16_t size) {
	(void) idx;
	(void) size;
}

static void Console_DefaultCallbackWrite(enum Console_e idx) {
	(void) idx;
}

void Console_CallbackReadRegister(enum Console_e idx, Console_CallbackRead_t cb){

	assert(idx < CONSOLE_NUM);

	if (cb) {
		s_console[idx].read.cb = cb;
	} else {
		s_console[idx].read.cb = Console_DefaultCallbackRead;
	}
}

void Console_CallbackWriteRegister(enum Console_e idx, Console_CallbackWrite_t cb){

	assert(idx < CONSOLE_NUM);

	if (cb) {
		s_console[idx].write.cb = cb;
	} else {
		s_console[idx].write.cb = Console_DefaultCallbackWrite;
	}
}

Console_Status_t Console_ReadLine(enum Console_e idx, uint8_t *pData, uint16_t Size){

	assert(idx< CONSOLE_NUM);

	if (s_console[idx].read.lock) {
		return CONSOLE_STATUS_BUSY;
	}

	if (Size == 0) {
		return CONSOLE_STATUS_OK;
	}

	struct Console_Read_s *cRead = &s_console[idx].read;

	Console_Lock(&cRead->lock);

	cRead->pData = pData;
	cRead->size = Size;
	cRead->index = 0;

	HAL_StatusTypeDef status = HAL_UART_Receive_IT(s_consoleDef[idx].huart,
			&cRead->pData[cRead->index++], 1);

	if (status != HAL_OK) {
		Console_Unlock(&cRead->lock);
	}

	return (Console_Status_t) status;
}

Console_Status_t Console_Puts(enum Console_e idx, const char *str) {

	assert(idx < CONSOLE_NUM);

	HAL_StatusTypeDef status = HAL_UART_Transmit(s_consoleDef[idx].huart, (uint8_t *)str,
			strlen(str), HAL_MAX_DELAY);

	return (Console_Status_t) status;

}

Console_Status_t Console_WriteAbort(enum Console_e idx)
{
	assert(idx< CONSOLE_NUM);

	struct Console_Write_s *cWrite = &s_console[idx].write;

	HAL_StatusTypeDef status;
	if (cWrite->lock) {
		 status = HAL_UART_AbortTransmit_IT(s_consoleDef[idx].huart);
	}else{
		status = HAL_UART_AbortTransmit(s_consoleDef[idx].huart);
	}

	return (Console_Status_t) status;
}

Console_Status_t Console_Write(enum Console_e idx, uint8_t *pData, uint16_t Size) {

	assert(idx< CONSOLE_NUM);

	struct Console_Write_s *cWrite = &s_console[idx].write;

	if (cWrite->lock) {
		return CONSOLE_STATUS_BUSY;
	}

	Console_Lock(&cWrite->lock);

	HAL_StatusTypeDef status = HAL_UART_Transmit_IT(s_consoleDef[idx].huart,
			pData, Size);

	if(status != HAL_OK)
	{
		Console_Unlock(&cWrite->lock);
	}

	return (Console_Status_t) status;
}

void Console_Init(void){
	for (enum Console_e idx = 0; idx < CONSOLE_NUM; ++idx) {
		s_console[idx].read.cb = Console_DefaultCallbackRead;
		s_console[idx].write.cb = Console_DefaultCallbackWrite;
	}
}
