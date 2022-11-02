// Memory Arena
// A memory arena is a block of memory that has its own custom allocators
// [XXXXX___-----]
// X = used memory, _ = padding, - = free space
// Every time a piece of the arena is allocated, we must align it foward.

#include <stdalign.h>
#include <stdlib.h>
#include "ints.h"

#define MAX_ALIGN (alignof(max_align_t))

typedef struct Arena Arena;

struct Arena {
	byte  *buf;
	usize  used;
	usize  cap;
};

Arena Arena_new(usize hint){
	if(hint < MAX_ALIGN)
		hint = MAX_ALIGN;
	Arena ar = {0};
	byte *buf;
	buf = malloc(hint * sizeof(*buf));
	// failed alloc
	if(buf == NULL){ exit(-1); return ar; }
	ar.buf  = buf;
	ar.used = 0;
	ar.cap  = hint;
	return ar;
}

// Aligns ptr foward to MAX_ALIGN
static uptr Arena_align_fwd(void *ptr){
	uptr p = (uptr)ptr;
	usize mod = p % MAX_ALIGN;
	if(mod != 0){
		p += MAX_ALIGN - mod;
	}
	return p;
}

void *Arena_alloc(Arena *ar, usize nbytes){
	if(nbytes == 0 || ar == NULL) return NULL;
}

void Arena_del(Arena *ar){
	if(ar == NULL) return;
	free(ar->buf);
	ar->buf  = NULL;
	ar->used = 0;
	ar->cap  = 0;
}

#undef MAX_ALIGN
