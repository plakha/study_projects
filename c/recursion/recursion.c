/*******************************************************************************
8/7/19
Recursive Functions Implementations
*******************************************************************************/

#ifndef NDEBUG
#include <stdio.h> /* printf */
#endif
#include <limits.h> /* INT_MIN */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "recursion.h" /* RecurFibonnaci */

/* for index "big enough" (> 10000), falls after ~174500 function calls */
long RecurFibonnaci(long n)
{	
	#ifndef NDEBUG
	static size_t calls = 0;
	#endif

	assert(0 <= n);
	
	if(0 == n || 1 == n)
	{
		return(n);
	}
	#ifndef NDEBUG
	++calls;
	printf("RecurFibonnaci call no. %lu - \n", calls);
	#endif
	return(RecurFibonnaci(n - 1) + RecurFibonnaci(n - 2));
}

/* "Much" more fast than the Recursive algorithm */
long IterFibonacci(long n)
{
	long prev_prev = 0;
	long prev = 1;
	long res = 0;
	long i = 1;
	
	assert(0 <= n);
	
	switch(n)
	{
		case 0:
		;
		case 1:
			return(n);
	}
	for(; i < n; ++i)
	{
		res = prev + prev_prev;
		prev_prev = prev;
		prev = res;
	}

	return(res);
}

size_t RecurStrlen(const char *s)
{
	assert(NULL != s);
		
	return(('\0' == *s) ? 0 : (1 + RecurStrlen(s + 1)));
}

int RecurStrcmp(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);
	
	if('\0' == *s1 || '\0' == *s2)
	{
		return(*s1 - *s2);
	}

	return((*s1 != *s2) ? (*s1 - *s2) : RecurStrcmp(s1 + 1, s2 + 1));
}

char *RecurStrcpy(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	*dest = *src;
	if('\0' != *src)
	{
		RecurStrcpy(dest + 1, src + 1);
	}

	return(dest);
}

/*typedef struct node*/
/*{*/
/*	void *data;*/
/*	struct node *next;*/
/*} node_t;*/
static node_t *UtilFlip(node_t *node, node_t *new_head)
{
	if(NULL == node->next)
	{
		return(node);
	}
	new_head = UtilFlip(node->next, new_head);
	node->next->next = node;
	
	return(new_head);
}

node_t *RecurFlip(node_t *node)
{
	node_t *new_head = UtilFlip(node, NULL);
	node->next = NULL;
	
	return(new_head);
}

/* *max must initially hold INT_MAX value to accomodate RecurStackSort */
static void StackExtractMin(stack_t *stack, int *min)
{
	int *holder = NULL;
	
	if(0 != STACKSize(stack))
	{
		holder = STACKPeek(stack);
	}
	if(NULL == holder)
	{
		return;
	}
	*min = (*min < *holder) ? *min : *holder;
	STACKPop(stack);

	StackExtractMin(stack, min);

	if(*holder > *min)
	{
		STACKPush(stack, holder);
	}
}

/* the algorithm gets rid of non-unique values */
void RecurStackSort(stack_t *stack)
{
	int min = INT_MAX;

	if(0 == STACKSize(stack))
	{
		return;
	}

	StackExtractMin(stack, &min);
	RecurStackSort(stack);
	STACKPush(stack, &min);
}
