/****

***/

#include <stddef.h> /* sizeof */
#include <assert.h> /* assert */

#define WORD_SIZE 8

void *Memcpy(void *dest, const void *src, size_t n)
{
	char *run_d = dest;
	const char *run_s = src;
	char *first_word_d = (char *)dest + (WORD_SIZE - (long)dest % WORD_SIZE);
	char *end_d = (char *)dest + n - 1;
	char *tail_d = end_d - (long)dest % WORD_SIZE;

	assert(NULL != src && NULL != dest);
			
	while(run_d < first_word_d && run_d <= end_d)
	{
		*run_d = *run_s;
		++run_s;
		++run_d;
	}

	while(run_d < tail_d)
	{
		*(size_t *)run_d = *(size_t *)run_s;
		run_s += WORD_SIZE;
		run_d += WORD_SIZE;
	}
	
	while(run_d <= end_d)
	{
		*run_d = *run_s;
		++run_s;
		++run_d;
	}
	
	return dest;
}
