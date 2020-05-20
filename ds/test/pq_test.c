#include <stdio.h> /* printf */

#include "pq.h" /* pq_t */


#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \
	
int IsToPushBefore(const void *data,const void  *new_data, const void *param)
{
	(void)param;
	
	return *(int *)data > *(int *)new_data;
}

int Is10Found(const void *data, const void *key, const void *param)
{
	(void)key;
	(void)param;
	
	return 10 == *(int *)data;
}
	
int FlowPQ()
{
	int ret = 0;
	pq_t *pq = NULL;
	int data1 = 1;
	int data2 = 10;
	
	if( NULL == (pq = PQCreate(IsToPushBefore)) )
	{
		puts("alloc fail");
		
		return 1;
	}
	puts("\nCreate and Destroy - check vlg! ");

	printf("empty PQ. PQIsEmpty = %d\n", PQIsEmpty(pq));
	if(!PQIsEmpty(pq))
	{
		puts("IsEmpty FAIL");
		ret = 1;
	}
	
	PQClear(pq);
	
	printf("None pushed. size = %lu\n", PQSize(pq));
	if(0 != PQSize(pq))
	{
		puts("Size 0  FAIL");
		ret = 1;
	}
	

	if(0 == PQErase(pq, NULL, IsToPushBefore))
	{
		ret = 1;
		puts("erased non existent data");
		
	}
	
	PQEnqueue(pq, &data1);
	PQEnqueue(pq, &data1);
	PQEnqueue(pq, &data1);	
	PQEnqueue(pq, &data2);
	if(4 != PQSize(pq))
	{
		ret = 1;
		puts("expected size 4 FAILED:(");
	}
	if(1 == PQErase(pq, NULL, Is10Found))
	{
		
		ret = 1;
		puts("not erased 10 data");
	}	
	if(3 != PQSize(pq))
	{
		ret = 1;
		puts("expected size 3 FAILED:(");
	}
	PQClear(pq);
	if(0 != PQSize(pq))
	{
		ret = 1;
		puts("expected size 0 FAILED:(");
	}
	PQDestroy(pq);
	
	return ret;
}

int main()
{
	pq_t *pq = PQCreate(IsToPushBefore);
	PQDestroy(pq);
	RUN_TEST(FlowPQ);
	return 0;
}
	
