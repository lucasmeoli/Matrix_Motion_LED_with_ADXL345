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

#include "API_max7219.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_DISPLAYS 			4

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static SPI_HandleTypeDef hspi1;
static uint8_t active_displays = MAX_DISPLAYS; // Set max as default
/* Private function prototypes -----------------------------------------------*/
/* Public functions ---------------------------------------------------------*/

bool_t max7219_SPI_init() {
	bool_t return_value = false;
	HAL_SPI_StateTypeDef spi_state = HAL_SPI_GetState(&hspi1);

	if(spi_state == HAL_SPI_STATE_RESET) {
		/* SPI configuration*/
		hspi1.Instance 					= SPI1;
		hspi1.Init.Mode 				= SPI_MODE_MASTER;
		hspi1.Init.Direction			= SPI_DIRECTION_1LINE;
		hspi1.Init.DataSize				= SPI_DATASIZE_16BIT;
		hspi1.Init.CLKPolarity			= SPI_POLARITY_LOW;
		hspi1.Init.CLKPhase				= SPI_PHASE_1EDGE;
		hspi1.Init.NSS 					= SPI_NSS_SOFT;
		hspi1.Init.BaudRatePrescaler 	= SPI_BAUDRATEPRESCALER_128;
		hspi1.Init.FirstBit				= SPI_FIRSTBIT_MSB;
		hspi1.Init.TIMode				= SPI_TIMODE_DISABLE;
		hspi1.Init.CRCCalculation 		= SPI_CRCCALCULATION_DISABLE;

		HAL_SPI_MspInit(&hspi1);
		if (HAL_SPI_Init(&hspi1) == HAL_OK) {
			return_value = true;
		}

		// Release Chip Select pin
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	} else if (spi_state != HAL_SPI_STATE_ERROR) {
		// Not an STATE_ERROR or STATE_RESET,so initialization was already done
		return_value = true;
	}
	return return_value;
}


void max7219_set_displays(uint8_t total_displays) {
	if (total_displays > MAX_DISPLAYS) {
		active_displays = MAX_DISPLAYS;
	} else {
		active_displays = total_displays;
	}
}

HAL_SPI_StateTypeDef max7219_get_SPI_state() {
	return HAL_SPI_GetState(&hspi1);
}


void max7219_send_data(uint8_t reg, uint8_t data, uint8_t display_num) {
	uint16_t buf = reg<<8 | data;
	uint16_t no_op = 0;

	if (display_num >= active_displays) {
		return;
	}

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

	for (uint8_t i = ((active_displays-1)-display_num); i > 0; i--) {
	    HAL_SPI_Transmit(&hspi1, (uint8_t *)&no_op, 1, 1000);
	}

	HAL_SPI_Transmit(&hspi1, (uint8_t *)&buf, 1, 1000);

	for (uint8_t i = 0; i < display_num; i++) {
		HAL_SPI_Transmit(&hspi1, (uint8_t *)&no_op, 1, 1000);
	}

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}


void max7219_clean_display(uint8_t display_num) {
	if (display_num >= active_displays) {
		return;
	}

	max7219_send_data(REG_DIGIT_0, 0x00, display_num);
	max7219_send_data(REG_DIGIT_1, 0x00, display_num);
	max7219_send_data(REG_DIGIT_2, 0x00, display_num);
	max7219_send_data(REG_DIGIT_3, 0x00, display_num);
	max7219_send_data(REG_DIGIT_4, 0x00, display_num);
	max7219_send_data(REG_DIGIT_5, 0x00, display_num);
	max7219_send_data(REG_DIGIT_6, 0x00, display_num);
	max7219_send_data(REG_DIGIT_7, 0x00, display_num);
}


void max7219_clean_all_displays() {
	for (uint8_t i = 0; i < MAX_DISPLAYS; i++) {
		max7219_send_data(REG_DIGIT_0, 0x00, i);
		max7219_send_data(REG_DIGIT_1, 0x00, i);
		max7219_send_data(REG_DIGIT_2, 0x00, i);
		max7219_send_data(REG_DIGIT_3, 0x00, i);
		max7219_send_data(REG_DIGIT_4, 0x00, i);
		max7219_send_data(REG_DIGIT_5, 0x00, i);
		max7219_send_data(REG_DIGIT_6, 0x00, i);
		max7219_send_data(REG_DIGIT_7, 0x00, i);
	}
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi) {
	GPIO_InitTypeDef  GPIO_InitStruct;

  	/*** Configure the GPIOs ***/
  	/* Enable GPIO clock */
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* Configure SPI SCK */
	GPIO_InitStruct.Pin 		= GPIO_PIN_5;
	GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull  		= GPIO_PULLDOWN;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate 	= GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Configure SPI MOSI */
	GPIO_InitStruct.Pin 		= GPIO_PIN_7;
	GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate 	= GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure SPI CS */
	GPIO_InitStruct.Pin 		= GPIO_PIN_4;
	GPIO_InitStruct.Mode 		= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull 		= GPIO_PULLUP;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*** Configure the SPI peripheral ***/
	/* Enable SPI clock */
	/* Peripheral clock enable */
	__HAL_RCC_SPI1_CLK_ENABLE();
}

/* Private functions ---------------------------------------------------------*/







