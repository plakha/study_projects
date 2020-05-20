#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "uid.h"

#ifndef FUNC_T
#define FUNC_T
typedef long(*func_t)(void *params); /* returns negative number for remove task,
0 for no change in inverval or positive number for new inverval  */
#endif

typedef struct scheduler scd_t;
/*struct scheduler
{
	pq_t *task_list;
	int should_stop;	
};*/

/* Use destroy on any created instance of scd_t */
scd_t *ScdCreate();

/* Only send valid scd_t* */
void ScdDestroy(scd_t *scheduler);

/* interval == 0 may cause undefined behaviour
do not input scheduler OR func == NULL  */
unid_t ScdAdd(scd_t *scheduler, time_t interval, func_t func, void *params); 

/* returns 0 on success or 1 on failure (uid not found). 
Must not use to remove task from within task - will yield unexpected results,
, do not input scheduler == NULL */ 
int ScdRemove(scd_t *scheduler, unid_t task_uid); 

/* Runs the Scheduler. returns number of remaining tasks in the queue, no NULL input */
size_t ScdRun(scd_t *scheduler); 

/* Stops the Scheduler, no NULL input */
void ScdStop(scd_t *scheduler);

/* Return Number of Tasks int the scheduler, no NULL input */
size_t ScdSize(const scd_t *scheduler);

/* Return 0 if the Scheduler is non empty, no NULL input*/
int ScdIsEmpty(const scd_t *scheduler);

#endif
