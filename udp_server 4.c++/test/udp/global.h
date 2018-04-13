#ifndef __GLOBAL__
#define __GLOBAL__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#ifndef ONLY_TEST_UDP
#include "APDS9960.h"
#include "L293D.h"
#include "opt3001.h"
#endif
enum run_mode_t {INIT_MODE, AUTO_MODE, MANUAL_MODE};
enum direction_t {STOP_DIR, OPEN_DIR, CLOSE_DIR};

class global
{
	public:
		global();
		global(unsigned short port);
		~global();
		void init_socket(void);
		bool make_control_thread(void);
		run_mode_t get_mode(void);
		direction_t get_direct(void);
		int get_open_timer(void);
		int get_close_timer(void);
		int recv(void);
		bool deal(int len);
		void close_complete(void);
		void open_complete(void);
#ifndef ONLY_TEST_UDP
		APDS9960 *get_APDS9960(void);
		L293D *get_L293D(void);
		opt3001 *get_opt3001(void);
#endif
	private:
		run_mode_t mode;
		direction_t direct;
		int open_timer, close_timer;
		unsigned short port;
		int fd_udp;
		bool cmp_str(char *buf, int len, const char *str);
		char buf[64];
		struct sockaddr_in addr;
		socklen_t addr_len;
#ifndef ONLY_TEST_UDP
		APDS9960 *_APDS9960;
		L293D *_L293D;
		opt3001 *_opt3001;
		time_t auto_open_time, auto_close_time;
#endif
		static void *control_thread (void * arg);
		void init_all_hardware(void);
};

extern global *g;
#endif

