#ifndef INCLUDE_PANIC_H_
#define INCLUDE_PANIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Panic(msg) {\
	time_t panic_timer_ = time(NULL);\
	struct tm panic_date_ = *localtime(&panic_timer_);\
	fprintf(stderr, "[%d-%02d-%02d %02d:%02d:%02d] PANIC: %s\n",\
	       panic_date_.tm_year + 1900, panic_date_.tm_mon + 1, panic_date_.tm_mday,\
	       panic_date_.tm_hour, panic_date_.tm_min, panic_date_.tm_sec, msg);\
	exit(-1);\
}

#endif
