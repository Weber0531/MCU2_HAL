/*
 * it.c
 *
 *  Created on: Jun 18, 2025
 *      Author: weber
 */


#include "main_app.h"
extern TIM_HandleTypeDef htimer6;


/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


void TIM6_DAC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer6);
}
