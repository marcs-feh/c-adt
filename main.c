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

	TEST_LOG("Vec_append");
	Vec_append(&v, 0);
	Vec_append(&v, 1.5);
	Vec_append(&v, -3.2);
	// Expect [0, 1.5, -3.2]
	TEST_EQ(0, v.data[0]);
	TEST_EQ(1.5f, v.data[1]);
	TEST_EQ(-3.2f, v.data[2]);
	TEST_EQ(3, v.len);

	TEST_LOG("Appending 40 elements.");
	for(size_t i = 0; i < 40; i++)
		Vec_append(&v, 0);
	TEST_EQ(43, v.len);

	TEST_LOG("Resize and append");
	Vec_resize(&v, 3);
	Vec_append(&v, 0);
	// Expect [0, 1.5, -3.2, 0]
	TEST_EQ(0, v.data[0]);
	TEST_EQ(1.5f, v.data[1]);
	TEST_EQ(-3.2f, v.data[2]);
	TEST_EQ(4, v.len);
	TEST_EQ(7, v.cap);

	TEST_LOG("Resize and pop");
	Vec_pop(&v);
	TEST_EQ(-3.2f, v.data[v.len - 1]);
	TEST_EQ(3, v.len);
	Vec_pop(&v);
	Vec_pop(&v);
	TEST_EQ(0, v.data[v.len - 1]);
	TEST_EQ(1, v.len);
	TEST_EQ(2, v.cap);
	TEST_LOG("Appending 20 elements.");
	for(size_t i = 0; i < 20; i++)
		Vec_append(&v, 0);
	TEST_EQ(21, v.len);
	TEST_EQ(23, v.cap);

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
