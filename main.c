#include "autotest.h"
#include "tests.c"
#include "hashtbl.c"

void printBucket(TableBucket *b){
	for(size_t i = 0; i < b->len; i++){
		printf("\t%s:%f  ", b->data[i].key, b->data[i].val);
	}
	printf("\n");
}

void printTable(HashTable *ht){
	printf("Table info:\n");
	//printf("  size:%zu\n", ht->size);
	//printf("  buckets:\n");
	for(size_t i = 0; i < ht->size; i++){
		//printf("\t[%zu] cap:%zu len:%zu\n", i, ht->buckets[i].cap, ht->buckets[i].len);
		printf("%zu\t|", i);
		printBucket(ht->buckets + i);
	}
}

void hashtbl_test(){
	HashTable ht = Table_new(12);
	TEST_LOG("table new");
	TEST_EQ(12, ht.size);
	TEST_EQ(false, (ht.buckets == NULL));
	TEST_LOG("testing buckets");
	for(size_t i = 0; i < ht.size; i++){
		TEST_EQ(false, (ht.buckets[i].data == NULL));
	}

	TEST_LOG("adding values");
	Table_add(&ht, (TableEntry){.key = "wow", .val = 7.5});
	Table_add(&ht, (TableEntry){.key = "flower", .val = 4.2});
	Table_add(&ht, (TableEntry){.key = "wow", .val = 7.5});
	Table_add(&ht, (TableEntry){.key = "egg", .val = 6.9});
	Table_add(&ht, (TableEntry){.key = "banana", .val = 5});
	Table_add(&ht, (TableEntry){.key = "wow", .val = 7.5});
	Table_add(&ht, (TableEntry){.key = "frogge", .val = -1});

	TEST_LOG("print table");
	printTable(&ht);
	TEST_LOG("Removing 'flower' and 'frogge'");
	Table_rm(&ht, "flower");
	Table_rm(&ht, "frogge");
	printTable(&ht);

	TEST_LOG("table del");
	Table_del(&ht);
	TEST_EQ(0, ht.size);
	TEST_EQ(true, (ht.buckets == NULL));
}

int main(int argc, const char** argv){
	hashtbl_test();
	return 0;
}
