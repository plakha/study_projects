/******************************
15/7/2019
Recursive int Mergesort

21/7
QSort, HeapSort, BinarySearch, JumpSearch
Reviewer - Alex
*******************************/

#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <sys/types.h> /* ssize_t */
#include <limits.h> /* LONG_MAX */
#include <math.h> /* sqrt */

#include "sorts.h"

#define TWO (2.0)

enum status 
{
	OK = 0,
	FAIL
};

enum heapchild
{
	LEFT = 0,
	RIGHT
};

typedef int (*cmp_f)(const int *const, const int *const);

static int CmpAsc(const int *const this, const int *const that)
{
	return *this - *that;
}

static int CmpDsc(const int *const this, const int *const that)
{
	return *that - *this;
}

static const cmp_f Compare[2] = {&CmpAsc, &CmpDsc};

size_t CalcPivotIndex(const int arr[], size_t n_membs)
{
	assert(n_membs);
	(void)arr;
	
	return rand() % n_membs;
}

static void Swap(int *a, int *b)
{
	int holder = *a;
	*a = *b;
	*b = holder;
}

/* holder has len1 + len2 allocated */
static void Merge(int *arr1, size_t len1, int *arr2, size_t len2, int *holder)
{
	if (0LU == len1 && 0LU == len2)
	{
		return ;
	}
	if (0LU == len2)
	{
		memcpy(holder, arr1, len1 * sizeof(int));
		
		return;
	}
	if (0LU == len1)
	{
		memcpy(holder, arr2, len2 * sizeof(int));
		
		return ;
	}
	if (*arr1 < *arr2)
	{
		*holder = *arr1;
		Merge(arr1 + 1, len1 - 1, arr2, len2, holder + 1);
	}
	else 
	{
		*holder = *arr2;
		Merge(arr1, len1, arr2 + 1, len2 - 1, holder + 1);
	}
}

int MergeSort(int *arr, size_t len)
{
	int *holder = NULL;
	int status = OK;
	
	assert(arr);

	if (2 > len)
	{
		return OK;
	}
	
	status = MergeSort(arr, len / 2);
	if (OK != status)
	{
		return status;
	}
	
	status = MergeSort(arr + len / 2,  len - len / 2);
	if (OK != status)
	{
		return status;
	}
	
	holder = (int *)malloc(len * sizeof(int));
	if (NULL == holder)
	{
		return 1;
	}
	
	Merge(arr, len / 2, arr + len / 2, len - len / 2, holder);
	memcpy(arr, holder, len * sizeof(int));
	free(holder);
	holder = NULL;
	
	return status;
}

/* Cormen algorithm */
static size_t QPartition(int arr[], size_t n_membs, enum direction dir)
{
	size_t i = ~0x0; /*-1LU;*/ /* well defined arithmetic underflow, it is for the flow*/
	size_t j = 0LU;
	size_t pivot = n_membs - 1;

	assert(1LU < n_membs);

	for (; j < n_membs; ++j)
	{
		if (0 >= (Compare[dir])(arr + j, arr + pivot))
		{
			++i;
			Swap(arr + i, arr + j);
		}
	}
	
	assert(n_membs > i);

	return i;
}

void QuickSort(int arr[], size_t n_membs, enum direction dir)
{
	size_t pivot = n_membs - 1;
	
	assert(arr);

	if (2 > n_membs)
	{
		return ;
	}

	pivot = CalcPivotIndex(arr, n_membs);
	Swap(arr + n_membs - 1, arr + pivot);
	pivot = QPartition(arr, n_membs, dir);
	QuickSort(arr, pivot++, dir);
	QuickSort(arr + pivot, n_membs - pivot, dir);
}

static size_t CalcHeapChild(size_t parent, enum heapchild side)
{
	assert(LEFT == side || RIGHT == side);
	
	return 2 * parent + 1 + side;
}

static void HeapifyDown(int arr[], size_t n_memb, 
						ssize_t traveler, enum direction dir)
{
	const ssize_t last_parent = n_memb / 2 - 1;
	size_t wanted_child = LONG_MAX; /* just an illegal value */
	
	while (last_parent >= traveler)
	{
		wanted_child = CalcHeapChild(traveler, LEFT);
		if (n_memb > CalcHeapChild(traveler, RIGHT))
		{
			wanted_child = (0 < ((Compare[dir])(arr + wanted_child + LEFT, 
			                                   arr + wanted_child + RIGHT))) 
			             ? (wanted_child + LEFT) 
			             : (wanted_child + RIGHT);
		}
		
		if (0 < (Compare[dir])(arr + wanted_child, arr + traveler))
		{
			Swap(arr + wanted_child, arr + traveler);
			traveler = wanted_child;
		}
		else
		{
			break ;
		}
	}
}

void HeapSort(int arr[], size_t n_membs, enum direction dir)
{
	ssize_t parent = n_membs / 2 - 1;
	int i = 0;
	
	for (; 0 <= parent; --parent)
	{
		HeapifyDown(arr, n_membs, parent, dir);
	}

	for (i = n_membs - 1; i > 0; --i)
	{
		Swap(arr, arr + i);
		HeapifyDown(arr, i, 0, dir);
	}
}

static const int *UtilBinarySearch(const int key, const int arr[], 
                                   size_t n_membs, const enum direction dir)
{
	size_t middle = n_membs / 2;
	int cmp = 0;
	
	if (!n_membs)
	{
		return NULL;
	}
	
	cmp = (Compare[dir])(arr + middle, &key);
	if (!cmp)
	{
		return arr + middle;
	}
	if (0 > cmp)
	{
		++middle;
		
 		return UtilBinarySearch(key, arr + middle, n_membs - middle, dir);
 	}

    return UtilBinarySearch(key, arr, middle,  dir);
}

/* returns boolean "Is Found ?" */
int BinarySearch(const int arr[], int key, size_t n_membs, size_t *found_index)
{
	const int *found = NULL;
	enum direction dir = ASC;
	
	assert(arr);
	
	found = UtilBinarySearch(key, arr, n_membs, dir);
	*found_index = found - arr;
	
	return NULL != found;
}

static const int *UtilLinearSearch(const int key, const int arr[],
                                   const size_t n_membs, 
                                   const enum direction dir)
{
    size_t i = 0LU;
    
    for (; n_membs > i; ++i)
    {
        if (0 == (Compare[dir](arr + i, &key)))
        {
            return (arr + i);
        }
    }
    
    return NULL;
}

static const int *UtilJumpSearch(const int key, const int arr[], 
							     const size_t n_membs, const enum direction dir)
{
	size_t skip = sqrt(n_membs);
	size_t i = 0LU;
	
	for (; n_membs > i && 0 > (Compare[dir])(arr + i, &key); i += skip)
	{;}
	
	i -= skip;
	
	return (UtilLinearSearch(key, arr + i, n_membs - i, dir));
	
}

int JumpSearch(const int arr[], int key, size_t n_membs, size_t *found_index)
{
	const int *found = NULL;
	enum direction dir = ASC;
	
	assert(arr);
	
	found = UtilJumpSearch(key, arr, n_membs, dir);
	*found_index = found - arr;
	
	return NULL != found;
}
