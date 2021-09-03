# TSL2591 avr-library

Simple avr-library for the TSL2591. It provides basic configuration to set the
gain and time for the internal ADC and nothing else (interrupts are not
handled). Once the device has been initialize call the `tsl2591_lux();` function
to get the lux value that the sensor is reading.

The `i2c.h` and `i2c.c` aren't written by me, I've copied from [this repo](https://github.com/Sylaina/oled-display) and the author is Michael Köhler.

## Usage

Import `tsl2591.h` and `tsl2591.c` in your project. In your `main` function,
before the infinite loop, call `tsl2591_init(CONFIG);` to initialize the
sensor. The argument `CONFIG` that you give specifies the time of the ADC and
the gain. Then in the infinite loop call `tsl2591_lux();` to get the `float`
value of the lux read by the sensor.

In `main.c` there is a simple example of usage of the library. In `tsl2591.h`
there are all the configuration parameters that you can set.

## Lux calculation
To get the lux value I used the formula that Adafruit implemented in their
arduino library
([here](https://github.com/adafruit/Adafruit_TSL2591_Library/blob/master/Adafruit_TSL2591.cpp)).
