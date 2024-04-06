/*
 * API_max7219_led_display.c
 *
 *  Created on: Apr 1, 2024
 *      Author: lpmeoli
 */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */


#include "API_max7219_led_display.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi1;

/* Private function prototypes -----------------------------------------------*/



/* Public functions ---------------------------------------------------------*/

void init_max7219() {

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	/* Peripheral clock enable */
	__HAL_RCC_SPI1_CLK_ENABLE();


	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin 		= GPIO_PIN_5|GPIO_PIN_7;
    GPIO_InitStruct.Mode 		= GPIO_MODE_AF_PP;
	//GPIO_InitStruct.Mode 		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate 	= GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	/*Configure GPIO pin : PA6 */
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* SPI configuration*/
	hspi1.Instance 					= SPI1;
	hspi1.Init.Mode 				= SPI_MODE_MASTER;
	hspi1.Init.Direction			= SPI_DIRECTION_1LINE;
	hspi1.Init.DataSize				= SPI_DATASIZE_8BIT; //el ejemplo dice 8
	hspi1.Init.CLKPolarity			= SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase				= SPI_PHASE_1EDGE; //example internet it said 1, segun grafico es 2
	hspi1.Init.NSS 					= SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler 	= SPI_BAUDRATEPRESCALER_256;
	hspi1.Init.FirstBit				= SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode				= SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation 		= SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial 		= 10;

	HAL_SPI_Init(&hspi1);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void send_data_SPI(uint8_t reg, uint8_t data) {

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // select slave
	HAL_SPI_Transmit(&hspi1, &reg, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

//	uint8_t aux[]={data,reg};
//	uint16_t size = sizeof(aux)/sizeof(uint8_t);
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
//	HAL_SPI_Transmit(&hspi1, (uint8_t *)aux, 1, HAL_MAX_DELAY);
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);


}

void send_data_SPI2(uint8_t reg, uint8_t data) {
	uint8_t no_op = 0x00;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // select slave

	HAL_SPI_Transmit(&hspi1, &reg, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

}

void send_data_SPI3(uint8_t reg, uint8_t data) {
	uint8_t no_op = 0x00;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // select slave

	HAL_SPI_Transmit(&hspi1, &reg, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

}

void send_data_SPI4(uint8_t reg, uint8_t data) {
	uint8_t no_op = 0x00;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // select slave
	HAL_SPI_Transmit(&hspi1, &reg, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &no_op, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);


}


/* Private functions ---------------------------------------------------------*/















