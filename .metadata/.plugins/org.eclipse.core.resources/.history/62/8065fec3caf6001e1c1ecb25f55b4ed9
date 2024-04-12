/*
 * API_debounce.h
 *
 *  Created on: Mar 22, 2024
 *      Author: lpmeoli
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

/* Function prototypes -----------------------------------------------*/

/**
 * @brief  Initialize the Finite State Machine (FSM) for debounce mechanism.
 * It also starts the non-blocking delay for debounce with the specified time.
 *
 * @param  time: The debounce time for stabilizing button inputs
 * @retval None
 */
void debounce_FSM_init(uint32_t debounceTime);

/**
 * @brief  FSM logic. It updates the debounce FSM state depending on the current state value,
 * the button state, and the debounce timer.
 *
 * @param  None
 * @retval None
 */
void debounce_FSM_update();

/**
 * @brief Reads the state of the key and resets the flag for a falling edge in case of true value.
 *
 * @param  None
 * @retval None
 */
bool_t read_key();

#endif /* API_INC_API_DEBOUNCE_H_ */
