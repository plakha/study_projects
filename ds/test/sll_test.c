#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <string.h> /* strcmp */

#include "../include/sll.h" /* sll header */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \
	
int FlowEmptySLL()
{
	int ret = 0;
	sll_t *sll = NULL;
	
	if( NULL == (sll = SLLCreate()) )
	{
		puts("alloc fail");
		
		return 1;
	}
	puts("\nCreate and Destroy - check vlg! ");

	printf("empty sll. SLLIsEmpty = %d\n", SLLIsEmpty(sll));
	if(!SLLIsEmpty(sll))
	{
		puts("IsEmpty FAIL");
		ret = 1;
	}
	
	printf("None pushed. size = %lu\n", SLLSize(sll));
	if(0 != SLLSize(sll))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	if(SLLEnd(sll) != SLLBegin(sll))
	{
		puts("Empty SSL Begin, End FAIL");
		ret = 1;
	}
	
	if(NULL != SLLNext(SLLEnd(sll)))
	{
		puts("Empty SSL End, Next FAIL");
		ret = 1;
	}
	
	SLLDestroy(sll);
	
	return ret;
}

int FlowPushFrontDestroy()
{
	int ret = 0;
	sll_t *sll = NULL;
	char data1[] = "home";
	char data2[] = "block";
/*	char data3[] = "streetlight";*/
/*	char data4[] = "pharmacy";*/
	
	if( NULL == (sll = SLLCreate()) )
	{
		puts("alloc fail");
		
		return 1;
	}
	puts("Create, Push, Destroy - vlg check");
	
	SLLPushFront(sll, data1);
	printf("non empty sll. SLLIsEmpty = %d\n", SLLIsEmpty(sll));
	if(SLLIsEmpty(sll))
	{
		puts("After Push IsEmpty - FAIL");
		ret = 1;
	}
	
	printf("One pushed. size = %lu\n", SLLSize(sll));
	if(1 != SLLSize(sll))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	if( 0 != strcmp ( data1, SLLGetData(SLLBegin(sll)) ) )
	{
		printf("inserted %s, read %s\n", data1, (char *)SLLGetData(SLLBegin(sll)));
		ret = 1;
	}
	
	if(SLLEnd(sll) != SLLNext(SLLBegin(sll)))
	{
		puts("Next SSL End, Next FAIL");
		ret = 1;
	}
	
	if(NULL != SLLNext(SLLEnd(sll)))
	{
		puts("Next SSL End, Next FAIL");
		ret = 1;
	}
	
	SLLPopBack(sll);
	printf("One popped. size = %lu\n", SLLSize(sll));
	if(0 != SLLSize(sll))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	SLLPushBack(sll, data1);
	printf("non empty sll. SLLIsEmpty = %d\n", SLLIsEmpty(sll));
	if(SLLIsEmpty(sll))
	{
		puts("After Push IsEmpty - FAIL");
		ret = 1;
	}
	
	printf("One pushed. size = %lu\n", SLLSize(sll));
	if(1 != SLLSize(sll))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	if( 0 != strcmp ( data1, SLLGetData(SLLBegin(sll)) ) )
	{
		printf("inserted %s, read %s\n", data1, (char *)SLLGetData(SLLBegin(sll)));
		ret = 1;
	}
	
	SLLPopFront(sll);
	printf("One popped. size = %lu\n", SLLSize(sll));
	if(0 != SLLSize(sll))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	SLLPushBack(sll, data1);
	SLLInsertAfter(sll, SLLBegin(sll), data2);
	sll = SLLFlip(sll);
	
	if( 0 == strcmp ( data2, SLLGetData(SLLBegin(sll)) ) )
	{
		puts("flip success OK");
	}
	else
	{
		ret = 1;
	}
	
	SLLDestroy(sll);	
	
	return ret;
}

int Act(void *data, const void *param)
{
	*(int *)data *= *(int *)param;
	return 0;
}

int Is10Found(const void *data, const void *hold)
{
/*	*(int *)&hold = 0xDEADBEEF;*/

	return (5 == *(int *)data);
}
int FlowForEach()
{
	int ret = 0;
	sll_t *sll = NULL;
	static int arr[] = {1, 1, 5, 5, 5, 5, 5};
	
	if( NULL == (sll = SLLCreate()) )
	{
		puts("alloc fail");
		
		return 1;
	}
	puts("Create, Push, Destroy - vlg check");
	
	SLLPushFront(sll, arr + 0);
	SLLPushBack(sll, arr + 1);
	SLLPushBack(sll, arr + 2);
	SLLPushBack(sll, arr + 3);
	
	SLLForEach(SLLBegin(sll), SLLEnd(sll), arr + 5, Act);
	if(5 == *(int *)SLLGetData(SLLBegin(sll)))
	{
		puts("ForEach OK");
	}
	else
	{
		printf("FAIL 1 * 5 = %d\n", *(int *)SLLGetData(SLLBegin(sll)));
		ret = 1;
	}
	
	printf("5 found? %d\n", *(int *)SLLGetData(SLLFind(SLLBegin(sll), SLLEnd(sll), (const void *)(arr + 5), Is10Found)));
	return ret;
}


int main()
{
	RUN_TEST(FlowEmptySLL);
	RUN_TEST(FlowPushFrontDestroy);
	RUN_TEST(FlowForEach);
	
	return 0;
}
