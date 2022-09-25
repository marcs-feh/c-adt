#include "autotest.h"
#include "tests.c"

void printQueue(Queue q){
	printf("C:%zu \tH(%zu)| ", q.cap, q.head);
	for(size_t i = q.head; i < q.tail; i++){
		printf("%.1f ", q.data[i]);
	}
	printf("|T(%zu)\n", q.tail);
}

void queue_test(){
	Queue q = Queue_new();
	TEST_LOG("queue new");
	TEST_EQ(0, q.head);
	TEST_EQ(0, q.tail);
	TEST_EQ(QUEUE_INIT_CAP, q.cap);
	TEST_EQ(true, q.data != NULL);

	TEST_LOG("enqueue");
	printQueue(q);
	Queue_enq(&q, 0.5f);
	printQueue(q);
	Queue_enq(&q, -1.2f);
	printQueue(q);
	Queue_enq(&q, 6.9f);
	printQueue(q);

	TEST_LOG("dequeue");
	Queue_deq(&q);
	printQueue(q);
	Queue_deq(&q);
	printQueue(q);
	Queue_deq(&q);
	printQueue(q);

	TEST_LOG("queue grow");
	for(size_t i = 0; i < 24; i++)
		Queue_enq(&q, i);
	TEST_EQ(33, q.cap);
	TEST_EQ(0, q.head);
	TEST_EQ(24, q.tail);
	printQueue(q);

	TEST_LOG("queue shrink");
	for(size_t i = 0; i < 18; i++)
		Queue_deq(&q);
	TEST_EQ(17, q.cap);
	TEST_EQ(1, q.head);
	TEST_EQ(7, q.tail);
	printQueue(q);


	TEST_LOG("queue del");
	Queue_del(&q);
	TEST_EQ(0, q.head);
	TEST_EQ(0, q.tail);
	TEST_EQ(0, q.cap);
	TEST_EQ(NULL, q.data);
}

int main(int argc, const char** argv){
	queue_test();
	return 0;
}
