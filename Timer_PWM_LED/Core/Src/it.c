/*
 * it.c
 *
 *  Created on: Jul 24, 2025
 *      Author: weber
 */


#include "main_app.h"

extern TIM_HandleTypeDef htimer3;

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


/**
  * @brief  This function handles TIM3 interrupt.
  */
void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer3);
}
