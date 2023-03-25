/*
 * port_expander.c
 *
 *  Created on: Mar 25, 2023
 *      Author: Andrii Davydenko
 */

#include "dvr_port_exp.h"

RV_t initExpander();
RV_t deinitExpander();
RV_t setExpanderPin(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t pin)
{
	static uint8_t data = 0;
	data |= (1 << pin);

	if (HAL_I2C_Master_Transmit(hi2c, (addr << 1), &data, sizeof(data), HAL_MAX_DELAY))
	{
		return RV_FAILURE;
	}

	return RV_SUCCESS;
}

RV_t resetExpanderPin(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t pin)
{
	static uint8_t data = 0;
	data &= ~(1 << pin);

	if (HAL_I2C_Master_Transmit(hi2c, (addr << 1), &data, sizeof(data), HAL_MAX_DELAY))
	{
		return RV_FAILURE;
	}

	return RV_SUCCESS;
}

RV_t setExpanderPort(I2C_HandleTypeDef *hi2c, uint8_t addr)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (setExpanderPin(hi2c, addr, i))
		{
			return RV_FAILURE;
		}
	}

	return RV_SUCCESS;
}

RV_t resetExpanderPort(I2C_HandleTypeDef *hi2c, uint8_t addr)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (resetExpanderPin(hi2c, addr, i))
		{
			return RV_FAILURE;
		}
	}

	return RV_SUCCESS;
}

RV_t readExpanderPin(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t pin, uint16_t *data)
{
	*data = 0;
	*data |= (uint16_t)(1 << pin);

	HAL_I2C_Master_Transmit(hi2c,  ((addr << 1) | 0x1), &data, sizeof(data), HAL_MAX_DELAY);

	data = 0;

	HAL_I2C_Master_Receive(hi2c, ((addr << 1) | 0x1), &data, sizeof(data), HAL_MAX_DELAY);

	return RV_SUCCESS;
}

RV_t readExpanderPort(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t pin, uint16_t *data)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (readExpanderPin(hi2c, addr, i, data[i]))
		{
			return RV_FAILURE;
		}
	}

	return RV_SUCCESS;
}


