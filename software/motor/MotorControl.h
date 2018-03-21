
class MotorControl {

public: 
	MotorControl(int pinForward, int pinReverse, int pinEnable); // Initalise 
	void setDirection(bool forward);// Set direction of motor
	void start();					// Start motor
	void stop(); 					// Stop motor

private: 

};