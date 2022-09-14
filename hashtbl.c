#include <stddef.h>
#include <stdlib.h>

#define HASH_TABLE_MIN_BUCKETS 8
#define HASH_TABLE_BUCKET_INIT_SIZE 16;

typedef struct {
	const char* key;
	float val;
} TableEntry;

typedef struct {
	size_t cap;
	size_t len;
	TableEntry *data;
} TableBucket;

typedef struct {
	TableBucket *buckets;
	size_t size;
} HashTable;

TableBucket Bucket_new(){
	TableBucket b;
	b.cap = HASH_TABLE_BUCKET_INIT_SIZE;
	b.len = 0;
	b.data = malloc(sizeof(*(b.data)) * b.cap);

	// Failed alloc.
	if(b.data == NULL){
		b.cap = 0;
		return b;
	}

	return b;
}

void Bucket_del(TableBucket *b){
	if(b == NULL) return;
	b->cap = 0;
	b->len = 0;
	free(b->data);
	b->data = NULL;
}

HashTable Table_new(size_t buckets){
	if(buckets < HASH_TABLE_MIN_BUCKETS)
		buckets = HASH_TABLE_MIN_BUCKETS;

	HashTable ht;
	ht.size = buckets;
	ht.buckets = malloc(sizeof(TableBucket) * ht.size);

	// Failed alloc.
	if(ht.buckets == NULL){
		ht.size = 0;
		return ht;
	}

	// Init buckets
	for(size_t i = 0; i < ht.size; i++){
		ht.buckets[i] = Bucket_new();
	}

	return ht;
}

void Table_del(HashTable *ht){
	if(ht == NULL) return;
	ht->size = 0;
	// Free bucket data.
	for(size_t i = 0; i < ht->size; i++){
		Bucket_del(&(ht->buckets[i]));
	}
	// Free buckets.
	free(ht->buckets);
	ht->buckets = NULL;
}
