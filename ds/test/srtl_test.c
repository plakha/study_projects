#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <string.h> /* strcmp */

#include "../include/srtl.h"

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \

int is_before(const void *data,const void  *new_data, const void *param)
{
	(void)param;
	
	return *(int *)data > *(int *)new_data;
}

int Is10Found(const void *data, const void *key, const void *param)
{
	(void)key;
	(void)param;
	
	return 0 == *(int *)data;
}
int FlowEmptySrtL()
{
	int ret = 0;
	srtl_t *srtl = NULL;
	
	if( NULL == (srtl = SrtLCreate(is_before, NULL)) )
	{
		puts("alloc fail");
		
		return 1;
	}
	puts("\nCreate and Destroy - check vlg! ");

	printf("empty SrtL. SrtLIsEmpty = %d\n", SrtLIsEmpty(srtl));
	if(!SrtLIsEmpty(srtl))
	{
		puts("IsEmpty FAIL");
		ret = 1;
	}
	
	printf("None pushed. size = %lu\n", SrtLSize(srtl));
	if(0 != SrtLSize(srtl))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	if(SrtLEnd(srtl) != SrtLBegin(srtl))
	{
		puts("Empty SSL Begin, End FAIL");
		ret = 1;
	}
	
	if(NULL != SrtLNext(SrtLEnd(srtl)))
	{
		puts("Empty SSL End, Next FAIL");
		ret = 1;
	}
	
	SrtLDestroy(srtl);
	
	return ret;
}

int FlowInsertPop()
{
	int ret = 0;
	srtl_t *srtl = NULL;
	int data1 = 20;
	int data2 = 1;
	int data3 = -9;
	int data4 = 10;
	
	if( NULL == (srtl = SrtLCreate(is_before, NULL)) )
	{
		puts("alloc fail");
		
		return 1;
	}
	puts("Create, Insert, Pop, Destroy - vlg check");
	
	SrtLInsert(srtl, &data1);
	printf("non empty SrtL. SrtLIsEmpty = %d\n", SrtLIsEmpty(srtl));
	if(SrtLIsEmpty(srtl))
	{
		puts("After Push IsEmpty - FAIL");
		ret = 1;
	}
	
	printf("One pushed. size = %lu\n", SrtLSize(srtl));
	if(1 != SrtLSize(srtl))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	if( *(int *)SrtLGetData(SrtLBegin(srtl)) != data1 )
	{
		printf("inserted %d, read %s\n", data1, (char *)SrtLGetData(SrtLBegin(srtl)));
		ret = 1;
	}
	
	
	
	
	SrtLPopBack(srtl);
	printf("One popped. size = %lu\n", SrtLSize(srtl));
	if(0 != SrtLSize(srtl))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	SrtLInsert(srtl, &data1);
	printf("non empty SrtL. SrtLIsEmpty = %d\n", SrtLIsEmpty(srtl));
	if(SrtLIsEmpty(srtl))
	{
		puts("After Push IsEmpty - FAIL");
		ret = 1;
	}
	
	printf("One pushed. size = %lu\n", SrtLSize(srtl));
	if(1 != SrtLSize(srtl))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	if(*(int *)SrtLGetData(SrtLBegin(srtl)) != data1)
	{
		printf("inserted %d, read %s\n", data1, (char *)SrtLGetData(SrtLBegin(srtl)));
		ret = 1;
	}
	
	SrtLPopFront(srtl);
	printf("One popped. size = %lu\n", SrtLSize(srtl));
	if(0 != SrtLSize(srtl))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	SrtLInsert(srtl, &data1);
	SrtLInsert(srtl, &data2);
	SrtLInsert(srtl, &data3);
	SrtLInsert(srtl, &data4);
	if(4 != SrtLSize(srtl))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	while(!SrtLIsEmpty(srtl))
	{
		printf("\n%d", *(int *)SrtLGetData(SrtLBegin(srtl)));
		SrtLPopFront(srtl);
	}
	SrtLDestroy(srtl);	
	
	return ret;
}

int Act(void *data, const void *param)
{
	*(int *)data *= *(int *)param;
	return 0;
}


/*int Is10Found(const void *data, const void *hold)*/
/*{*/
/*	*(int *)&hold = 0xDEADBEEF;*/

/*	return (5 == *(int *)data);*/
/*}*/

int FlowForEach()
{

	int ret = 0;
	srtl_t *srtl = NULL;
	int data1 = 20;
	int data2 = 1;
	int data3 = -9;
	int data4 = 10;
	int param = 2;
	
	if( NULL == (srtl = SrtLCreate(is_before, NULL)) )
	{
		puts("alloc fail");
		
		return 1;
	}
	
	SrtLInsert(srtl, &data1);
	SrtLInsert(srtl, &data2);
	SrtLInsert(srtl, &data3);
	SrtLInsert(srtl, &data4);
	if(4 != SrtLSize(srtl))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	SrtLForEach(SrtLBegin(srtl), SrtLEnd(srtl), Act, &param);
	while(!SrtLIsEmpty(srtl))
	{
		printf("%d\n", *(int *)SrtLGetData(SrtLPrev(SrtLEnd(srtl))));
		SrtLPopBack(srtl);
	}
	
	SrtLInsert(srtl, &data1);
	SrtLInsert(srtl, &data2);
	SrtLInsert(srtl, &data3);
	SrtLInsert(srtl, &data4);
	
	printf("\n20 found ? %x\n",  (long)SrtLGetData(SrtLFind(SrtLBegin(srtl), SrtLEnd(srtl), Is10Found, NULL, NULL)) );
	
	SrtLDestroy(srtl);	
	
	return ret;
}

static void PrintList(srtl_t *srtl)
{
	sit_t iter = SrtLBegin(srtl);
	sit_t end = SrtLEnd(srtl);
	while(end != iter)
	{
		printf("%d->", *(int *)SrtLGetData(iter));
		iter = SrtLNext(iter);
	}
	puts("");
}

int TestMerge()
{
	int data1[] = {1, 21, -9, 9, 8, -9};
	int data2[] = {1, 56, 0};
/*	int data1[] = {1, 4, 5, 7};*/
/*	int data2[] = {2, 3, 6, 8, 9};*/
	size_t i = 0;
	srtl_t *srtl1 = NULL;
	srtl_t *srtl2 = NULL;
	int ret = 0;
	
	puts("Test Merge");
	
	if( NULL == (srtl1 = SrtLCreate(is_before, NULL)) 
		|| NULL == (srtl2 = SrtLCreate(is_before, NULL)))
	{
		puts("alloc fail");
		free(srtl1);
		free(srtl2);
		
		return 1;
	}
	
	for(i = 0; 6 > i; ++i)
	{
		SrtLInsert(srtl1, data1 + i);
	}
	PrintList(srtl1);
	for(i = 0; 3 > i; ++i)
	{
		SrtLInsert(srtl2, data2 + i);
	}
	PrintList(srtl2);
	SrtLMerge(srtl1, srtl2);	
	
		PrintList(srtl1);
		
	SrtLDestroy(srtl1);	
	SrtLDestroy(srtl2);	

	
	return ret;
}

int main()
{
	srtl_t *srtl = SrtLCreate(is_before, NULL);
	SrtLDestroy(srtl);
	
	RUN_TEST(FlowEmptySrtL);
	RUN_TEST(FlowInsertPop);
	RUN_TEST(FlowForEach);
	RUN_TEST(TestMerge);

	
	return 0;
}
