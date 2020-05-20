/**************************************************
*                                                 *
*   Author: Roi Kramer                            *
*   Date: 13/06/19                                *
*   Description: Single Process Scheduler         *
*                                                 *
**************************************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <unistd.h> /* sleep  */
#include <errno.h>  /* errno  */
#include <time.h>   /* time   */

#include "scheduler.h" /* scheduler header file */
#include "task.h"      /* task header file */
#include "pq.h"        /* priority queue */

struct scheduler
{
	pq_t *task_list;
	int should_stop;
};

int EraseAndDestroyByUID(const void *task, const void *uid, const void *params);
int Prioritize(const void *data, const void *new_data, const void *params);

scd_t *ScdCreate()
{
	scd_t *new_scheduler = NULL;
	
	new_scheduler = (scd_t *)malloc(sizeof(scd_t));
	if(NULL == new_scheduler)
	{
		return NULL;
	}
	
	new_scheduler->task_list = PQCreate(Prioritize);
	if(NULL == new_scheduler->task_list)
	{
		free(new_scheduler);
		
		return NULL;
	}
	
	new_scheduler->should_stop = 0;
	
	return new_scheduler;
}

void ScdDestroy(scd_t *scheduler)
{
	task_t *cur_task = NULL;
	
	assert(NULL != scheduler);
	
	while(!PQIsEmpty(scheduler->task_list))
	{
		cur_task = (task_t *)PQPeek(scheduler->task_list);
		TaskDestroy(cur_task);
		PQDequeue(scheduler->task_list);
	}
	
	PQDestroy(scheduler->task_list);
	free(scheduler);
}

int ScdRemove(scd_t *scheduler, unid_t uid)
{
	assert(NULL != scheduler);
	
	return PQErase(scheduler->task_list, &uid, EraseAndDestroyByUID);
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

unid_t ScdAdd(scd_t *scheduler, time_t interval, func_t func, void *params)
{
	task_t *new_task = NULL;
	
	assert(NULL != scheduler && NULL != func);
	
	new_task = TaskCreate(interval, func, params);
	if(NULL == new_task)
	{
		return bad_uid;
	}
	
	if(0 != PQEnqueue(scheduler->task_list, new_task))
	{
		TaskDestroy(new_task);
	
		return bad_uid;
	}
	
	return TaskGetUID(new_task);
}

size_t ScdRun(scd_t *scheduler)
{
	task_t *cur_task = NULL;
	time_t sleep_time = 0;
	
	assert(NULL != scheduler);
	
	scheduler->should_stop = 0; /* reset the flag */
	
	while(!scheduler->should_stop && !ScdIsEmpty(scheduler))
	{
		cur_task = PQPeek(scheduler->task_list);
		sleep_time = TaskGetTime(cur_task) - time(NULL);
		
		if(0 < sleep_time)
		{
			sleep(sleep_time);
			continue; /* if sleep was interrupted, this would come back */
		}
		
		if(TaskExecute(cur_task)) /* if recurring task - enqueue */
		{
			if(1 == PQEnqueue(scheduler->task_list, cur_task)) /* if failed */
			{
				errno = ENOMEM;
				
				return ScdSize(scheduler);
			}
		}
		else /* if the task is one time - destroy */
		{
			TaskDestroy(cur_task);
		}
		
		PQDequeue(scheduler->task_list);
	}
	
	return ScdSize(scheduler);
}

int Prioritize(const void *data, const void *new_data, const void *params)
{
	(void)params;
	
	return (long)TaskGetTime((task_t *)new_data) < 
				TaskGetTime((task_t *)data);
}

int EraseAndDestroyByUID(const void *task, const void *uid, const void *params)
{
	(void)params;
	if(UIDIsSame(TaskGetUID((task_t *)task), *(unid_t *)uid))
	{
		TaskDestroy((task_t *)task);
		
		return 1;
	}

	return 0;
}
