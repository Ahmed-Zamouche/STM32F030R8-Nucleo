/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"

/* USER CODE BEGIN 0 */
#include "console.h"
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart1;

/******************************************************************************/
/*            Cortex-M0 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles EXTI line 4 to 15 interrupts.
*/
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */

  /* USER CODE END EXTI4_15_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
* @brief This function handles TIM6 global interrupt.
*/
void TIM6_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_IRQn 0 */

  /* USER CODE END TIM6_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_IRQn 1 */

  /* USER CODE END TIM6_IRQn 1 */
}

/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */





void CustomDefault_HandlerC(uint32_t *stack) {

	/* These are volatile to try and prevent the compiler/linker optimising them
	 away as the variables never actually get used.  If the debugger won't show the
	 values of the variables, make them global my moving their declaration outside
	 of this function. */
	struct CM0_Stack_s {
		volatile uint32_t r0;
		volatile uint32_t r1;
		volatile uint32_t r2;
		volatile uint32_t r3;
		volatile uint32_t r12;
		volatile uint32_t lr; /* Link register. */
		volatile uint32_t pc; /* Program counter. */
		volatile uint32_t psr;/* Program status register. */
	}reg;

	reg.r0  = stack[0];
	reg.r1  = stack[1];
	reg.r2  = stack[2];
	reg.r3  = stack[3];

	reg.r12 = stack[4];
	reg.lr  = stack[5];
	reg.pc  = stack[6];
	reg.psr = stack[7];

	char str[32];

	volatile uint32_t exception_number = (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk);

	(void) Console_WriteAbort(CONSOLE_1);

	sprintf(str, "\r\nE: Caught Exception %ld\r\n",
			exception_number);
	Console_Puts(CONSOLE_1, str);

	sprintf(str , "r0  = 0x%08lx\r\n", reg.r0);
	Console_Puts(CONSOLE_1, str);
	sprintf(str , "r1  = 0x%08lx\r\n", reg.r1);
	Console_Puts(CONSOLE_1, str);
	sprintf(str , "r2  = 0x%08lx\r\n", reg.r2);
	Console_Puts(CONSOLE_1, str);
	sprintf(str , "r3  = 0x%08lx\r\n", reg.r3);
	Console_Puts(CONSOLE_1, str);
	sprintf(str , "r12 = 0x%08lx\r\n", reg.r12);
	Console_Puts(CONSOLE_1, str);
	sprintf(str , "lr  = 0x%08lx\r\n", reg.lr);
	Console_Puts(CONSOLE_1, str);
	sprintf(str , "pc  = 0x%08lx\r\n", reg.pc);
	Console_Puts(CONSOLE_1, str);
	sprintf(str , "psr = 0x%08lx\r\n", reg.psr);
	Console_Puts(CONSOLE_1, str);

	/*__asm volatile("bkpt #01");*/

	while (1) {

	}
}
void __attribute__ ((noinline)) CustomDefault_Handler(void)
{
	volatile static int dummy = -1;

	  __asm volatile (
	    " movs r0,#4       			\n"
	    " movs r1, lr      			\n"
	    " tst r0, r1       			\n"
	    " beq _MSP         			\n"
	    " mrs r0, psp      			\n"
	    " b _HALT          			\n"
	  "_MSP:               			\n"
	    " mrs r0, msp      			\n"
	  "_HALT:              			\n"
	    " ldr r1,[r0,#20]  			\n"
	    " b CustomDefault_HandlerC 	\n"
	    /*" bkpt #0          			\n"*/
	  );

    (void) dummy;
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
