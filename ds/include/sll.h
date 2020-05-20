/* In the world of iterator - return end-iterator for failure */
/* tail is exclusi*/
/*
typedef struct node
{
	void *data;
	struct node *next;
}node_t;

struct sll
{
	node_t *head;
	node_t *tail;
}
*/

#include <stddef.h> /* size_t */

typedef struct node *it_t;
typedef struct sll sll_t;

typedef int (*act_f)(void *data, const void *param);
typedef int (*cmp_f)(const void *data, const void *keyword);

sll_t *SLLCreate();

void SLLDestroy(sll_t *sll);

/* Return end-iterator if failed. Return iterator of inserted data */
it_t SLLInsertAfter(sll_t *sll, it_t i, const void *data);


void SLLPopFront(sll_t *sll);


void SLLPopBack(sll_t *sll);

/* Return end-iterator if failed . Return iterator of inserted data*/
it_t SLLPushFront(sll_t *sll, const void *data);

/* Return end-iterator if failed. Return iterator of inserted data */
it_t SLLPushBack(sll_t *sll, const void *data);


it_t SLLBegin(const sll_t *sll);


it_t SLLEnd(const sll_t *sll);


it_t SLLNext(it_t i);

/* "to" iterator exclusive. If not found return to. 
Compare function is boolean - return TRUE if found */
it_t SLLFind(it_t from, it_t to, const void *keyword, cmp_f is_found);


void *SLLGetData(it_t i);

/* "to" iterator exclusive. Return the act_f return value. O for success. 
Stop execution if act_f fails. */
int SLLForEach(it_t from, it_t to, const void *param, act_f action);

/* if i doesn't belong to sll, crash may result */
void SLLErase(sll_t *sll, it_t i);


size_t SLLSize(const sll_t *sll);

/* return same sll or create new one or no matter ? */
sll_t *SLLFlip(sll_t *sll);


int SLLIsEmpty(const sll_t *sll);

/* Advanced, for bug squashing */
int HasLoop(const sll_t *sll);

/* Advanced, for bug squashing. If found, return the iterator. 
If not found, return end of sll1. */
it_t FindIntersection(const sll_t *sll1, const sll_t *sll2);

