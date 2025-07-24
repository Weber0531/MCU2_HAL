/*
 * msp.c
 *
 *  Created on: Jul 1, 2025
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
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// 2. Configure GPIOs to behave as timer3 channel 1,2,3 and 4
	/* PC6 --> TIM3_CH1
	   PB5 --> TIM3_CH2
	   PC8 --> TIM3_CH3
	   PC9 --> TIM3_CH4 */
	tim3OC_ch_gpios.Mode = GPIO_MODE_AF_PP;
	tim3OC_ch_gpios.Alternate = GPIO_AF2_TIM3;
	tim3OC_ch_gpios.Pull = GPIO_NOPULL;
	tim3OC_ch_gpios.Speed = GPIO_SPEED_FREQ_LOW;

	tim3OC_ch_gpios.Pin = GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9;
	HAL_GPIO_Init(GPIOC, &tim3OC_ch_gpios);

	tim3OC_ch_gpios.Pin = GPIO_PIN_5;
	HAL_GPIO_Init(GPIOB, &tim3OC_ch_gpios);

	// 3. NVIC settings
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	HAL_NVIC_SetPriority(TIM3_IRQn, 15, 0);
}


/**
  * @brief  UART MSP Init.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;

	// Here we are going to do the low level inits of the USART2 peripheral
	// 1. enable the clock for the USART2 peripheral as well as for GPIOA peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// 2. Do the pin muxing configurations
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Alternate = GPIO_AF1_TIM2;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;

	gpio_uart.Pin = GPIO_PIN_2; // USART2 TX
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin = GPIO_PIN_3; // USART2 RX
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	// 3 . Enable the IRQ and set up the priority (NVIC settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}
