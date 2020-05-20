#include <stdio.h> /* printf */

#include "../include/bst.h" /* pq_t */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \

enum status {SUCCESS};
enum truth_value {FALSE};

static int IntCompare(const void *n, const void *m, const void *params)
{
	(void)params;

	return( *(int *)n - *(int *)m );
}

/*static int IntCompare(const void *n, const void *m, const void *params)*/
/*{*/
/*	(void)params;*/

/*	return((*(int *)n - *(int *)m) > 0) ? 1 : 0;*/
/*}*/

#define ARR_LEN (8)
static int BasicTest()
{
	bst_it_t runner = NULL;
	size_t i = 0;
	int ret = SUCCESS;
	int arr[] = {50, 40, 60, -15, 45, 55, 46, 43};
	bst_t *bst = NULL;

	puts("Fill distinct numbers, Count");
	puts("Min, Max, Check Order");
	puts("Find&Remove Leaf/One-child, Two-child nodes, Count, Destroy");
	bst = BSTCreate(IntCompare, NULL);
	if(NULL == bst)
	{
		perror("alloc error");
		
		return 1;
	}
	if((i = BSTCount(bst)) != 0)
	{
		ret = 1;
		printf("Line%d Count=%lu, expected %d ##FAIL##", __LINE__,  i,0);
	}	


	for(i = 0; ARR_LEN > i; ++i)
	{
		BSTInsert(bst, arr + i);
	}
	if((i = BSTCount(bst)) != ARR_LEN)
	{
		ret = 1;
		printf("Line%d Count=%lu, expected %d ##FAIL##\n", __LINE__,  i, ARR_LEN);
	}
	runner = BSTBegin(bst);
	
	for(i = 0; ARR_LEN -1 > i; ++i)
	{
		if(*(int *)BSTGetData(runner) > *(int *)(BSTGetData(BSTNext(runner))))
		{
			printf("Line%d, %d>%d",__LINE__, *(int *)BSTGetData(runner), 
							*(int *)(BSTGetData(BSTNext(runner))));
		}
		runner = BSTNext(runner);
	}

	if(arr[5] != (*(int *)BSTGetData(runner = BSTFind(bst, arr + 5))))
	{
		ret = 1;
		printf("Line%d, didn't found one-child node ##FAIL##\n", __LINE__);
	}
	BSTRemove(runner);
	if((i = BSTCount(bst)) != 7)
	{
		ret = 1;
		printf("Line%d Count=%lu, expected %d ##FAIL##\n", __LINE__,  i, 7);
	}
	
	if(arr[3] != (*(int *)BSTGetData(runner = BSTFind(bst, arr + 3))))
	{
		ret = 1;
		printf("Line%d, didn't found leaf ##FAIL##\n", __LINE__);
	}
	BSTRemove(runner);
	if((i = BSTCount(bst)) != 6)
	{
		ret = 1;
		printf("Line%d Count=%lu, expected %d ##FAIL##\n", __LINE__,  i,6);
	}
	
	if(arr[0] != (*(int *)BSTGetData(runner = BSTFind(bst, arr + 0))))
	{
		ret = 1;
		printf("Line%d, didn't found two_child node ##FAIL##\n", __LINE__);
	}
	BSTRemove(runner);
	if((i = BSTCount(bst)) != 5)
	{
		ret = 1;
		printf("Line%d Count=%lu, expected %d ##FAIL##\n", __LINE__,  i,5);
	}
	
	i = 0;
	if(BSTEnd(bst) != BSTFind(bst, &i))
	{
		ret = 1;
		printf("Line%d, found non existing data ##FAIL##\n", __LINE__);
	}
	if((i = BSTCount(bst)) != 5)
	{
		ret = 1;
		printf("Line%d Count=%lu, expected %d ##FAIL##", __LINE__,  i,6);
	}
	
	BSTDestroy(bst);
	return ret;
}
#undef ARR_LEN

static int MultBy2(void *data, const void *args)
{
	(void)args;
	*(int *)data *= 2;

	return(SUCCESS);
}

#define ARR_LEN (10)
int TestForEach()
{
 	bst_it_t runner = NULL;
	size_t i = 0;
	int ret = SUCCESS;
	int arr[] = {50, 40, 60, -15, 45, 55, 46, 0, 40, 43};
	int sorted_arr[] = {-15, 0, 40, 43, 45, 46, 50, 55, 60} ;
	int foreached_arr[] = {-30, 0, 80, 86, 90, 92, 100, 110, 120};
	bst_t *bst = NULL;
	puts("Sort array with non unique members, apply operation for each member");

	bst = BSTCreate(IntCompare, NULL);
	if(NULL == bst)
	{
		perror("alloc error");
		
		return 1;
	}
	if(!BSTIsEmpty(bst))
	{
		ret = 1;		
		printf("Line%d, expected empty, found not empty ##FAIL##\n", __LINE__);
	} 
	for(i = 0; ARR_LEN > i; ++i)
	{
		BSTInsert(bst, arr + i);
	}
	
	i = 0;
	runner = BSTBegin(bst);
	while(BSTEnd(bst) != runner)
	{
		if(*(int *)BSTGetData(runner) != sorted_arr[i++])
		{ 
			ret = 1;
	 		printf("Sorting:Line%d, bst memn=%d != sorted_arr[%lu]=%d ##FAIL##", 
				__LINE__, *(int *)BSTGetData(runner), i, sorted_arr[i]);
			break;
		}
		
		runner = BSTNext(runner);
	}

	BSTForEach(BSTBegin(bst), BSTEnd(bst), MultBy2, NULL);
	
	i = 0;
	runner = BSTBegin(bst);
	while(BSTEnd(bst) != runner)
	{
		if(*(int *)BSTGetData(runner) != foreached_arr[i++])
		{ 
			ret = 1;
	 		printf("ForEach:Line%d, bst memn=%d != sorted_arr[%lu]=%d ##FAIL##", 
				__LINE__, *(int *)BSTGetData(runner), i, foreached_arr[i]);
			break;
		}
		
		runner = BSTNext(runner);
	}	
	runner = BSTBegin(bst);
while(BSTEnd(bst) != runner)
	{
		printf("%d - ", *(int *)BSTGetData(runner));
		runner = BSTNext(runner);
	}
	runner = BSTBegin(bst);
	BSTDestroy(bst);

	return ret;
}
#undef ARR_LEN

int main()
{
	RUN_TEST(BasicTest);
	RUN_TEST(TestForEach);
	
	return 0;
}
	
