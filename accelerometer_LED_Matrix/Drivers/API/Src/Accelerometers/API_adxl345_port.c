/*
 * API_adxl345_port.c
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
#include "API_adxl345.h"
#include "API_adxl345_port.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_TIMEOUT			1000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
uint8_t I2C_read_register(I2C_HandleTypeDef *p_hi2c, uint8_t reg) {
	uint8_t value;

	HAL_I2C_Master_Transmit(p_hi2c, ADXL345_ADDRESS<<1, &reg, sizeof(reg), I2C_TIMEOUT);
	HAL_I2C_Master_Receive(p_hi2c, ADXL345_ADDRESS<<1, &value, sizeof(value), I2C_TIMEOUT);

	return value;
}


void I2C_write_register(I2C_HandleTypeDef *p_hi2c, uint8_t reg, uint8_t value) {
	 uint8_t buf[] = {reg, value};
	 uint16_t size = sizeof(buf) / sizeof(uint8_t);

	 HAL_I2C_Master_Transmit(p_hi2c, ADXL345_ADDRESS<<1, buf, size, I2C_TIMEOUT);
}


void I2C_read_registers(I2C_HandleTypeDef *p_hi2c, uint8_t reg_data, uint8_t * p_data, uint16_t data_size) {
	HAL_I2C_Master_Transmit(p_hi2c, ADXL345_ADDRESS<<1, &reg_data, sizeof(reg_data), I2C_TIMEOUT);
	HAL_I2C_Master_Receive(p_hi2c, ADXL345_ADDRESS<<1,p_data, data_size, I2C_TIMEOUT);
}


HAL_I2C_StateTypeDef I2C_get_state(I2C_HandleTypeDef *p_hi2c) {
	return HAL_I2C_GetState(p_hi2c);
}
