/*
 * API_accelerometer_adxl345.c
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

#include "API_accelerometer_adxl345.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADXL345_ADDRESS 	0x53

//Register address
#define	REG_DEVID			0x00
#define REG_THRESH_ACT		0x24
#define	REG_ACT_INACT_CTL	0x27
#define	REG_BW_RATE			0x2C
#define REG_POWER_CTL 		0x2D
#define REG_DATA_FORMAT 	0x31
#define REG_DATAX0 			0x32  //X-Axis Data 0
#define REG_DATAX1 			0x33  //X-Axis Data 1
#define REG_DATAY0 			0x34  //Y-Axis Data 0
#define REG_DATAY1 			0x35  //Y-Axis Data 1
#define REG_DATAZ0 			0x36  //Z-Axis Data 0
#define REG_DATAZ1 			0x37  //Z-Axis Data 1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t pmesg_error[] = "ERROR!!!!! \n\r";
static I2C_HandleTypeDef hi2c1;

/* Private function prototypes -----------------------------------------------*/
static void write_register(uint8_t reg, uint8_t value);
static uint8_t read_register(uint8_t reg);


/* Public functions ---------------------------------------------------------*/
void init_adlx345() {

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

	HAL_I2C_Init(&hi2c1);

	/* Chequeo que la direccion statica sea correcta */
	if (read_register(REG_DEVID) != 0xE5) {
		uart_send_string(pmesg_error);
	}

	write_register(REG_BW_RATE, 0x08);
	write_register(REG_DATA_FORMAT, 0x08);
	write_register(REG_POWER_CTL, 0x08);
}

/**
 * @brief   Reads the X-coordinate from the ADXL345 accelerometer.
 * @param   None.
 * @retval  Value of the X-coordinate read as a 16-bit integer.
 */
int16_t read_x_coordinate() {
	uint8_t reg_data_coord = REG_DATAX0;
	uint16_t x_coord;

	if (HAL_I2C_Master_Transmit(&hi2c1, ADXL345_ADDRESS<<1, &reg_data_coord, sizeof(reg_data_coord), 1000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}

	if (HAL_I2C_Master_Receive(&hi2c1, ADXL345_ADDRESS<<1, (uint8_t *) &x_coord, sizeof(x_coord), 10000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}

	return x_coord;
}

/**
 * @brief   Reads the Y-coordinate from the ADXL345 accelerometer.
 * @param   None.
 * @retval  Value of the Y-coordinate read as a 16-bit integer.
 */
int16_t read_y_coordinate() {
	uint8_t reg_data_coord = REG_DATAY0;
	uint16_t y_coord;

	if (HAL_I2C_Master_Transmit(&hi2c1, ADXL345_ADDRESS<<1, &reg_data_coord, sizeof(reg_data_coord), 1000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}

	if (HAL_I2C_Master_Receive(&hi2c1, ADXL345_ADDRESS<<1, (uint8_t *) &y_coord, sizeof(y_coord), 10000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}

	return y_coord;
}


/**
 * @brief   Reads the Z-coordinate from the ADXL345 accelerometer.
 * @param   None.
 * @retval  Value of the Z-coordinate read as a 16-bit integer.
 */
int16_t read_z_coordinate() {
	uint8_t reg_data_coord = REG_DATAZ0;
	uint16_t z_coord;

	if (HAL_I2C_Master_Transmit(&hi2c1, ADXL345_ADDRESS<<1, &reg_data_coord, sizeof(reg_data_coord), 1000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}

	if (HAL_I2C_Master_Receive(&hi2c1, ADXL345_ADDRESS<<1, (uint8_t *) &z_coord, sizeof(z_coord), 10000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}

	return z_coord;
}


/**
 * @brief   Reads the coordinates from the ADXL345 accelerometer.
 * @param   None.
 * @retval  Coordinates structure containing X, Y, and Z coordinates.
 */
coordinates_t read_coordinates() {
	uint8_t reg_data_coord = REG_DATAX0;
	coordinates_t coord;
	uint16_t coord_size = sizeof(coord) / sizeof(uint8_t);

	if (HAL_I2C_Master_Transmit(&hi2c1, ADXL345_ADDRESS<<1, &reg_data_coord, sizeof(reg_data_coord), 1000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}

	if (HAL_I2C_Master_Receive(&hi2c1, ADXL345_ADDRESS<<1, (uint8_t *) &coord, coord_size, 10000) != HAL_OK) {
		uart_send_string(pmesg_error);
	}

	return coord;
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













