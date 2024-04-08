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
#include "API_accelerometer_adxl345.h"
#include "API_max7219_led_display.h"

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
int indice;

/* Private function prototypes -----------------------------------------------*/
static void FSM_error_handler(void);


/* Public functions ---------------------------------------------------------*/
void coordinates_FSM_init() {
	current_state = CONFIGURE_MODULES;

	if(!uart_init()){
		FSM_error_handler();
	}

	adlx345_init();

	max7219_SPI_init();

	positive = false;
}

void coordinates_FSM_update() {
	switch (current_state) {
		case CONFIGURE_MODULES:
			for (int8_t display = 0; display < 2; display++) {
				max7219_send_data(REG_SHUTDOWN,		0x00, display);
				max7219_send_data(REG_DECODE_MODE,  0x00, display);
				max7219_send_data(REG_INTENSITY, 	0x03, display);
				max7219_send_data(REG_SCAN_LIMIT, 	0x07, display);
				max7219_send_data(REG_SHUTDOWN,		0x01, display);
			}


			current_state = READ_COORDINATES;



			max7219_send_data(REG_DIGIT_0, 0x00, 0);
			max7219_send_data(REG_DIGIT_1, 0x00, 0);
			max7219_send_data(REG_DIGIT_2, 0x00, 0);
			max7219_send_data(REG_DIGIT_3, 0x00, 0);
			max7219_send_data(REG_DIGIT_4, 0x00, 0);
			max7219_send_data(REG_DIGIT_5, 0x00, 0);
			max7219_send_data(REG_DIGIT_6, 0x00, 0);
			max7219_send_data(REG_DIGIT_7, 0x00, 0);


			break;

		case READ_COORDINATES:
			coordinates = read_coordinates();

			current_state = DECODE_COORDINATES;
			break;

		case DECODE_COORDINATES:

		    if (coordinates.y_coord >= -255 && coordinates.y_coord <= 255) {
		        indice = (coordinates.y_coord + 255) / 64; // Calcula el índice del bit activado
		        coordenada_y = 1 << (7 - indice); // Enciende el bit correspondiente
		    }


			if( coordinates.y_coord < 0) {
				positive = false;
			} else {
				positive = true;
			}

			current_state = DISPLAY_COORDINATES;
			break;

		case DISPLAY_COORDINATES:




			max7219_send_data(REG_DIGIT_0, coordenada_y, 0);

//			if(positive) {
//
//				//uart_send_string("Negativo\n\r");
//
//				max7219_send_data(REG_DIGIT_0, 0xFF, 0);
////				max7219_send_data(REG_DIGIT_1, 0xFF, 0);
////				max7219_send_data(REG_DIGIT_2, 0xFF, 0);
////				max7219_send_data(REG_DIGIT_3, 0xFF, 0);
////				max7219_send_data(REG_DIGIT_4, 0x00, 0);
////				max7219_send_data(REG_DIGIT_5, 0x00, 0);
////				max7219_send_data(REG_DIGIT_6, 0x00, 0);
////				max7219_send_data(REG_DIGIT_7, 0x00, 0);
//
//
//			} else {
//				//uart_send_string("Positivo\n\r");
//
//				max7219_send_data(REG_DIGIT_0, 0x00, 0);
////				max7219_send_data(REG_DIGIT_1, 0x00, 0);
////				max7219_send_data(REG_DIGIT_2, 0x00, 0);
////				max7219_send_data(REG_DIGIT_3, 0x00, 0);
////				max7219_send_data(REG_DIGIT_4, 0xFF, 0);
////				max7219_send_data(REG_DIGIT_5, 0xFF, 0);
////				max7219_send_data(REG_DIGIT_6, 0xFF, 0);
////				max7219_send_data(REG_DIGIT_7, 0xFF, 0);
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