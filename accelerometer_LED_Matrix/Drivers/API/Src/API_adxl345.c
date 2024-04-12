/*
 * API_adxl345.c
 *
 *  Created on: Mar 31, 2024
 *      Author: lpmeoli
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include "API_uart.h"
#include "API_adxl345.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADXL345_ADDRESS 	0x53

//Register address


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t pmesg_error[] = "ERROR!!!!! \n\r";
static I2C_HandleTypeDef hi2c1;

/* Private function prototypes -----------------------------------------------*/
static void write_register(uint8_t reg, uint8_t value);
static uint8_t read_register(uint8_t reg);


/* Public functions ---------------------------------------------------------*/
void adlx345_init() {
	if(HAL_I2C_GetState(&hi2c1) == HAL_I2C_STATE_RESET) {
		/* I2C configuration*/
		hi2c1.Instance 				= I2C1;
		hi2c1.Init.ClockSpeed 		= 100000;
		hi2c1.Init.DutyCycle 		= I2C_DUTYCYCLE_2;
		hi2c1.Init.OwnAddress1 		= 0;
		hi2c1.Init.AddressingMode 	= I2C_ADDRESSINGMODE_7BIT;
		hi2c1.Init.DualAddressMode 	= I2C_DUALADDRESS_DISABLE;
		hi2c1.Init.OwnAddress2 		= 0;
		hi2c1.Init.GeneralCallMode 	= I2C_GENERALCALL_DISABLE;
		hi2c1.Init.NoStretchMode 	= I2C_NOSTRETCH_DISABLE;


		HAL_I2C_MspInit(&hi2c1);

		if(HAL_I2C_Init(&hi2c1) != HAL_OK) {
			uart_send_string("Error en la INICIALIZACION \n\r");
		}

		/* Chequeo que la direccion statica sea correcta */
		if (read_register(REG_DEVID) != 0xE5) {
			uart_send_string("Error primer registro \n\r");
		}

		write_register(REG_BW_RATE, 0x08);
		write_register(REG_DATA_FORMAT, 0x08);
		write_register(REG_POWER_CTL, 0x08);
	}
}


void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c1) {
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* I2C GPIO configuration */
	GPIO_InitStruct.Pin 		= GPIO_PIN_8|GPIO_PIN_9;
	GPIO_InitStruct.Mode 		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate 	= GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	 /* Peripheral clock enable */
	__HAL_RCC_I2C1_CLK_ENABLE();
}



/**
 * @brief   Reads the coordinates from the ADXL345 accelerometer.
 * @param   None.
 * @retval  Coordinates structure containing X, Y, and Z coordinates.
 */
coordinates_t adxl345_read_coordinates() {
	uint8_t reg_data_coord = REG_DATAX0;
	coordinates_t coord;
	uint16_t coord_size = sizeof(coord)/ sizeof(uint8_t);

	if (HAL_I2C_Master_Transmit(&hi2c1, ADXL345_ADDRESS<<1, &reg_data_coord, sizeof(reg_data_coord), 1000) != HAL_OK) {
		uart_send_string("Error de que voy a leer\n\r");
	}

	if (HAL_I2C_Master_Receive(&hi2c1, ADXL345_ADDRESS<<1, (uint8_t *) &coord, coord_size, 10000) != HAL_OK) {
		uart_send_string("Error al lleer todas las cosas juntas\n\r");
	}

	return coord;
}



void adxl345_modify_sensitivity(adxl345_sensitivity_t sensitivity) {
	uint8_t reg_sensitivity = (0x00|sensitivity);
	write_register(REG_DATA_FORMAT, reg_sensitivity);
}




/* Private functions ---------------------------------------------------------*/

/**
 * @brief   Reads the value from the specified register of the ADXL345 accelerometer.
 * @param   reg: The register address to read from.
 * @retval  The value read from the specified register.
 */
static uint8_t read_register(uint8_t reg) {
	uint8_t value;

	if (HAL_I2C_Master_Transmit(&hi2c1, ADXL345_ADDRESS<<1, &reg, sizeof(reg), 10000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}
	if (HAL_I2C_Master_Receive(&hi2c1, ADXL345_ADDRESS<<1, &value, sizeof(value), 10000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}

	return value;
}


/**
 * @brief   Writes a value to the specified register of the ADXL345 accelerometer.
 * @param   reg: The register address to write to.
 * @param   value: The value to write to the register.
 * @retval  None.
 */
static void write_register(uint8_t reg, uint8_t value) {
	 uint8_t buf[] = {reg, value};
	 uint16_t size = sizeof(buf) / sizeof(uint8_t);

	if (HAL_I2C_Master_Transmit(&hi2c1, ADXL345_ADDRESS<<1, buf, size, 10000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}
}


