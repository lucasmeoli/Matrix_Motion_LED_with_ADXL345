/*
 * API_decode_coordinates.c
 *
 *  Created on: Apr 8, 2024
 *      Author: lpmeoli
 */


/* Includes ------------------------------------------------------------------*/


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h"

#include "API_uart.h"
#include "API_adxl345.h"
#include "API_max7219.h"

#include "API_decode_coordinates.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {
    CONFIGURE_MODULES,
    READ_COORDINATES,
    DECODE_COORDINATES,
    DISPLAY_COORDINATES,
} coordinatesState_t;

/* Private define ------------------------------------------------------------*/
#define ADXL345_BW_RATE_VALUE 		0x08 // Set normal operation and 25 Hz output data rate
#define ADXL345_DATA_FORMAT_VALUE 	0x08 // Set full resolution and 2g sensitivity
#define ADXL345_POWER_CTL_VALUE 	0x08 // Set measurement mode
#define COORD_MAX_VALUE    			256

#define MAX_DISPLAYS       			4
#define DISPLAY_DIVISIONS  			8

#define DISPLAY_X_INTERVAL			(COORD_MAX_VALUE*2)
#define RANGE_X_INTERVAL			(DISPLAY_X_INTERVAL / DISPLAY_DIVISIONS)
#define DISPLAY_Y_INTERVAL   		((COORD_MAX_VALUE*2) / MAX_DISPLAYS)
#define RANGE_Y_DIVISON      		(DISPLAY_Y_INTERVAL / DISPLAY_DIVISIONS)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static int16_t display_limits[MAX_DISPLAYS] = {-DISPLAY_Y_INTERVAL, 0, DISPLAY_Y_INTERVAL, COORD_MAX_VALUE};
static uint16_t decoded_x_coordinate;
static uint16_t decoded_y_coordinate;
static uint8_t current_display;
static coordinatesState_t current_state;
static coordinates_t coordinates;

/* Private function prototypes -----------------------------------------------*/
static void FSM_error_handler(void);
static void configure_adxl345(void);
static void configure_max7219(void);
static void decode_x_coordinate(void);
static void decode_y_coordinate(void);



/* Public functions ---------------------------------------------------------*/
bool_t coordinates_FSM_init() {
	HAL_I2C_StateTypeDef adxl345_i2c_state = adxl345_get_I2C_state();
	HAL_SPI_StateTypeDef max7219_spi_state = max7219_get_SPI_state();

	current_state = CONFIGURE_MODULES;

	if ((adxl345_i2c_state == HAL_I2C_STATE_ERROR) || (adxl345_i2c_state == HAL_I2C_STATE_RESET)) {
		return false;
	}

	if ((max7219_spi_state == HAL_SPI_STATE_ERROR) || (max7219_spi_state == HAL_SPI_STATE_RESET)) {
		return false;
	}

	return true;
}

void coordinates_FSM_update() {
	switch (current_state) {
		case CONFIGURE_MODULES:
			configure_adxl345();
			configure_max7219();

			current_state = READ_COORDINATES;
			break;

		case READ_COORDINATES:
			coordinates = adxl345_read_coordinates();

			if(coordinates.z_coord > 0) {
				current_state = DECODE_COORDINATES;
			}
			break;

		case DECODE_COORDINATES:
			decode_x_coordinate();
			decode_y_coordinate();

			current_state = DISPLAY_COORDINATES;
			break;

		case DISPLAY_COORDINATES:
			max7219_clean_all_displays();

			max7219_send_data(decoded_x_coordinate, decoded_y_coordinate, current_display);

			current_state = READ_COORDINATES;
			break;

		default:
			FSM_error_handler();
			break;
	}
}






/* Private functions ---------------------------------------------------------*/


static void configure_adxl345(void) {
	adxl345_set_BW_RATE(ADXL345_BW_RATE_VALUE);
	adxl345_set_DATA_FORMAT(ADXL345_DATA_FORMAT_VALUE);
	adxl345_set_POWER_CTL(ADXL345_POWER_CTL_VALUE);
}

static void configure_max7219(void) {
	for (int8_t display = 0; display < 4; display++) {
		max7219_send_data(REG_SHUTDOWN,		0x00, display);
		max7219_send_data(REG_DECODE_MODE,  0x00, display);
		max7219_send_data(REG_INTENSITY, 	0x03, display);
		max7219_send_data(REG_SCAN_LIMIT, 	0x07, display);
		max7219_send_data(REG_SHUTDOWN,		0x01, display);
	}
}


static void decode_x_coordinate(void) {
    if (coordinates.x_coord  > (-COORD_MAX_VALUE) && coordinates.x_coord < COORD_MAX_VALUE) {
    	decoded_x_coordinate = ((coordinates.x_coord  + COORD_MAX_VALUE) / RANGE_X_INTERVAL) + 1;
    }
}


static void decode_y_coordinate(void) {
	uint8_t max_index = MAX_DISPLAYS -1;
	uint8_t position;

    if ((coordinates.y_coord > (-COORD_MAX_VALUE)) && (coordinates.y_coord < COORD_MAX_VALUE)) {
    	for (int i = 0; i < MAX_DISPLAYS; i++) {
    	    if (coordinates.y_coord < display_limits[i]) {
    	        current_display = max_index - i;
    	        position = (coordinates.y_coord + display_limits[max_index-i]) / RANGE_Y_DIVISON;
    	        decoded_y_coordinate = 1 << (7 - position);
    	        break;
    	    }
    	}
    }
}





/**
 * @brief  This function is executed in case of error occurrence.
 *
 * @param  None
 * @retval None
 */
static void FSM_error_handler(void) {
	/* Turn LED2 on */
	BSP_LED_Init(LED2);
	BSP_LED_On(LED2);
	while (1)
	{
	}
}
