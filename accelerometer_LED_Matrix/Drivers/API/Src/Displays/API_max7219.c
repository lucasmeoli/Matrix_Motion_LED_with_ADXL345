/*
 * API_max7219_led_display.c
 *
 *  Created on: Apr 1, 2024
 *      Author: lpmeoli
 */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "API_max7219_port.h"
#include "API_max7219.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {
    REG_NO_OP           = 0x00,
    REG_DIGIT_0         = 0x01,
    REG_DIGIT_1         = 0x02,
    REG_DIGIT_2         = 0x03,
    REG_DIGIT_3         = 0x04,
    REG_DIGIT_4         = 0x05,
    REG_DIGIT_5         = 0x06,
    REG_DIGIT_6         = 0x07,
    REG_DIGIT_7         = 0x08,
    REG_DECODE_MODE     = 0x09,
    REG_INTENSITY       = 0x0A,
    REG_SCAN_LIMIT      = 0x0B,
    REG_SHUTDOWN        = 0x0C,
    REG_DISPLAY_TEST    = 0x0F,
} MAX7219_REGISTERS;

/* Private define ------------------------------------------------------------*/
#define MAX_DISPLAYS	4

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static SPI_HandleTypeDef hspi1;
static uint8_t active_displays = MAX_DISPLAYS; // Set max as default

/* Private function prototypes -----------------------------------------------*/
static void max7219_send_data(uint8_t reg, uint8_t data, uint8_t display_num);

/* Public functions ---------------------------------------------------------*/
bool_t max7219_SPI_init(SPI_HandleTypeDef aux_hspi1) {
	bool_t return_value = false;
	HAL_SPI_StateTypeDef spi_state;

	hspi1 = aux_hspi1;
	spi_state = SPI_get_state(&hspi1);;

	if ((spi_state != HAL_SPI_STATE_RESET) && (spi_state != HAL_SPI_STATE_ERROR)) {
			return_value = true;
	}

	return return_value;
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


void max7219_turn_on_LEDs(uint8_t reg, uint8_t data, uint8_t display_num) {
	if ((reg >= REG_DIGIT_0) && (reg <= REG_DIGIT_7)) {
		max7219_send_data(reg, data, display_num);
	}
}


/* ---------- Setters ---------- */
#define MAX7219_SET_REGISTER_FUNC(name,reg) \
void max7219_set_##name(uint8_t data, uint8_t display_num) { \
    max7219_send_data(reg, data, display_num); \
}

MAX7219_SET_REGISTER_FUNC(decode_mode, REG_DECODE_MODE)
MAX7219_SET_REGISTER_FUNC(intensity, REG_INTENSITY)
MAX7219_SET_REGISTER_FUNC(scan_limit, REG_SCAN_LIMIT)
MAX7219_SET_REGISTER_FUNC(shutdown, REG_SHUTDOWN)

void max7219_set_displays(uint8_t total_displays) {
	if (total_displays > MAX_DISPLAYS) {
		active_displays = MAX_DISPLAYS;
	} else {
		active_displays = total_displays;
	}
}


/* ---------- Getters ---------- */
HAL_SPI_StateTypeDef max7219_get_SPI_state() {
	return SPI_get_state(&hspi1);
}


/* Private functions ---------------------------------------------------------*/
/**
  * @brief Sends data to a specific register of a specific display.
  *
  * @param reg: The register address to write to.
  * 			data: The data to write to the register.
  * 			display_num: The number of the display to write data to. First display corresponds to number 0
  * @retval None
  */
static void max7219_send_data(uint8_t reg, uint8_t data, uint8_t display_num) {
	uint16_t buf = reg<<8 | data;
	uint16_t no_op = 0;

	if (display_num >= active_displays) {
		return;
	}

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

	/* The no-op register is used for cascading MAX7219 since is acts like a shift register of 16-bit word
	   To address a specific chip, send the desired 16-bit word followed by the appropriate no-op codes.
	   The positioning of the no-op codes depends on the chip you want to communicate with, either
	   preceding or following the desired word.	For example, in a cascade of four MAX7219s, writing to the
	   third chip requires sending first one no-op code, then the desired word followed by two no-op codes.
	   When LOAD/CS transitions high, data is latched in all devices.
	*/
	for (uint8_t i = ((active_displays-1)-display_num); i > 0; i--) {
		SPI_send_data(&hspi1, no_op, sizeof(uint8_t));
	}

	SPI_send_data(&hspi1, buf, sizeof(uint8_t));

	for (uint8_t i = 0; i < display_num; i++) {
		SPI_send_data(&hspi1, no_op, sizeof(uint8_t));
	}

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}




