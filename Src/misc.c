/*
 * misc.c
 *
 *  Created on: 16 Nov 2017
 *      Author: ahmed
 */

#include "port.h"
#include "misc.h"


void delay_ms(uint16_t ms)
{
	HAL_Delay(ms);
}
