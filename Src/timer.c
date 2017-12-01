/*
 * timer.c
 *
 *  Created on: 30 Nov 2017
 *      Author: Ahmed.Z
 */


#include <assert.h>

#include "tim.h"

#include "timer.h"

void timer_start(enum Timer_e tmr){
	(void) tmr;
	assert(HAL_TIM_Base_Start(&htim14) == HAL_OK);
}

void timer_stop(enum Timer_e tmr){
	(void) tmr;
	assert(HAL_TIM_Base_Stop(&htim14) == HAL_OK);
}

uint32_t timer_counterValue(enum Timer_e tmr){
	(void) tmr;
	return __HAL_TIM_GET_COUNTER(&htim14);
}


