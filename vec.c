#include <stddef.h>
#include <stdlib.h>

#define VEC_INIT_CAP 16
#define MIN(a, b) (((a <= b) * a) + ((b < a) * b))

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

void Vec_resize(Vec *v, size_t n){
	if(v == NULL) return;
	float *newdata = realloc(v->data, n * sizeof(*newdata));

	// Failed alloc.
	if(newdata == NULL) return;

	v->data = newdata;
	v->cap = n;
	if(v->len > n)
		v->len = n;
}

void Vec_append(Vec *v, float e){
	if(v == NULL) return;
	if(v->len + 1 >= v->cap){
		Vec_resize(v, (v->cap * 2) + 1);
	}

	v->data[v->len] = e;
	v->len++;
}


