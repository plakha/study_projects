#include <stdio.h> /* printf for test*/
#include <string.h> /* strcmp for test */
#include <stdlib.h>/* malloc for test */
#include <errno.h> /* perror for test */

#include <stddef.h> /* sizeof */
#include <assert.h> /* assert */

#define WORD_SIZE 8

void *Memmove(void *dest, const void *src, size_t n);

int main()
{
	char s[] = "123456789A";

	Memmove(s + 1, s, 9);

	puts(s + 1);
	
	return 0;
}

int TestMemmove()
{
	char s[] = "123456789A";

	Memmove(s + 1, s, 9);
	if(0 != strcmp(s, "123456789A"))
	{

		return 1;
	}

	Memmove(s + 1, s, 9);
	if(0 != strcmp(s + 1, "123456789"))
	{

		return 1;
	}


	
	return 0;
}

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
	}
	else
	{
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
	}
	return dest;
}
