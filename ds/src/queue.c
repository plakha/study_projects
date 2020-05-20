/***************************************************************
Queue library (wrapper around Singly Linked List)
Author Andrei
Reviewer Mishel
6.6.2019
*********************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "sll.h" /* SLLIsEmpty */

#include "queue.h" /* Queue wrapper on singly link list */

struct queue
{
	sll_t *sll;
};

/*typedef struct queue queue_t;*/

static sll_t *StripQueueToSLL(queue_t *queue)
{
	assert(NULL != queue);
	
	return queue->sll;
}

queue_t *QueueCreate()
{
	queue_t *queue = (queue_t *)malloc(sizeof(*queue));
	
	if(NULL == queue)
	{
	
		return NULL;
	}
	
	if(NULL == (queue->sll = SLLCreate()))
	{
		free(queue);
		
		return NULL;
	}
	
	return queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLDestroy(StripQueueToSLL(queue));
	free(queue);
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	assert(NULL != 	StripQueueToSLL((queue_t *)queue));
	
	return SLLIsEmpty(StripQueueToSLL((queue_t *)queue));
}

size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);
	assert(NULL != 	StripQueueToSLL((queue_t *)queue));
	
	return SLLSize(StripQueueToSLL((queue_t *)queue));
}

int QueueEnqueue(queue_t *queue, const void *data)
{
	assert(NULL != queue);
	assert(NULL != StripQueueToSLL(queue));

	return SLLEnd(StripQueueToSLL(queue)) 
						== SLLPushBack(StripQueueToSLL(queue), (void *)data);
}

void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);
	assert(NULL != StripQueueToSLL(queue));
	assert(!QueueIsEmpty(queue));
	
	SLLPopFront(StripQueueToSLL(queue));
}

void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	assert(NULL != StripQueueToSLL((queue_t *)queue));
	
	return SLLGetData(SLLBegin(StripQueueToSLL((queue_t *)queue)));
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	it_t run_src = NULL;
	
	assert(NULL != dest && NULL != src);
	assert(NULL != StripQueueToSLL(dest) && NULL != StripQueueToSLL(src));
	
	run_src = SLLBegin(StripQueueToSLL(src));
	while(SLLEnd(StripQueueToSLL(src)) != run_src)
	{
		SLLPushBack(StripQueueToSLL(dest), SLLGetData(run_src));
		run_src = SLLNext(run_src);
	}
	
	return dest;
}
