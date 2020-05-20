/*****************
Recursive implementation of balanced avl binary search tree
*****************/
#include <stdio.h> /*printf */
#include <unistd.h> /* ssize_t */
#include <stdlib.h> /* rand */
#include <assert.h> /* assert */

#include "avl.h" /* avl_t */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \

enum return_status {SUCCESS = 0, E_MALLOC, E_DEREFER, FAIL};

static int IsNumInArr(int *arr, int num, size_t len)
{
	size_t i = 0;
	
	for(i = 0; len > i; ++i)
	{
		if(num == arr[i])
		{
			return 1;
		}
	}
	
	return 0;
}
	
	

static int Compare(const void *data1, const void *data2, const void *params)
{
	(void)params;
	return *(int *)data1 - *(int *)data2;
}

static int Act(void *data, const void *args)
{
	(void)args;
	if(NULL == data)
	{
		return E_DEREFER;
	}
	++(*(int *)data);
}

static int Print(void *data, const void *args)
{
	int ret = SUCCESS;
	
	(void)args;
	assert(data);
	return 0 > printf("Data %d -->\n",*(int *)data);
}

static int PushToArr(void *data, const void *arr)
{
	int **arr1 = (int **)arr;
	
	(**arr1) = *(int *)data;
	++(*arr1);
	
	return SUCCESS;
}

static int TestEmpty()
{
	int ret = SUCCESS;
	avl_t *avl = AVLCreate(Compare, NULL);
	if(NULL == avl)
	{
		return E_MALLOC;
	}
	
	if(!AVLIsEmpty(avl))
	{	/*whitebox ing static function*/
		ret = 1;
		printf("%d", __LINE__);
	}
	if(0 != AVLGetSize(avl))
	{
		ret = 1;
		printf("%d", __LINE__);
	}
	AVLDestroy(avl);
	
	return ret;
}

#define ARR_LEN (8)
static int TestInsert()
{
	int ret = SUCCESS;
	ssize_t i = 0;
/*	int arr[] = {50, 40, 60, -15, 45, 55, 46, 43};*/
	int *arr = (int *)malloc(sizeof(*arr) * ARR_LEN);
/*	int *res = (int *)malloc(sizeof(*res) * ARR_LEN);*/
	int num = 0;
	int not_found = 10000;
	avl_t *avl = AVLCreate(Compare, NULL);
	if(NULL == avl)
	{
		return E_MALLOC;
	}
	for(i = 0; ARR_LEN > i; ++i)
	{
		do
		{
			num = rand() % 1000 - 500;
		}
		while(IsNumInArr(arr, num, i));
		
		arr[i] = num; 
	}
	
	for(i = 0; ARR_LEN > i; ++i)
	{
		
		AVLInsert(avl, arr + i);
	}
	if(AVLIsEmpty(avl))
	{	
		ret = 1;
		printf("TestLine%d", __LINE__);
	}
	if((i = AVLGetSize(avl)) != ARR_LEN)
	{
		ret = 1;
		printf("TestLine%d \n", __LINE__);
	}
	
/*	AVLForEach(avl, PushToArr, &res);*/
	AVLForEach(avl, Print, NULL);
	
/*	for(i = 0; ARR_LEN > i; ++i)*/
/*	{*/
/*		printf("%d\n", res[i]);*/
/*	}*/
	
/*	for(i = 1; ARR_LEN > i; ++i)*/
/*	{*/
/*		if(res[i - 1] <= res[i])*/
/*		{*/
/*			printf("TestLine%d \n", __LINE__,  i,5);*/
/*			ret = 1;*/
/*		}*/
/*	}*/
	

	if((i = AVLGetSize(avl)) != ARR_LEN)
	{
		ret = 1;
		printf("TestLine%d \n", __LINE__);
	}
	
/*	for(i = ARR_LEN - 1; 0 <= i; --i)*/
/*	{*/
/*		AVLRemove(avl, arr + i);*/
/*	}*/

	for(i = 0; ARR_LEN > i; ++i)
	{
		AVLRemove(avl, arr + i);
	}

	if((i = AVLGetSize(avl)) != 0)
	{
		ret = 1;
		printf("size = %lu, TestLine%d \n", i, __LINE__);
		AVLForEach(avl, Print, NULL);
	}
	
	

	AVLDestroy(avl);
	avl = NULL;
/*	free(arr);*/
/*	arr = NULL;*/

	return ret;
}
#undef ARR_LEN

int main()
{
/*	RUN_TEST(TestEmpty);*/
	RUN_TEST(TestInsert);

	return SUCCESS;
}
