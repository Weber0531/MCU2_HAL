/*
 * main_app.c
 *
 *  Created on: Jun 16, 2025
 *      Author: weber
 */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "main_app.h"

#define TRUE	1
#define FALSE	0

/* Private function prototypes -----------------------------------------------*/
void UART2_Init(void);
void Error_handler(void);
void SystemClock_Config(uint8_t clock_freq);

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;


int main(void)
{
	char msg[100];
	HAL_Init();

	SystemClock_Config(SYS_CLOCK_FREQ_50_MHZ); // run HCLK at 50 MHz
	//SystemClock_Config(SYS_CLOCK_FREQ_84_MHZ); // run HCLK at 84 MHz
	//SystemClock_Config(SYS_CLOCK_FREQ_120_MHZ); // run HCLK at 120 MHz

	UART2_Init();

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "SYSCLK : %ld\r\n", HAL_RCC_GetSysClockFreq());
	//HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	printf("%s", msg);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "HCLK : %ld\r\n", HAL_RCC_GetHCLKFreq());
	//HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	printf("%s", msg);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK1 : %ld\r\n", HAL_RCC_GetPCLK1Freq());
	//HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	printf("%s", msg);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK2 : %ld\r\n", HAL_RCC_GetPCLK2Freq());
	//HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	printf("%s", msg);

	while(1);

	return 0;
}


void SystemClock_Config(uint8_t clock_freq)
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	uint32_t FLatency = 0;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.HSICalibrationValue = 16;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;

	switch(clock_freq)
	{
		case SYS_CLOCK_FREQ_50_MHZ:
		{
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 100;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
								 RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			FLatency = FLASH_ACR_LATENCY_1WS;
			break;
		}
		case SYS_CLOCK_FREQ_84_MHZ:
		{
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 168;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
								 RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			FLatency = FLASH_ACR_LATENCY_2WS;
			break;
		}
		case SYS_CLOCK_FREQ_120_MHZ:
		{
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 240;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
								 RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			FLatency = FLASH_ACR_LATENCY_3WS;
			break;
		}
		default:
			return;
	}

	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
	{
		Error_handler();
	}

	if(HAL_RCC_ClockConfig(&clk_init, FLatency) != HAL_OK)
	{
		Error_handler();
	}

	// SYSTICK Configuration
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}


/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;

	if( HAL_UART_Init(&huart2) != HAL_OK )
	{
		// There is a problem
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
