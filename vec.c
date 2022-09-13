#include <stddef.h>
#include <stdlib.h>

#define VEC_INIT_CAP 16

typedef struct {
	size_t cap;
	size_t len;
	float *data;
} Vec;

Vec Vec_new(){
	Vec v;
	v.cap = VEC_INIT_CAP;
	v.len = 0;
	v.data = malloc(v.cap * sizeof(*v.data));

	// Failed alloc.
	if(v.data == NULL) v = (Vec){0, 0, NULL};

	return v;
}

void Vec_del(Vec *v){
	if(v == NULL) return;
	v->len = 0;
	v->cap = 0;
	free(v->data);
	v->data = NULL;
}


