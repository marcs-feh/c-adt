// Queue
// A queue is a FIFO structure, this implementation uses an underlying dynamic
// array as its storage.
// [ - - - - H x x x x x T - ]
// Whenever the queue needs more space the array is grown, to avoid too much
// memory consumption once the number of elements in the queue use less than
// half of its capacity, the underlying array is shrunk.

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

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
	q.cap = QUEUE_INIT_CAP;
	q.head = 0;
	q.tail = 0;
	q.data = malloc(sizeof(float) * q.cap);

	if(q.data == NULL){
		// Failed alloc
		q.cap = 0;
	}

	return q;
}

void Queue_resize(Queue *q, size_t n){
	if(q == NULL || n == 0) return;
	float *newdat = malloc(sizeof(float) * n);
	if(newdat == NULL){
		// Failed alloc
		return;
	}

	size_t i;
	for(i = 0; i < n && (i + q->head) < q->tail ; i++){
		newdat[i] = q->data[i + q->head];
	}

	q->cap = n;
	q->head = 0;
	q->tail = i;
	free(q->data);
	q->data = newdat;

}

void Queue_enq(Queue *q, float e){
	if(q == NULL) return;

	// Need more space.
	if(q->tail + 1 >= q->cap){
		// Resize
		Queue_resize(q, (q->cap * 2) + 1);
	}

	q->data[q->tail] = e;
	q->tail++;
}

void Queue_deq(Queue *q){
	if(q == NULL) return;
	if(q->head == q->tail) return;

	// More than half of queue is empty, shrink it.
	if(q->head > (q->cap / 2)){
		// Resize
		Queue_resize(q, (q->cap / 2) + 1);
	}

	q->head++;
}

void Queue_fit(Queue *q){
	if(q == NULL) return;
	Queue_resize(q, q->tail - q->head);
}

float *Queue_head(Queue *q){
	if(q == NULL) return NULL;
	return NULL;
}

float *Queue_tail(Queue *q){
	if(q == NULL) return NULL;
	return NULL;
}

void Queue_del(Queue *q){
	if(q == NULL) return;

	q->cap = 0;
	q->head = 0;
	q->tail = 0;
	free(q->data);
	q->data = NULL;
}
