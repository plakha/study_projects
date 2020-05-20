/***********************************
Data Structure Task
16/6/2019
Author Andrei
Reviewer Sandra
***********************************/

#include <assert.h> /* assert */
#include <unistd.h> /* getpid */
#include <time.h> /* time */
#include <stdlib.h> /* malloc */

#include "task.h" /* task_t */

struct task
{
	func_t func;
	void *params;
	unid_t uid;
	size_t interval; /* in sec */
	time_t time_to_run;
};
/*typedef struct task task_t;*/

/*typedef long(*func_t)(void *params); */
/* returns negative number for remove task, 
0 for no change in inverval or positive number for new inverval  */

task_t *TaskCreate( size_t interval, func_t func, void *params)
{
	task_t *new_task = NULL;
	
	assert(NULL != func);
	
	new_task = (task_t *)malloc(sizeof(*new_task));
	if(NULL == new_task)
	{
		return NULL;
	}

	new_task->func = func;
	new_task->params = params;
	new_task->uid = UIDCreate();
	new_task->interval = interval;
	new_task->time_to_run = time(NULL) + new_task->interval;

	return new_task;
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	task->func = NULL;
	task->params = NULL;
	task->uid = bad_uid;
	task->interval = 0;
	task->time_to_run = 0;

	free(task);
}

time_t TaskGetTime(const task_t *task)
{
	assert(NULL != task);

	return task->time_to_run;
}

unid_t TaskGetUID(const task_t *task)
{
	assert(NULL != task);

	return task->uid;
}

int TaskExecute(task_t *task)
{
	long func_return = 0;
	time_t delta_to_run = 0;

	assert(NULL != task);

	assert(NULL != task->func);
	
/* TODO interval == 0 may cause indefined behaviour */
/*	if(0 == task->interval)*/
/*	{*/
/*		return 1;*/
/*	}*/

	delta_to_run = TaskGetTime(task) - time(NULL);
	if(0 > delta_to_run)
	{
		task->time_to_run = time(NULL) + (time_t)task->interval;
		
		return 1;
	}
	
	if(0 < (func_return = task->func(task->params)))
	{
		task->interval = func_return;

	}
	if(0 > func_return)
	{
		return task->interval = 0;
	}
	

	task->time_to_run = time(NULL) + task->interval;
	
	return 1;
}
