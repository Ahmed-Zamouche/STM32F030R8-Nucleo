/*
 * port.h
 *
 *  Created on: 13 Nov 2017
 *      Author: ahmed
 */

#ifndef INC_PORT_H_
#define INC_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx_hal.h"
#include "main.h"
#include "tim.h"

#include <stdbool.h>


/*-----------------------------------------*/
static inline void Port_EnterCritical(void) {
	__disable_irq();
}

static inline void Port_ExitCritical(void)
{
	__enable_irq();
}



#ifdef __cplusplus
}
#endif

#endif /* INC_PORT_H_ */
