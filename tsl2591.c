#include "tsl2591.h"

uint8_t tsl2591_read_reg(uint8_t reg)
{
	uint8_t read_byte;

	// select the device in W mode
	i2c_start(TSL2591_I2C_ADD << 1);
	// normal comand to read register
	i2c_byte(TSL2591_NORM_CMD | reg);
	// select the device in R mode
	i2c_start((TSL2591_I2C_ADD << 1) | 0x01);
	// read the response
	read_byte = i2c_readNAck();

	i2c_stop();

	return read_byte;
}

void tsl2591_write_reg(uint8_t reg, uint8_t val)
{
	// select the device in W mode
	i2c_start(TSL2591_I2C_ADD << 1);
	// normal comand to write register
	i2c_byte(TSL2591_NORM_CMD | reg);
	// send the value to write
	i2c_byte(val);

	i2c_stop();
}

uint16_t atime, again;

uint8_t tsl2591_init(uint8_t config)
{
	uint8_t id_reg = 0, conf_reg;

	i2c_init();

	// check the ID is correct
	id_reg = tsl2591_read_reg(TSL2591_REG_ID);
	if (id_reg != TSL2591_ID)
		return 1;

	// check the initialization is correct
	tsl2591_write_reg(TSL2591_REG_CONFIG, config);
	conf_reg = tsl2591_read_reg(TSL2591_REG_CONFIG);

	if (conf_reg != config)
		return 1;

	// start the ADCs
	tsl2591_write_reg(TSL2591_REG_ENABLE, TSL2591_PON | TSL2591_AEN);

	// setting atime
	switch (config & 0x07)
	{
		case TSL2591_ATIME_100:
			atime = 100;
			break;
		case TSL2591_ATIME_200:
			atime = 200;
			break;
		case TSL2591_ATIME_300:
			atime = 300;
			break;
		case TSL2591_ATIME_400:
			atime = 400;
			break;
		case TSL2591_ATIME_500:
			atime = 500;
			break;
		case TSL2591_ATIME_600:
			atime = 600;
			break;
		default: // 100ms
			atime = 100;
			break;
	}

	// setting the again
	switch (config & 0x30)
	{
		case TSL2591_AGAIN_LOW:
			again = 1;
			break;
		case TSL2591_AGAIN_MED:
			again = 25;
			break;
		case TSL2591_AGAIN_HIGH:
			again = 42;
			break;
		case TSL2591_AGAIN_MAX:
			again = 9876;
			break;
		default:
			again = 1;
			break;
	}

	return 0;
}

float tsl2591_lux()
{
	uint8_t ch0_low, ch0_hig, ch1_low, ch1_hig;
	uint16_t ch0, ch1;
	float cpl, lux;

	ch0_low = tsl2591_read_reg(TSL2591_REG_CH0_LOW);
	ch0_hig = tsl2591_read_reg(TSL2591_REG_CH0_HIGH);
	ch0 = ((uint16_t)ch0_hig << 8) | ch0_low;

	ch1_low = tsl2591_read_reg(TSL2591_REG_CH1_LOW);
	ch1_hig = tsl2591_read_reg(TSL2591_REG_CH1_HIGH);
	ch1 = ( (uint16_t)ch1_hig << 8) | ch1_low;

	cpl = ( (float) again * (float) atime ) / 408.0;
	lux = (((float)ch0 - (float)ch1)) * (1.0 - ((float)ch1 / (float)ch0)) / cpl;

	return lux;
}
