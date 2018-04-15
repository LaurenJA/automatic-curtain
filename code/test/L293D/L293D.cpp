#include "L293D.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

L293D::L293D()
{
}

L293D::~L293D()
{
}

//control the motor
void L293D::set(int value)
{
	if(value == 0) {//stop
		digitalWrite(pin_A, HIGH);
		digitalWrite(pin_B, LOW);
		digitalWrite(pin_E, LOW);
	} else if(value > 0){//the direction of opening the curtain
		digitalWrite(pin_A, HIGH);
		digitalWrite(pin_B, LOW);
		digitalWrite(pin_E, HIGH);
	} else if(value < 0){//the direction of closing the curtain
		digitalWrite(pin_A, LOW);
		digitalWrite(pin_B, HIGH);
		digitalWrite(pin_E, HIGH);
	}
}

//Initialize the motor controller, configure three IO pins as output mode, and stop the motor
void L293D::init(int pin_A, int pin_B, int pin_E)
{
	this->pin_A = pin_A;
	this->pin_B = pin_B;
	this->pin_E = pin_E;
	wiringPiSetup();
	pinMode(this->pin_A, OUTPUT);
	pinMode(this->pin_B, OUTPUT);
	pinMode(this->pin_E, OUTPUT);
	this->set(0);
}

