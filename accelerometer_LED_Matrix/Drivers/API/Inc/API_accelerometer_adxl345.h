/*
 * API_accelerometer_adxl345.h
 *
 *  Created on: Mar 31, 2024
 *      Author: lpmeoli
 */

#ifndef API_INC_API_ACCELEROMETER_ADXL345_H_
#define API_INC_API_ACCELEROMETER_ADXL345_H_

typedef struct {
	int16_t x_coord;
	int16_t y_coord;
	int16_t z_coord;
} coordinates_t;


void init_adlx345();
int16_t read_x_coordinate();
int16_t read_y_coordinate();
int16_t read_z_coordinate();
coordinates_t read_coordinates();

#endif /* API_INC_API_ACCELEROMETER_ADXL345_H_ */
