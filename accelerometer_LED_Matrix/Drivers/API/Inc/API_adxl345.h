/*
 * API_accelerometer_adxl345.h
 *
 *  Created on: Mar 31, 2024
 *      Author: lpmeoli
 */

#ifndef API_INC_API_ADXL345_H_
#define API_INC_API_ADXL345_H_

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
} adxl345_register_t;

typedef enum {
	RESOLUTION_2G		= 0x00,
	RESOLUTION_4G		= 0x01,
	RESOLUTION_8G		= 0x02,
	RESOLUTION_16G		= 0x03,
} adxl345_sensitivity_t;


void adlx345_init();
coordinates_t adxl345_read_coordinates();
void adxl345_modify_sensitivity(adxl345_sensitivity_t sensitivity);

#endif /* API_INC_API_ADXL345_H_ */
