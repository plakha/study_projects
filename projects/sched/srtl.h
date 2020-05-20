/* Please only input Sorted List created with SrtlCreate */
#ifndef SRTL_H
#define SRTL_H

#include "dll.h"

/*old
  typedef int (*scmp_f)(const void *data,const void  *key, const void *param);*/
/*typedef int (*sact_f)(void *data, const void  *param);*/
/*typedef struct srtl srtl_t;*/

typedef int (*scmp_f)(const void *data, const void *key, const void *params);

/* TODO 'key' is switched to 'new_data' in context of IsBefore.  pseudo new function pointer header */
typedef int (*isbefore_f)(const void *data, const void *new_data, const void *params); 

typedef int (*sact_f)(void *data, const void *params);

typedef struct srtl srtl_t;
typedef it_t sit_t;

/*struct srtl
{
    dll_t *list;
    isbefore_f IsBefore; 
    const void *params;
}
*/

srtl_t *SrtLCreate(isbefore_f IsBefore, const void *params);


void SrtLDestroy(srtl_t *srtl);

size_t SrtLSize(const srtl_t *srtl);

int SrtLIsEmpty(const srtl_t *srtl);
 
sit_t SrtLInsert(srtl_t *srtl, void *data);

/*returns the node after the one removed*/ 
sit_t SrtLErase(sit_t where); 

void SrtLPopFront(srtl_t *srtl);

void SrtLPopBack(srtl_t *srtl);

sit_t SrtLFind(sit_t from, sit_t to, scmp_f IsFound, const void *key, 															const void *params);
/*old sit_t SrtLFind(sit_t from, sit_t to, scmp_f compare, const void *params, const void *key); */

/* returns 0 on success, Don't change the sorting field */
int SrtLForEach(sit_t from, sit_t to, sact_f Action, const void *params); 
sit_t SrtLBegin(const srtl_t *srtl);
sit_t SrtLEnd(const srtl_t *srtl);

/* do not pass SrtLEnd ("end of srtl") as 'iter' */
sit_t SrtLNext(const sit_t iter); 

/* do not pass SrtLBein ("start of srtl") as 'iter' */
sit_t SrtLPrev(const sit_t iter); 
void *SrtLGetData(const sit_t iter);
int SrtLIsSame(const sit_t iter1, const sit_t iter2);
void SrtLMerge(srtl_t *dest, srtl_t *src); /* 2 Lists with the same params */

#endif
