/*
 * timer.c
 *
 *  Created on: 30 Nov 2017
 *      Author: Ahmed.Z
 */


#include <assert.h>

#include "tim.h"

#include "timer.h"

/*---------------------------------------------------------------------------*/
struct Timer_Def_s {

   TIM_HandleTypeDef* htim;
};
/*---------------------------------------------------------------------------*/
static const struct Timer_Def_s  s_timerDef[TIMER_NUM] = {{.htim = &htim14,}};
/*---------------------------------------------------------------------------*/
void timer_start(enum Timer_e tmr){
   (void) tmr;
   HAL_TIM_Base_Start(s_timerDef[tmr].htim);
}

void timer_stop(enum Timer_e tmr){
   (void) tmr;
   HAL_TIM_Base_Stop(s_timerDef[tmr].htim);
}

uint32_t timer_counterValue(enum Timer_e tmr){
   (void) tmr;
   /**@note: TIM14 is 16 bits only*/
   return __HAL_TIM_GET_COUNTER(s_timerDef[tmr].htim);
}

uint32_t timer_overheadValue(enum Timer_e tmr)
{
   static int init = 0;
   static int32_t  s_overhead[TIMER_NUM];

    if(init == 0)
    {
       uint32_t start, end;

        timer_start(tmr);

        start = timer_counterValue(tmr);
        end = timer_counterValue(tmr);

        timer_stop(tmr);

        overhead = (end - start);

       init = 1;

    }

    return (uint32_t) s_overhead[tmr];
}

void Timer_Init(void) {
   for (enum Timer_e tmr = 0; tmr < TIMER_NUM; ++tmr) {
      timer_overheadValue(tmr);
   }
}
