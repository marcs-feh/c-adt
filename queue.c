// Queue
// A queue is a FIFO structure, this implementation uses an underlying dynamic
// array as its storage.
// [ - - - - T x x x x x H - ]
// Whenever the queue needs more space the array is grown, to avoid too much
// memory consumption once the number of elements in the queue use less than
// 40% of its capacity, the underlying array is shrunk.

#include <stddef.h>
#include <stdint.h>

#define QUEUE_INIT_CAP 16
#define MAX(a, b) (((a >= b) * a) + ((b > a) * b))
#define MIN(a, b) (((a <= b) * a) + ((b < a) * b))

typedef struct Queue Queue;

struct Queue {
	size_t cap;
	size_t head;
	size_t tail;
	float *data;
};


Queue Queue_new(){
	Queue q;
	q.cap = 0;
	q.head = 0;
	q.tail = 0;
	q.data = NULL;
	return q;
}

void Queue_enq(){}

void Queue_deq(){}

float *Queue_head(Queue *q){
	if(q == NULL) return NULL;
	return NULL;
}

float *Queue_tail(Queue *q){
	return NULL;
}

void Queue_del(Queue *q){
}
