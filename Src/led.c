/*
 * led.c
 *
 *  Created on: 11 Nov 2017
 *      Author: ahmed
 */

#include <assert.h>

#include "port.h"

#include "led.h"

/*---------------------------------------------------------------------------*/
struct Led_Def_s {
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
};
/*---------------------------------------------------------------------------*/
static const struct Led_Def_s s_ledDef[LED_NUM] = { { .GPIOx = LD2_GPIO_Port,
		.GPIO_Pin = LD2_Pin }, };
/*---------------------------------------------------------------------------*/
void Led_Set(enum Led_e idx, bool state) {

	assert(idx < LED_NUM);

	HAL_GPIO_WritePin(s_ledDef[idx].GPIOx, s_ledDef[idx].GPIO_Pin,
			state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Led_Toggle(enum Led_e idx) {
	GPIO_PinState state = HAL_GPIO_ReadPin(s_ledDef[idx].GPIOx, s_ledDef[idx].GPIO_Pin);

	Led_Set(idx, state ? GPIO_PIN_RESET :GPIO_PIN_SET);
}

void Led_Init(void) {

}
