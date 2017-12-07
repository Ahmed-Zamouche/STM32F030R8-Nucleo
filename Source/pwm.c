/*
 * pwm.c
 *
 *  Created on: 8 Nov 2017
 *      Author: ahmed
 */

#include <stdbool.h>
#include <assert.h>

#include "port.h"

#include "pwm.h"

/*---------------------------------------------------------------------------*/
#define Pwm_TimerStart()				 	 	HAL_TIM_Base_Start_IT(&htim6)
#define Pwm_TimerStop()							HAL_TIM_Base_Stop_IT(&htim6)
/*---------------------------------------------------------------------------*/
struct Pwm_s
{
	Pwm_Callback_t cb;
	uint8_t actual;
	uint8_t target;
	uint8_t counter;
	uint8_t fader;

};
/*---------------------------------------------------------------------------*/
static struct Pwm_s s_pwm[PWM_CHANNEL_NUM];
static uint8_t s_numEnabledChannels;
static uint8_t s_faderPrescaler = 0x80;
/*---------------------------------------------------------------------------*/
static void Pwm_TimerPeriodElapsedCallback(void);
static void Pwm_DefaultCallback(bool ena);
/*---------------------------------------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance != TIM6) {
		return;
	}

	Pwm_TimerPeriodElapsedCallback();

}

static void Pwm_TimerPeriodElapsedCallback(void){

	for (enum Pwm_Channel_e idx = 0; idx < PWM_CHANNEL_NUM; ++idx) {

		struct Pwm_s *pwmObj = &s_pwm[idx];

		if (pwmObj->fader & s_faderPrescaler) {

			if (pwmObj->actual < pwmObj->target) {
				pwmObj->actual++;
			} else if (pwmObj->actual > pwmObj->target) {
				pwmObj->actual--;
			} else {
				if (pwmObj->target == 0) {
					s_numEnabledChannels--;
				}
			}
			pwmObj->fader = 0;
		}

		pwmObj->cb(pwmObj->counter < pwmObj->actual);

		pwmObj->counter += 2;

		pwmObj->fader++;

	}
	if (s_numEnabledChannels == 0) {
		Pwm_TimerStop();
	}
}

static void Pwm_DefaultCallback(bool ena){
	(void) ena;
}
/*---------------------------------------------------------------------------*/
void Pwm_SetDutyCycle(enum Pwm_Channel_e ch, uint8_t value)
{
	assert(ch < PWM_CHANNEL_NUM);

	Port_EnterCritical();

	if(s_pwm[ch].target == 0 && value != 0){
		s_numEnabledChannels++;
		Pwm_TimerStart();
	}
	s_pwm[ch].target = value;

	Port_ExitCritical();
}

void Pwm_SetFaderPrescaler(uint8_t prescaler)
{
	s_faderPrescaler = prescaler;
}

void Pwm_CallbackRegister(enum Pwm_Channel_e ch, Pwm_Callback_t cb){


	assert(ch < PWM_CHANNEL_NUM);

	if(cb){
		s_pwm[ch].cb = cb;
	}else{
		s_pwm[ch].cb = Pwm_DefaultCallback;
	}

}

void Pwm_Init(void)
{
	s_numEnabledChannels = 0;
	for (enum Pwm_Channel_e ch = 0; ch < PWM_CHANNEL_NUM; ++ch) {
		s_pwm[ch].cb = Pwm_DefaultCallback;
	}
}
