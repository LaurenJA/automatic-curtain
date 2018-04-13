#ifndef __L293D_H__
#define __L293D_H__
class L293D
{
	public:
		L293D();
		~L293D();
		void init(int pin_A, int pin_B, int pin_E);
		void set(int value);
	private:
		int pin_A, pin_B, pin_E;
};
#define MOVE_STOP 0
#define MOVE_OPEN 1
#define MOVE_CLOSE -1
#endif
