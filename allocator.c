#include "types.h"
#include <stdlib.h>

typedef struct LinearAlloc LinearAlloc;

#define DEFAULT_ALIGN (alignof(max_align_t))

/* Memory utility macros */
#define KiB(n) (n * 1024)
#define MiB(n) (n * 1024 * 1024)
#define GiB(n) (n * 1024 * 1024 * 1024)

struct LinearAlloc {
	usize offset;
	usize cap;
	byte* base;
};

uintptr Alloc_align_fwd(void* ptr, usize align){
	uintptr p = (uintptr)ptr;
	usize mod = p % align;

	if(mod != 0){
		p += align - mod;
	}

	return p;
}

LinearAlloc* LAlloc_new(usize nbytes){
	if(nbytes < DEFAULT_ALIGN) return NULL;
	LinearAlloc* allocator = malloc(sizeof(*allocator));
	allocator->base   = malloc(sizeof(*(allocator->base)) * nbytes);
	allocator->offset = 0;
	allocator->cap    = nbytes;

	return allocator;
}

void* LAlloc_alloc(LinearAlloc* allocator, usize nbytes){
	if(nbytes == 0) return NULL;
	uintptr base  = (uintptr)allocator->base;
	uintptr limit = base + allocator->cap;
	uintptr p = Alloc_align_fwd(allocator->base + allocator->offset, DEFAULT_ALIGN);
	// OOM
	if((p + nbytes) >= limit){
		return NULL;
	}

	allocator->offset = (p + nbytes) - base;
	return (void*)p;
}

void LAlloc_del(LinearAlloc* allocator){
	if(allocator == NULL) return;
	free(allocator->base);
	free(allocator);
}
