/*
 * API_max7219_port.h
 *
 *  Created on: Apr 17, 2024
 *      Author: lpmeoli
 */

#ifndef API_INC_DISPLAYS_API_MAX7219_PORT_H_
#define API_INC_DISPLAYS_API_MAX7219_PORT_H_


/* Exported functions ------------------------------------------------------- */
/**
 * @brief   Sends data over SPI communication using the specified SPI peripheral.
 *
 * @param   p_hspi1: Pointer to an SPI_HandleTypeDef structure containing
 *          the configuration information for the specified SPI peripheral.
 * @param   data: The data to be sent over SPI.
 * @param   size: The size of the data to be sent, in bytes.
 */
void SPI_send_data(SPI_HandleTypeDef *p_hspi1, uint16_t data, uint16_t size);

/**
 * @brief   Obtains the current state of the specified SPI peripheral.
 *
 * @param   p_hspi1: Pointer to an SPI_HandleTypeDef structure containing
 *          the configuration information for the specified SPI peripheral.
 * @retval  The current state of the specified SPI peripheral.
 */
HAL_SPI_StateTypeDef SPI_get_state(SPI_HandleTypeDef *p_hspi1);
#endif /* API_INC_DISPLAYS_API_MAX7219_PORT_H_ */
