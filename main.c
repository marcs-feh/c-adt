#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "autotest.h"
// Dynamic array (vector)
#include "vec.c"

void vec_test(){
	Vec v = Vec_new();
	TEST_LOG("Vec_new");
	TEST_EQ(0, v.len);
	TEST_EQ(VEC_INIT_CAP, v.cap);
	TEST_EQ(false, (v.data == NULL));
	TEST_LOG("Vec_del");
	Vec_del(&v);
	TEST_EQ(0, v.len);
	TEST_EQ(0, v.cap);
	TEST_EQ(true, (v.data == NULL));
}

int main(int argc, const char** argv){
	vec_test();
	return 0;
}
