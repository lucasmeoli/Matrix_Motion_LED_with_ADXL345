/*
 * API_accelerometer_adxl345.h
 *
 *  Created on: Mar 31, 2024
 *      Author: lpmeoli
 */

#ifndef API_INC_API_ADXL345_H_
#define API_INC_API_ADXL345_H_

/* Exported types ------------------------------------------------------------*/
typedef bool bool_t;

typedef struct {
	int16_t x_coord;
	int16_t y_coord;
	int16_t z_coord;
} coordinates_t;

typedef enum {
	RESOLUTION_2G		= 0x00,
	RESOLUTION_4G		= 0x01,
	RESOLUTION_8G		= 0x02,
	RESOLUTION_16G		= 0x03,
} adxl345_sensitivity_t;

/* Exported constants --------------------------------------------------------*/
#define ADXL345_ADDRESS 	0x53


/* Exported functions ------------------------------------------------------- */

/**
  * @brief  Initializes the I2C1 communication interface with the ADXL345 accelerometer.
  *         This function configures the I2C1 peripheral for communication with the ADXL345 accelerometer.
  *         It sets the clock speed to 100 kHz and the addressing mode to 7 bits.
  *         If the I2C1 peripheral is in RESET state, it configures the peripheral with specified parameters.
  *         After initialization, it verifies communication by reading the static device ID register.
  *
  * @param  None
  * @retval bool_t - TRUE if initialization is successful or if it has already been initialized successfully; FALSE otherwise.
  */
bool_t adxl345_I2C_init(I2C_HandleTypeDef aux_hi2c);

/**
 * @brief   Reads the coordinates from the ADXL345 accelerometer.
 *
 * @param   None.
 * @retval  Coordinates structure containing X, Y, and Z coordinates.
 */
coordinates_t adxl345_read_coordinates();

/**
  * @brief  Get the current state of the I2C communication interface with ADXL345.
  * @param  None
  * @retval HAL_I2C_StateTypeDef - Current state of the I2C communication.
  */
HAL_I2C_StateTypeDef adxl345_get_I2C_state();

/**
  * @brief  Checks if data is ready to be read from the ADXL345 accelerometer.
  * @param  None
  * @retval bool_t - TRUE if data is ready, FALSE otherwise.
  */
bool_t adxl345_is_data_ready();


/* ---------- Setters ---------- */
/**
 * @brief   Set the sensitivity of the ADXL345 accelerometer by writing the DATA_FORMAT register
 *
 * @param   sensitivity: The new sensitivity value to be set. This value
 * 			should be within the range of adxl345_sensitivity_t enum.
 * @retval  None.
 */
void adxl345_set_sensitivity(adxl345_sensitivity_t sensitivity);

/**
  * @brief  Sets the Bandwidth Rate (BW_RATE) register of the ADXL345 accelerometer.
  * @param  value: The value to be written to the register.
  * @retval None
  */
void adxl345_set_bandwidth_rate(uint8_t value);

/**
  * @brief  Sets the Power Control (POWER_CTL) register of the ADXL345 accelerometer.
  *
  * @param  value: The value to be written to the register.
  * @retval None
  */
void adxl345_set_power_control(uint8_t value);

/**
  * @brief  Sets the Data Format (DATA_FORMAT) register of the ADXL345 accelerometer.
  * @param  value: The value to be written to the register.
  * @retval None
  */
void adxl345_set_data_format(uint8_t value);


#endif /* API_INC_API_ADXL345_H_ */
