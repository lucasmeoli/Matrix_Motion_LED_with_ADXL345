#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"

/* Public typedef -----------------------------------------------------------*/
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
	tick_t start_time;
	tick_t duration;
	bool_t running;
} delay_t;

/* Public function prototypes -----------------------------------------------*/

/**
 * @brief  Initializes the delay structure with the given duration.
 *
 * @param  delay: Pointer to the structure representing the delay.
 * 		   time_ms: The duration of the delay in milliseconds. It must be greater than 0.
 * @retval None
 */
void delay_init(delay_t * delay, tick_t duration);

/**
 * @brief  Checks the state of the 'running' flag. If true, calculates
 * whether the delay time has elapsed or not. When the delay time elapses,
 * sets the 'running' flag to false.
 *
 * @param  delay: Pointer to the structure representing the delay.
 * @retval Boolean value indicating whether the delay time has elapsed.
 */
bool_t delay_read(delay_t * delay);

/**
 * @brief  Allows changing the duration time of an existing delay. If there was a timer running it stop and
 * write a new timer without waiting the timer to stop.
 *
 * @param  delay: Pointer to the structure representing the delay.
 *  	   duration: The new duration time for the delay in milliseconds. Must be greater than 0.
 * @retval None
 */
void delay_write(delay_t * delay, tick_t duration);

/**
 * @brief  Allows changing the duration time of an existing delay only if the
 * delay it is not running.
 *
 * @param  delay: Pointer to the structure representing the delay.
 *  	   duration: The new duration time for the delay in milliseconds. Must be greater than 0.
 * @retval Boolean value indicating if it was possible to change timer time.
 */
bool_t delay_write_inactive_timer(delay_t *delay, tick_t duration);



#endif /* API_INC_API_DELAY_H_ */
