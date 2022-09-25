// Hash Table
// A hash table uses a hashing function to associate a certain key to a index
// in its internal storage. This implementation uses closed addressing, each
// bucket is a Dynamic Array that can grow as needed. The number of buckets is
// decided upon initializing the table.
// 4 buckets example
// | -> [{key:val} {key:val} | <free space>]
// | -> [{key:val} | <free space>]
// | -> [ | <free storage]
// | -> [{key:val} | <free space>]

#include "autotest.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_MIN_BUCKETS 8
#define HASH_TABLE_BUCKET_INIT_SIZE 16;
#define HASH_TABLE_NPOS ((size_t)(-1))

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
	//b.data = malloc(sizeof(*b.data) * b.cap);
	b.data = calloc(b.cap, sizeof(*b.data));

	// Failed alloc.
	if(b.data == NULL){
		b.cap = 0;
		return b;
	}


	return b;
}

void Bucket_resize(TableBucket *b, size_t n){
	if(b == NULL) return;
	TableEntry *newdata = realloc(b->data, n * sizeof(*newdata));

	// Failed alloc.
	if(newdata == NULL) return;

	b->data = newdata;
	b->cap = n;
	if(b->len > n)
		b->len = n;
}

bool Bucket_hasKey(TableBucket *b, const char* key){
	if(b == NULL || key == NULL) return false;
	for(size_t i = 0; i < b->len; i++)
		if(strcmp(b->data[i].key, key) == 0)
			return true;
	return false;
}

void Bucket_add(TableBucket *b, TableEntry entry){
	if(b == NULL) return;

	// Check conflict.
	if(!Bucket_hasKey(b, entry.key)){
		// Grow if needed.
		if(b->len + 1 >= b->cap){
			Bucket_resize(b, (2 * b->len) + 1);
		}
		b->data[b->len] = entry;
		b->len++;
	}
}

size_t Bucket_find(TableBucket *b, const char* key){
	if(b == NULL) return HASH_TABLE_NPOS;
	if(b->len == 0 || key == NULL) return HASH_TABLE_NPOS;

	for(size_t i = 0; i < b->len; i++){
		if(strcmp(key, b->data[i].key) == 0){
			return i;
		}
	}
	return HASH_TABLE_NPOS;
}

void Bucket_rm(TableBucket *b, const char* key){
	if(b == NULL) return;
	if(b->len == 0 || key == NULL) return;
	size_t idx = Bucket_find(b, key);

	// Shrink if needed.
	if(b->len - 1 <= (b->cap / 2)){
		Bucket_resize(b, b->len);
	}

	if(idx != HASH_TABLE_NPOS){
		if(idx == b->len){ // Removing at pos len is same as popping.
			b->len--;
		} else {
			for(uint i = idx; i < b->len - 1; i++){
				b->data[i] = b->data[i+1];
			}
			b->len--;
		}
	}
}

void Bucket_del(TableBucket *b){
	if(b == NULL) return;
	free(b->data);
	b->data = NULL;
	b->cap = 0;
	b->len = 0;
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

size_t Table_hfunc(const char* key, size_t tbl_size){
	const size_t keylen = strlen(key);
	size_t h = 1;
	for(size_t i = 0; i < keylen; i++)
		h = ((h * 31) + (size_t)(key[i]));

	return (h % tbl_size);
}

void Table_add(HashTable *ht, TableEntry entry){
	if(ht == NULL) return;
	if(entry.key == NULL) return;

	size_t pos = Table_hfunc(entry.key, ht->size);

	Bucket_add(ht->buckets + pos, entry);
}

float* Table_get(HashTable *ht, const char *key){
	if(ht == NULL || key == NULL) return NULL;

	size_t tpos = Table_hfunc(key, ht->size);
	size_t bpos = Bucket_find(ht->buckets + tpos, key);

	if(bpos == HASH_TABLE_NPOS)
		return NULL;
	else
		return &(ht->buckets[tpos].data[bpos].val);
}

void Table_rm(HashTable *ht, const char *key){
	if(ht == NULL || key == NULL) return;
	TableBucket *b = ht->buckets + Table_hfunc(key, ht->size);
	Bucket_rm(b, key);
}

void Table_del(HashTable *ht){
	if(ht == NULL) return;
	// Free bucket data.
	for(size_t i = 0; i < ht->size; i++){
		Bucket_del(ht->buckets + i);
	}
	// Free bucket array.
	free(ht->buckets);
	ht->buckets = NULL;
	ht->size = 0;
}

