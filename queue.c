#include <stddef.h>

typedef struct Queue Queue;

struct Queue {
	size_t cap;
	size_t head;
	size_t tail;
	float *data;
};

Queue Queue_new(){
	Queue q;
	return q;
}

void Queue_enq(){}

void Queue_deq(){}

float *Queue_head(Queue *q){
	return NULL;
}

float *Queue_tail(Queue *q){
	return NULL;
}

void Queue_del(Queue *q){
}
