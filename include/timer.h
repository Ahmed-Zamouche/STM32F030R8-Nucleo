/*
 * timer.h
 *
 *  Created on: 30 Nov 2017
 *      Author: Ahmed.Z
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "timer.h"

enum Timer_e
{
	TIMER_1,

	TIMER_NUM,

};

void timer_start(enum Timer_e);

void timer_stop(enum Timer_e);

uint32_t timer_counterValue(enum Timer_e);

uint32_t timer_overheadValue(enum Timer_e);

void Timer_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_TIMER_H_ */
