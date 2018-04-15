#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "global.h"

global *g;

//Default port, constructor port defaults to 10000, but udp socket is not established
global::global()
{
	mode = INIT_MODE;
	direct = STOP_DIR;
	open_timer = -1;//Open_timer represents the time of the timer opening, is the number of seconds after 00:00:00, -1 means the timer is not open
	close_timer = -1;//Representing the timing of closing, explained above
	port = 10000;
	fd_udp = -1;//
#ifndef ONLY_TEST_UDP
	_APDS9960 = new APDS9960();
	_L293D = new L293D();
	_opt3001 = new opt3001();
	auto_open_time = 0;
	auto_close_time = 0;
#endif
}

//Constructor with port number
global::global(unsigned short port)
{
	mode = INIT_MODE;
	direct = STOP_DIR;
	open_timer = -1;
	close_timer = -1;
	this->port = port;
	fd_udp = -1;
#ifndef ONLY_TEST_UDP
	_APDS9960 = new APDS9960();
	_L293D = new L293D();
	_opt3001 = new opt3001();
	auto_open_time = 0;
	auto_close_time = 0;
#endif
}

global::~global()
{
	if(fd_udp >= 0)
		close(fd_udp);//Close udp socket
#ifndef ONLY_TEST_UDP
	delete _APDS9960;
	delete _L293D;
	delete _opt3001;
#endif
}

//The following four are to get member variables, because these member variables are private variables, will not directly accessible
run_mode_t global::get_mode(void)
{
	return mode;
}

direction_t global::get_direct(void)
{
	return direct;
}

int global::get_open_timer(void)
{
	return open_timer;
}

int global::get_close_timer(void)
{
	return close_timer;
}


//Initialize socket to form udp server
void global::init_socket(void)
{
	struct sockaddr_in addr;

	//Create a socket
	fd_udp = socket(PF_INET, SOCK_DGRAM, 0);
	if(fd_udp < 0) {
		fprintf(stderr,"%s:%d:socket error:%s\n",__FILE__,__LINE__,strerror(errno));
		exit(1);
	}

	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);//The port number
	addr.sin_addr.s_addr = htonl(INADDR_ANY);//Ip for all network interfaces

	//Bind, socket can accept udp information
	if(bind(fd_udp, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		fprintf(stderr,"%s:%d:bind error:%s\n",__FILE__,__LINE__,strerror(errno));
		exit(1);
	}
	int buf_size;
	//Buffer 8k is sufficient for this application
	buf_size = 1024*8;
	setsockopt(fd_udp, SOL_SOCKET, SO_RCVBUF, (void*)&buf_size, sizeof(buf_size));
	setsockopt(fd_udp, SOL_SOCKET, SO_SNDBUF, (void*)&buf_size, sizeof(buf_size));
}

bool global::cmp_str(char *buf, int len, const char *str)
{
	if(len == (int)strlen(str) && memcmp(buf, str, len) == 0) {
		return true;
	} else {
		return false;
	}
}

//For the processing of the command, set the variable and fill in the return packet and send
bool global::deal(int len)
{
	if(cmp_str(buf, len, "auto")) {
		mode = INIT_MODE;
		direct = STOP_DIR;
		strcpy(buf, "ok");
	} else if(cmp_str(buf, len, "manual")) {
		mode = MANUAL_MODE;
		direct = STOP_DIR;
		strcpy(buf, "ok");
	} else if(cmp_str(buf, len, "open")) {
		if(mode != MANUAL_MODE) {
			strcpy(buf, "bad");
		} else {
			direct = OPEN_DIR;
			strcpy(buf, "ok");
		}
	} else if(cmp_str(buf, len, "close")) {
		if(mode != MANUAL_MODE) {
			strcpy(buf, "bad");
		} else {
			direct = CLOSE_DIR;
			strcpy(buf, "ok");
		}
	} else if(cmp_str(buf, len, "stop")) {
		if(mode != MANUAL_MODE) {
			strcpy(buf, "bad");
		} else {
			direct = STOP_DIR;
			strcpy(buf, "ok");
		}
	} else if(cmp_str(buf, len, "deltimer")) {
		open_timer = -1;
		close_timer = -1;
		strcpy(buf, "ok");
	} else {
		int hour, minute;
		char cmd[30];
		buf[len] = '\0';
		if(sscanf(buf, "%20[a-zA-Z]%d:%d", cmd, &hour, &minute) != 3) {
			strcpy(buf, "bad");
		} else if(hour<0||hour>23||minute<0||minute>59) {
			strcpy(buf, "bad");
		} else if(strcmp(cmd, "opentimer") == 0) {
			open_timer = hour*3600 + minute*60;
			strcpy(buf, "ok");
		} else if(strcmp(cmd, "closetimer") == 0) {
			close_timer = hour*3600 + minute*60;
			strcpy(buf, "ok");
		}
	}

	//Send reply packet
	socklen_t sock_len = sizeof(addr);
	sendto(fd_udp, buf, strlen(buf), 0, (struct sockaddr*)&addr, sock_len);
	//Print out the sending data
	printf("Send %d bytes: %s\n", (int)strlen(buf), buf);
	return true;
}


int global::recv(void)
{
	int i, ret;

	addr_len = sizeof(addr);
	memset(&addr,0,addr_len);
	//Receive udp packets
	ret = recvfrom(fd_udp, buf, 63, 0, (struct sockaddr*)&addr, &addr_len);
	//Print the received data
	if(ret >= 0) {
		printf("Recieve %d bytes:", ret);
		for(i=0;i<ret;i++) {
			unsigned char c;
			c = buf[i];
			if(c>=(unsigned char)32&&c<=(unsigned char)126)
				printf("%c", c);
			else
				printf(".");
		}
		printf("\nFor hex:");
		for(i=0;i<ret;i++)
			printf(" %02hhx", buf[i]);
		printf("\n");
	}
	
	return ret;
}

int main(int argc, char**argv)
{
	unsigned short port = 10000;

	//Get the port number to bind from the command line
	if(argc > 1)
		sscanf(argv[1], "%hu", &port);
	//Create a global object
	g = new global(port);
	//Initialization socket
	g->init_socket();
#ifndef ONLY_TEST_UDP
	//Generate hardware controlled threads
	g->make_control_thread();
#endif

	//The loop gets the udp command from the GUI and processes it
	while(true) {
		//Get a udp package
		int len = g->recv();
		if(len < 0) {
			fprintf(stderr,"%s:%d:%m\n",__FILE__,__LINE__);
			continue;
		}
		//Processing package
		g->deal(len);
	}

	return 0;
}

