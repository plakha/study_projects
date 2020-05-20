/****

***/

#include <stdio.h> /* printf for test*/
#include <string.h> /* memset int test */
#include <stdlib.h>/* malloc for test */

#include <assert.h> /* assert */
#include <errno.h> /* perror */

void *Memset(void *s, int c, size_t n)
{
	
	assert(NULL != s);
	if(0 == n)
	{
		return s;
	}
		
	return s;
}

int main()
{
	void *s = NULL;
	size_t len = 0;
	size_t i = 0; 

	if(NULL == (s = malloc(len)))
	{
		perror("Can't allocate memory ");
	}
	
	printf("%lu\n", s);

	for(i = 0; i <= len; ++i)
	{
		printf("1 %d\n", *((char *)s + i));
	}
	
	 *(char *)s = 1;

	for(i = 0; i <= len; ++i)
	{
		printf("2 %d\n", *((char *)s + i));
	}
		
	free(s);

	for(i = 0; i <= len; ++i)
	{
		printf("3 %d\n", *((char *)s + i));
	}

		printf("%lu\n", s);

	*((char *)s) = 2;

	for(i = 0; i <= len; ++i)
	{
		printf("4 %d\n", *((char *)s + i));
	}

	return 0;
}
