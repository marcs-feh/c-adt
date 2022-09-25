#include "autotest.h"
#include "tests.c"

void queue_test(){
	Queue q = Queue_new();
	TEST_LOG("queue new");
	TEST_EQ(0, q.head);
	TEST_EQ(0, q.tail);
	TEST_EQ(QUEUE_INIT_CAP, q.cap);
	TEST_EQ(true, q.data != NULL);

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
