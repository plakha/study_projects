/************************
1/7/2019

Sorting algorithms iterative implementation.
Comparative algorithms: Selection, Insertion, Swap.
"Linear" (int) algorithms: Counting.

Author: Andrei
Reviewer: Alexa
*************************/

#include <errno.h> /* errno */
#include <assert.h> /* assert */
#include <string.h> /* memmove */
#include <stdlib.h> /* malloc */
#include <errno.h> /* errno */

#include "../include/sort.h" /* cmp_f */

/* The Compare function returns: 
positive value if data1 is "greater" than data2,
negative value if data1 is "lesser: than data2,
zero if data1 and data2 are equivalent. */
/*typedef int (*cmp_f)(const void *data1, const void *data2);*/

/* The key_to_num function takes data and 
returns num in range (0 to (range - 1)) */
/*typedef size_t (*key_to_num)(const void *data, const void *args);*/

enum status {SUCCESS, FAIL}; 

static void *NextMemb(const void *memb, size_t memb_size)
{
	assert(NULL != memb);
	assert(0 < memb_size);
	
	return((void *)((char *)memb + memb_size));
}    

static void *PrevMemb(const void *memb, size_t memb_size)
{
	assert(NULL != memb);
	assert(0 < memb_size);

	return( (void *)((char *)memb - memb_size) );
}

static void *NthMemb(const void *base, size_t index, size_t memb_size)
{
	assert(NULL != base);
	assert(0 < memb_size);

	return( (void *)((char *)base + index * memb_size) );
}

/* The member to be inserted is next to the end of the array pointed by base */
static void MembInsert(void *base, void *memb, size_t memb_size, cmp_f Compare, 
					   void *holder)
{
	size_t move_by = 0;

	assert(NULL != base);
	assert(NULL != memb);
	assert(0 < memb_size);
	assert(NULL != Compare);
	assert(NULL != holder);

	memcpy(holder, memb, memb_size);
	
	while(0 > Compare(base, memb))
	{
		base = NextMemb(base, memb_size);
	}
	if(base == memb)
	{
		return;
	}

	move_by = (size_t)((char *)memb - (char *)base); /*TODO move_by -> sorted_array_size */
	memmove(NextMemb(base, memb_size), base, move_by);
	memcpy(base, holder, memb_size);
}

void MergeSort(void *base, size_t n_memb, size_t memb_size, cmp_f Compare)
{
	
}

void InsertionSort(void *base, size_t n_memb, size_t memb_size, cmp_f Compare)
{
	char *sorted_base = base;
	char *unsorted_memb = NextMemb(base, memb_size);
	const char *last_memb = (char *)base + memb_size * (n_memb - 1);/* TODO use NthMemb */
	void *holder = NULL;

	assert(NULL != base);
	assert(0 < n_memb);
	assert(0 < memb_size);
	assert(NULL != Compare);

	holder = malloc(memb_size);
	if(NULL == holder)
	{
		errno = ENOMEM;

		return;
	}

	while(last_memb >= unsorted_memb)
	{
		MembInsert(sorted_base, unsorted_memb, memb_size, Compare, holder);
		unsorted_memb = NextMemb(unsorted_memb, memb_size);		
	}
	
	unsorted_memb = NULL;
	free(holder);
	holder = NULL;	

	assert(base == sorted_base);
}

static void ChSwap(char *c1, char *c2)
{
	*c1 = *c1 ^ *c2;
	*c2 = *c1 ^ *c2;
	*c1 = *c1 ^ *c2;
}

static void Swap(void *data1, void *data2, size_t memb_size)
{
	assert(NULL != data1);
	assert(NULL != data2);
	assert(0 < memb_size);
	assert(data1 != data2);

	while(0 < memb_size)
	{
		ChSwap(data1, data2);
		data1 = (char *)data1 + 1;
		data2 = (char *)data2 + 1;
		--memb_size;
	}
}

void BubbleSort(void *base, size_t n_memb, size_t memb_size, cmp_f Compare)
{
	char *left = base;
	char *right = base;
	const char *last_memb = (char *)base + memb_size * (n_memb - 1);
	int was_swapped = 1;
	
	assert(NULL != base);
	assert(0 < n_memb);
	assert(0 < memb_size);
	assert(NULL != Compare);
	
	while(0 != was_swapped)
	{
		left = base;
		was_swapped = 0;
		while(last_memb > left)
		{
			right = NextMemb(left, memb_size);
			if(0 < Compare(left, right))
			{
				was_swapped = 1;
				Swap(left, right, memb_size);
			}
			left = NextMemb(left, memb_size);
		}
	}
}

static void *FindExtremum(const void *base, size_t n_memb, size_t memb_size, cmp_f Compare)
{
	const void *extremum = base;	
	const void *runner = NextMemb(base, memb_size);
	
	assert(NULL != base);
	assert(0 < n_memb);
	assert(0 < memb_size);
	assert(NULL != Compare);
	
	while(1 < n_memb)
	{
		if(0 < Compare(extremum, runner))
		{
			extremum = runner;
		}
		runner = NextMemb(runner, memb_size);
		--n_memb;
	}

	return((void *)extremum);
}
		
void SelectionSort(void *base, size_t n_memb, size_t memb_size, cmp_f Compare)
{
	void *unsorted_base = base;
	void *extremum = NULL;
	
	assert(NULL != base);
	assert(0 < n_memb);
	assert(0 < memb_size);
	assert(NULL != Compare);
	
	while(0 < n_memb)
	{
		extremum = FindExtremum(unsorted_base, n_memb, memb_size, Compare);
		if(unsorted_base != extremum)
		{
			Swap(unsorted_base, extremum, memb_size);
		}
		
		unsorted_base = NextMemb(unsorted_base, memb_size);
		--n_memb;
	}
}

/*TODO FillTable */
static void InitTable(size_t *table, size_t range, void *base, 
					  size_t n_memb, size_t memb_size, key_to_num ktn_f, 
					  const void *args)
{
	size_t i = 0;
	size_t num_from_key = 0;
	const char *last_memb = (char *)base + memb_size * (n_memb - 1);
	
	assert(NULL != table);
	assert(1 < range);
	assert(NULL != base);
	assert(2 < n_memb);
	assert(0 < memb_size);
	assert(NULL != ktn_f);
	
	while(last_memb >= (char *)base)
	{
		num_from_key = ktn_f(base, args);
		assert(num_from_key <= range);
		++(table[num_from_key]);
		base = NextMemb(base, memb_size);
	}
	base = NULL;

	for(i = 0; i < range; ++i)
	{
		table[i + 1] += table[i];
	}
}

static void FillResult(void *result, void *base, size_t n_memb, 
					   size_t memb_size, key_to_num ktn_f, const void *args, 
					   size_t *table, size_t range)
{
	char *run_base = (char *)base + memb_size * (n_memb - 1);
	void *run_res = NULL;
	const char *first_memb = base;
	size_t num_from_key = 0;
	size_t i = 0;
	
	assert(NULL != result);
	assert(NULL != base);
	assert(2 < n_memb);
	assert(0 < memb_size);
	assert(NULL != ktn_f);
	assert(NULL != table);
	
	while(first_memb <= run_base)
	{
		num_from_key = ktn_f(run_base, args);

		assert(num_from_key <= range);
		assert(0 < table[num_from_key]);

		--(table[num_from_key]);
		i = table[num_from_key];
		run_res = NthMemb(result, i, memb_size);
		memcpy(run_res, run_base, memb_size);
		run_base = PrevMemb(run_base, memb_size);
	}
}

int CountingSort(void *base, size_t n_memb, size_t memb_size,
					key_to_num ktn_f, const void *args, size_t range)
{
	void *result = NULL;
	size_t *table = NULL;
	size_t i = 0;
	
	assert(NULL != base);
	assert(2 < n_memb);
	assert(0 < memb_size);
	assert(NULL != ktn_f);
	assert(1 < range);
	
	result = malloc(memb_size * n_memb);
	if(NULL == result)
	{
		errno = ENOMEM;
		
		return(FAIL);
	}
	table = calloc(range + 1, sizeof(size_t));
	if(NULL == table)
	{
		errno = ENOMEM;
		free(result);
		
		return(FAIL);
	}
	
	InitTable(table, range, base, n_memb, memb_size, ktn_f, args);
	#ifndef NDEBUG
	for(i = 0; i < range; ++i)
	{
		assert(table[i] <= table[i + 1]);
	}
	#endif
	FillResult(result, base, n_memb, memb_size, ktn_f, args, table, range);
	memcpy(base, result, n_memb * memb_size);

	free(result);
	free(table);

	return(SUCCESS);
}
