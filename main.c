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
	// access
	fourFloats[0] = 6.9f; fourFloats[1] = 4.20f; fourFloats[2] = -0.3f; fourFloats[3] = 1.0f;
	printf("[%.2f,%.2f,%.2f,%.2f]\n", fourFloats[0], fourFloats[1], fourFloats[2], fourFloats[3]);
	TEST_EQ(sizeof(*fourFloats) * 4, al->offset);
	char* threeChars = LAlloc_alloc(al, sizeof(*threeChars) * 3);
	TEST_EQ(false, threeChars == NULL);
	TEST_EQ(16 + 3, al->offset);
	int* num = LAlloc_alloc(al, sizeof(*num));
	TEST_EQ(16 + 3 + (DEFAULT_ALIGN - 3) + 4, al->offset);
	TEST_EQ(false, num == NULL);
	TEST_LOG("free");
	LAlloc_free(al);
	TEST_EQ(0, al->offset);
	TEST_LOG("allocating");
	for(usize i = 0; i < (KiB(2) / DEFAULT_ALIGN); i++){
		void* _ = LAlloc_alloc(al, DEFAULT_ALIGN);
	}
	//printf("off:%zu\n", al->offset);
	num = LAlloc_alloc(al, sizeof(*num) + 1); // +1 to mess alginment a bit
	threeChars = LAlloc_alloc(al, sizeof(*threeChars) * 3);
	TEST_EQ(false, num == NULL);
	TEST_EQ(true, threeChars == NULL);
	TEST_EQ(NULL, LAlloc_alloc(al, 100));
	TEST_LOG("free 2");
	LAlloc_free(al);
	TEST_EQ(false, LAlloc_alloc(al, 100) == NULL);
	TEST_EQ(100, al->offset);
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
