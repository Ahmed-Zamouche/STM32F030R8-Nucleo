/*
 * pwm.h
 *
 *  Created on: 8 Nov 2017
 *      Author: ahmed
 */

#ifndef PWM_H_
#define PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/*---------------------------------------------------------------------------*/
enum Pwm_Channel_e
{
	PWM_CHANNEL_1,

	PWM_CHANNEL_NUM,

};

typedef void (*Pwm_Callback_t)(bool);

/*---------------------------------------------------------------------------*/
void Pwm_SetDutyCycle(enum Pwm_Channel_e, uint8_t value);

void Pwm_CallbackRegister(enum Pwm_Channel_e, Pwm_Callback_t);

void Pwm_Init(void);

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* PWM_H_ */
