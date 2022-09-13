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

void Vec_insert(Vec *v, size_t idx, float e){
	if(v == NULL) return;
	if(idx > v->len) return;

	// Inserting at pos len is same as appending.
	if(idx == v->len){
		Vec_append(v, e);
	} else {
		if(v->len + 1 >= v->cap){
			Vec_resize(v, (v->len * 2) + 1);
		}
		for(size_t i = v->len; i >= idx; i--){
			v->data[i + 1] = v->data[i];
			if(i == 0) break;
		}
		v->data[idx] = e;
		v->len++;
	}
}

void Vec_pop(Vec *v){
	if(v == NULL) return;
	if(v->len == 0) return;

	if(v->len - 1 <= (v->cap / 2)){
		Vec_resize(v, v->len);
	}

	v->len--;
}

float* vec_at(Vec *v, size_t idx){
	if(v == NULL) return NULL;
	if(idx >= v->len) return NULL;

	return v->data + idx;
}


