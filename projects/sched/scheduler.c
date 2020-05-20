/*************************************
16.6.2019 data structure Scheduler
Author Andrei
Reviewer Sandra
*************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /*assert */
#include <errno.h> /* errno */
#include <stdio.h> /* perror */
#include <time.h> /* time */
#include <unistd.h> /* sleep */

#include "scheduler.h" /* scd_t */
/*typedef long(*func_t)(void *params); */
/* returns negative number for remove task, 0 for no change in inverval, 
or a positive number for new inverval  */

#include "pq.h"
/*typedef int(*pqpriority_f)(const void *data, const void *new_data, 
													const void *params);*/
/*typedef int(*pqcmp_f)(const void *data, const void *key, 
													const void *params);*/
#include "task.h" /* task_t */



struct scheduler
{
	pq_t *task_list;
	int should_stop;	

};
/*typedef struct scheduler scd_t;*/

static int IsBefore(const void *task, const void *new_task, const void *unused)
{
	(void)unused;
	
	return TaskGetTime((task_t *)task) > TaskGetTime((task_t *)new_task);
}

scd_t *ScdCreate()
{
	scd_t *new_scd = (scd_t *)malloc(sizeof(*new_scd));
	if(NULL == new_scd)
	{
		perror(" alloc fail");
		return NULL;
	}
	new_scd->should_stop = 0; 
	new_scd->task_list = PQCreate(IsBefore);
	if(NULL == new_scd->task_list)
	{
		perror("PQ alloc fail");
		free(new_scd);
		new_scd = NULL;
	}
	
	return new_scd;	
}

void ScdDestroy(scd_t *scheduler)
{
	assert(NULL != scheduler);

	while(!PQIsEmpty(scheduler->task_list))
	{
		free(PQPeek(scheduler->task_list));
		PQDequeue(scheduler->task_list);
	}
	PQDestroy(scheduler->task_list);
	free(scheduler);
}

unid_t ScdAdd(scd_t *scheduler, time_t interval, func_t func, void *params)
{
	task_t *new_task = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != func);
/*	assert(0 < interval); TODO interval == 0 may cause undefined behaviour*/

	new_task = TaskCreate(interval, func, params);
	if(NULL == new_task)
	{
		return bad_uid;
	}
	
	if(1 == PQEnqueue(scheduler->task_list, new_task))
	{
		free(new_task);
		
		return bad_uid;
	}
	
	return TaskGetUID(new_task);
}

static int ShouldEraseThenErase(const void *task, const void *key, 
													const void *unused)
{
	int should_erase = 0;
	
	(void)unused;
	
	if(UIDIsSame(TaskGetUID(task), *(unid_t *)key))
	{
		should_erase = 1;
		free((void *)task);
	}
	
	return should_erase;
}

int ScdRemove(scd_t *scheduler, unid_t task_uid)
{
	assert(NULL != scheduler);
	
	return PQErase(scheduler->task_list, &task_uid, ShouldEraseThenErase);
}

static void RunInfrastructure(scd_t *scheduler)
{
	task_t *top_task = NULL;
	time_t sleep_time = 0;
	int task_ret = 0;
	scheduler->should_stop = 0;

	while(0 == scheduler->should_stop && !ScdIsEmpty(scheduler))
	{
		top_task = PQPeek(scheduler->task_list);
		
		sleep_time = TaskGetTime(top_task) - time(NULL);
		/* TODO */
		if (0 > sleep_time)
		{
		    sleep_time = 0;
		}
		/* TODO */
		
		/*TODO*/
/*		while(0 < sleep_time) */
/*		{*/
/*		}*/
/*TODO*/
	    sleep_time = sleep(sleep_time);

		task_ret = TaskExecute(top_task);
		if(1 == task_ret)
		{
			if(0 != PQEnqueue(scheduler->task_list, top_task))
			{
				errno = ENOMEM;
				scheduler->should_stop = 1;
				return;
			}
		}
		else
		{
			TaskDestroy(top_task);
		}
		PQDequeue(scheduler->task_list);
	}
}

size_t ScdRun(scd_t *scheduler)
{
	assert(NULL != scheduler);
	
	RunInfrastructure(scheduler);
	
	return ScdSize((const scd_t *)scheduler);
}

void ScdStop(scd_t *scheduler)
{
	assert(NULL != scheduler);
	
	scheduler->should_stop = 1;
}

size_t ScdSize(const scd_t *scheduler)
{
	assert(NULL != scheduler);
	
	return PQSize(scheduler->task_list);
}

int ScdIsEmpty(const scd_t *scheduler)
{
	assert(NULL != scheduler);
	
	return PQIsEmpty(scheduler->task_list);
}
