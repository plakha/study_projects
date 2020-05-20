#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc */
#include <limits.h> /* UCHAR_MAX */
#include <string.h> /* strcmp */

#include "hash.h" /* pq_t */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \

enum status {OK = 0, FAIL};
enum truthvalue {FALSE = 0};

#define RANGE (12)
#define BIRTHDAY_LEN (14)
const int birthdays[] = {1701, 1805, 2802, 2407, 508, 702, 1810, 401, 308, 709,
						 210, 103, 603, 1810};
						 
int IsSame(const void *data1, const void *data2)
{
	return *(int *)data1 == *(int *)data2;
}

int Print(void *data, const void *params)
{
	(void)params;
	printf("%d\n", *(int *)data);
	
	return OK;
}

/* tha data is birthday (e.g. 0811 for the 8th of November. 
The hash value is the month: data 0811 -> hash value 11 */
size_t HashFunc(void *data)
{
	return *(int *)data % 100;
}
static int TestSimple()
{
	int ret = OK;
	size_t range = RANGE;
	hash_t *hash = HashCreate(IsSame, HashFunc, range);
	if (NULL == hash)
	{
		return FAIL;
	}
	
	if (!HashIsEmpty(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}	
	if (0 != HashSize(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}
	if (0 != HashLoad(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}
	if (0 != HashSD(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}
	/******end empty table *********/
	
	if (0 != HashInsert(hash, (void *)birthdays))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}
	if (HashIsEmpty(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}	
	if (1 != HashSize(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}
	if (birthdays != HashFind(hash, (void *)birthdays))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}
	HashForEach(hash, Print, NULL);
	if (1.0 / 12 != HashLoad(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}
	HashRemove(hash, (void *)birthdays);
	if (!HashIsEmpty(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}	
	HashDestroy(hash);
	
	return ret;
}

static int TestInsert()
{
	size_t i = 0;
	int ret = OK;
	size_t range = RANGE;
	hash_t *hash = HashCreate(IsSame, HashFunc, range);
	
	for (; BIRTHDAY_LEN > i; ++i)
	{
		HashInsert(hash, (int *)birthdays + i);
	}
	if (HashIsEmpty(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}
	if (BIRTHDAY_LEN != HashSize(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}
	HashForEach(hash, Print, NULL);
	if (BIRTHDAY_LEN != HashSize(hash))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}
	for (i = 0; BIRTHDAY_LEN > i; ++i)
	{
		HashRemove(hash, (int *)birthdays + i);
		if (BIRTHDAY_LEN - 1 - i != HashSize(hash))
		{
			printf("hash size: %lu\n", HashSize(hash));
			printf("%d ##FAIL##\n", __LINE__);
			ret = FAIL;
		}
		
	}
	HashDestroy(hash);
	return ret;
}

#undef BIRTHDAY_LEN
#undef RANGE

int SPrint(void *data, const void *params)
{
	(void)params;
	printf("%s\n", (char *)data);
	
	return OK;
}

static size_t HashStr(void *data)
{
	size_t hash = 0;
	char *str = (char* )data;
	
	for(hash = 0; '\0' != *str; ++str)
	{
		hash = *str + 31 * hash;
	}
	
	return hash;
}

static int IsSameEntry(const void *data, const void *key)
{
	return 0 == strcmp((const char *)data, (const char *)key);
}
#define MAX_DIC_ENTRY_LEN (47)
#define N_ENTRIES_DIC (102305)
#define RANGE (31)

int TestDictionary()
{
	char **dic = NULL;
	int ret = OK;
	size_t i = 0;
	FILE *file = NULL;
	char *holder = NULL;
	hash_t * hash_table = NULL;
	
	/* alloc */
	dic = (char **)calloc(N_ENTRIES_DIC + 1, sizeof (*dic));
	if (!dic)
	{
		printf("calloc %d ##FAIL##\n", __LINE__);
		return FAIL;
	}
	for (i = 0; N_ENTRIES_DIC > i; ++i)
	{
		dic[i] = (char *)calloc(MAX_DIC_ENTRY_LEN, sizeof (*dic[i]));
		if (!dic[i])
		{
			printf("calloc %d ##FAIL##\n", __LINE__);
			for (; 0 < i; --i)
			{
				free(dic[i]);
			}
			free(dic[i]);
			free(dic);
			
			return FAIL;
		}
	}
	hash_table = HashCreate(IsSameEntry, HashStr, RANGE);
	if (!hash_table)
	{
		printf("%d ##FAIL##\n", __LINE__);
		for (i = 0; N_ENTRIES_DIC  > i; ++i)
		{
			free(dic[i]);
		}
		free(dic);
		
		return  FAIL;
	}
	file = fopen("/usr/share/dict/words", "r");
	if (!file)
	{
		printf("calloc %d ##FAIL##\n", __LINE__);
		for (i = 0; N_ENTRIES_DIC  > i; ++i)
		{
			free(dic[i]);
		}
		free(dic);
		HashDestroy(hash_table);
		
		return FAIL;
	}
	
	/* end alloc */
	
	for (i = 0; N_ENTRIES_DIC > i; ++i)
	{
		holder = fgets(dic[i], MAX_DIC_ENTRY_LEN, file);
		if (!holder)
		{
			break;
		}
	}
	fclose(file);
	
	for (i = 1; N_ENTRIES_DIC > i; ++i)
	{
		HashInsert(hash_table, dic[i]);
	}
	printf("%lu\n", HashSize(hash_table));	
	/* HashForEach(hash_table, SPrint, NULL); */
	
	if (HashFind(hash_table, "presumptuousfewfness\n"))
	{
		printf("%d ##FAIL##\n", __LINE__);
		ret = FAIL;
	}	
	
	for(i = 0; N_ENTRIES_DIC > i; ++i)
	{
		if (!HashFind(hash_table, "presumptuousness\n"))
		{
			printf("%d ##FAIL##\n", __LINE__);
			ret = FAIL;
		}	
	}
	/* free */
	HashDestroy(hash_table);
	for (i = 0; N_ENTRIES_DIC  > i; ++i)
	{
		free(dic[i]);
	}
	free(dic);

	return ret;
}

int main()
{
	RUN_TEST(TestSimple);
	RUN_TEST(TestInsert);
	RUN_TEST(TestDictionary);
	return 0;
}
	
	
	
	
	
