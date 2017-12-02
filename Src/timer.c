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
	HAL_TIM_Base_Start(&htim14);
}

void timer_stop(enum Timer_e tmr){
	(void) tmr;
	HAL_TIM_Base_Stop(&htim14);
}

uint32_t timer_counterValue(enum Timer_e tmr){
	(void) tmr;
	return __HAL_TIM_GET_COUNTER(&htim14);
}

uint32_t timer_overheadValue(void)
{
    static int32_t overhead = -1;

    if(overhead == -1)
    {
       uint32_t start, end;

        timer_start(TIMER_1);

        start = timer_counterValue(TIMER_1);
        end = timer_counterValue(TIMER_1);

        timer_stop(TIMER_1);

        overhead = (end - start);
    }

    return (uint32_t) overhead;
}
