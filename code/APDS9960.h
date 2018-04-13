#ifndef __APDS9960_H__
#define __APDS9960_H__
#include "APDS9960_RPi.h"
class APDS9960
{
	public:
		APDS9960();
		~APDS9960();
		void init(void);
		unsigned char read(void);
	private:
		APDS9960_RPi *apds;
};
#endif
