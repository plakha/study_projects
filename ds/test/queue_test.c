#include <stdio.h> /* printf */
#include <string.h> /*strcmp */

#include "../include/queue.h" /* Singly linked list */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \
	
int FlowEmptyQueue()
{
	queue_t *queue = NULL;
	int ret = 0;
	
	if(NULL == (queue = QueueCreate()))
	{
		puts("create alloc failure");
		
		return 1;
	}
	
	if(!QueueIsEmpty(queue))
	{
		printf("line %d IsEmpty == %d FAIL\n", __LINE__, QueueIsEmpty(queue));
	}
	
	
	if(0 != QueueSize(queue))
	{
		printf("line %d Size == %ld FAIL\n", __LINE__, QueueSize(queue));
	}
	
	QueueDestroy(queue);

	return ret;;
}

int FlowQueueEnqueueDequeuePeek()
{
	static char *data1 = "You_say_good-bye";
	static char *data2 = "But_I_say_hello";
	queue_t *queue = NULL;
	int ret = 0;
	
	if(NULL == (queue = QueueCreate()))
	{
		puts("create alloc failure");
		
		return 1;
	}
	
	QueueEnqueue(queue, data1);
	QueueEnqueue(queue, data2);
	if(0 != strcmp((char *)QueuePeek(queue), data1))
	{
		printf("line%d Enqueue FAIL", __LINE__);
		ret = 1;
	}
	if(2 != QueueSize(queue))
	{
		printf("line %d Size == %ld FAIL\n", __LINE__, QueueSize(queue));
		ret = 2;
	}
	QueueDequeue(queue);
	if(0 != strcmp((char *)QueuePeek(queue), data2))
	{
		printf("line%d Dequeue FAIL", __LINE__);
		ret = 2;
	}
	
	QueueDestroy(queue);
	
	return ret;
}

int FlowAppend()
{
	static char *data1 = "You_say_good-bye";
	static char *data2 = "But_I_say_hello";
	queue_t *queue1 = NULL;
	queue_t *queue2 = NULL;
	int ret = 0;
	
	if(NULL == (queue1 = QueueCreate()))
	{
		puts("create alloc failure");
		
		return 1;
	}
	if(NULL == (queue2 = QueueCreate()))
	{
		puts("create alloc failure");
		
		return 1;
	}
	QueueEnqueue(queue1, data1);
	puts((char *)QueuePeek(queue1));
	QueueEnqueue(queue2, data2);
	puts((char *)QueuePeek(queue2));
	QueueAppend(queue1, queue2);
	QueueDestroy(queue2);
	puts((char *)QueuePeek(queue1));
	if(0 != strcmp((char *)QueuePeek(queue1), data1))
	{
		printf("line%d Dequeue FAIL", __LINE__);
		ret = 2;
	}
	
	QueueDestroy(queue1);
	return ret;
}

int main()
{
	RUN_TEST(FlowEmptyQueue);
	RUN_TEST(FlowQueueEnqueueDequeuePeek);
	RUN_TEST(FlowAppend);
	
	return 0;
}
