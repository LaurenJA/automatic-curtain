#include "APDS9960.h"

//Apply an APDS9960_RPi object when constructing
APDS9960::APDS9960()
{
	apds = new APDS9960_RPi();
}

//Delete the APDS9960_RPi object when it is destroyed
APDS9960::~APDS9960()
{
	delete apds;
}

//Initialize hardware and call APDS9960_RPi related interfaces
void APDS9960::init(void)
{
	apds->init();
	apds->setProximityGain(PGAIN_2X);
	apds->enableProximitySensor(false);
}

//Call APDS9960_RPi related interface to get the distance
unsigned char APDS9960::read(void)
{
	uint8_t proximity_data = 0;
	apds->readProximity(proximity_data);
	return (unsigned char)proximity_data;
}

