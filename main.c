#include "autotest.h"
#include "tests.c"
#include "hashtbl.c"

void hashtbl_test(){
	HashTable ht = Table_new(12);
	TEST_LOG("table new");
	TEST_EQ(12, ht.size);
	TEST_EQ(false, (ht.buckets == NULL));
	TEST_LOG("testing buckets");
	for(size_t i = 0; i < ht.size; i++){
		TEST_EQ(false, (ht.buckets[i].data == NULL));
	}

	TEST_LOG("table del");
	Table_del(&ht);
	TEST_EQ(0, ht.size);
	TEST_EQ(true, (ht.buckets == NULL));
}

int main(int argc, const char** argv){
	hashtbl_test();
	return 0;
}
