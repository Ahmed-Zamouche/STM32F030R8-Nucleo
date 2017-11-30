/*
 * button.c
 *
 *  Created on: 12 Nov 2017
 *      Author: ahmed
 */

#include <assert.h>

#include "port.h"

#include "button.h"

/*---------------------------------------------------------------------------*/
struct Button_Def_s {

	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
};

struct Button_s
{
	Button_Callback_t cb;

};
/*---------------------------------------------------------------------------*/
static void Button_DefaultCallback(enum Button_e, enum ButtonEvent_e);
/*---------------------------------------------------------------------------*/
static const struct Button_Def_s s_buttonDef[BUTTON_NUM] = { { .GPIOx =
		B1_GPIO_Port, .GPIO_Pin = GPIO_PIN_13 }, };

static struct Button_s s_button[BUTTON_NUM];
/*---------------------------------------------------------------------------*/
static void Button_DefaultCallback(enum Button_e idx, enum ButtonEvent_e event) {
	(void) idx;
	(void) event;
}
/*---------------------------------------------------------------------------*/
void Button_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if(Button_IsPressed(BUTTON_1)){
		s_button[BUTTON_1].cb(BUTTON_1, BUTTON_EVENT_PRESS);
	}else{
		s_button[BUTTON_1].cb(BUTTON_1, BUTTON_EVENT_RELEASE);
	}

}

void Button_GenerateSWIT(enum Button_e idx)
{
	__HAL_GPIO_EXTI_GENERATE_SWIT(s_buttonDef[BUTTON_1].GPIO_Pin);
}

bool Button_IsPressed(enum Button_e idx) {

	assert(idx < BUTTON_NUM);
	return HAL_GPIO_ReadPin(s_buttonDef[idx].GPIOx, s_buttonDef[idx].GPIO_Pin)
			== GPIO_PIN_SET;
}

bool Button_IsReleased(enum Button_e idx) {
	return !Button_IsPressed(idx);
}

void Button_CallbackRegister(enum Button_e idx, Button_Callback_t cb) {

	assert(idx < BUTTON_NUM);

	if (cb) {
		s_button[idx].cb = cb;
	} else {
		s_button[idx].cb = Button_DefaultCallback;
	}

}

void Button_Init(void) {
	for (enum Button_e idx = 0; idx < BUTTON_NUM; ++idx) {
		s_button[idx].cb = Button_DefaultCallback;
	}
}
