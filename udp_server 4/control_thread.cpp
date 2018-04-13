#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "global.h"

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

bool global::make_control_thread(void)
{
	pthread_t id;

	if(pthread_create(&id, NULL, control_thread, NULL) != 0)
		return false;
	return true;
}

void global::init_all_hardware(void)
{
	_APDS9960->init();
	_L293D->init(4, 5, 6);
	_opt3001->init();
}

void global::close_complete(void)
{
	time_t t;
	time(&t);
	if(t - auto_close_time < 3600*22)
		return;
	_L293D->set(MOVE_CLOSE);
	while(true) {
		unsigned char x;
		usleep(1000*200);//200ms
		x = _APDS9960->read();
		if( x == (unsigned char)0xFF) {
			_L293D->set(MOVE_STOP);
			break;
		}
	}
	auto_close_time = t;
}

void global::open_complete(void)
{
	time_t t;
	time(&t);
	if(t - auto_open_time < 3600*22)
		return;
	_L293D->set(MOVE_OPEN);
	sleep(10);
	_L293D->set(MOVE_STOP);
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
		direction_t direct = g->get_direct();
		if(pre_direct != direct) {
			pre_direct = direct;
			switch(direct) {
				case OPEN_DIR:
					g->get_L293D()->set(MOVE_OPEN);
					break;
				case CLOSE_DIR:
					g->get_L293D()->set(MOVE_CLOSE);
					break;
				case STOP_DIR:
					g->get_L293D()->set(MOVE_STOP);
					break;
			}
			continue;
		}
		int mode = g->get_mode();
		switch(mode) {
			case AUTO_MODE:
				{
					float lux = g->get_opt3001()->read_lux();
					if(lux < 1.0f) {
						g->close_complete();
					}else if(lux > 10.0f) {
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

