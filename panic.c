#include <stdio.h>
#include <time.h>

void panic(const char* msg){
	time_t t = time(NULL);
	struct tm date = *localtime(&t);
	fprintf(stderr, "[%d-%02d-%02d %02d:%02d:%02d] PANIC: %s",
	       date.tm_year + 1900, date.tm_mon + 1, date.tm_mday,
	       date.tm_hour, date.tm_min, date.tm_sec, msg);
}
