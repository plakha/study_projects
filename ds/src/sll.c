/*******************
5.6.19, Singly Linked List
Author Andrei
Reviewer Ben
**********/

/* In the world of iterator - return end-iterator for failure */

/*
typedef struct node *it_t;
typedef struct sll sll_t;

typedef int (*act_f)(void *data, const void *param);
typedef int (*cmp_f)(const void *data, const void *keyword);
*/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "sll.h" /* singly linked list header */

typedef struct node
{
	void *data;
	struct node *next;
}node_t;

struct sll
{
	struct node *head;
	struct node *tail;
};

static node_t *NodeCreate(const void *data)
{
	node_t *new = (node_t *)malloc(sizeof(*new));
	if(NULL == new)
	{

		return NULL;	
	}
	
	new->next = NULL;
	new->data = (void *)data;
	
	return new;
}

sll_t *SLLCreate()
{
	sll_t *sll = (sll_t *)malloc(sizeof(*sll));
	if(NULL == sll)
	{
	
		return NULL;
	}
	
	sll->head = (node_t *)malloc(sizeof(node_t));
	sll->tail = (node_t *)malloc(sizeof(node_t));
	if((NULL == sll->head) || (NULL == sll->tail))
	{
		free(sll->head);
		free(sll->tail);
		free(sll);
		
		return NULL;
	}
	
	sll->head->data =(void *)0xDEADBEEF;
	sll->tail->data = (void *)0xDEADBEEF;
	sll->head->next = sll->tail;
	sll->tail->next = NULL;

	return sll;
}

/* No NULL input ! */
void SLLDestroy(sll_t *sll)
{
	node_t *hold = NULL;
	node_t *run = NULL;
			
	assert(NULL != sll);
	
	hold = sll->head;
	run = hold->next;
	
	while(NULL != run)
	{
		free(hold);
		hold = run;
		run = run->next;
	}
	free(hold);
	free(sll);	
}

/* Return end-iterator if failed. Return iterator of inserted data */
it_t SLLInsertAfter(sll_t *sll, it_t i, const void *data)
{
	node_t *new = NULL;
	
	assert((NULL != sll) && (i != NULL) && (i != sll->tail));
	
	new = NodeCreate(data);
	if(NULL == new)
	{

		return NULL;	
	}
	
	new->next = i->next;
	i->next = new;
	
	return new;
}

/* do not use on empty sll! */
void SLLPopFront(sll_t *sll)
{
	node_t *hold_to_pop = NULL;
	
	assert((NULL != sll) && !SLLIsEmpty(sll));
	
	hold_to_pop = sll->head->next;
	sll->head->next = hold_to_pop->next;
	free(hold_to_pop);
}

void SLLPopBack(sll_t *sll)
{
	node_t *hold_to_pop = NULL;
	node_t *hold_to_keep = NULL;

	assert((NULL != sll) && !SLLIsEmpty(sll));
	
	hold_to_keep = sll->head;
	hold_to_pop = sll->head->next;
	while(hold_to_pop->next != sll->tail)
	{
		hold_to_keep = hold_to_pop;
		hold_to_pop = hold_to_pop->next;
	}
	hold_to_keep->next = hold_to_pop->next;
	free(hold_to_pop);
}

it_t SLLPushFront(sll_t *sll, const void *data)
{
	node_t *new = NULL;
	
	assert(NULL != sll);
	
	new = NodeCreate(data);
	if(NULL == new)
	{
	
		return NULL;
	}
	
	new->next = sll->head->next;
	sll->head->next = new;
	
	return new;
}

it_t SLLPushBack(sll_t *sll, const void *data)
{
	node_t *new = NULL;
	node_t *last = NULL;
	
	assert(NULL != sll);
	
	new = NodeCreate(data);
	if(NULL == new)
	{
	
		return NULL;
	}
	
	last = sll->head;
	while(last->next != sll->tail)
	{
		last = last->next;
	}
	new->next = last->next;
	last->next = new;
	
	return new;
}

it_t SLLBegin(const sll_t *sll)
{
	assert(NULL != sll);
	
	return sll->head->next;
}

it_t SLLEnd(const sll_t *sll)
{
	assert(NULL != sll);
	
	return sll->tail;
}


it_t SLLNext(it_t i)
{
	assert(NULL != i);
		
	return i->next;
}

it_t SLLFind(it_t from, it_t to, const void *keyword, cmp_f is_found)
{
	while(from != to)
	{
		if(is_found(from->data, keyword))
		{
		
			return from;
		}
		from = from->next;
	}
	
	return to;
}

void *SLLGetData(it_t i)
{
	assert(NULL != i);

	return i->data;
}

int SLLForEach(it_t from, it_t to, const void *param, act_f action)
{
	int ret = 0;
	
	while(from != to)
	{
		ret = action(from->data, param);
		
		if(0 != ret)
		{		
			return ret;
		}
		
		from = from->next;
	}
	
	return ret;
}

void SLLErase(sll_t *sll, it_t i)
{
	node_t *keep = NULL;
	
	assert((NULL != sll) && (NULL != i));
	
	keep = sll->head;
	while(keep->next != i)
	{
		keep = keep->next;
	}
	keep->next = i->next;
	free(i);
}

size_t SLLSize(const sll_t *sll)
{
	size_t count = 0;
	node_t *run = NULL;
	
	assert(NULL != sll);
	
	run = sll->head;
	while(NULL != run->next->next)
	{
		++count;
		run = run->next;
	}
	
	return count;
}

sll_t *SLLFlip(sll_t *sll)
{
	node_t *prev = NULL;
	node_t *curr = NULL;
	node_t *next = NULL;
	
	assert(NULL != sll);
	
	prev = sll->head;
	curr = prev->next;
	next = curr->next;
	
	sll->head = sll->tail;
	sll->tail = prev;
	
	prev->next = NULL; /* if this line not applied, ther is loop */
	while(NULL != next)
	{
		curr->next = prev;
		prev = curr;
		curr = next;
		next = next->next;
	}
	curr->next = prev;	
		
	return sll;
}

int SLLIsEmpty(const sll_t *sll)
{
	return sll->head->next == sll->tail;
}

/* Advanced, for bug squashing */
int HasLoop(const sll_t *sll)
{
	return 0;
}

/* Advanced, for bug squashing */
it_t FindIntersection(const sll_t *sll1, const sll_t *sll2)
{
	return NULL;
}

