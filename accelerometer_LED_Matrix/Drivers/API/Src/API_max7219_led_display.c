/*
 * API_max7219_led_display.c
 *
 *  Created on: Apr 1, 2024
 *      Author: lpmeoli
 */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */


#include "API_max7219_led_display.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi1;

/* Private function prototypes -----------------------------------------------*/



/* Public functions ---------------------------------------------------------*/

void init_max7219() {

	/* I2C configuration*/
	hspi1.Instance 					= SPI1;
	hspi1.Init.Mode 				= SPI_MODE_MASTER;
	hspi1.Init.Direction			= SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize				= SPI_DATASIZE_16BIT;
	hspi1.Init.CLKPolarity			= SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase				= SPI_PHASE_2EDGE; //example internet it said 1
	//hspi1.Init.NSS					=
	//hspi1.Init.BaudRatePrescaler 	= SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit				= SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode				= SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation 		= SPI_CRCCALCULATION_DISABLE;

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* I2C GPIO configuration */
	GPIO_InitStruct.Pin 		= GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7;
	GPIO_InitStruct.Mode 		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate 	= GPIO_AF5_SPI1;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	 /* Peripheral clock enable */
	__HAL_RCC_SPI1_CLK_ENABLE();

	HAL_SPI_Init(&hspi1);

}

/* Private functions ---------------------------------------------------------*/















