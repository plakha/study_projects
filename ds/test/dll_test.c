#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <string.h> /* strcmp */

#include "dll.h" 

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \
	
int FlowEmptyDLL()
{
	int ret = 0;
	dll_t *dll = NULL;
	
	if( NULL == (dll = DLLCreate()) )
	{
		puts("alloc fail");
		
		return 1;
	}
	puts("\nCreate and Destroy - check vlg! ");

	printf("empty DLL. DLLIsEmpty = %d\n", DLLIsEmpty(dll));
	if(!DLLIsEmpty(dll))
	{
		puts("IsEmpty FAIL");
		ret = 1;
	}
	
	printf("None pushed. size = %lu\n", DLLSize(dll));
	if(0 != DLLSize(dll))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	if(DLLEnd(dll) != DLLBegin(dll))
	{
		puts("Empty SSL Begin, End FAIL");
		ret = 1;
	}
	
	if(NULL != DLLNext(DLLEnd(dll)))
	{
		puts("Empty SSL End, Next FAIL");
		ret = 1;
	}
	
	DLLDestroy(dll);
	
	return ret;
}

int FlowPushFrontDestroy()
{
	int ret = 0;
	dll_t *dll = NULL;
	char data1[] = "home";
	char data2[] = "block";
	char data3[] = "streetlight";
	char data4[] = "pharmacy";
	
	if( NULL == (dll = DLLCreate()) )
	{
		puts("alloc fail");
		
		return 1;
	}
	puts("Create, Push, Destroy - vlg check");
	
	DLLPushFront(dll, data1);
	printf("non empty DLL. DLLIsEmpty = %d\n", DLLIsEmpty(dll));
	if(DLLIsEmpty(dll))
	{
		puts("After Push IsEmpty - FAIL");
		ret = 1;
	}
	
	printf("One pushed. size = %lu\n", DLLSize(dll));
	if(1 != DLLSize(dll))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	if( 0 != strcmp ( data1, DLLGetData(DLLBegin(dll)) ) )
	{
		printf("inserted %s, read %s\n", data1, (char *)DLLGetData(DLLBegin(dll)));
		ret = 1;
	}
	
	if(DLLEnd(dll) != DLLNext(DLLBegin(dll)))
	{
		puts("Next SSL End, Next FAIL");
		ret = 1;
	}
	
	if(NULL != DLLNext(DLLEnd(dll)))
	{
		puts("Next SSL End, Next FAIL");
		ret = 1;
	}
	
	DLLPopBack(dll);
	printf("One popped. size = %lu\n", DLLSize(dll));
	if(0 != DLLSize(dll))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	DLLPushBack(dll, data1);
	printf("non empty DLL. DLLIsEmpty = %d\n", DLLIsEmpty(dll));
	if(DLLIsEmpty(dll))
	{
		puts("After Push IsEmpty - FAIL");
		ret = 1;
	}
	
	printf("One pushed. size = %lu\n", DLLSize(dll));
	if(1 != DLLSize(dll))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	if( 0 != strcmp ( data1, DLLGetData(DLLBegin(dll)) ) )
	{
		printf("inserted %s, read %s\n", data1, (char *)DLLGetData(DLLBegin(dll)));
		ret = 1;
	}
	
	DLLPopFront(dll);
	printf("One popped. size = %lu\n", DLLSize(dll));
	if(0 != DLLSize(dll))
	{
		puts("Size FAIL");
		ret = 1;
	}
	
	DLLPushBack(dll, data1);
	DLLInsert(dll, DLLBegin(dll), data2);
	
	DLLDestroy(dll);	
	
	return ret;
}

static int Act(void *data, const void *param)
{
	*(int *)data *= *(int *)param;
	return 0;
}


static int Is10Found(const void *data, const void *key, const void *hold)
{
	*(int *)&hold = 0xDEADBEEF;
	(void)hold;
	(void)key;
	return (5 == *(int *)data);
}

int FlowForEach()
{
	int ret = 0;
	dll_t *dll = NULL;
	static int arr[] = {1, 1, 5, 5, 5, 5, 5};
	it_t end = NULL;
	it_t begin = NULL;
	it_t find = NULL;

	if( NULL == (dll = DLLCreate()) )
	{
		puts("alloc fail");
		
		return 1;
	}
	puts("Create, Push, Destroy - vlg check");

	end = DLLEnd(dll);
	begin = DLLBegin(dll);
printf("Empty list 5 found? %x\n", (size_t)DLLGetData( DLLFind (DLLBegin(dll), 
		DLLEnd(dll), Is10Found, &ret, NULL)) );
	
	DLLPushFront(dll, arr + 0);
	DLLPushBack(dll, arr + 1);
	DLLPushBack(dll, arr + 2);
	DLLPushBack(dll, arr + 3);
	
	end = DLLEnd(dll);
	begin = DLLBegin(dll);
printf("Empty list 5 found? %x\n", *(int *)DLLGetData( DLLFind (begin, 
		end, Is10Found, &ret, NULL)) );

	DLLForEach(DLLBegin(dll), DLLEnd(dll), Act, arr + 5);
	if(5 == *(int *)DLLGetData(DLLBegin(dll)))
	{
		puts("ForEach OK");
	}
	else
	{
		printf("FAIL 1 * 5 = %d\n", *(int *)DLLGetData(DLLBegin(dll)));
		ret = 1;
	}
	
	printf("5 found? %x\n", *(int *)DLLGetData( DLLFind (DLLBegin(dll), 
		DLLEnd(dll), Is10Found, NULL, NULL)) );

	DLLDestroy(dll);
	return ret;
}

int TestSpliceBefore()
{
	int ret = 0;
	dll_t *dll_dest = NULL;
	dll_t *dll_src = NULL;
	it_t i = NULL;
	char data1[] = "home";
	char data2[] = "block";
	char data3[] = "streetlight";
	char data4[] = "pharmacy";
	
	if( NULL == (dll_dest = DLLCreate()) || NULL == (dll_src = DLLCreate()) )
	{
		puts("alloc fail");
		free(dll_dest);
		free(dll_src);
		
		return 1;
	}
	puts("Create, Push, Destroy - vlg check");
	
	DLLPushFront(dll_dest, data4);
	DLLPushFront(dll_dest, data3);
	DLLPushFront(dll_dest, data2);
	DLLPushFront(dll_src, data1);
	
	DLLSpliceBefore(DLLBegin(dll_dest), DLLBegin(dll_src), DLLNext(DLLBegin(dll_src)));
	
	for(i = DLLBegin(dll_dest); i != DLLEnd(dll_dest); i = DLLNext(i))
	{
		puts((char *)DLLGetData(i));
	}
	
	for(i = DLLBegin(dll_dest); i != DLLEnd(dll_dest); i = DLLNext(i))
	{
		puts((char *)DLLGetData(i));
	}

	for(i = DLLPrev(DLLEnd(dll_dest)); i != DLLBegin(dll_dest); i = DLLPrev(i))
	{
		puts((char *)DLLGetData(i));
	}
	
	DLLDestroy(dll_dest);
	DLLDestroy(dll_src);
	return ret;
}

int main()
{
	RUN_TEST(FlowEmptyDLL);
	RUN_TEST(FlowPushFrontDestroy);
	RUN_TEST(FlowForEach);
	RUN_TEST(TestSpliceBefore);
	
	return 0;
}
