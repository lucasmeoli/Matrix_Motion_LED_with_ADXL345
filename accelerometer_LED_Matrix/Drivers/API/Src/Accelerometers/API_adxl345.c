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
#include "API_adxl345_port.h"
#include "API_adxl345.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {
	REG_DEVID			= 0x00,
	REG_THRESH_ACT		= 0x24,
	REG_ACT_INACT_CTL	= 0x27,
	REG_BW_RATE			= 0x2C,
	REG_POWER_CTL 		= 0x2D,
	REG_INT_SOURCE		= 0x30,
	REG_DATA_FORMAT 	= 0x31,
	REG_DATAX0 			= 0x32,
	REG_DATAX1 			= 0x33,
	REG_DATAY0 			= 0x34,
	REG_DATAY1 			= 0x35,
	REG_DATAZ0 			= 0x36,
	REG_DATAZ1 			= 0x37,
} adxl345_register_t;

/* Private define ------------------------------------------------------------*/
#define REGISTER_DEVID		0xE5
#define MASK_DATA_READY		0x80

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static I2C_HandleTypeDef hi2c1;

/* Private function prototypes -----------------------------------------------*/
/* Public functions ---------------------------------------------------------*/

bool_t adxl345_I2C_init(I2C_HandleTypeDef aux_hi2c) {
	bool_t return_value = false;
	HAL_I2C_StateTypeDef i2c_state;

	hi2c1 = aux_hi2c;
	i2c_state = I2C_get_state(&hi2c1);

	if ((i2c_state != HAL_I2C_STATE_RESET) && (i2c_state != HAL_I2C_STATE_ERROR)) {

		if ((I2C_read_register(&hi2c1, REG_DEVID) == REGISTER_DEVID)) {
			return_value = true;
		}
	}

	return return_value;
}

coordinates_t adxl345_read_coordinates() {
	uint8_t reg_data_coord = REG_DATAX0;
	coordinates_t coord;
	uint16_t coord_size = sizeof(coord)/ sizeof(uint8_t);

	I2C_read_registers(&hi2c1, reg_data_coord, (uint8_t *) &coord, coord_size);

	return coord;
}


HAL_I2C_StateTypeDef adxl345_get_I2C_state() {
	return I2C_get_state(&hi2c1);
}

bool_t adxl345_is_data_ready() {
	uint8_t reg = REG_INT_SOURCE;
	uint8_t value = I2C_read_register(&hi2c1,reg);

	if (value&MASK_DATA_READY) {
		return true;
	} else {
		return false;
	}
}

void adxl345_set_sensitivity(adxl345_sensitivity_t sensitivity) {
	uint8_t reg_sensitivity = sensitivity;

	if (sensitivity > RESOLUTION_16G) {
		return;
	}

	I2C_write_register(&hi2c1, REG_DATA_FORMAT, reg_sensitivity);
}


#define DEFINE_ADXL345_REGISTER_FUNCTION(name, reg) \
    void adxl345_set_##name(uint8_t value) { \
		I2C_write_register(&hi2c1, reg, value); \
    }

DEFINE_ADXL345_REGISTER_FUNCTION(bandwidth_rate, REG_BW_RATE)
DEFINE_ADXL345_REGISTER_FUNCTION(power_control, REG_POWER_CTL)
DEFINE_ADXL345_REGISTER_FUNCTION(data_format, REG_DATA_FORMAT)


