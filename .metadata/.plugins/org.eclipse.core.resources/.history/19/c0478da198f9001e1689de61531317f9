/*
 * API_adxl345_sensitivity.h
 *
 *  Created on: Apr 9, 2024
 *      Author: lpmeoli
 */

#ifndef API_INC_API_ADXL345_SENSITIVITY_H_
#define API_INC_API_ADXL345_SENSITIVITY_H_
/* Function prototypes -----------------------------------------------*/

/**
 * @brief  Initialize the Finite State Machine (FSM) for debounce mechanism.
 * It also starts the non-blocking delay for debounce with the specified time.
 *
 * @param  time: The debounce time for stabilizing button inputs
 * @retval None
 */
void sensitivity_FSM_init();

/**
 * @brief  FSM logic. It updates the debounce FSM state depending on the current state value,
 * the button state, and the debounce timer.
 *
 * @param  None
 * @retval None
 */
void sensitivity_FSM_update(uint8_t taps);

#endif /* API_INC_API_ADXL345_SENSITIVITY_H_ */
