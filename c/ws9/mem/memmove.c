
#include "mem.h"

#include <stddef.h> /* sizeof */
#include <assert.h> /* assert */

#define WORD_SIZE 8

void *Memmove(void *dest, const void *src, size_t n)
{
	char *run_d = dest;
	char *run_s = (char *)src;
	char *first_word_d = (char *)dest + (WORD_SIZE - (long)dest % WORD_SIZE);
	char *end_d = (char *)dest + n - 1;
	char *tail_d = end_d - (long)dest % WORD_SIZE;
	char *end_s = (char *)src + n -1;

	assert(NULL != src && NULL != dest);
	
	if((char *)dest >= (char *)src && (char *)dest <= end_s)	
	{
		run_d = end_d;
		run_s = end_s;

		while(run_d >= tail_d && run_d >= (char *)dest)
		{
			*run_d = *run_s;
			--run_s;
			--run_d;
		}
		while(run_d < tail_d && run_d >= first_word_d)
		{
			*(size_t *)run_d = *(size_t *)run_s;
			run_s -= WORD_SIZE;
			run_d -= WORD_SIZE;
		}
		while(run_d >= (char *)dest)
		{
			*run_d = *run_s;
			--run_s;
			--run_d;
		}

		return dest;
	}
	else
	{

		return Memcpy(dest, src, n);
	}
}
