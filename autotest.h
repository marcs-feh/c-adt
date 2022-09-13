#include <stdio.h>

#define TEST_EQ(expect, fcall) { \
    if(expect == fcall) printf("[\033[0;32mok\033[0m]");\
    else printf("[\033[0;31mfail\033[0m]"); \
    printf("\t %s == %s\n", #fcall, #expect); \
}

#define TEST_EQFUNC(expect, fcall, eqfunc) { \
    if(eqfunc(expect, fcall)) printf("[\033[0;32mok\033[0m]");\
    else printf("[\033[0;31mfail\033[0m]"); \
    printf("\t %s(%s, %s)\n", #eqfunc, #expect, #fcall); \
}

#define TEST_LOG(msg) { \
	printf("[\033[0;34mlog\033[0m]\t%s\n", #msg);\
}

