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
#define CLOCK_SPEED			100000	// This parameter must be set to a value lower than 400kHz
#define REGISTER_DEVID		0xE5


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t pmesg_error[] = "ERROR!!!!! \n\r";
static I2C_HandleTypeDef hi2c1;

/* Private function prototypes -----------------------------------------------*/
static void write_register(uint8_t reg, uint8_t value);
static uint8_t read_register(uint8_t reg);


/* Public functions ---------------------------------------------------------*/
#define DEFINE_ADXL345_REGISTER_FUNCTION(name, reg) \
    void adxl345_set_##name(uint8_t value) { \
        write_register(reg, value); \
    }

DEFINE_ADXL345_REGISTER_FUNCTION(BW_RATE, REG_BW_RATE)
DEFINE_ADXL345_REGISTER_FUNCTION(POWER_CTL, REG_POWER_CTL)
DEFINE_ADXL345_REGISTER_FUNCTION(DATA_FORMAT, REG_DATA_FORMAT)



bool_t adlx345_I2C_init() {
	bool_t return_value = false;
	HAL_I2C_StateTypeDef i2c_state = HAL_I2C_GetState(&hi2c1);

	if (i2c_state == HAL_I2C_STATE_RESET) {
		/* I2C configuration*/
		hi2c1.Instance 				= I2C1;
		hi2c1.Init.ClockSpeed 		= CLOCK_SPEED;
		hi2c1.Init.DutyCycle 		= I2C_DUTYCYCLE_2;
		hi2c1.Init.AddressingMode 	= I2C_ADDRESSINGMODE_7BIT;
		hi2c1.Init.DualAddressMode 	= I2C_DUALADDRESS_DISABLE;
		hi2c1.Init.GeneralCallMode 	= I2C_GENERALCALL_DISABLE;
		hi2c1.Init.NoStretchMode 	= I2C_NOSTRETCH_DISABLE;

		HAL_I2C_MspInit(&hi2c1);

		// Init I2C and read static device ID to check communication
		if ((HAL_I2C_Init(&hi2c1) == HAL_OK) && (read_register(REG_DEVID) == REGISTER_DEVID)) {
			return_value = true;
		}
	} else if (i2c_state != HAL_I2C_STATE_ERROR) {
		// Not an STATE_ERROR or STATE_RESET,so initialization was already done
		return_value = true;
	}

	return return_value;
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

HAL_I2C_StateTypeDef adxl345_get_I2C_state() {
	return HAL_I2C_GetState(&hi2c1);
}



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



void adxl345_set_sensitivity(adxl345_sensitivity_t sensitivity) {
	uint8_t reg_sensitivity = sensitivity;

	if (sensitivity > RESOLUTION_16G) {
		return;
	}

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


