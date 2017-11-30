/*
 * pwm.h
 *
 *  Created on: 8 Nov 2017
 *      Author: ahmed
 */

#ifndef INCLUDE_PWM_H_
#define INCLUDE_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>

/*---------------------------------------------------------------------------*/
#define PWM_FREQ_HZ					(20*1000)

enum Pwm_Channel_e
{
	PWM_CHANNEL_1,

	PWM_CHANNEL_NUM,

};

typedef void (*Pwm_Callback_t)(bool);

/*---------------------------------------------------------------------------*/
void Pwm_SetDutyCycle(enum Pwm_Channel_e, uint8_t value);

void Pwm_SetFaderPrescaler(uint8_t prescaler);

void Pwm_CallbackRegister(enum Pwm_Channel_e, Pwm_Callback_t);

void Pwm_Init(void);

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_PWM_H_ */
