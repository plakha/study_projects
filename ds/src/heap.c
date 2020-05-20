#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <sys/types.h> /* ssize_t */
#include <limits.h> /* LONG_MAX */

#include "heap.h" 
#include "dvec.h"

#define MEMB_SIZE (sizeof(void *))
#define N_MEMB (4)

enum status {OK = 0, FAIL, NOT_FOUND};
enum truthvalue	{FALSE = 0};

struct heap
{
	dvec_t *vector;
	int (*is_before_f)(const void *data1, 
						const void *data2, 
						const void *params);
};/* typedef struct heap heap_t;*/

heap_t *HeapCreate(int (*IsBefore)(const void *data1, 
									const void *data2, 
									const void *garbage))
{
	heap_t *heap =NULL;
	
	assert(IsBefore);
		
	heap = (heap_t *)malloc(sizeof(*heap));
	if (!heap)
	{
		return NULL;
	}
	
	heap->is_before_f = IsBefore;
	heap->vector = DVECCreate(MEMB_SIZE, N_MEMB);
	if (!heap->vector)
	{
		free(heap);
		heap = NULL;
		
		return NULL;
	}
	
	return heap;
}




void HeapDestroy(heap_t *heap)
{
	assert(heap);
	
	DVECDestroy(heap->vector);
	heap->vector = NULL;
	
	free(heap);
	heap = NULL;
}

static ssize_t CalcParentIndex(ssize_t index)
{
	return (((index + 1) / 2) - 1);
}

static void Swap (void **data1, void **data2)
{
	void *holder = *data1;
	
	*data1 = *data2;
	*data2 = holder;
}	

/* return boolean: was heapified or not, 
also updates newbie index, if was heapified */
static int DoneDoHeapifyUpOnce(heap_t *heap, 
						ssize_t parent_index, 
						ssize_t *newbie_index)
{
	void **p_parent_data = DVECGetItemAddress(heap->vector, parent_index);
	void **p_newbie_data = DVECGetItemAddress(heap->vector, *newbie_index);

	if ((heap->is_before_f)(*p_newbie_data, *p_parent_data, NULL))
	{
		return FALSE;
	}
	
	Swap(p_parent_data, p_newbie_data);
	*newbie_index = parent_index;
	
	return 1;
}

int HeapPush(heap_t *heap, void *data)
{
	int ret_status = OK;
	int was_heapified = FALSE;
	ssize_t newbie_index = LONG_MAX;
	ssize_t parent_index = LONG_MAX;
	
	assert(heap);
	assert(data);
	
	ret_status = DVECPushBack(heap->vector, &data);
	if (OK != ret_status)
	{
		return ret_status;
	}
	
	newbie_index = DVECSize(heap->vector) - 1;
	
	while (0 < newbie_index)
	{
		parent_index = CalcParentIndex(newbie_index);
		was_heapified = DoneDoHeapifyUpOnce(heap, parent_index, &newbie_index);
		switch (was_heapified)
		{
			case FALSE:
				
				return ret_status;
		}		
	}
	
	return ret_status;
}



void *HeapPeek(const heap_t *heap)
{
	assert(heap);
	
	return *(void **)DVECGetItemAddress(heap->vector, 0);
}

static ssize_t CalcLChildIndex(ssize_t parent_index)
{
	return (parent_index + 1)  * 2 - 1;
}

static ssize_t CalcRChildIndex(ssize_t parent_index)
{
	return CalcLChildIndex(parent_index) + 1;
}

static int DoneDoHeapifyDownOnce(heap_t *heap, ssize_t *traveler_index)
{
	ssize_t l_child_index = CalcLChildIndex(*traveler_index); 
	ssize_t r_child_index = CalcRChildIndex(*traveler_index); 
	void **p_l_child_data = DVECGetItemAddress(heap->vector, l_child_index);
	void **p_r_child_data = NULL;
	void **p_data_to_swap = p_l_child_data;
	ssize_t index_to_swap = l_child_index;
	void **p_traveler_data = DVECGetItemAddress(heap->vector, *traveler_index);
	
	assert(DVECSize(heap->vector) > l_child_index);
	
	if (DVECSize(heap->vector) > r_child_index)
	{
		p_r_child_data = DVECGetItemAddress(heap->vector, r_child_index);
		
		if((heap->is_before_f)(*p_l_child_data, *p_r_child_data, NULL))
		{
		p_data_to_swap = p_r_child_data;
		index_to_swap = r_child_index;
		}
	}
	
	if ((heap->is_before_f)( *p_data_to_swap, *p_traveler_data, NULL))
	{
		return FALSE;
	}
	
	Swap(p_traveler_data, p_data_to_swap);
	*traveler_index = index_to_swap;
	
	return 1;
}

void HeapPop(heap_t *heap)
{
	ssize_t traveler_index = 0;
	ssize_t last_index = LONG_MAX;
	void **p_front_data = NULL;
	void **p_back_data = NULL;
	int was_heapified = FALSE;
	
	assert(heap);
	assert(!HeapIsEmpty(heap));
	
	last_index = HeapSize(heap) - 1;
	p_front_data = DVECGetItemAddress(heap->vector, traveler_index);
	p_back_data = DVECGetItemAddress(heap->vector, last_index);
	Swap(p_front_data, p_back_data);
	DVECPopBack(heap->vector);
	
	last_index = CalcParentIndex(HeapSize(heap) - 1);
	while (traveler_index <= last_index) /* TODO : < or <= */
	{
		assert(!HeapIsEmpty(heap));
		was_heapified = DoneDoHeapifyDownOnce(heap, &traveler_index);
		switch (was_heapified)
		{
			case FALSE:
				
				return ;
		}
	}	
}

 static void **FindData(const heap_t *heap, int (*ShouldRemove)(const void *data, 
									const void *key, 
									const void *garbage), 
						const void *key, 
						ssize_t *traveler_index)
{
	void **p_data = NULL;
	ssize_t i = 0;
	const ssize_t len = HeapSize(heap);
	
	for (; len > i; ++i)
	{
		p_data = DVECGetItemAddress(heap->vector, i);
		if (ShouldRemove(*p_data, key, NULL))
		{
			*traveler_index = i;
			
			return p_data;
		}
	}
	
	return NULL;
}

int HeapRemove(heap_t *heap, 
				int (*ShouldRemove)(const void *data, 
									const void *key, 
									const void *garbage), 
				const void *key)
{
	ssize_t traveler_index = LONG_MAX;
	ssize_t last_index = LONG_MAX;
	void **p_back_data = NULL;
	void **p_to_remove_data = NULL;
	int was_heapified = FALSE;
	ssize_t parent_index = LONG_MAX;
	
	assert(heap);
	assert(ShouldRemove);
	
	p_to_remove_data = FindData(heap, ShouldRemove, key, &traveler_index);
	if(!p_to_remove_data)
	{
		assert(LONG_MAX == traveler_index); 
		return NOT_FOUND;
	}
	assert(0 <= traveler_index);
	
	last_index = HeapSize(heap) - 1;
	assert(traveler_index <= last_index);
	p_back_data = DVECGetItemAddress(heap->vector, last_index);
	Swap(p_to_remove_data, p_back_data);
	DVECPopBack(heap->vector);
	
	/* treat case heapify up */
	/* if  */
	if (traveler_index >= HeapSize(heap) / 2 )
	{
		while (0 < traveler_index)
		{
			parent_index = CalcParentIndex(traveler_index);
			was_heapified = DoneDoHeapifyUpOnce(heap, 
												parent_index, 
												&traveler_index);
			switch (was_heapified)
			{
				case FALSE:
					
					return OK;
			}		
		}
		
		return OK;
	}
	
	/* treat case heapify down */
	last_index = CalcParentIndex(HeapSize(heap) - 1);
	while (traveler_index <= last_index) /* TODO : < or <= */
	{
		assert(!HeapIsEmpty(heap));
		was_heapified = DoneDoHeapifyDownOnce(heap, &traveler_index);
		switch (was_heapified)
		{
			case FALSE:
				
				return OK;
		}
	}

	return OK;
}

size_t HeapSize(const heap_t *heap)
{
	assert(heap);
	
	return DVECSize(heap->vector);
}




int HeapIsEmpty(const heap_t *heap)
{
	assert(heap);
	
	return 0 == HeapSize(heap);
}

