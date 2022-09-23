#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

// Testing macros
#include "autotest.h"
// Dynamic array (vector)
#include "vec.c"
// Hash table
#include "hashtbl.c"

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
	TEST_LOG("Pop 50 times.");
	for(size_t i = 0; i < 50; i++)
		Vec_pop(&v);
	TEST_EQ(0, v.len);
	TEST_EQ(1, v.cap);

	TEST_LOG("Inserting");
	Vec_insert(&v, 0, 9);
	Vec_insert(&v, 0, 6);
	Vec_insert(&v, 0, 0);
	// Expect [0, 6, 9]
	TEST_EQ(0, v.data[0]);
	TEST_EQ(6, v.data[1]);
	TEST_EQ(9, v.data[2]);
	// Expect [0, 4, 6, 2, 9]
	Vec_insert(&v, 2, 2);
	Vec_insert(&v, 1, 4);
	TEST_EQ(0, v.data[0]);
	TEST_EQ(4, v.data[1]);
	TEST_EQ(6, v.data[2]);
	TEST_EQ(2, v.data[3]);
	TEST_EQ(9, v.data[4]);

	TEST_LOG("Removing");
	Vec_remove(&v, 0);
	Vec_remove(&v, 2);
	// Expect [4, 6, 9]
	TEST_EQ(4, v.data[0]);
	TEST_EQ(6, v.data[1]);
	TEST_EQ(9, v.data[2]);

	TEST_LOG("Access");
	TEST_EQ(false, (Vec_at(&v, 0) == NULL));
	TEST_EQ(false, (Vec_at(&v, 1) == NULL));
	TEST_EQ(false, (Vec_at(&v, 2) == NULL));
	TEST_EQ(true, (Vec_at(&v, 6) == NULL));

	TEST_LOG("Vec_del");
	Vec_del(&v);
	TEST_EQ(0, v.len);
	TEST_EQ(0, v.cap);
	TEST_EQ(true, (v.data == NULL));
}

void printBucket(TableBucket *b){
	for(size_t i = 0; i < b->len; i++){
		printf("\t%s:%f  ", b->data[i].key, b->data[i].val);
	}
	printf("\n");
}

void printTable(HashTable *ht){
	printf("Table info:\n");
	for(size_t i = 0; i < ht->size; i++){
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

	TEST_LOG("get values");
	TEST_EQ(7.5f, *Table_get(&ht, "wow"));
	TEST_EQ(NULL, Table_get(&ht, "frogge"));

	TEST_LOG("table del");
	Table_del(&ht);
	TEST_EQ(0, ht.size);
	TEST_EQ(true, (ht.buckets == NULL));
}

