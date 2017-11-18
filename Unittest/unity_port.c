/*
 * unity_port.c
 *
 *  Created on: 18 Nov 2017
 *      Author: ahmed
 */


#include <stdint.h>
#include "console.h"




int __putchar(int c) {

	static char ch;

	Console_Status_t status;

	ch = c;

	do {
		status = Console_Write(CONSOLE_1, (uint8_t *)&ch, 1);

	} while (CONSOLE_STATUS_BUSY == status);

	return (CONSOLE_STATUS_OK == status) ? c : -1;
}
