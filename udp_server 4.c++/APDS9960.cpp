#include "APDS9960.h"

APDS9960::APDS9960()
{
	apds = new APDS9960_RPi();
}

APDS9960::~APDS9960()
{
	delete apds;
}

void APDS9960::init(void)
{
	apds->init();
	apds->setProximityGain(PGAIN_2X);
	apds->enableProximitySensor(false);
}

unsigned char APDS9960::read(void)
{
	uint8_t proximity_data = 0;
	apds->readProximity(proximity_data);
	return (unsigned char)proximity_data;
}

