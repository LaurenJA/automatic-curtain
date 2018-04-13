#include <stdio.h>
#include <unistd.h>
#include "L293D.h"

int main(int argc, char**argv)
{
	L293D x;
	x.init(4, 5, 6);
	while(1) {
		sleep(2);
		x.set(0);
		sleep(2);
		x.set(1);
		sleep(2);
		x.set(0);
		sleep(2);
		x.set(-1);
	}
	return 0;
}
