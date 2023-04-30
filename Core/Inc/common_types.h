#ifndef _COMMON_TYPES_H_
#define _COMMON_TYPES_H_

/******************************************************************************/
/*                                PUBLIC TYPES                                */
/******************************************************************************/
typedef enum
{
  RV_FAILURE = -3,
  RV_NULLPTR,
  RV_NOT_READY, 
  RV_SUCCESS,
} RV_t;

// typedef uint32_t (*i2c_read)(uint8_t dev_addr, uint8_t reg_addr, uint8_t *p_data, uint8_t length);
// typedef uint32_t (*i2c_write)(uint8_t dev_addr, uint8_t reg_addr, uint8_t *p_data, uint8_t length);

#define PIN_0 (1 << 0)
#define PIN_1 (1 << 1)
#define PIN_2 (1 << 2)
#define PIN_3 (1 << 3)
#define PIN_4 (1 << 4)
#define PIN_5 (1 << 5)
#define PIN_6 (1 << 6)
#define PIN_7 (1 << 7)

#define MAX_PIN_NUM 7

#endif
