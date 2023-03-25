/*
 * port_expander.h
 *
 *  Created on: Mar 25, 2023
 *      Author: Andrii Davydenko
 */

#ifndef DRV_PORT_EXP_H_
#define DRV_PORT_EXP_H_

#include "main.h"

typedef enum
{
  RV_FAILURE = -3,
  RV_NULLPTR,
  RV_NOT_READY,
  RV_SUCCESS
} RV_t;

typedef enum
{
	WRITE,
	READ
} MODE;

RV_t initExpander();
RV_t deinitExpander();
RV_t setExpanderPin(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t pin);
RV_t resetExpanderPin(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t pin);
RV_t setExpanderPort(I2C_HandleTypeDef *hi2c, uint8_t addr);
RV_t resetExpanderPort(I2C_HandleTypeDef *hi2c, uint8_t addr);
RV_t readExpanderPin(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t pin, uint16_t *data);
RV_t readExpanderPort(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t pin, uint16_t *data);

#endif // DRV_PORT_EXP_H_
