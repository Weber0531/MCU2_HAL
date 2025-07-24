/*
 * msp.c
 *
 *  Created on: Jul 24, 2025
 *      Author: weber
 */


#include "main_app.h"


/**
  * @brief  Initialize the MSP.
  * @retval None
  */
void HAL_MspInit(void)
{
	// Here will do low level processor specific inits
	// 1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// 2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= (0x7 << 16); // usage fault, memory fault and bus fault system exceptions

	// 3. Configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}


/**
  * @brief  Initializes the TIM PWM MSP.
  * @param  htim TIM PWM handle
  * @retval None
  */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef tim3OC_ch_gpios;

	// 1. Enable the peripheral clock for the timer3 peripheral
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// 2. Configure GPIOs to behave as timer3 channel 1
	tim3OC_ch_gpios.Pin = GPIO_PIN_6; // TIM3_CH1
	tim3OC_ch_gpios.Mode = GPIO_MODE_AF_PP;
	tim3OC_ch_gpios.Alternate = GPIO_AF2_TIM3;
	tim3OC_ch_gpios.Pull = GPIO_NOPULL;
	tim3OC_ch_gpios.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &tim3OC_ch_gpios);

	// 3. NVIC settings
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	HAL_NVIC_SetPriority(TIM3_IRQn, 15, 0);
}
