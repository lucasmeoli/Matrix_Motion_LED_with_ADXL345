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

typedef enum {
	REG_DEVID			= 0x00,
	REG_THRESH_ACT		= 0x24,
	REG_ACT_INACT_CTL	= 0x27,
	REG_BW_RATE			= 0x2C,
	REG_POWER_CTL 		= 0x2D,
	REG_DATA_FORMAT 	= 0x31,
	REG_DATAX0 			= 0x32, //X-Axis Data 0
	REG_DATAX1 			= 0x33, //X-Axis Data 1
	REG_DATAY0 			= 0x34, //Y-Axis Data 0
	REG_DATAY1 			= 0x35, //Y-Axis Data 1
	REG_DATAZ0 			= 0x36, //Z-Axis Data 0
	REG_DATAZ1 			= 0x37, //Z-Axis Data 1
} ADLX345_REGISTERS;


void adlx345_init();
int16_t read_x_coordinate();
int16_t read_y_coordinate();
int16_t read_z_coordinate();
coordinates_t read_coordinates();

#endif /* API_INC_API_ACCELEROMETER_ADXL345_H_ */
