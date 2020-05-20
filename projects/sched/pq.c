/***********************************
Data Structure Priority Queue (PQ) - based on SrtL (that is based on DLL)
Auteur Andrei Plakhotta
Reviewer Daniel Meisel
***********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "pq.h" /* pq_t */

struct pq
{
 srtl_t *srtl;
};

/*typedef struct pq pq_t;*/
/*typedef int(*pqpriority_f)(const void *data, const void *new_data, const void *params);*/
/*typedef int(*pqcmp_f)(const void *data, const void *key, const void *params);*/

pq_t *PQCreate(pqpriority_f IsToPushBefore)
{
	pq_t *pq = NULL;
	
	assert(NULL != IsToPushBefore);
	
	if(NULL == (pq = (pq_t *)malloc(sizeof(*pq))))
	{
		return NULL;
	}
	if(NULL == (pq->srtl = SrtLCreate(IsToPushBefore, NULL)))
	{
		free(pq);
		
		return NULL;
	}
	
	return pq;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	assert(NULL != pq->srtl);
	
	SrtLDestroy(pq->srtl);
	free(pq);
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	
	assert(NULL != pq->srtl);
	
	return (SrtLEnd(pq->srtl) == SrtLInsert(pq->srtl, data)) ? 1 : 0;
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	assert(NULL != pq->srtl);
	
	return SrtLGetData(SrtLBegin(pq->srtl));
}


int PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->srtl);
	
	SrtLPopFront(pq->srtl);
	
	return 0;
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	assert(NULL != pq->srtl);
	
	return SrtLIsEmpty(pq->srtl);
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	assert(NULL != pq->srtl);
	
	return SrtLSize(pq->srtl);
}

void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while(!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

int PQErase(pq_t *pq, const void *key, pqcmp_f ShouldErase)
{
	sit_t found = NULL;
	sit_t end = NULL;
	
	assert(NULL != pq);
	assert(NULL != ShouldErase);
	
	assert(NULL != pq->srtl);
	
	end = SrtLEnd(pq->srtl);
	found = SrtLFind(SrtLBegin(pq->srtl), end, ShouldErase, key, NULL);
	if (end == found)
	{
		return 1;
	}
	SrtLErase(found);
	
	return 0;									
}
