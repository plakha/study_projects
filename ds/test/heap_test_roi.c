/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 17/07/19                                *
*   Description: Heap DS tests                    *
*                                                 *
**************************************************/
#include <stdio.h>  /* printf */

#include "tests.h" /* test macros */
#include "heap.h"  /* heap header file */

size_t g_total_tests = 0;
size_t g_total_failed = 0;
size_t g_total_success = 0;

int IsData1IsBeforeData2(const void *data1, const void *data2, const void *args);
int ShouldRemove(const void *data, const void *key, const void *args);
int IsOrdered(int *arr, size_t size);
void PrintArray(int *arr, size_t size);

int Test_CreateDestroy(void);
int Test_Size(void);
int Test_IsEmpty(void);
int Test_PushPeek(void);
int Test_PushPop(void);
int Test_Remove(void);
int Test_HeapSort(void);

int main() 
{
	puts("\x1B[36m_____________Test Results:_____________\033[0m");
	RUN_TEST(Test_CreateDestroy);
	RUN_TEST(Test_Size);
	RUN_TEST(Test_IsEmpty);
	RUN_TEST(Test_PushPeek);
	RUN_TEST(Test_PushPop);
	RUN_TEST(Test_Remove);
	RUN_TEST(Test_HeapSort);

	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);

	return 0;
}

int Test_CreateDestroy(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	heap_t *heap = NULL;

	puts("\x1B[33m[Test_CreateDestroy]\033[0m");

	heap = HeapCreate(IsData1IsBeforeData2);

	/* test1 */
	res = heap != NULL;
	TEST_EQUAL(res, 1);

	return result;
}

int Test_Size(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	heap_t *heap = NULL;
	int arr[] = {123, 332, 421, 1203, 129310, 1222};

	puts("\x1B[33m[Test_Size]\033[0m");

	heap = HeapCreate(IsData1IsBeforeData2);

	/* test1 */
	res = (int)HeapSize(heap);
	TEST_EQUAL(res, 0);

	/* test2 */
	HeapPush(heap, &arr[0]);
	res = (int)HeapSize(heap);
	TEST_EQUAL(res, 1);

	return result;
}

int Test_IsEmpty(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	heap_t *heap = NULL;
	int arr[] = {123, 332, 421, 1203, 129310, 1222};

	puts("\x1B[33m[Test_IsEmpty]\033[0m");

	heap = HeapCreate(IsData1IsBeforeData2);

	/* test1 */
	res = HeapIsEmpty(heap);
	TEST_EQUAL(res, 1);

	/* test2 */
	HeapPush(heap, &arr[0]);
	res = HeapIsEmpty(heap);
	TEST_EQUAL(res, 0);

	return result;
}

int Test_PushPeek(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	heap_t *heap = NULL;
	int arr[] = {123, 332, 421, 1203, 129310, 1222};

	puts("\x1B[33m[Test_PushPeek]\033[0m");

	heap = HeapCreate(IsData1IsBeforeData2);

	/* test1 */
	res = HeapPush(heap, &arr[0]);
	TEST_EQUAL(res, 0);

	/* test2 */
	res = *(int *)HeapPeek(heap);
	TEST_EQUAL(res, 123);
	
	return result;
}

int Test_PushPop(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	heap_t *heap = NULL;
	int arr[] = {123, 332, 421, 1203, 129310, 1222};

	puts("\x1B[33m[Test_PushPop]\033[0m");

	heap = HeapCreate(IsData1IsBeforeData2);

	/* test1 */
	res = HeapPush(heap, &arr[0]);
	TEST_EQUAL(res, 0);

	/* test2 */
	res = HeapPush(heap, &arr[1]);
	TEST_EQUAL(res, 0);

	/* test3 */
	res = HeapPush(heap, &arr[2]);
	TEST_EQUAL(res, 0);

	/* test4 */
	res = *(int *)HeapPeek(heap);
	TEST_EQUAL(res, arr[2]);

	/* test5 */
	res = (int)HeapSize(heap);
	TEST_EQUAL(res, 3);

	/* test6 */
	HeapPop(heap);
	res = *(int *)HeapPeek(heap);
	TEST_EQUAL(res, arr[1]);

	/* test7 */
	res = (int)HeapSize(heap);
	TEST_EQUAL(res, 2);

	/* test8 */
	HeapPop(heap);
	res = *(int *)HeapPeek(heap);
	TEST_EQUAL(res, arr[0]);

	/* test9 */
	res = (int)HeapSize(heap);
	TEST_EQUAL(res, 1);
	
	return result;
}

int Test_Remove(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	heap_t *heap = NULL;
	int arr[] = {123, 332, 421, 1203, 129310, 1222};
	int args = arr[0];

	puts("\x1B[33m[Test_Remove]\033[0m");

	heap = HeapCreate(IsData1IsBeforeData2);

	HeapPush(heap, &arr[0]);
	HeapPush(heap, &arr[1]);
	HeapPush(heap, &arr[2]);
	HeapPush(heap, &arr[3]);
	HeapPush(heap, &arr[4]);

	res = HeapSize(heap);
	TEST_EQUAL(res, 5);

	res = *(int *)HeapPeek(heap);
	TEST_EQUAL(res, arr[4]);

	HeapRemove(heap, ShouldRemove, &args);

	res = HeapSize(heap);
	TEST_EQUAL(res, 4);

	res = *(int *)HeapPeek(heap);
	TEST_EQUAL(res, arr[4]);

	args = arr[4];
	HeapRemove(heap, ShouldRemove, &args);

	res = HeapSize(heap);
	TEST_EQUAL(res, 3);

	res = *(int *)HeapPeek(heap);
	TEST_EQUAL(res, arr[3]);	
	
	return result;
}

int Test_HeapSort(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	heap_t *heap = NULL;
	int arr[6] = {123, -120, 421, 1203, 129310, 30};
	int sorted_arr[6];
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	size_t i = arr_size - 1;

	puts("\x1B[33m[Test_HeapSort]\033[0m");

	heap = HeapCreate(IsData1IsBeforeData2);

	HeapPush(heap, &arr[0]);
	HeapPush(heap, &arr[1]);
	HeapPush(heap, &arr[2]);
	HeapPush(heap, &arr[3]);
	HeapPush(heap, &arr[4]);
	HeapPush(heap, &arr[5]);

	res = IsOrdered(arr, arr_size);
	TEST_EQUAL(res, 0);

	res = (int)HeapSize(heap);
	TEST_EQUAL(res, 6);

	PrintArray(arr, arr_size);

	while (!HeapIsEmpty(heap))
	{
		sorted_arr[i] = *(int *)HeapPeek(heap);
		HeapPop(heap);
		res = (int)HeapSize(heap);
		TEST_EQUAL(res, ((int)i));
		--i;
	}
	
	res = IsOrdered(sorted_arr, arr_size);
	TEST_EQUAL(res, 1);

	PrintArray(sorted_arr, arr_size);
	
	return result;
}

int IsData1IsBeforeData2(const void *data1, const void *data2, const void *args)
{
	(void)args;
	return (*(int *)data1 < *(int *)data2);
}

int ShouldRemove(const void *data, const void *key, const void *args)
{
	(void)args;
	return *(int *)data == *(int *)key;
}

int IsOrdered(int *arr, size_t size)
{
	size_t i = 0;

	--size;

	for(; i < size; ++i)
	{
		if(arr[i] > arr[i + 1])
		{
			return 0;
		}
	}
	
	return 1;
}

void PrintArray(int *arr, size_t size)
{
	size_t i = 0;

	printf("[");
	for(; i < size - 1; ++i)
	{
		printf("%d, ", arr[i]);
	}

	printf("%d]\n", arr[i]);
}
