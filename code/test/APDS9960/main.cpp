#include <stdio.h>
#include <unistd.h>
#include "APDS9960.h"

int main(int argc, char**argv)
{
	APDS9960 x;
	x.init();
	while(true) {
		usleep(1000*150);
		unsigned char c = x.read();
		printf("read %hhu\n", c);
	}
	return 0;
}

