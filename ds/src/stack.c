#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "../include/stack.h"

#define OFFSET_BASE (size_t)(((stack_t *)NULL)->base)

struct Stack
{
	void *end; /* end points at "after" the end of the stack */
	void *current; /* current points at the "next" place */
	size_t element_size;
	char base[1];
};

stack_t *STACKCreate(size_t n_elements, size_t element_size)
{
	size_t stack_size = (1 + n_elements) * element_size;
	stack_t *ret = NULL;
	
	assert(0 != n_elements * element_size);

	ret = (stack_t *)malloc(sizeof(stack_t) + stack_size 
				- (sizeof(stack_t) - OFFSET_BASE));
	if(NULL == ret)
	{

		return NULL;
	}

	ret->current = ret->base;
	ret->element_size = element_size;
	ret->end = (void *)((char *)ret->base + stack_size - element_size); 
	
	return ret;
}

/* dont use this if but assert !!!*/
void STACKPop(stack_t *stack)
{
	assert(NULL != stack);

	if((size_t)(stack->base) < (size_t)(stack->current))
	{
		stack->current = (void *)((char *)stack->current - stack->element_size);
	}
}

int STACKPush(stack_t *stack, const void *element)
{
	assert(NULL != stack);
	assert(NULL != element);
/* dont use this if but assert !!!*/
	if((size_t)stack->current >= (size_t)stack->end)
	{

		return 1;
	}

	if(NULL == memcpy(stack->current, element, stack->element_size))
	{

		return 1;
	}
	stack->current = (void *)((char *)stack->current + stack->element_size);

	return 0;
}

void *STACKPeek(const stack_t *stack)
{
	assert(NULL != stack);

	if(stack->base == stack->current)
	{

		return NULL;
	}

	return (void *)((char *)stack->current - stack->element_size);
}

size_t STACKSize(const stack_t *stack)
{
	assert(NULL != stack);

	return ((size_t)stack->current - (size_t)stack->base) / stack->element_size;
}

void STACKDestroy(stack_t *stack)
{
	free(stack);
}
