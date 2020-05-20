/****

***/

#include <stddef.h> /* sizeof */
#include <assert.h> /* assert */

#define WORD_SIZE 8

void *Memset(void *s, int c, size_t n)
{
	char *run_s = s;
	char *first_word = (char *)s + (WORD_SIZE - (long)s % WORD_SIZE);
	char *end = (char *)s + n - 1;
	char *tail = end - (long)s % WORD_SIZE;
	long word = c;	
	
	assert(NULL != s);
			
	word = (word << 8) | word;
	word = (word << 16) | word;
	word = (word << 32) | word;

	while(run_s < first_word && run_s <= end)
	{
		*run_s = c;
		++run_s;
	}

	while(run_s < tail)
	{
		*(size_t *)run_s = word;
		run_s += WORD_SIZE;
	}
	
	while(run_s <= end)
	{
		*(char *)run_s = c;
		++run_s;
	}
	
	return s;
}

