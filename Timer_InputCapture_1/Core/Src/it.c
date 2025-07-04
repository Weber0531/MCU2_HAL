/*
 * it.c
 *
 *  Created on: Jun 18, 2025
 *      Author: weber
 */


#include "main_app.h"
extern TIM_HandleTypeDef htimer2;
extern TIM_HandleTypeDef htimer6;


/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer2);
}


void TIM6_DAC_IRQHandler(void)
{
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
	HAL_TIM_IRQHandler(&htimer6);
}
