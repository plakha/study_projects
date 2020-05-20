#include <string.h> /* strlen */
#include <stdlib.h> /* rand */
#include <stdio.h> /* printf */
#include <limits.h> /* INT_MAX */
#include <stdlib.h> /* malloc */

#include "recursion.h" /* RecurFibonnaci */

enum status {SUCCESS = 0, FAIL};
enum statuc {FALSE = 0};

#define N_MEMBS (15)
/*static node_t node_list[N_MEMBS];*/


static int TestRecurStackSort()
{
	stack_t *stack= STACKCreate(N_MEMBS, sizeof(int));
	int ret = SUCCESS;
	int is_stack_over = FALSE;
	int rand_num = 0;
	while(!is_stack_over)
	{
		rand_num =  rand() % 100 - 50;
		is_stack_over = SUCCESS != STACKPush(stack, &rand_num);
	}
	
	RecurStackSort(stack);

	while(0 != STACKSize(stack))
	{
		printf("%d -> ", *(int *)STACKPeek(stack));
		STACKPop(stack);
	}

	STACKDestroy(stack);
	return ret;
}

int main()
{
	char *dest = (char *)malloc(1000);
	node_t *new = malloc(sizeof(*new));
	node_t *node_list = (node_t *)malloc(sizeof(*node_list) * N_MEMBS);

	node_t *runner = NULL;
	size_t i = 0;
	
	printf("RecurFibonnaci result %ld\n", RecurFibonnaci(10));
	printf("IterFibonacci result %ld\n", IterFibonacci(10));
	
	printf("Strlen %ld\n", RecurStrlen("123456"));
	printf("strlen %ld\n", strlen("123456"));
	
	printf("RecurStrcmp %d\n", RecurStrcmp("r3", "r"));
	printf("strcmp %d\n", strcmp("r3", "r"));
	
	RecurStrcpy(dest, "I am Robot. Kill all Human");
	puts(dest);
	free(dest);


	for(i = 0; N_MEMBS > i; ++i)
	{
		node_list[i].data = (void *)i;
		node_list[i].next = node_list + i + 1;
	}
	node_list[i - 1].next = NULL;

	runner = node_list;
	while(NULL != runner)
	{
		printf("node %lu - \n", (size_t)runner->data);
		runner = runner->next;
	}
	
	runner = node_list;
	runner = RecurFlip(runner);
	while(NULL != runner)
	{
		printf("%lu - ", (size_t)runner->data);
		runner = runner->next;
	}
	
	free(new);
	free(node_list);
	

	
	TestRecurStackSort();

	return 0;
	
}



