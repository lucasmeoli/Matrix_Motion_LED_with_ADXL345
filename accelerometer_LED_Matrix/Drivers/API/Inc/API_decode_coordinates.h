/*
 * API_decode_coordinates.h
 *
 *  Created on: Apr 8, 2024
 *      Author: lpmeoli
 */

#ifndef API_INC_API_DECODE_COORDINATES_H_
#define API_INC_API_DECODE_COORDINATES_H_


/*
 * @brief  Initializes the coordinate Finite State Machine (FSM) and checks the initialization status of following modules:
 *		   - I2C for adxl345 accelerometer
 *		   - SPI for MAX7219 matrix display
 *		   - UART
 *		   It only initialize modules if they were not initialized before.
 *
 * @param  None
 * @retval bool_t - TRUE if all communication modules (I2C, SPI, UART) are running, false otherwise.
*/
bool_t coordinates_FSM_init();

/**
 * @brief  FSM logic. It updates the coordinate FSM state depending on the current state value,
 * 		   the adxl coordinates value. It also decodes coordinates to show them in 8x32 matrix display and
 * 		   via UART.
 *
 * @param  None
 * @retval None
 */
void coordinates_FSM_update();

#endif /* API_INC_API_DECODE_COORDINATES_H_ */
