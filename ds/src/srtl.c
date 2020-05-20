/****************************
Data Structure Sorted Linked List
				15.6.2019
Author Andrei
Reviewer Eran
****************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */

#include "srtl.h"  

/*typedef int (*scmp_f)(const void *data, const void *key, const void *params);*/
/*typedef int (*isbefore_f)(const void *data, const void *new_data, const void *params); */
/*typedef int (*sact_f)(void *data, const void *params);*/
/*typedef it_t sit_t;*/

struct srtl
{
    dll_t *dll;
    isbefore_f IsBefore;
    const void *params; 
};
/*typedef struct srtl srtl_t;*/

static dll_t *StripDLL(srtl_t *srtl)
{
	return srtl->dll;
}

srtl_t *SrtLCreate(isbefore_f IsBefore, const void *params)
{
	srtl_t *new_srtl = NULL;

	assert(NULL != IsBefore);

	new_srtl = malloc(sizeof(*new_srtl));
	if(NULL == new_srtl)
	{
		return NULL;
	}
	
	if(NULL == (new_srtl->dll = DLLCreate()))
	{
		free(new_srtl);
		
		return NULL;
	}
	
	new_srtl->IsBefore = IsBefore;
	new_srtl->params = params;
	
	return new_srtl;
}

void SrtLDestroy(srtl_t *srtl)
{
	assert(NULL != srtl);
	assert(NULL != StripDLL(srtl));

	DLLDestroy(StripDLL(srtl));
	free(srtl);
}

size_t SrtLSize(const srtl_t *srtl)
{
	assert(NULL != srtl);

	assert(NULL != StripDLL((srtl_t *)srtl));

	return DLLSize(StripDLL((srtl_t *)srtl));
}

int SrtLIsEmpty(const srtl_t *srtl)
{
	assert(NULL != srtl);

	assert(NULL != StripDLL((srtl_t *)srtl));

	return DLLIsEmpty(StripDLL((srtl_t *)srtl));
}

sit_t SrtLInsert(srtl_t *srtl, void *new_data)
{
	sit_t iter = NULL;
	
	assert(NULL != srtl);

	assert(NULL != StripDLL((srtl_t *)srtl));
	
	for(iter = SrtLBegin(srtl); 
		iter != SrtLEnd(srtl) 
		&& !(srtl->IsBefore)(SrtLGetData((const sit_t)iter), 
										(const void *)new_data, srtl->params);
		iter = SrtLNext((const sit_t)iter))
		{;}
		
	return (sit_t)DLLInsert(StripDLL(srtl), (it_t)SrtLPrev((const sit_t)iter), 
								(void *)new_data);	
}

sit_t SrtLErase(sit_t where)
{
	assert(NULL != where);
	
	return (sit_t)DLLErase((it_t)where);
}

void SrtLPopFront(srtl_t *srtl)
{	
	assert(NULL != srtl);
	assert(!SrtLIsEmpty(srtl));

	assert(NULL != StripDLL((srtl_t *)srtl));
	
	DLLPopFront(StripDLL((srtl_t *)srtl));
}

void SrtLPopBack(srtl_t *srtl)
{
	assert(NULL != srtl);

	assert(NULL != StripDLL((srtl_t *)srtl));
	
	DLLPopBack(StripDLL((srtl_t *)srtl));
}

sit_t SrtLFind(sit_t from, sit_t to, scmp_f IsFound, 
							const void *key, const void *params)
{
	assert(NULL != from && NULL != to && NULL != IsFound);
	
	return (sit_t)DLLFind((it_t)from, (it_t) to, IsFound, key, params);
}

int SrtLForEach(sit_t from, sit_t to, sact_f Action, const void *params)
{
	assert(NULL != from && NULL != to && NULL != Action);
	
	return DLLForEach((it_t)from, (it_t) to, Action, params);
}

sit_t SrtLBegin(const srtl_t *srtl)
{
	assert(NULL != srtl);

	assert(NULL != StripDLL((srtl_t *)srtl));
	
	return (sit_t)DLLBegin(StripDLL((srtl_t *)srtl));
}

sit_t SrtLEnd(const srtl_t *srtl)
{
	assert(NULL != srtl);

	assert(NULL != StripDLL((srtl_t *)srtl));
	
	return (sit_t)DLLEnd(StripDLL((srtl_t *)srtl));
}

sit_t SrtLNext(const sit_t iter)
{
	assert(NULL != iter);
	
	return (sit_t)DLLNext((const it_t)iter);
}

sit_t SrtLPrev(const sit_t iter)
{
	assert(NULL != iter);
		
	return (sit_t)DLLPrev((const it_t)iter);
}

void *SrtLGetData(const sit_t iter)
{
	assert(NULL != iter);
	
	return DLLGetData((const it_t)iter);
}

int SrtLIsSame(const sit_t iter1, const sit_t iter2)
{
	assert(NULL != iter1 && NULL != iter2);
	
	return DLLIsSameIter((const it_t)iter1, (const it_t)iter2);
}


void SrtLMerge(srtl_t *dest, srtl_t *src)
{
	sit_t where = NULL;
	sit_t from = NULL;
	sit_t to = NULL;
	sit_t end_dest = NULL;
	sit_t end_src = NULL;

	assert(NULL != dest && NULL != src);
	assert(src != dest);
	
	where = SrtLBegin((const srtl_t *)dest);
	end_dest = SrtLEnd(dest);
	end_src = SrtLEnd(src);

	from = SrtLBegin((const srtl_t *)src);
	to = SrtLNext(from);
	while(!SrtLIsEmpty(src) && SrtLEnd(dest) != where)
	{
		
		while(end_dest != where && (*dest->IsBefore)(SrtLGetData(from), 
									SrtLGetData(where),	dest->params))
		{
			where = SrtLNext(where);
		}
		
		if(end_dest == where)
		{
			to = end_src;
		}
		
		
		while(end_src != to	
		&& (*dest->IsBefore)(SrtLGetData(where), SrtLGetData(to), dest->params))
		{
			to = SrtLNext(to);
		}
		
		DLLSpliceBefore((it_t)where, (it_t)from, (it_t)to);
		
		from = to;
		to = SrtLNext(from);
	}
		
	SrtLDestroy(src);
}
