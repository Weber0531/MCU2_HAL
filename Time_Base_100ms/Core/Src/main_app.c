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
void GPIO_Init(void);
void TIMER6_Init(void);

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htimer6;

int main(void)
{
	HAL_Init();
	SystemClockConfig();
	GPIO_Init();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET); // 設為低電位
	while(1);
	TIMER6_Init();

	// Start timer
	HAL_TIM_Base_Start(&htimer6);

	while(1){
		// Loop until the update event flag is set
		while( ! (TIM6->SR & TIM_SR_UIF) );

		/* The required time delay has been elapsed */
		/* User code can be executed */
		TIM6->SR = 0;
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
	}




	return 0;
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClockConfig(void)
{


}


void GPIO_Init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_12;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &ledgpio);
}


void TIMER6_Init(void)
{
	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler = 24;
	htimer6.Init.Period = 64000 - 1;
	if( HAL_TIM_Base_Init(&htimer6) != HAL_OK )
	{
		Error_handler();
	}
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_handler(void)
{
	while(1);
}
