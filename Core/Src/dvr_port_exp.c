/*
* port_expander.c
*
*  Created on: Mar 25, 2023
*      Author: Andrii Davydenko
*/

#include "dvr_port_exp.h"

static struct {
  uint8_t addr;
  uint8_t port;
  uint8_t is_init;
} exp;

I2C_HandleTypeDef hi2c;

RV_t dvr_port_exp_init(I2C_HandleTypeDef *i2c, uint8_t addr)
{
  hi2c = *i2c;

  exp.addr = (addr << 1);
  exp.port = 0;
  exp.is_init = 1;

  return RV_SUCCESS;
}

RV_t dvr_port_exp_deinit()
{
  exp.addr = 0;
  exp.port = 0;
  exp.is_init = 0;

  return RV_SUCCESS;
}

RV_t dvr_port_exp_set_pin(uint8_t pin)
{
  RV_t state = RV_SUCCESS;
  do
  {
    if (pin > 7)
    {
      state = RV_FAILURE;
      break;
    }

    exp.port |= (1 << pin);

    if (HAL_I2C_Master_Transmit(&hi2c, exp.addr, &exp.port, sizeof(exp.port), HAL_MAX_DELAY))
    {
	  state = RV_FAILURE;
    }

  } while (0);

  return state;
}

RV_t dvr_port_exp_reset_pin(uint8_t pin)
{
  RV_t state = RV_SUCCESS;
  do
  {
    if (pin > 7)
    {
      state = RV_FAILURE;
      break;
    }

    exp.port &= ~(1 << pin);

    if (HAL_I2C_Master_Transmit(&hi2c, exp.addr, &exp.port, sizeof(exp.port), HAL_MAX_DELAY))
    {
      state = RV_FAILURE;
    }

  } while (0);

  return state;
}

RV_t dvr_port_exp_set_port()
{
  RV_t state = RV_SUCCESS;

  exp.port = 0xFF;

  if (HAL_I2C_Master_Transmit(&hi2c, exp.addr, &exp.port, sizeof(exp.port), HAL_MAX_DELAY))
  {
    state = RV_FAILURE;
  }

  return state;
}

RV_t dvr_port_exp_reset_port()
{
  RV_t state = RV_SUCCESS;

  exp.port = 0x00;

  if (HAL_I2C_Master_Transmit(&hi2c, exp.addr, &exp.port, sizeof(exp.port), HAL_MAX_DELAY))
  {
    state = RV_FAILURE;
  }

  return state;
}

RV_t dvr_port_exp_read_pin(uint8_t pin, uint8_t *data)
{
  RV_t state = RV_SUCCESS;
  do
  {
    if (HAL_I2C_Master_Receive(&hi2c, (exp.addr | 0x1), data, sizeof(data), HAL_MAX_DELAY))
    {
      state = RV_FAILURE;
      break;
    }

    if (pin > 7)
    {
      state = RV_FAILURE;
      break;
    }

    *data &= (1 << pin);

  } while (0);

  return state;
}

RV_t dvr_port_exp_read_port(uint8_t *data)
{
  RV_t state = RV_SUCCESS;

  do
  {
    if (HAL_I2C_Master_Receive(&hi2c, (exp.addr | 0x1), data, sizeof(data), HAL_MAX_DELAY))
    {
      state = RV_FAILURE;
      break;
    }

  } while (0);

  return state;
}


