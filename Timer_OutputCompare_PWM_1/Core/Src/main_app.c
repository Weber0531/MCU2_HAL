/*
 * main_app.c
 *
 *  Created on: Jul 1, 2025
 *      Author: weber
 */


/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "main_app.h"

/* Private function prototypes -----------------------------------------------*/
void GPIO_Init(void);
void Error_Handler(void);
void TIMER3_Init(void);
void UART2_Init(void);
void SystemClock_Config_HSE(uint8_t clock_freq);

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htimer3;
UART_HandleTypeDef huart2;

int main(void)
{
	HAL_Init();

	SystemClock_Config_HSE(SYS_CLOCK_FREQ_50_MHZ);

	GPIO_Init();

	TIMER3_Init();

	UART2_Init();

	if( HAL_TIM_PWM_Start(&htimer3, TIM_CHANNEL_1) != HAL_OK )
	{
		Error_Handler();
	}

	if( HAL_TIM_PWM_Start(&htimer3, TIM_CHANNEL_2) != HAL_OK )
	{
		Error_Handler();
	}

	if( HAL_TIM_PWM_Start(&htimer3, TIM_CHANNEL_3) != HAL_OK )
	{
		Error_Handler();
	}

	if( HAL_TIM_PWM_Start(&htimer3, TIM_CHANNEL_4) != HAL_OK )
	{
		Error_Handler();
	}

	while(1);

	return 0;
}


void SystemClock_Config_HSE(uint8_t clock_freq)
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	uint32_t FLatency = 0;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_ON;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

	switch(clock_freq)
	{
	case SYS_CLOCK_FREQ_50_MHZ:
	{
		osc_init.PLL.PLLM = 4;
		osc_init.PLL.PLLN = 50;
		osc_init.PLL.PLLP = RCC_PLLP_DIV2;
		osc_init.PLL.PLLQ = 2;

		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
							 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
		clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
		clk_init.APB2CLKDivider = RCC_HCLK_DIV1;

		FLatency = FLASH_ACR_LATENCY_1WS;
		break;
	}
	case SYS_CLOCK_FREQ_84_MHZ:
	{
		osc_init.PLL.PLLM = 4;
		osc_init.PLL.PLLN = 84;
		osc_init.PLL.PLLP = RCC_PLLP_DIV2;
		osc_init.PLL.PLLQ = 2;

		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
							 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
		clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
		clk_init.APB2CLKDivider = RCC_HCLK_DIV1;

		FLatency = FLASH_ACR_LATENCY_2WS;
		break;
	}
	case SYS_CLOCK_FREQ_120_MHZ:
	{
		osc_init.PLL.PLLM = 4;
		osc_init.PLL.PLLN = 120;
		osc_init.PLL.PLLP = RCC_PLLP_DIV2;
		osc_init.PLL.PLLQ = 2;

		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
							 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
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
		Error_Handler();
	}

	if(HAL_RCC_ClockConfig(&clk_init, FLatency) != HAL_OK)
	{
		Error_Handler();
	}

	/* Configure the systick timer interrupt frequency (for every 1 ms) */
	uint32_t hclk_freq = HAL_RCC_GetHCLKFreq();
	HAL_SYSTICK_Config(hclk_freq / 1000);

	/* Configure the Systick */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


void GPIO_Init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef gpioled;
	gpioled.Pin = GPIO_PIN_12;
	gpioled.Mode = GPIO_MODE_OUTPUT_PP;
	gpioled.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &gpioled);
}


void TIMER3_Init(void)
{
	TIM_OC_InitTypeDef tim3PWM_Config;

	htimer3.Instance = TIM3;
	htimer3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimer3.Init.Period = 10000 - 1;
	htimer3.Init.Prescaler = 4;
	if( HAL_TIM_PWM_Init(&htimer3) != HAL_OK )
	{
		Error_Handler();
	}

	memset(&tim3PWM_Config, 0, sizeof(tim3PWM_Config));

	tim3PWM_Config.OCMode = TIM_OCMODE_PWM1;
	tim3PWM_Config.OCPolarity = TIM_OCPOLARITY_HIGH;
	tim3PWM_Config.Pulse = (htimer3.Init.Period * 25) / 100;
	if( HAL_TIM_PWM_ConfigChannel(&htimer3, &tim3PWM_Config, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}

	tim3PWM_Config.Pulse = (htimer3.Init.Period * 45) / 100;
	if( HAL_TIM_PWM_ConfigChannel(&htimer3, &tim3PWM_Config, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}

	tim3PWM_Config.Pulse = (htimer3.Init.Period * 75) / 100;
	if( HAL_TIM_PWM_ConfigChannel(&htimer3, &tim3PWM_Config, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}

	tim3PWM_Config.Pulse = (htimer3.Init.Period * 90) / 100;
	if( HAL_TIM_PWM_ConfigChannel(&htimer3, &tim3PWM_Config, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}
}


void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;

	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
}


void Error_Handler(void)
{
	while(1);
}
