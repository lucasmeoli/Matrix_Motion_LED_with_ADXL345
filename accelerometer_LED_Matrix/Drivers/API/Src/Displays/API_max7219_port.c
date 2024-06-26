/*
 * API_max7219_port.c
 *
 *  Created on: Apr 17, 2024
 *      Author: lpmeoli
 */
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include "API_max7219.h"
#include "API_max7219_port.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SPI_TIMEOUT			1000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void SPI_send_data(SPI_HandleTypeDef *p_hspi1, uint16_t data, uint16_t size) {
	HAL_SPI_Transmit(p_hspi1, (uint8_t *)&data, size, SPI_TIMEOUT);
}

HAL_SPI_StateTypeDef SPI_get_state(SPI_HandleTypeDef *p_hspi1) {
	return HAL_SPI_GetState(p_hspi1);
}



