#include <util/delay.h>
#include "tsl2591.h"

int main(void)
{
	float lux;

	if(tsl2591_init(TSL2591_AGAIN_LOW | TSL2591_ATIME_200))
		while(1);  // error on initialize the sensor

	while(1)
	{
		_delay_ms(1000);
		lux = tsl2591_lux();
	}
}
