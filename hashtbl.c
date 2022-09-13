#include <stddef.h>

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
	const size_t size;
} HashTable;

