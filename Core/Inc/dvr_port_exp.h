/*
 * port_expander.h
 *
 *  Created on: Mar 25, 2023
 *      Author: Andrii Davydenko
 */

#ifndef DVR_PORT_EXP_H_
#define DVR_PORT_EXP_H_

#include "common_types.h"
#include "main.h"
#include <stdbool.h>

RV_t dvr_port_exp_init(I2C_HandleTypeDef *i2c, uint8_t addr);
RV_t dvr_port_exp_deinit();
RV_t dvr_port_exp_set_pin(uint8_t pin);
RV_t dvr_port_exp_reset_pin(uint8_t pin);
RV_t dvr_port_exp_set_port(uint8_t pin);
RV_t dvr_port_exp_reset_port(uint8_t pin);
RV_t dvr_port_exp_read_pin(uint8_t pin, uint8_t *data);
RV_t dvr_port_exp_read_port(uint8_t *data);

#endif // DVR_PORT_EXP_H_
