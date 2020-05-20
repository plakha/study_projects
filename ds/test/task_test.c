#include <stdio.h> /* printf */

#include "task.h" /* pq_t */



#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \

long test(void *params)
{
	puts((char *)params);

	return 0;
}

int Flow()
{
	int ret = 0;
	task_t *task = TaskCreate(3, test, "bleeh!");
	if(UIDIsBad(TaskGetUID(task)))
	{
		puts("bad UID");
		ret = 1;
	}
	printf("run in %ld o'clock\n", TaskGetTime(task));
	if(0 == TaskExecute(task))
	{
		puts("unrecurrent");	
		ret = 1;
	}
	printf("run in %ld o'clock\n", TaskGetTime(task));

	TaskExecute(task);
	TaskDestroy(task);


}

int main()
{
	RUN_TEST(Flow);

	return 0;
}
	
