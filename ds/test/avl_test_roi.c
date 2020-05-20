/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 09/07/19                                *
*   Description: AVL Tests                        *
*                                                 *
*                                                 *
**************************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <time.h>   /* clock */

#include "tests.h" /* test macros */
#include "avl.h"   /* avl header file */

size_t g_total_tests = 0;
size_t g_total_failed = 0;
size_t g_total_success = 0;

int IntCompare(const void *data1, const void *data2, const void *params);
int PrintAndSumNodes(void *data, const void *args);
void PrintArr(int *arr, size_t size);
void FillArr(int *arr, size_t size);
int CheckDuplicates(int *arr, size_t size);
int HasNum(int *arr, size_t size, int num);
int ArrFind(int *arr, size_t size, int num);

int Test_CreateDestroy(void);
int Test_Insert(void);
int Test_Remove(void);
int Test_IsEmpty(void);
int Test_Size(void);
int Test_Height(void);
int Test_ForEach(void);
int Test_Find(void);
int Test_StressTest(void);

int main() 
{
	puts("\x1B[36m_____________Test Results:_____________\033[0m");
	RUN_TEST(Test_CreateDestroy);
	RUN_TEST(Test_Insert);
	RUN_TEST(Test_Remove);
	RUN_TEST(Test_IsEmpty);
	RUN_TEST(Test_Size);
	RUN_TEST(Test_Height);
	RUN_TEST(Test_ForEach);
	RUN_TEST(Test_Find);
	RUN_TEST(Test_StressTest);

	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);
	

	return 0;
}

int Test_CreateDestroy(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *avl = NULL;

	puts("\x1B[33m[Test_CreateDestroy]\033[0m");

	avl = AVLCreate(IntCompare, NULL);

	/* test1 */
	res = NULL != avl;
	TEST_EQUAL(res, 1);

	AVLDestroy(avl);

	return result;
}

int Test_Insert(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *avl = NULL;
	int data[10] = {20, 30, 40, 10, 5, 15, 17, 16, 18, 19};

	puts("\x1B[33m[Test_Insert]\033[0m");

	avl = AVLCreate(IntCompare, NULL);

	/* test1 */
	res = NULL != avl;
	TEST_EQUAL(res, 1);
	
	/* test2 */
	res = AVLInsert(avl, (void *)&data[0]);
	TEST_EQUAL(res, 0);

	/* test3 */
	res = AVLInsert(avl, (void *)&data[1]);
	TEST_EQUAL(res, 0);

	/* test4 */
	res = AVLInsert(avl, (void *)&data[2]);
	TEST_EQUAL(res, 0);

	AVLInsert(avl, (void *)&data[3]);
	AVLInsert(avl, (void *)&data[4]);
	AVLInsert(avl, (void *)&data[5]);
	AVLInsert(avl, (void *)&data[6]);
	AVLInsert(avl, (void *)&data[7]);
	AVLInsert(avl, (void *)&data[8]);
	AVLInsert(avl, (void *)&data[9]);

	AVLDestroy(avl);

	return result;
}

int Test_Remove(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *avl = NULL;
	int data[10] = {20, 30, 40, 10, 5, 15, 17, 16, 18, 19};
	int key = 0;
	int *found = NULL;

	puts("\x1B[33m[Test_Remove]\033[0m");

	avl = AVLCreate(IntCompare, NULL);
	
	AVLInsert(avl, (void *)&data[0]);
	AVLInsert(avl, (void *)&data[1]);
	AVLInsert(avl, (void *)&data[2]);
	AVLInsert(avl, (void *)&data[3]);
	AVLInsert(avl, (void *)&data[3]); /* duplicate */
	AVLInsert(avl, (void *)&data[4]);
	AVLInsert(avl, (void *)&data[5]);
	AVLInsert(avl, (void *)&data[6]);
	AVLInsert(avl, (void *)&data[7]);
	AVLInsert(avl, (void *)&data[8]);
	AVLInsert(avl, (void *)&data[9]);
	
	/* test1 */
	key = 40;
	AVLRemove(avl, (void *)&key);
	found = AVLFind(avl, (void *)&key);
	res = NULL == found;
	TEST_EQUAL(res, 1);
	
	/* test2 */
	key = 17;
	AVLRemove(avl, (void *)&key);
	found = AVLFind(avl, (void *)&key);
	res = NULL == found;
	TEST_EQUAL(res, 1);
	
	/* test2 */
	key = 20;
	AVLRemove(avl, (void *)&key);
	found = AVLFind(avl, (void *)&key);
	res = NULL == found;
	TEST_EQUAL(res, 1);

	AVLDestroy(avl);

	return result;
}

int Test_IsEmpty(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *avl = NULL;
	int data[10] = {20, 30, 40, 10, 5, 15, 17, 16, 18, 19};
	int key = 20;

	puts("\x1B[33m[Test_IsEmpty]\033[0m");

	avl = AVLCreate(IntCompare, NULL);
	
	/* test1 */
	res = AVLIsEmpty(avl);
	TEST_EQUAL(res, 1);
	
	AVLInsert(avl, (void *)&data[0]);
	
	/* test2 */
	res = AVLIsEmpty(avl);
	TEST_EQUAL(res, 0);
	
	AVLRemove(avl, (void *)&key);

	puts("ready");
	/* test3 */
	res = AVLIsEmpty(avl);
	TEST_EQUAL(res, 1);

	AVLDestroy(avl);

	return result;
}

int Test_Size(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *avl = NULL;
				/*  0   1   2   3   4  5   6   7   8   9*/
	int data[10] = {20, 30, 40, 10, 5, 15, 17, 16, 18, 19};
	int key = 40;

	puts("\x1B[33m[Test_Size]\033[0m");

	avl = AVLCreate(IntCompare, NULL);

	/* Test1 */
	res = (int)AVLGetSize(avl);
	TEST_EQUAL(res, 0);
	
	AVLInsert(avl, (void *)&data[0]);
	AVLInsert(avl, (void *)&data[1]);
	AVLInsert(avl, (void *)&data[2]);
	AVLInsert(avl, (void *)&data[3]);
	AVLInsert(avl, (void *)&data[3]); /* duplicate */
	AVLInsert(avl, (void *)&data[4]);
	AVLInsert(avl, (void *)&data[5]);
	AVLInsert(avl, (void *)&data[6]);
	AVLInsert(avl, (void *)&data[7]);
	AVLInsert(avl, (void *)&data[8]);
	AVLInsert(avl, (void *)&data[9]);
	
	/* Test2 */
	res = (int)AVLGetSize(avl);
	TEST_EQUAL(res, 10);
	
	AVLRemove(avl, (void *)&key);
	
	/* Test3 */
	res = (int)AVLGetSize(avl);
	TEST_EQUAL(res, 9);
	
	key = 17;
	
	AVLRemove(avl, (void *)&key);
	
	/* Test4 */
	res = (int)AVLGetSize(avl);
	TEST_EQUAL(res, 8);
	
	key = 20;
	
	AVLRemove(avl, (void *)&key);
	
	/* Test5 */
	res = (int)AVLGetSize(avl);
	TEST_EQUAL(res, 7);

	AVLDestroy(avl);

	return result;
}

int Test_Height(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *avl = NULL;
	int data[10] = {20, 30, 40, 10, 5, 15, 17, 16, 18, 19};
	int key = 40;

	puts("\x1B[33m[Test_Height]\033[0m");

	avl = AVLCreate(IntCompare, NULL);
	
	/* Test1 */
	res = (int)AVLGetHeight(avl);
	TEST_EQUAL(res, -1);
	
	AVLInsert(avl, (void *)&data[0]);
	AVLInsert(avl, (void *)&data[1]);
	AVLInsert(avl, (void *)&data[2]);
	AVLInsert(avl, (void *)&data[3]);
	AVLInsert(avl, (void *)&data[3]); /* duplicate */
	AVLInsert(avl, (void *)&data[4]);
	AVLInsert(avl, (void *)&data[5]);
	AVLInsert(avl, (void *)&data[6]);
	AVLInsert(avl, (void *)&data[7]);
	AVLInsert(avl, (void *)&data[8]);
	AVLInsert(avl, (void *)&data[9]);
	
	/* Test2 */
	res = (int)AVLGetHeight(avl);
	TEST_EQUAL(res, 3);
	
	AVLRemove(avl, (void *)&key);
	
	/* Test3 */
	res = (int)AVLGetHeight(avl);
	TEST_EQUAL(res, 3);
	
	key = 17;
	
	AVLRemove(avl, (void *)&key);
	
	/* Test4 */
	res = (int)AVLGetHeight(avl);
	TEST_EQUAL(res, 3);
	
	key = 20;
	
	AVLRemove(avl, (void *)&key);
	
	/* Test5 */
	res = (int)AVLGetHeight(avl);
	TEST_EQUAL(res, 2);
	
	key = 18;
	
	AVLRemove(avl, (void *)&key);
	
	/* Test6 */
	res = (int)AVLGetHeight(avl);
	TEST_EQUAL(res, 2);
	
	key = 19;
	
	AVLRemove(avl, (void *)&key);
	
	/* Test7 */
	res = (int)AVLGetHeight(avl);
	TEST_EQUAL(res, 2);

	AVLDestroy(avl);

	return result;
}

int Test_ForEach(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *avl = NULL;
	int data[10] = {20, 30, 40, 10, 5, 15, 17, 16, 18, 19};
	int act_res = 0;
	long args = 30;

	puts("\x1B[33m[Test_ForEach]\033[0m");

	avl = AVLCreate(IntCompare, NULL);
	
	AVLInsert(avl, (void *)&data[0]);
	AVLInsert(avl, (void *)&data[1]);
	AVLInsert(avl, (void *)&data[2]);
	AVLInsert(avl, (void *)&data[3]);
	AVLInsert(avl, (void *)&data[3]); /* duplicate */
	AVLInsert(avl, (void *)&data[4]);
	AVLInsert(avl, (void *)&data[5]);
	AVLInsert(avl, (void *)&data[6]);
	AVLInsert(avl, (void *)&data[7]);
	AVLInsert(avl, (void *)&data[8]);
	AVLInsert(avl, (void *)&data[9]);
	
	act_res = AVLForEach(avl, PrintAndSumNodes, &args);
	
	/* test1 */
	res = act_res;
	TEST_EQUAL(res, -1);
	
	/* test2 */
	res = (int)args;
	TEST_EQUAL(res, -16);
	
	args = 1000;
	
	act_res = AVLForEach(avl, PrintAndSumNodes, &args);
	
	/* test3 */
	res = act_res;
	TEST_EQUAL(res, 0);
	
	/* test4 */
	res = (int)args;
	TEST_EQUAL(res, 810);

	AVLDestroy(avl);

	return result;
}

int Test_Find(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *avl = NULL;
	int data[10] = {20, 30, 40, 10, 5, 15, 17, 16, 18, 19};
	int act_res = 0;
	int key = 0;
	int *found = NULL;

	puts("\x1B[33m[Test_Find]\033[0m");

	avl = AVLCreate(IntCompare, NULL);
	
	AVLInsert(avl, (void *)&data[0]);
	AVLInsert(avl, (void *)&data[1]);
	AVLInsert(avl, (void *)&data[2]);
	AVLInsert(avl, (void *)&data[3]);
	AVLInsert(avl, (void *)&data[3]); /* duplicate */
	AVLInsert(avl, (void *)&data[4]);
	AVLInsert(avl, (void *)&data[5]);
	AVLInsert(avl, (void *)&data[6]);
	AVLInsert(avl, (void *)&data[7]);
	AVLInsert(avl, (void *)&data[8]);
	AVLInsert(avl, (void *)&data[9]);

	/* test1 */	
	key = 20;
	found = AVLFind(avl, (void *)&key);
	res = *found;
	TEST_EQUAL(res, 20);
	
	/* test2 */	
	key = 19;
	found = AVLFind(avl, (void *)&key);
	res = *found;
	TEST_EQUAL(res, 19);
	
	/* test3 */	
	key = 13;
	found = AVLFind(avl, (void *)&key);
	res = NULL == found;
	TEST_EQUAL(res, 1);


	AVLDestroy(avl);

	return result;
}

int Test_StressTest(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	avl_t *avl = NULL;
	int *arr = NULL;
	size_t arr_size = 50000;
	int key = 0;
	size_t i = 0, n = 1000;
	clock_t start = 0, end = 0;
	double tree_avg = 0, arr_avg = 0;
	double secs = 0.0;

	puts("\x1B[33m[Test_StressTest]\033[0m");

	avl = AVLCreate(IntCompare, NULL);
	
	arr = (int *)malloc(sizeof(int) * arr_size);
	if(NULL == arr)
	{
		perror("malloc error");
		return 0;
	}
	
	start = clock();
	
	FillArr(arr, arr_size);
	
	end = clock();
	secs = (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("\tFilled unique array! Took: %0.4f secs. Inserting to tree...\n",
		secs);
	
	/* test1 */
	res = CheckDuplicates(arr, arr_size);
	TEST_EQUAL(res, 0);
	
	start = clock();

	for(; i < arr_size; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	
	end = clock();
	secs = (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("\tFilled tree! took: %0.4f secs. Checking tree size...\n", secs);
	
	/* test2 */
	start = clock();
	res = (int)AVLGetSize(avl);
	end = clock();
	secs = (double)(end - start) / CLOCKS_PER_SEC;
	TEST_EQUAL(res, ((int)(arr_size)));
	printf("\ttook: %0.4f secs. Checking tree height...\n", secs);
	
	/* test3 */
	start = clock();
	res = (int)AVLGetHeight(avl);
	end = clock();
	secs = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\tChecking if the height of the tree is approximately log(%lu):\n", arr_size);
	printf("\tHeight: %d\n", res);
	res = (res < 20 && res > 14); /* height should be in the range of log2(50000) */
	TEST_EQUAL(res, 1);
	printf("\ttook: %0.4f secs. Comparing tree vs. array performance...\n", secs);

	
	for(i = 0; i < n; ++i)
	{
		key = arr[rand() % arr_size];
	
		start = clock();
		ArrFind(arr, arr_size, key);
		end = clock();
		secs = (double)(end - start) / CLOCKS_PER_SEC;
		arr_avg += secs;
	
		start = clock();
		key = *(int *)AVLFind(avl, &key);
		end = clock();
		secs = (double)(end - start) / CLOCKS_PER_SEC;
		tree_avg += secs;
	}
	
	printf("\tarray took an average of: %f secs to find %lu random elements\n",
			 (arr_avg / n), n);
	printf("\ttree took an average of: %f secs to find %lu random elements\n",
			 (tree_avg / n), n);

	printf("\n\tTest Conclusions: Trees are good...\n\n");

	free(arr);
	AVLDestroy(avl);

	return result;
}

int IntCompare(const void *data1, const void *data2, const void *params)
{
	(void)params;
			
	return *(int *)data1 - *(int *)data2;
}

int PrintAndSumNodes(void *data, const void *args)
{
	printf("test: %d\n", *(int *)data);
	
	*(long *)args -= (long)*(int *)data;
	
	if(*(long *)args < 0)
	{
		return -1;
	}
	
	return 0;
}

void PrintArr(int *arr, size_t size)
{
	size_t i = 0;
	
	printf("[");
	
	for(; i < size - 1; ++i)
	{
		printf("%d, ", arr[i]);
	}
	
	printf("%d]\n", arr[i]);
}

void FillArr(int *arr, size_t size)
{
	size_t i = 0;
	int new_rand = 0;
	
	for(; i < size; ++i)
	{
		do
		{
			new_rand = rand();
		} while(HasNum(arr, size, new_rand));
		
		arr[i] = new_rand;
	}
}

int CheckDuplicates(int *arr, size_t size)
{
	size_t i = 0, j = 0;

	for(; i < size; ++i)
	{
		for(; j < size; ++j)
		{
			if(i != j && arr[i] == arr[j])
			{
				return 1;
			}
		}
	}

	return 0;
}

int HasNum(int *arr, size_t size, int num)
{
	size_t i = 0;
	
	for(; i < size; ++i)
	{
		if(num == arr[i])
		{
			return 1;
		}
	}
	
	return 0;
}

int ArrFind(int *arr, size_t size, int num)
{
	size_t i = 0;
	
	for(; i < size; ++i)
	{
		if(num == arr[i])
		{
			return arr[i];
		}
	}
	
	return -1;
}
