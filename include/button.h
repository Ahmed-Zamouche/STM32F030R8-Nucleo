/*
 * button.h
 *
 *  Created on: 12 Nov 2017
 *      Author: ahmed
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/*---------------------------------------------------------------------------*/
enum Button_e {
	BUTTON_1,

	BUTTON_NUM
};

enum ButtonEvent_e {
	BUTTON_EVENT_PRESS,
	BUTTON_EVENT_RELEASE,
	BUTTON_EBENT_NUM
};

typedef void (*Button_Callback_t)(enum Button_e, enum ButtonEvent_e);

typedef enum Button_e Button_Handel_t;
/*---------------------------------------------------------------------------*/
void Button_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void Button_CallbackRegister(enum Button_e, Button_Callback_t);

bool Button_IsPressed(enum Button_e);

bool Button_IsReleased(enum Button_e);

void Button_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_BUTTON_H_ */
