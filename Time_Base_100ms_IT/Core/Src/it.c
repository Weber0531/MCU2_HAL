/*
 * it.c
 *
 *  Created on: Jun 18, 2025
 *      Author: weber
 */


#include "main_app.h"


/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
