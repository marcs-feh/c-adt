#include "autotest.h"
#include "tests.c"
#include "panic.h"

#include "allocator.c"

static void alloc_test(){
	TEST_LOG("Linear Allocator");
	TEST_LOG("create");
	LinearAlloc *al = LAlloc_new(KiB(2));
	TEST_EQ(false, al->base == NULL);
	TEST_EQ(0, al->offset);
	TEST_EQ(KiB(2), al->cap);
	TEST_LOG("alloc");
	int* tooMuch = LAlloc_alloc(al, MiB(100));
	TEST_EQ(NULL, tooMuch);
	float* fourFloats = LAlloc_alloc(al, sizeof(*fourFloats) * 4);
	TEST_EQ(false, fourFloats == NULL);
	TEST_EQ(sizeof(*fourFloats) * 4, al->offset);
	//printf("off:%zu\n", al->offset);
	TEST_LOG("delete");
	LAlloc_del(al);
}

int main(int argc, const char** argv){
	//queue_test();
	//vec_test();
	//hashtbl_test();
	alloc_test();
	return 0;
}
