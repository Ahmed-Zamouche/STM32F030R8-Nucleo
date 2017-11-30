/*
 * TestEvents.c
 *
 *  Created on: 25 Nov 2017
 *      Author: Ahmed.Z
 */

#include "unity.h"
#include "unity_fixture.h"

#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "button.h"
#include "console.h"
#include "led.h"
#include "misc.h"
#include "pwm.h"

TEST_GROUP(Events);



TEST_SETUP(Events)
{

}

TEST_TEAR_DOWN(Events)
{

}

static volatile uint32_t s_var;

static void Pwm_Callback(bool ena){
	if(ena)
	{
		s_var++;
	}
}

static void Button_Callback(enum Button_e idx, enum ButtonEvent_e event) {
	(void) idx;
	(void) event;

	s_var = 1;
}

static void Console_CallbackRead(enum Console_e idx, uint16_t size) {
	(void) idx;
	(void) size;

}

static void Console_CallbackWrite(enum Console_e idx) {
	(void) idx;
	s_var = 1;
}

TEST(Events, Pwm_Callback)
{

	Pwm_SetFaderPrescaler(0x01);

	Pwm_CallbackRegister(PWM_CHANNEL_1, Pwm_Callback);
	Pwm_SetDutyCycle(PWM_CHANNEL_1, 64);
	s_var = 0;
	delay_ms(100);
	TEST_ASSERT_INT32_WITHIN(30, 250/* = (100E-3*PWM_FREQ_HZ)*(64/256)*/, s_var);

	Pwm_SetDutyCycle(PWM_CHANNEL_1, 0);
	delay_ms(5);
	s_var = 0;
	delay_ms(100);
	TEST_ASSERT_EQUAL_INT(0, s_var);

	Pwm_CallbackRegister(PWM_CHANNEL_1, NULL);
}

TEST(Events, Button_Callback)
{
	s_var = 0;
	Button_CallbackRegister(BUTTON_1, Button_Callback);
	Button_GenerateSWIT(BUTTON_1);
	delay_ms(1);
	TEST_ASSERT_EQUAL_INT(1, s_var);

	s_var = 0;
	Button_CallbackRegister(BUTTON_1, NULL);
	Button_GenerateSWIT(BUTTON_1);
	delay_ms(1);
	TEST_ASSERT_EQUAL_INT(0, s_var);
}

TEST(Events, Console_CallbackRead)
{
	Console_CallbackReadRegister(CONSOLE_1, Console_CallbackRead);
	TEST_ASSERT(1);
	Console_CallbackReadRegister(CONSOLE_1, NULL);
	TEST_ASSERT(1);
}

TEST(Events, Console_CallbackWrite)
{
	static const char *str = "T:Console_CallbackWrite\r\n";

	s_var = 0;
	Console_CallbackWriteRegister(CONSOLE_1, Console_CallbackWrite);
	while(Console_Write(CONSOLE_1, (uint8_t *) str, strlen(str)) == CONSOLE_STATUS_BUSY);
	while(Console_Write(CONSOLE_1, NULL, 0) == CONSOLE_STATUS_BUSY);
	TEST_ASSERT_EQUAL_INT(1, s_var);

	s_var = 0;
	Console_CallbackWriteRegister(CONSOLE_1, NULL);
	while(Console_Write(CONSOLE_1, (uint8_t *) str, strlen(str)) == CONSOLE_STATUS_BUSY);
	while(Console_Write(CONSOLE_1, NULL, 0) == CONSOLE_STATUS_BUSY);
	TEST_ASSERT_EQUAL_INT(0, s_var);
}




