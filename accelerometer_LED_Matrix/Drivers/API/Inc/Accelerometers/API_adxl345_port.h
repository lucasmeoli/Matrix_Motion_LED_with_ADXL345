/*
 * API_adxl345_port.h
 *
 *  Created on: Apr 17, 2024
 *      Author: lpmeoli
 */

#ifndef API_INC_ACCELEROMETERS_API_ADXL345_PORT_H_
#define API_INC_ACCELEROMETERS_API_ADXL345_PORT_H_


/* Exported functions ------------------------------------------------------- */
/**
 * @brief   Reads the value from the specified register of the ADXL345 accelerometer.
 *
 * @param   p_hi2c: Pointer to a I2C_HandleTypeDef structure that contains
 *          the configuration information for the specified I2C.
 * 		    reg: The register address to read from.
 * @retval  The value read from the specified register.
 */
uint8_t read_register(I2C_HandleTypeDef *p_hi2c, uint8_t reg);

/**
 * @brief   Writes a value to the specified register of the ADXL345 accelerometer.
 *
 * @param   p_hi2c: Pointer to a I2C_HandleTypeDef structure that contains
 *          the configuration information for the specified I2C.
 * 		    reg: The register address to write to.
 * 		    value: The value to write to the register.
 * @retval  None.
 */
void write_register(I2C_HandleTypeDef *p_hi2c, uint8_t reg, uint8_t value);



#endif /* API_INC_ACCELEROMETERS_API_ADXL345_PORT_H_ */
