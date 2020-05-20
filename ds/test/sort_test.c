/************************
Sorting algorithms iterative implementation
*************************/
#include <stdlib.h> /* rand */
#include <stdio.h> /* printf */
#include <string.h> /* memcpy */
#include <time.h> /* clock */
#include <errno.h> /* perror */

#include "../include/sort.h" /* BubbleSort */

#define ARR_SIZE (5000)

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \

/* Returns non_zero if member_is_before should come before member_in_place; 
otherwise, returns zero */
/*typedef int (*cmp_f)(const void *memb_in_place, const void *memb_is_before);*/

/*typedef size_t (*key_to_num)(const void *data, const void *args); */

enum status {SUCCESS, FAIL};

static int IntCompare(const void *n, const void *m)
{
	return( *(int *)n - *(int *)m );
}

static int TestCompSorts()
{
	int *arr_rand = NULL;
/*	int arr_rand[] = {15, -78, 16, 1, 4};*/
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
	MergeSort(arr, ARR_SIZE);
	after = clock();
	printf("Merge Sort runtime %ld clock ticks, %ld milisec\n", (after - before), 1000 * (after - before)/CLOCKS_PER_SEC);
	for(i = 1; ARR_SIZE > i; ++i)
	{
		if(0 > IntCompare((arr+i), (arr + i - 1)))
		{
			ret = FAIL;
			printf("Merge Sort: arr[%lu] = %d  smaller than arr[%lu]=%d ##FAIL##\n", i, arr[i], i-1, arr[i - 1]);
			break;
		}
	}

	memcpy(arr, arr_rand, ARR_SIZE * sizeof(int));
	before = clock();
	SelectionSort(arr, ARR_SIZE, sizeof(arr[0]), IntCompare);
	after = clock();
	printf("Selection Sort runtime %ld clock ticks, %ld milisec\n", (after - before), 1000 * (after - before)/CLOCKS_PER_SEC);
	for(i = 0; ARR_SIZE  > i; ++i)
	for(i = 1; ARR_SIZE > i; ++i)
	{
		if(0 > IntCompare((arr+i), (arr + i - 1)))
		{
			ret = FAIL;
			printf("Selection Sort: arr[%lu] = %d  smaller than arr[%lu]=%d ##FAIL##\n", i, arr[i], i-1, arr[i - 1]);
			break;
		}
	}

	memcpy(arr, arr_rand, ARR_SIZE * sizeof(int));
	before = clock();
	InsertionSort(arr, ARR_SIZE, sizeof(arr[0]), IntCompare);
	after = clock();
	printf("Insertion Sort runtime %ld clock ticks, %ld milisec\n", (after - before), 1000 * (after - before)/CLOCKS_PER_SEC);

	for(i = 1; ARR_SIZE > i; ++i)
	{
		if(0 > IntCompare((arr+i), (arr + i - 1)))
		{
			ret = FAIL;
			printf("Insertion Sort: arr[%lu] = %d  smaller than arr[%lu]=%d ##FAIL##\n", i, arr[i], i-1, arr[i - 1]);
			break;
		}
	}
	
	memcpy(arr, arr_rand, ARR_SIZE * sizeof(int));
	before = clock();
	qsort(arr, ARR_SIZE, sizeof(arr[0]), IntCompare);
	after = clock();
	printf("Quick Sort runtime %ld clock ticks, %ld milisec\n", (after - before), 1000 * (after - before)/CLOCKS_PER_SEC);
	for(i = 1; ARR_SIZE > i; ++i)
	{
		if(0 > IntCompare((arr+i), (arr + i - 1)))
		{
			ret = FAIL;
			printf("Quick Sort: arr[%lu] = %d  smaller than arr[%lu]=%d ##FAIL##\n", i, arr[i], i-1, arr[i - 1]);
			break;
		}
	}

	free(arr);
	free(arr_rand);

	return ret;
}

static size_t KTN(const void *data, const void *args)
{
	(void)args;
	
	return( (size_t)((*(int *)data) - *(int *)args) );
}

static int GetMin(int *arr, size_t n_memb)
{
	size_t i = 0;
	int min = arr[0];
	for(i = 1; i < n_memb; ++i)
	{
		min = (min < arr[i]) ? min : arr[i];
	}
	
	return min;
}

static int GetMax(int *arr, size_t n_memb)
{
	size_t i = 0;
	int max = arr[0];
	
	for(i = 1; i < n_memb; ++i)
	{
		max = (max > arr[i]) ? max : arr[i];
	}
	
	return max;
}

static int TestCountSort()
{
	int ret = SUCCESS;
	int *arr = NULL;
	int min = 0;
	int max = 0;
	int range = 0;
	size_t i = 0;
	clock_t before = 0;
	clock_t after = 0;
	
	
	arr = malloc(ARR_SIZE * sizeof(int));
	if(NULL == arr)
	{
		perror("alloc fail");
		
		return FAIL;
	}
	
	for(i = 0; ARR_SIZE > i; ++i)
	{
		arr[i] = rand() % 100000000;
	}
	
	min = GetMin(arr, ARR_SIZE);
	printf("min=%d\n", min);
	max = GetMax(arr, ARR_SIZE);
	printf("max=%d\n", max);
	range = max - min;
	printf("range=%d\n", range);
	
	before = clock();
	CountingSort(arr, ARR_SIZE, sizeof(int), KTN, &min, range);
	after = clock();
	printf("Count Sort runtime %ld clock ticks, %ld milisec\n", (after - before), 1000 * (after - before)/CLOCKS_PER_SEC);
	
	for(i = 1; ARR_SIZE > i; ++i)
	{
		if(0 > IntCompare((arr+i), (arr + i - 1)))
		{
			ret = FAIL;
			printf("Count Sort: arr[%lu] = %d  smaller than arr[%lu]=%d ##FAIL##\n", i, arr[i], i-1, arr[i - 1]);
			break;
		}
	}
	if(arr[0] != min)
	{
		ret = FAIL;
		printf("arr[0]=%d min=%d ##FAIL##\n", arr[0], min);
	}
	if(arr[ARR_SIZE - 1] != max)
	{
		ret = FAIL;
		printf("arr[ARR_SIZE - 1]=%d max=%d ##FAIL##\n", arr[ARR_SIZE - 1], max);
	}
	free(arr);
	
	return ret;
}

int main()
{
	RUN_TEST(TestCompSorts);
	RUN_TEST(TestCountSort);
	
	return 0;
}

/*TODO second variant of Swap. If used, must modify so that malloc is relegated 
to the calling function.*/
/*static int Swap(void *data1, void *data2, size_t memb_size)*/
/*{*/
/*	void *holder = NULL;*/
/*	*/
/*	assert(NULL != data1);*/
/*	assert(NULL != data2);*/
/*	assert(0 < memb_size);*/
/*	*/
/*	holder = malloc(memb_size);*/
/*	if(NULL == holder)*/
/*	{*/
/*		return(FAIL);*/
/*	}*/
/*	*/
/*	memcpy(holder, data1, memb_size);*/
/*	memcpy(data1, data2, memb_size);*/
/*	memcpy(data2, holder, memb_size);*/
/*	*/
/*	free(holder);*/
/*	holder = NULL;*/
/*	*/
/*	return(SUCCESS);*/
/*}*/

