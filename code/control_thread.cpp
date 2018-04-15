#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "global.h"

//Three hardware object pointers are private and require three get interfaces
APDS9960 *global::get_APDS9960(void)
{
	return _APDS9960;
}

L293D *global::get_L293D(void)
{
	return _L293D;
}

opt3001 *global::get_opt3001(void)
{
	return _opt3001;
}

//Generate hardware processing threads
bool global::make_control_thread(void)
{
	pthread_t id;

	//Generate thread
	if(pthread_create(&id, NULL, control_thread, NULL) != 0)
		return false;
	return true;
}

//Initialize hardware and call three init interfaces respectively
void global::init_all_hardware(void)
{
	_APDS9960->init();
	_L293D->init(4, 5, 6);//the gpio of the motor is 4/5/6
	_opt3001->init();
}

//Completely close the curtains
void global::close_complete(void)
{
	time_t t;
	time(&t);
	//Within 22 hours, it will not be automatically closed again
	if(t - auto_close_time < 3600*22)
		return;
	printf("action: close\n");
	_L293D->set(MOVE_CLOSE);//Motor running in closed direction
	while(true) {
		unsigned char x;
		usleep(1000*200);//200ms
		x = _APDS9960->read();//reading position
		if( x == (unsigned char)0xFF) {//Representative close tight
			printf("action: stop\n");
			_L293D->set(MOVE_STOP);//the motor is closed
			break;
		}
	}
	//Once you have closed automatically, set the time for this close
	auto_close_time = t;
}

//Completely open the curtains
void global::open_complete(void)
{
	time_t t;
	time(&t);
	//Within 22 hours, it will not be automatically opened again
	if(t - auto_open_time < 3600*22)
		return;
	printf("action: open\n");
	_L293D->set(MOVE_OPEN);//open
	sleep(10);
	printf("action: stop\n");
	_L293D->set(MOVE_STOP);//Motor stops moving
	//After the auto-open once, set the time of this close
	auto_open_time = t;
}

void* global::control_thread (void * arg)
{
	time_t t;
	direction_t pre_direct = STOP_DIR;

	pthread_detach(pthread_self());
	g->init_all_hardware();

	while(true) {
		usleep(1000*200);//200ms
		time(&t);
		//Get direction of operation
		direction_t direct = g->get_direct();
		//If you change direction
		if(pre_direct != direct) {
			pre_direct = direct;
			switch(direct) {
				case OPEN_DIR:
					printf("action: open\n");
					g->get_L293D()->set(MOVE_OPEN);
					break;
				case CLOSE_DIR:
					printf("action: close\n");
					g->get_L293D()->set(MOVE_CLOSE);
					break;
				case STOP_DIR:
					printf("action: stop\n");
					g->get_L293D()->set(MOVE_STOP);
					break;
			}
			continue;
		}
		//Get the operating mode set
		int mode = g->get_mode();
		switch(mode) {
			case AUTO_MODE:
				{
					float lux = g->get_opt3001()->read_lux();
					//When the light is gone, close the curtain
					if(lux < 1.0f) {
						g->close_complete();
					}else if(lux > 100.0f) {//The light is strong to open the curtains
						g->open_complete();
					}
				}
				break;
			case MANUAL_MODE:
				{
					struct tm *p;
					int seconds;
					p = localtime(&t);
					seconds = p->tm_hour * 3600 + p->tm_min * 60;
					int close_timer = g->get_close_timer();
					int open_timer = g->get_open_timer();
					//Judgment Auto Close and Auto Open
					if(close_timer >= 0 && seconds >= close_timer && (seconds - close_timer) < 2) {
						g->close_complete();
					} else if(open_timer >= 0 && seconds >= open_timer && (seconds - open_timer) < 2) {
						g->open_complete();
					}
				}
				break;
			INIT_MODE:
			default:
				break;
		}
	}

	return NULL;
}

