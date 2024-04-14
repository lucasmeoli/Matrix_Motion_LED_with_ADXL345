#include "API_delay.h"

void delay_init(delay_t *delay, tick_t duration) {
	if ((delay == NULL) || (duration == 0))
		return;

	delay->duration = duration;
	delay->running = false;
	delay->start_time = 0;
}


bool_t delay_read(delay_t *delay) {
	uint32_t elapsed_time = 0;
	bool_t return_value = false;

	if (delay == NULL)
		return return_value;

	if (delay->running == false) {
		delay->start_time = HAL_GetTick();
		delay->running = true;
	} else {
		elapsed_time = HAL_GetTick() - delay->start_time;
		if (elapsed_time >= delay->duration) {
			delay->running = false;
			return_value = true;
		}
	}

	return return_value;
}


void delay_write(delay_t *delay, tick_t duration) {
	if ((delay == NULL) || (duration == 0))
		return;

	delay->duration = duration;
	delay->running = false;
	delay->start_time = 0;
}

bool_t delay_write_inactive_timer(delay_t *delay, tick_t duration) {
	if ((delay == NULL) || (duration == 0))
		return false;

	if (delay->running == false) {
		delay->duration = duration;
		return true;
	}

	return false;
}
