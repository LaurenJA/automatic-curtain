#include <stdio.h>
#include <unistd.h>
#include "opt3001.h"
int main(int argc, const char * argv[])
{
	opt3001 x;
	x.init();
	while (true) {
		usleep(150*1000);
		float lux = x.read_lux();
		printf ("lux %f\n", lux);
	}
	return 0;
}

