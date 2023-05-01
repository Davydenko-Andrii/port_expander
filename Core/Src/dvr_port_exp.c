/*
* port_expander.c
*
*  Created on: Mar 25, 2023
*      Author: Andrii Davydenko
*/

#include "dvr_port_exp.h"
#include <string.h>

#define MAX_PIN_NUM 7

typedef HAL_StatusTypeDef (*i2c_read)(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
typedef HAL_StatusTypeDef (*i2c_write)(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout) {
  return HAL_I2C_Master_Transmit(hi2c, DevAddress, pData, Size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout) {
  return HAL_I2C_Master_Receive(hi2c, DevAddress, pData, Size, HAL_MAX_DELAY);
}

static struct {
  uint8_t addr;
  uint8_t port;
  uint8_t is_init;  
  i2c_read read;
  i2c_write write;
} port_exp_descr;

I2C_HandleTypeDef hi2c;

RV_t dvr_port_exp_init(I2C_HandleTypeDef *i2c, uint8_t addr)
{
  hi2c = *i2c;

  port_exp_descr.addr = (addr << 1);
  port_exp_descr.port = 0;
  port_exp_descr.is_init = 1;
  port_exp_descr.read = &read;
  port_exp_descr.write = &write;

  return RV_SUCCESS;
}

RV_t dvr_port_exp_deinit()
{

  memset(&port_exp_descr, 0, sizeof(port_exp_descr));

  return RV_SUCCESS;
}

RV_t dvr_port_exp_set_pin(uint8_t pin)
{
  RV_t state = RV_SUCCESS;
  do
  {
    if (pin > MAX_PIN_NUM)
    {
      state = RV_FAILURE;
      break;
    }

    port_exp_descr.port |= (1 << pin);

    if (port_exp_descr.write(&hi2c, port_exp_descr.addr, &port_exp_descr.port, sizeof(port_exp_descr.port), HAL_MAX_DELAY))
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
    if (pin > MAX_PIN_NUM)
    {
      state = RV_FAILURE;
      break;
    }

    port_exp_descr.port &= ~(1 << pin);

    if (port_exp_descr.write(&hi2c, port_exp_descr.addr, &port_exp_descr.port, sizeof(port_exp_descr.port), HAL_MAX_DELAY))
    {
      state = RV_FAILURE;
    }

  } while (0);

  return state;
}


RV_t dvr_port_exp_set_port(uint8_t port)
{
  RV_t state = RV_SUCCESS;

  port_exp_descr.port |= port;

  if (port_exp_descr.write(&hi2c, port_exp_descr.addr, &port_exp_descr.port, sizeof(port_exp_descr.port), HAL_MAX_DELAY))
  {
    state = RV_FAILURE;
  }

  return state;
}

RV_t dvr_port_exp_reset_port(uint8_t port)
{
  RV_t state = RV_SUCCESS;

  port_exp_descr.port &= ~port;

  if (port_exp_descr.write(&hi2c, port_exp_descr.addr, &port_exp_descr.port, sizeof(port_exp_descr.port), HAL_MAX_DELAY))
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
    if (pin > MAX_PIN_NUM)
    {
      state = RV_FAILURE;
      break;
    }

    if (port_exp_descr.read(&hi2c, (port_exp_descr.addr | 0x1), data, sizeof(data), HAL_MAX_DELAY))
    {
      state = RV_FAILURE;
      break;
    }

    *data = *data & (1 << pin) ? true : false;

  } while (0);

  return state;
}

RV_t dvr_port_exp_read_port(uint8_t *data)
{
  RV_t state = RV_SUCCESS;

  do
  {
    if (port_exp_descr.read(&hi2c, (port_exp_descr.addr | 0x1), data, sizeof(data), HAL_MAX_DELAY))
    {
      state = RV_FAILURE;
      break;
    }

  } while (0);

  return state;
}


