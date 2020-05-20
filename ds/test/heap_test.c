#include <stdio.h> /* printf */
#include <stdlib.h> /* rand */
#include <assert.h> /* assert */

#include "heap.h"

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \

enum status {OK = 0, FAIL};


static int IsBefore(const void *data1, const void *data2, const void *garbage)
{
	(void)garbage;
	
	return 0 > *(int *)data1 - *(int *)data2;
}

static int IsSame(const void *data1, const void *data2, const void *garbage)
{
	(void)garbage;
	
	return *(int *)data1 == *(int *)data2;
}

static int HeapSort(int *arr, size_t len)
{
	int *res = NULL;
	heap_t *heap = NULL;
	size_t i = 0;
	res = (int *)malloc(len * sizeof(*res));
	if (!res)
	{
		return FAIL;
	}
	
	heap = HeapCreate(&IsBefore);
	if (!res)
	{
		free(res);
		
		return FAIL;
	}
	
	for (i = 0; i < len; ++i)
	{
		HeapPush(heap, arr + i);
	}
	assert(i == len);
	
	for (i = 0; i < len; ++i)
	{
		assert(!HeapIsEmpty(heap));
		res[i] = *(int *)HeapPeek(heap);
		HeapPop(heap);
	}
	
	for (i = 0; i < len; ++i)
	{
		arr[i] = res[i];
	}
	
	free(res);
	HeapDestroy(heap);
	
	return OK;	
}

#define N_MEMB_ARR (5)
const int arr[] = {5, 8, 10, 100, 200};
static int TestBasic()
{
	heap_t *heap = NULL;
	int ret = OK;
	size_t i = 0; 
	
	heap = HeapCreate(&IsBefore);
	if (!heap)
	{
		printf ("malloc %d ##FAIL##\n", __LINE__);
		return FAIL;
	}
	
	if (0 != HeapSize(heap))
	{
		printf ("%d ##FAIL##\n", __LINE__);
		return FAIL;
	}
	
	if (!HeapIsEmpty(heap))
	{
		ret = FAIL;
		printf ("%d ##FAIL##\n", __LINE__);
	}
	
	puts("push");
	for (i = 0; N_MEMB_ARR > i; ++i)
	{
		HeapPush(heap, (int *)arr + i);
		printf("%d\n", *(int *)HeapPeek(heap));
	}
	
	puts("pop");
	while (!HeapIsEmpty(heap))
	{
		printf("%d\n", *(int *)HeapPeek(heap));
		HeapPop(heap);
	}
	HeapDestroy(heap);
	
	return ret;
}
#undef N_MEMB_ARR


#define N_MEMB_ARR (100)
static int TestHeapSort()
{
	int ret = OK;
	int arr[N_MEMB_ARR] = {0};
	size_t i = 0;
	
	for (i = 0; N_MEMB_ARR > i; ++i)
	{
		arr[i] = rand() % 1000 - 500;
	}
	
	ret = HeapSort(arr, N_MEMB_ARR);
	if (OK != ret)
	{
		return ret;
	}
	
	for (i = 0; N_MEMB_ARR > i; ++i)
	{
		printf("%d\n", arr[i]);
	}
	
	for (i = 1; N_MEMB_ARR > i; ++i)
	{
		if (arr[i - 1] < arr[i])
		{
			ret = FAIL;
			printf ("%d ##FAIL##\n", __LINE__);
			break ;
		}
	}
	
	return ret;
}
#undef N_MEMB_ARR

#define N_MEMB_ARR (5)
/*const int arr[] = {5, 8, 10, 100, 200};*/
static int TestRemoveTop()
{
	heap_t *heap = NULL;
	int ret = OK;
	size_t i = 0;
	
	heap = HeapCreate(&IsBefore);
	if (!heap)
	{
		printf ("malloc %d ##FAIL##\n", __LINE__);
		return FAIL;
	}
	
	puts("push");
	for (i = 0; N_MEMB_ARR - 4 > i; ++i)
	{
		HeapPush(heap, (int *)arr + i);
		printf("%d\n", *(int *)HeapPeek(heap));
	}
	
	HeapRemove(heap, &IsSame, arr);
	
	HeapDestroy(heap);
}

static int TestRemoveLast()
{

}

static int TestRemoveNonexistent()
{

}
#undef N_MEMB_ARR
int main()
{
	RUN_TEST(TestBasic);
	RUN_TEST(TestHeapSort);
	RUN_TEST(TestRemoveTop);
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
