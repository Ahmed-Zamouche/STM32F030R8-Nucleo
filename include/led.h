/*
 * led.h
 *
 *  Created on: 11 Nov 2017
 *      Author: ahmed
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

enum Led_e{

	LED_1,

	LED_NUM
};

void Led_Set(enum Led_e, bool);

void Led_Toggle(enum Led_e);

void Led_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_LED_H_ */
