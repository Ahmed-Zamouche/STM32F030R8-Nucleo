/*
 * Test.c
 *
 *  Created on: 14 Nov 2017
 *      Author: ahmed
 */

#include <stdint.h>
#include "misc.h"
#include "led.h"
#include "pwm.h"
#include "button.h"
#include "console.h"



uint8_t readBuf[16];

static void Led_Pwm_Callback(bool ena){
	Led_Set(LED_1, ena);
}

static void Button_Callback(enum Button_e idx, enum ButtonEvent_e event) {
	Led_Set(LED_1, event == BUTTON_EVENT_RELEASE);
}

static void Console_CallbackRead(enum Console_e idx, uint16_t size) {
	(void) idx;
	(void) size;
	Led_Toggle(LED_1);
	Console_ReadLine(CONSOLE_1, readBuf, sizeof(readBuf));
	Console_Write(CONSOLE_1, readBuf, size);
}

static void Console_CallbackWrite(enum Console_e idx) {
	(void) idx;
	Led_Toggle(LED_1);
}

static void Exception_Rise(void)
{
	/*HAL_NVIC_EnableIRQ(0);
	HAL_NVIC_SetPendingIRQ(0);*/
}

int mainApp(int argc, char **argv) {

	Pwm_CallbackRegister(PWM_CHANNEL_1, Led_Pwm_Callback);
	Button_CallbackRegister(PWM_CHANNEL_1, Button_Callback);
	Console_CallbackReadRegister(CONSOLE_1, Console_CallbackRead);
	Console_CallbackWriteRegister(CONSOLE_1, Console_CallbackWrite);

	Console_Write(CONSOLE_1, (uint8_t *) "MainTask\r\n", 10);
	Console_ReadLine(CONSOLE_1, readBuf, sizeof(readBuf));

	Exception_Rise();


	for (;;) {
		//led_set(LED_1, true);
		Pwm_SetDutyCycle(PWM_CHANNEL_1, 0);
		delay_ms(5000);
		//led_set(LED_1, false);
		Pwm_SetDutyCycle(PWM_CHANNEL_1, 255);
		delay_ms(5000);
	}

	while (1)
		;
	return 0;

}
