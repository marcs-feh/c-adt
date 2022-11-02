#ifndef INCLUDE_PANIC_H_
#define INCLUDE_PANIC_H_

#include <stdio.h>
#include <time.h>

#define Panic(msg) {\
	time_t sys_time_ = time(NULL); \
	struct tm date_ = *localtime(&t); \
	fprintf(""); \
}

#endif
