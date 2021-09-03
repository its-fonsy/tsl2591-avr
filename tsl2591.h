#ifndef TSL2591_H
#define TSL2591_H

#include "i2c.h"

#define TSL2591_I2C_ADD			0x29
#define TSL2591_ID				0x50
#define TSL2591_NORM_CMD		0xA0
#define TSL2591_PON				0x01
#define TSL2591_AEN				0x02

#define TSL2591_REG_ENABLE		0x00
#define TSL2591_REG_CONFIG		0x01
#define TSL2591_REG_ID			0x12
#define TSL2591_REG_CH0_LOW		0x14
#define TSL2591_REG_CH0_HIGH	0x15
#define TSL2591_REG_CH1_LOW		0x16
#define TSL2591_REG_CH1_HIGH	0x17

/* set time for the ADC */
/* last 3 bit of control register */
#define TSL2591_SRESET			0x80

#define TSL2591_ATIME_100		0x00 // 0b000
#define TSL2591_ATIME_200		0x01 // 0b001
#define TSL2591_ATIME_300		0x02 // 0b010
#define TSL2591_ATIME_400		0x03 // 0b011
#define TSL2591_ATIME_500		0x04 // 0b100
#define TSL2591_ATIME_600		0x05 // 0b101

/* set gain for the ADC */
/* bit 5 and 4 of control register */
#define TSL2591_AGAIN_LOW		0x00
#define TSL2591_AGAIN_MED		0x10
#define TSL2591_AGAIN_HIGH		0x20
#define TSL2591_AGAIN_MAX		0x30

uint8_t	tsl2591_init(uint8_t control_reg);
uint8_t	tsl2591_read_reg(uint8_t reg);
void tsl2591_write_reg(uint8_t reg, uint8_t val);
float tsl2591_lux();

#endif
