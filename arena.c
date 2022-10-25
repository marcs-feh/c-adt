// Memory Arena
// A memory arena is a block of memory that has its own custom allocators
// [XXXXX___-----]
// X = used memory, _ = padding, - = free space
// Every time a piece of the arena is allocated, we must align it foward.

#include <stdalign.h>
#include "ints.h"

#define MAX_ALIGN (alignof(max_align_t))

typedef struct Arena Arena;

struct Arena {
	byte  *buf;
	usize  used;
	usize  cap;
};

Arena Arena_init(usize hint){
	if(hint < MAX_ALIGN)
		hint = MAX_ALIGN;
	Arena ar = {NULL, 0, 0};
	return ar;
}

#undef MAX_ALIGN
