#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#include "opt3001.h"

#define CONF_REG 0x01
#define RES_REG 0x00

opt3001::opt3001()
{
}

opt3001::~opt3001()
{
}

//Initialize the hardware
void opt3001::init(void)
{
	fd = wiringPiI2CSetup(0x44);//your iic address
        wiringPiI2CWriteReg16(fd, CONF_REG, 0x10C4);
}

//Get the light intensity, refer to the datasheet
float opt3001::read_lux(void)
{
	unsigned readres = wiringPiI2CReadReg16(fd, RES_REG);
	unsigned left = readres&0xFF;
	left = left << 8;
	unsigned right = readres&0xFF00;
	right = right >> 8;
	readres = (left|right);

	unsigned exponential = (readres>>12)&0xF;
	float LSB_Size=pow(2, exponential)*0.01;
	int R = readres&0xFFF;
	return R*LSB_Size;
}

