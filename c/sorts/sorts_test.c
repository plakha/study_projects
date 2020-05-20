/******************************
15/7/2019
Recursive int Mergesort
*******************************/

#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */
#include <string.h> /* memcpy */
#include <time.h> /* clock */
#include <limits.h> 

#include "sorts.h" /* dir ASC, DSC */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \

enum status 
{
	SUCCESS = 0,
	FAIL
};

enum {FALSE = 0, TRUE};

static int IntCompare(const void *n, const void *m)
{
	return( *(int *)n - *(int *)m );
}


static int TestMergeSort()
{
	int arr[] = {5, 3, 89, 6, 8, 9};
	int i = 0;
	
	MergeSort(arr, 6);
	for(i = 0; 6 > i; ++i)
	{
		printf("%d, ", arr[i]);
	}
	
	return 0;
}

static int TestHeapSort()
{
	int arr[] = {50, 20, 80, 30};
	int i = 0;
	
	HeapSort(arr, 4, ASC);
	for(i = 0; 4 > i; ++i)
	{
		printf("%d, ", arr[i]);
	}
	
	return 0;
}


static int TestQuickSort()
{
	int arr[] = {5, 3, 89, 6, 8, 9};
	int i = 0;
	
	QuickSort(arr, 6, ASC);
	for(i = 0; 6 > i; ++i)
	{
		printf("%d, ", arr[i]);
	}
	
	return 0;
}

#define ARR_SIZE (100000)
static int TestCompSorts()
{
	int *arr_rand = NULL;
	int *arr = NULL;
	size_t i = 0;
	clock_t before = 0;
	clock_t after = 0;
	int ret = SUCCESS;

	arr_rand = (int *)malloc(ARR_SIZE * sizeof(int));
	if(NULL == arr_rand)
	{
		perror("alloc fail");
		
		return FAIL;
	}
	arr = (int *)malloc(ARR_SIZE * sizeof(int));
	if(NULL == arr)
	{
		free(arr_rand);
		perror("alloc fail");
		
		return FAIL;
	}
	
	for(i = 0; ARR_SIZE > i; ++i)
	{
		arr_rand[i] = rand() % 100000000;
	}
	
	memcpy(arr, arr_rand, ARR_SIZE * sizeof(int));
	before = clock();
	qsort(arr, ARR_SIZE, sizeof(arr[0]), IntCompare);
	after = clock();
	printf("Libc QSort runtime %ld clock ticks, %ld milisec\n", (after - before), 1000 * (after - before)/CLOCKS_PER_SEC);
	for(i = 1; ARR_SIZE > i; ++i)
	{
		if(0 > IntCompare((arr+i), (arr + i - 1)))
		{
			ret = FAIL;
			printf("Lib Quick Sort: arr[%lu] = %d  smaller than arr[%lu]=%d ##FAIL##\n", i, arr[i], i-1, arr[i - 1]);
			break;
		}
	}

	memcpy(arr, arr_rand, ARR_SIZE * sizeof(int));
	before = clock();
	QuickSort(arr, ARR_SIZE, ASC);
	after = clock();
	printf("Custom QuickSort runtime %ld clock ticks, %ld milisec\n", (after - before), 1000 * (after - before)/CLOCKS_PER_SEC);
	for(i = 1; ARR_SIZE > i; ++i)
	{
		if(0 > IntCompare((arr+i), (arr + i - 1)))
		{
			ret = FAIL;
			printf(" Custom QuickSort: arr[%lu] = %d  smaller than arr[%lu]=%d ##FAIL##\n", i, arr[i], i-1, arr[i - 1]);
			break;
		}
	}

	memcpy(arr, arr_rand, ARR_SIZE * sizeof(int));
	before = clock();
	HeapSort(arr, ARR_SIZE, ASC);
	after = clock();
	printf(" HeapSort runtime %ld clock ticks, %ld milisec\n", (after - before), 1000 * (after - before)/CLOCKS_PER_SEC);
	for(i = 1; ARR_SIZE > i; ++i)
	{
		if(0 > IntCompare((arr+i), (arr + i - 1)))
		{
			ret = FAIL;
			printf("  HeapSort: arr[%lu] = %d  smaller than arr[%lu]=%d ##FAIL##\n", i, arr[i], i-1, arr[i - 1]);
			break;
		}
	}

	memcpy(arr, arr_rand, ARR_SIZE * sizeof(int));
	before = clock();
	MergeSort(arr, ARR_SIZE);
	after = clock();
	printf("MergeSort runtime %ld clock ticks, %ld milisec\n", (after - before), 1000 * (after - before)/CLOCKS_PER_SEC);
	for(i = 1; ARR_SIZE > i; ++i)
	{
		if(0 > IntCompare((arr+i), (arr + i - 1)))
		{
			ret = FAIL;
			printf("MergeSort: arr[%lu] = %d  smaller than arr[%lu]=%d ##FAIL##\n", i, arr[i], i-1, arr[i - 1]);
			break;
		}
	}


	free(arr);
	free(arr_rand);

	return ret;
}
#undef ARR_SIZE

#define ARR_SIZE (7)
#define N_KEYS (5)
    const int g_arr[] = {-5, 0, 1, 5, 10, 15, 1000};
int TestJumpSearch()
{
	size_t n_membs = ARR_SIZE; /* sizeof(arr) / sizeof(int);*/
	size_t found_index = -1;
	const int key[] = {1000, 0, -5, -6, 5};
	int ret_status = SUCCESS;
	int is_found = FALSE;
	size_t i = 0lu;

	for (; N_KEYS > i; ++i)
	{
		is_found = JumpSearch(g_arr, key[i], n_membs, &found_index);
		if (is_found)
		{
			if (g_arr[found_index] != key[i])
			{
				ret_status = FAIL;
				printf ("Looked for %d, said found, found index %lu, found %d\
						##FAIL\n", key[i], found_index, g_arr[found_index]);
			}
		}
		else 
		{

		}
	}
	ret_status = !is_found;

	return ret_status;
}

int TestBinarySearch()
{
	const int arr[] = {-5, 0, 1, 5, 10, 15, 1000};
	size_t n_membs = sizeof(arr) / sizeof(int);
	size_t found_index = -1;
	const int key[] = {1000, 0, -5, -6, 5};
	int ret_status = SUCCESS;
	int is_found = FALSE;
	size_t i = 0lu;

	for (; N_KEYS > i; ++i)
	{
		is_found = BinarySearch(arr, key[i], n_membs, &found_index);
		if (is_found)
		{
			if (arr[found_index] != key[i])
			{
				ret_status = FAIL;
				printf ("Looked for %d, said found, found index %lu, found %d\
						##FAIL\n", key[i], found_index, arr[found_index]);
			}
		}
		else 
		{

		}
	}
	ret_status = !is_found;

	return ret_status;
}

#undef N_KEYS

int main()
{
	RUN_TEST(TestMergeSort);
	RUN_TEST(TestHeapSort);
	RUN_TEST(TestQuickSort);
	RUN_TEST(TestCompSorts);
	RUN_TEST(TestBinarySearch);
	RUN_TEST(TestJumpSearch);

	return 0;
}









































