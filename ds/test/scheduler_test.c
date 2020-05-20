#include <stdio.h> /* printf */
#include <string.h>
#include <time.h> /* time */
#include <unistd.h> /* sleep */

#include "scheduler.h"
#include "uid.h" 

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \

/* static */ unid_t task_to_remove;

long Print(void *params)
{	
	static int ret = 2;
	puts((char *)params);
	--ret;
	printf("param %s, rerun in %d seconds\n", (char *)params, ret);

	return ret;
}

long PrintRecurr(void *params)
{	
	puts((char *)params);
	printf("param %s, rerun\n", (char *)params);

	return 0;
}

long StopOnce(void *scheduler)
{

	ScdStop((scd_t *)scheduler);
	
	return -1;	
}

long StopRecurr(void *scheduler)
{

	ScdStop((scd_t *)scheduler);
	
	return 0;	
}

static int FlowSize()
{
	int ret = 0;
	size_t interval = 1;
	unid_t task_uid = bad_uid;
	scd_t *scheduler = ScdCreate();
	if(NULL == scheduler)
	{
		perror("create alloc failure");
	}
	
	if(0 != ScdSize(scheduler))
	{
		puts("expect size = 0");
		ret = 1;
	}
	if(!ScdIsEmpty(scheduler))
	{
		puts("expected Empty FAIL");
		ret = 1;
	}
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval, Print, "bleeeeeeeeh"))))
	{
		perror("task alloc failure");
	}
	if(ScdIsEmpty(scheduler))
	{
		puts("expected non-Empty FAIL");
		ret = 1;
	}
	if(1 != ScdSize(scheduler))
	{
		puts("expect size = 1");
		ret = 1;
	}
	if(1 == ScdRemove(scheduler, task_uid))
	{
		puts("task remove FAIL");
	}
	if(!ScdIsEmpty(scheduler))
	{
		puts("expected Empty FAIL");
		ret = 1;
	}
	ScdRun(scheduler);
	
	ScdDestroy(scheduler);
	
	return ret;
}

static int FlowNoStop()
{
	int ret = 0;
	size_t interval = 1;
	unid_t task_uid = bad_uid;
	time_t start_time = 0;
	time_t end_time = 0;
	scd_t *scheduler = ScdCreate();
	if(NULL == scheduler)
	{
		perror("create alloc failure");
	}
	
	start_time = time(NULL);
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval, Print, "bleeeeeeeeh"))))
	{
		perror("task alloc failure");
	}
	
/*	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval + 3, StopOnce, scheduler))))*/
/*	{*/
/*		perror("task alloc failure");*/
/*	}*/
	ScdRun(scheduler);
	end_time = time(NULL);	
	if( 3 != (end_time - start_time))
	{
		ret = 1;
		printf("expected 2 sec, ran for %ld", end_time - start_time);
	}
	if(!ScdIsEmpty(scheduler))
	{
		ret = 1;
		puts("expected emptied pq FAIL");
	}
	ScdDestroy(scheduler);
	
	return ret;
}

static int FlowStopOnce()
{
	int ret = 0;
	size_t interval = 1;
	unid_t task_uid = bad_uid;
	time_t start_time = 0;
	time_t end_time = 0;
	scd_t *scheduler = ScdCreate();
	if(NULL == scheduler)
	{
		perror("create alloc failure");
	}
	
	start_time = time(NULL);
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval, PrintRecurr, "bleeeeeeeeh"))))
	{
		perror("task alloc failure");
	}
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval + 3, StopOnce, scheduler))))
	{
		perror("task alloc failure");
	}
	ScdRun(scheduler);
	end_time = time(NULL);	
	if( 4 != (end_time - start_time))
	{
		ret = 1;
		printf("expected 4 sec, ran for %ld\n", end_time - start_time);
	}
	if(1 != ScdSize(scheduler))
	{
		ret = 1;
		printf("size in the end = %lu\n", ScdSize(scheduler));
		puts("expected emptied pq FAIL");
	}
	ScdDestroy(scheduler);
	
	return ret;
}

static int FlowStopRecurr()
{
	int ret = 0;
	size_t interval = 1;
	unid_t task_uid = bad_uid;
	time_t start_time = 0;
	time_t end_time = 0;
	scd_t *scheduler = ScdCreate();
	if(NULL == scheduler)
	{
		perror("create alloc failure");
	}
	
	start_time = time(NULL);
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval, PrintRecurr, "bleeeeeeeeh"))))
	{
		perror("task alloc failure");
	}
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval + 3, StopRecurr, scheduler))))
	{
		perror("task alloc failure");
	}
	ScdRun(scheduler);
	end_time = time(NULL);	
	if( 4 != (end_time - start_time))
	{
		ret = 1;
		printf("expected 4 sec, ran for %ld\n", end_time - start_time);
	}
	if(2 != ScdSize(scheduler))
	{
		ret = 1;
		printf("size in the end = %lu\n", ScdSize(scheduler));
		puts("expected emptied pq FAIL");
	}
	ScdDestroy(scheduler);
	
	return ret;
}

static int FlowStopRun()
{
	int ret = 0;
	size_t interval = 1;
	unid_t task_uid = bad_uid;
	time_t start_time = 0;
	time_t end_time = 0;
	scd_t *scheduler = ScdCreate();
	if(NULL == scheduler)
	{
		perror("create alloc failure");
	}
	
	start_time = time(NULL);
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval, Print, "bleeeeeeeeh"))))
	{
		perror("task alloc failure");
	}
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval+3, Print, "bleeeeeeeeh"))))
	{
		perror("task alloc failure");
	}
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval, StopOnce, scheduler))))
	{
		perror("task alloc failure");
	}
	ScdRun(scheduler);
	puts("sleep");
	sleep(3);
	puts("wake");
	ScdRun(scheduler);
	end_time = time(NULL);	
	if( 4 != (end_time - start_time))
	{
		ret = 1;
		printf("expected 4 sec, ran for %ld\n", end_time - start_time);
	}
	if(0 != ScdSize(scheduler))
	{
		ret = 1;
		printf("size in the end = %lu\n", ScdSize(scheduler));
		puts("expected emptied pq FAIL");
	}
	
	
	ScdDestroy(scheduler);
	
	return ret;

}


long FileSleep(void *howlong)
{
	FILE *file = NULL;
	if(NULL != (file = fopen("sleep", "r")))
	{
		sleep(*(time_t *)howlong);
		fclose(file);
	}

	return 0;
}

static int FlowSleepFromFile()
{
	size_t interval = 1;
	unid_t task_uid = bad_uid;

	time_t how_long_sleep = 2;
	scd_t *scheduler = ScdCreate();
	if(NULL == scheduler)
	{
		perror("create alloc failure");
	}
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval, PrintRecurr, "bleeeeeeeeh"))))
	{
		perror("task alloc failure");
	}
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval, FileSleep, &how_long_sleep))))
	{
		perror("task alloc failure");
	}
	
	ScdRun(scheduler);
		
	return 0;
}

long AddTask(void *scheduler)
{
	(UIDIsSame(bad_uid, (ScdAdd((scd_t *)scheduler, 2, PrintRecurr, "addd!!")))) ? 
	0 : -1;

}

static int FlowAddTaskFromFile()
{
	size_t interval = 1;
	unid_t task_uid = bad_uid;

	time_t how_long_sleep = 2;
	scd_t *scheduler = ScdCreate();
	if(NULL == scheduler)
	{
		perror("create alloc failure");
	}
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval, PrintRecurr, "bleeeeeeeeh"))))
	{
		perror("task alloc failure");
	}
	
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, 2, AddTask, scheduler))))
	{
		perror("task alloc failure");
	}
	if(UIDIsSame(bad_uid, (task_uid = ScdAdd(scheduler, interval + 10, StopOnce, scheduler))))
	{
		perror("task alloc failure");
	}
	
	ScdRun(scheduler);
	
	/* if executed to this point, good for me */
	return 0;
}

static long RemoveTask(void *scheduler)
{
	return (0 == ScdRemove((scd_t *)scheduler, task_to_remove)) ? 
	-1 : 0;

}

static int FlowRemoveFromTask()
{
	unid_t task_uid = bad_uid;

	time_t how_long_sleep = 2;
	scd_t *scheduler = ScdCreate();
	if(NULL == scheduler)
	{
		perror("create alloc failure");
	}
	
	if(UIDIsSame(bad_uid, (task_to_remove = ScdAdd(scheduler, 4, PrintRecurr, "mustn't print - FAIL"))))
	{
		perror("task alloc failure");
	}
	if(UIDIsSame(bad_uid, (ScdAdd(scheduler, 1, RemoveTask, scheduler))))
	{
		perror("task alloc failure");
	}
/*	if(UIDIsSame(bad_uid, (ScdAdd(scheduler, 20, StopOnce, scheduler))))*/
/*	{*/
/*		perror("task alloc failure");*/
/*	}*/
	
		ScdRun(scheduler);
	/* if executed to this point, good for me */
	return 0;
}
	
int main()
{
/*	RUN_TEST(FlowSize);*/
/*	RUN_TEST(FlowNoStop);*/
/*	RUN_TEST(FlowStopOnce);*/
/*	RUN_TEST(FlowStopRecurr);*/
/*	RUN_TEST(FlowStopRun);*/
/*	RUN_TEST(FlowSleepFromFile);*/
/*	RUN_TEST(FlowAddTaskFromFile);*/
	RUN_TEST(FlowRemoveFromTask);
	

	return 0;
}
