/******************************************
			17/7/2019
            Class: OL69
            Exersice: Hash Table
            Author Andrei
            Reviewer Michel
******************************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <limits.h> /* ULONG_MAX */
#include <math.h> /* pow */

#include "hash.h" /* hash_t */
#include "dll.h" /* it_t */

#define TWO (2.0)

struct hash
{
	dll_t **table;
	size_t range;
	int (*IsSame)(const void *data, const void *key);
	size_t (*HashFunc)(void *key);
}; /* typedef struct hash hash_t; */

enum status {OK = 0, FAIL};
enum truthvalue {FALSE = 0} ;

static int FillTable(dll_t **arr, const size_t len)
{
	int flag_to_destroy = FALSE;
	size_t i = 0;
	
	for(; i < len; ++i)
	{
		arr[i] = DLLCreate();
		if (!arr[i])
		{
			flag_to_destroy = 1;
			break ;
		}
	}
	
	switch (flag_to_destroy)
	{
		case FALSE:
			break ;
		default :
		for (; i > 0; --i)
		{
			DLLDestroy(arr[i]);
			arr[i] = NULL;
			
		}
		assert(0 == i);
		DLLDestroy(arr[i]);
	}
	
	return FALSE == flag_to_destroy ? OK : FAIL;
}

hash_t *HashCreate(int (*IsSame)(const void *data, const void *key), 
					size_t (*HashFunc)(void *key), 
					size_t range)
{
	hash_t *hash = NULL;
	int status = OK;
	
	assert(IsSame);
	assert(HashFunc);
	assert(0 < range);
	
	hash = (hash_t *)malloc(sizeof(*hash));
	if (!hash)
	{
		return NULL;
	}
	
	hash->table = (dll_t **)malloc(range * sizeof(*(hash->table)));
	if (!hash->table)
	{
		free(hash);
		hash = NULL;
		
		return NULL;
	}

	status = FillTable(hash->table, range);
	if (OK != status)
	{
		free(hash->table);
		hash->table = NULL;
		free(hash);
		hash = NULL;
	}
	
	hash->range = range;
	hash->IsSame = IsSame;
	hash->HashFunc = HashFunc;
	
	return hash;
}


void HashDestroy(hash_t *hash)
{
	size_t i = 0;
	
	assert(hash);
	
	for (; i < hash->range; ++i)
	{
		DLLDestroy(hash->table[i]);
		hash->table[i] = NULL;
	}
	
	free(hash->table);
	hash->table = NULL;
	
	free(hash);
	hash = NULL;
}

int HashInsert(hash_t *hash, void *data)
{
	size_t hash_value = ULONG_MAX;
	it_t end  = NULL;
	
	assert(hash);
	
	hash_value = hash->HashFunc(data) % hash->range;
	end = DLLEnd(hash->table[hash_value]);
	if (DLLIsSameIter(DLLPushFront(hash->table[hash_value], data), end))
	{
		return FAIL;
	}
	
	return	OK;
}

static int DLLIsFound(const void *data, const void *key, const void *params)
{
	return ((hash_t *)params)->IsSame(data, key); 
}

void HashRemove(hash_t *hash, void *key)
{
	size_t hash_value = ULONG_MAX;
	it_t found = NULL;
	it_t end = NULL;
	it_t begin = NULL;
	
	assert(hash);
	assert(key);
	
	hash_value = hash->HashFunc(key) % hash->range;
	begin = DLLBegin(hash->table[hash_value]);	
	end = DLLEnd(hash->table[hash_value]);
	found = DLLFind(begin, end, &DLLIsFound, key, hash);
	if (!DLLIsSameIter(end, found)) /* if found */
	{
		DLLErase(found);
	}
}

void *HashFind(const hash_t *hash, void *key)
{
	size_t hash_value = ULONG_MAX;
	it_t found = NULL;
	it_t end = NULL;
	it_t begin = NULL;
	void *data = NULL;
	
	assert(hash);
	assert(key);
	
	hash_value = hash->HashFunc(key) % hash->range;
	begin = DLLBegin(hash->table[hash_value]);	
	end = DLLEnd(hash->table[hash_value]);
	found = DLLFind(begin, end, &DLLIsFound, key, hash);	
	if (DLLIsSameIter(end, found)) /* key not found */
	{
		return	NULL;
	}
	data = DLLGetData(found);

	/* caching: relocate found data to front, unless DLLInsert failed */
	/* TODO if (!IsSame(found, front)) -- that is if the data is already cached - don't go there */
	if (!DLLIsSameIter(end, DLLPushFront(hash->table[hash_value], data)))
	{
		DLLErase(found);
	}
	
	return data;	
}

size_t HashSize(const hash_t *hash)
{
	size_t size = 0;
	size_t i = 0;
	
	assert(hash);
	
	for (; i < hash->range; ++i)
	{
		size += DLLSize(hash->table[i]);
	}
	
	return size;
}

int HashIsEmpty(const hash_t *hash)
{
	size_t i = 0;
	int ret = 1;
	
	assert(hash);
	
	for (; i < hash->range; ++i)
	{
		ret = DLLIsEmpty(hash->table[i]);
		if (FALSE == ret)
		{
			return ret;
		}
	}
	
	return ret;
}

int HashForEach(hash_t *hash, 
				int(*Act)(void *data, const void *params), 
				const void *params)
{
	size_t i = 0;
	int status = OK;
	it_t from = NULL;
	it_t to = NULL;
	
	assert(hash);
	assert(Act);
	
	for (; i < hash->range; ++i)
	{
		from = DLLBegin(hash->table[i]);
		to = DLLEnd(hash->table[i]);
		status = DLLForEach(from, to, Act, params);
		switch (status)
		{
			case OK:
				break ;
			default :
				return status;
		}
	}
	
	return status;
}

double HashLoad(const hash_t *hash)
{
	assert(hash);
	assert(hash->range);
	
	return (double)HashSize(hash) / hash->range;
}

double HashSD(const hash_t *hash)
{
	double sum = 0.0;
	double aver = 0.0;
	size_t i = 0;
	
	assert(hash);
	
	aver = HashLoad(hash);
	for (; i < hash->range; ++i)
	{
		sum += pow(DLLSize(hash->table[i]) - aver, TWO);
	}
	
	return sqrt(sum / hash->range);
}
