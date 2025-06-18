/*
 * main_app.c
 *
 *  Created on: Jun 18, 2025
 *      Author: weber
 */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "main_app.h"

/* Private function prototypes -----------------------------------------------*/
void Error_handler(void);
void SystemClockConfig(void);

/* Private variables ---------------------------------------------------------*/


int main(void)
{
	HAL_Init();
	SystemClockConfig();

	while(1);

	return 0;
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClockConfig(void)
{


}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_handler(void)
{
	while(1);
}
