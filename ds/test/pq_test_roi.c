/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 11/06/19                                *
*   Description: Priority Queue test file.        *
*                                                 *
**************************************************/
#include <stdio.h>  /* printf */

#include "tests.h" /* test macros */
#include "pq.h" /* priority queue header file */

size_t g_total_tests = 0;
size_t g_total_failed = 0;
size_t g_total_success = 0;

typedef struct task
{
	int id;
	int niceness;
} task_t;

int Prioritize(const void *data, const void *key, const void *params);
int RemoveTasksWithLowPriorityint(const void *data, const void *key, const void *params);


int Test_CreateDestroy(void);
int Test_PushNPop(void);
int Test_Clear(void);
int Test_Erase(void);

int main() 
{
	puts("\x1B[36m_____________Test Results:_____________\033[0m");
	RUN_TEST(Test_CreateDestroy);
	RUN_TEST(Test_PushNPop);
	RUN_TEST(Test_Clear);
	RUN_TEST(Test_Erase);

	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);
	

	return 0;
}

/* puts tasks with bigger niceness at the start of the list */
int Prioritize(const void *data, const void *key, const void *params)
{
	task_t cur_task = *(task_t *)data;
	task_t my_task = *(task_t *)key;
	
	(void)params;
	
	if(my_task.niceness > cur_task.niceness)
	{
		return 1;
	}
	
	return 0;
}

int RemoveTaskWithLowPriority(const void *data, const void *key,
	const void *params)
{
	task_t *cur_task = (task_t *)data;
	
	(void)params;
	
	if(cur_task->niceness < *(int *)key)
	{
		return 1;
	}
	
	return 0;
}

int Test_CreateDestroy(void)
{
	int result = 1;
	size_t test_no = 0;
	pq_t *pq = NULL;
	
	puts("\x1B[33m[Test_CreateDestroy]\033[0m");

	pq = PQCreate(Prioritize);

	TEST_EQUAL(1, 1);

	PQDestroy(pq);

	return result;
}

int Test_PushNPop(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	pq_t *pq = NULL;
	task_t tasks[5] = {{123, 1}, {323, 2}, {444, 3}, {111, 1}, {222, 1}};
	task_t *t;
	
	puts("\x1B[33m[Test_PushNPop]\033[0m");

	pq = PQCreate(Prioritize);

	PQEnqueue(pq, tasks);
	PQEnqueue(pq, tasks + 1);
	PQEnqueue(pq, tasks + 2);
	PQEnqueue(pq, tasks + 3);
	PQEnqueue(pq, tasks + 4);

	/* test1 */
	res = (int)PQSize(pq);
	TEST_EQUAL(res, 5);
	
	/* test2 */
	t = (task_t *)PQPeek(pq);
	res = t->niceness;
	TEST_EQUAL(res, 3);
	/* test3 */
	res = t->id;
	TEST_EQUAL(res, 444);
	
	PQDequeue(pq);
	
	/* test4 */
	t = (task_t *)PQPeek(pq);
	res = t->niceness;
	TEST_EQUAL(res, 2);
	/* test5 */
	res = t->id;
	TEST_EQUAL(res, 323);
	
	PQDequeue(pq);
	
	/* test6 */
	t = (task_t *)PQPeek(pq);
	res = t->niceness;
	TEST_EQUAL(res, 1);
	/* test7 */
	res = t->id;
	TEST_EQUAL(res, 123);

	PQDequeue(pq);
	
	/* test8 */
	t = (task_t *)PQPeek(pq);
	res = t->niceness;
	TEST_EQUAL(res, 1);
	/* test9 */
	res = t->id;
	TEST_EQUAL(res, 111);

	PQDequeue(pq);
	
	/* test10 */
	t = (task_t *)PQPeek(pq);
	res = t->niceness;
	TEST_EQUAL(res, 1);
	/* test11 */
	res = t->id;
	TEST_EQUAL(res, 222);

	PQDequeue(pq);

	/* test12 */
	res = PQIsEmpty(pq);
	TEST_EQUAL(res, 1);

	if(result)
	{
		puts("\tQUEUE IS STABLE");
	}
	else
	{
		puts("\tQUEUE IS NOT STABLE!");
	}
	
	PQDestroy(pq);

	return result;
}

int Test_Clear(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	pq_t *pq = NULL;
	task_t tasks[3] = {{123, 1}, {323, 2}, {444, 3}};
	
	puts("\x1B[33m[Test_Clear]\033[0m");

	pq = PQCreate(Prioritize);

	PQEnqueue(pq, tasks);
	PQEnqueue(pq, tasks + 1);
	PQEnqueue(pq, tasks + 2);

	PQClear(pq);
	
	/* test1 */
	res = (int)PQSize(pq);
	TEST_EQUAL(res, 0);

	/* test2 */
	res = (int)PQSize(pq);
	TEST_EQUAL(res, 0);
	
	PQEnqueue(pq, tasks);

	/* test3 */
	res = (int)PQSize(pq);
	TEST_EQUAL(res, 1);
	
	PQClear(pq);

	/* test4 */
	res = (int)PQSize(pq);
	TEST_EQUAL(res, 0);
	
	PQClear(pq);

	/* test5 */
	res = (int)PQSize(pq);
	TEST_EQUAL(res, 0);
	
	PQDestroy(pq);

	return result;
}

int Test_Erase(void)
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	pq_t *pq = NULL;
	int param = 3;
	task_t tasks[3] = {{123, 1}, {323, 2}, {444, 3}};
	
	puts("\x1B[33m[Test_Erase]\033[0m");

	pq = PQCreate(Prioritize);

	PQEnqueue(pq, tasks);
	PQEnqueue(pq, tasks + 1);
	PQEnqueue(pq, tasks + 2);
	
	/* test1 */
	res = (int)PQSize(pq);
	TEST_EQUAL(res, 3);
	
	/* test1 */
	res = (int)PQErase(pq, &param, RemoveTaskWithLowPriority);
	TEST_EQUAL(res, 0);
	
	/* test2 */
	res = (int)PQSize(pq);
	TEST_EQUAL(res, 2);
	
	/* test1 */
	res = (int)PQErase(pq, &param, RemoveTaskWithLowPriority);
	TEST_EQUAL(res, 0);
	
	/* test2 */
	res = (int)PQSize(pq);
	TEST_EQUAL(res, 1);
	
	/* test1 */
	res = (int)PQErase(pq, &param, RemoveTaskWithLowPriority);
	TEST_EQUAL(res, 1);
	
	/* test2 */
	res = (int)PQSize(pq);
	TEST_EQUAL(res, 1);

	PQDestroy(pq);

	return result;
}














