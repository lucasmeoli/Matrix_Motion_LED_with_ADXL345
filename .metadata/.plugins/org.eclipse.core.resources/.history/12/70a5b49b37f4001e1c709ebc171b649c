/*
 * API_max7219_led_display.h
 *
 *  Created on: Apr 1, 2024
 *      Author: lpmeoli
 */

#ifndef API_INC_API_MAX7219_LED_DISPLAY_H_
#define API_INC_API_MAX7219_LED_DISPLAY_H_

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

void init_max7219();
void send_data_SPI(uint8_t reg, uint8_t data);
void send_data_SPI2(uint8_t reg, uint8_t data);
void send_data_SPI3(uint8_t reg, uint8_t data);
void send_data_SPI4(uint8_t reg, uint8_t data);
#endif /* API_INC_API_MAX7219_LED_DISPLAY_H_ */
