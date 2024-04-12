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
#include "API_max7219_led_display.h"
#include "API_adxl345.h"

#include "API_decode_coordinates.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {
    CONFIGURE_MODULES,
    READ_COORDINATES,
    DECODE_COORDINATES,
    DISPLAY_COORDINATES,
} coordinatesState_t;

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static coordinatesState_t current_state;
static coordinates_t coordinates;
static bool_t positive;
uint8_t coordenada_y;
uint8_t coordenada_x;
int indice;
uint8_t current_display;

/* Private function prototypes -----------------------------------------------*/
static void FSM_error_handler(void);


/* Public functions ---------------------------------------------------------*/
void coordinates_FSM_init() {
	current_state = CONFIGURE_MODULES;

	if(!uart_init()){
		FSM_error_handler();
	}

	adlx345_init();

	HAL_Delay(500);

	max7219_SPI_init();

	positive = false;
}

void coordinates_FSM_update() {
	switch (current_state) {
		case CONFIGURE_MODULES:
//			max7219_configure_displays();
			for (int8_t display = 0; display < 4; display++) {
				max7219_send_data(REG_SHUTDOWN,		0x00, display);
				max7219_send_data(REG_DECODE_MODE,  0x00, display);
				max7219_send_data(REG_INTENSITY, 	0x03, display);
				max7219_send_data(REG_SCAN_LIMIT, 	0x07, display);
				max7219_send_data(REG_SHUTDOWN,		0x01, display);
			}
			current_state = READ_COORDINATES;
			break;

		case READ_COORDINATES:
			coordinates = adxl345_read_coordinates();
			if(coordinates.z_coord>0) {
				current_state = DECODE_COORDINATES;
			}

			break;

		case DECODE_COORDINATES:
		    if (coordinates.y_coord >= -255 && coordinates.y_coord <= 255) {
		    	if (coordinates.y_coord <= -128) {
		    		current_display = 3;
			        indice = (coordinates.y_coord + 255) / 16;
			        coordenada_y = 1 << (7 - indice);
		    	} else if (coordinates.y_coord <= 0) {
			        indice = (coordinates.y_coord + 128) / 16;
			        coordenada_y = 1 << (7 - indice);
		    		current_display = 2;
		    	} else if (coordinates.y_coord <= 128) {
		    		current_display = 1;
			        indice = (coordinates.y_coord) / 16;
			        coordenada_y = 1 << (7 - indice);
		    	} else {
		    		current_display = 0;
			        indice = (coordinates.y_coord -128) / 16;
			        coordenada_y = 1 << (7 - indice);
		    	}



		    }

		    if (coordinates.x_coord  >= -255 && coordinates.x_coord <= 255) {
		        indice = (coordinates.x_coord  + 255) / 64;
		        coordenada_x = indice + 1;
		    }

			current_state = DISPLAY_COORDINATES;
			break;

		case DISPLAY_COORDINATES:
			max7219_clean_all_displays();

			max7219_send_data(coordenada_x, coordenada_y, current_display);
//			if (coordinates.y_coord > 0) {
//				//TODO tener en cuenta que podria hacer un clear displkay que mande todo de una bajando una sola vez el CS+
//
//				// Pensar si aca agregho un changin o no y que ahi se entre el update changin machine dependiendo de si se toco el pulsador o no
//				max7219_send_data(coordenada_x, coordenada_y, 2);
//
//			} else {
//				//TODO tener en cuenta que podria hacer un clear displkay que mande todo de una bajando una sola vez el CS
//
//				// Pensar si aca agregho un changin o no y que ahi se entre el update changin machine dependiendo de si se toco el pulsador o no
//
//
//
//			}

			current_state = READ_COORDINATES;
			break;

		default:
			FSM_error_handler();
			break;
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
