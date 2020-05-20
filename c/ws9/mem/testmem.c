#include "mem.h"

#include <stdio.h> /* printf for test*/
#include <string.h> /* memset int test */
#include <stdlib.h>/* malloc for test */
#include <errno.h> /* perror for test */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \

int TestMemset();
int TestMemcpy();
int TestMemmove();

int main()
{
	RUN_TEST(TestMemset);
	RUN_TEST(TestMemcpy);
	RUN_TEST(TestMemmove);

	return 0;
}

int TestMemset()
{
	int i = 0;
	char s[5];
	
	Memset(s, 'a', 5);	
	for(; i < 5; ++i)
	{	
		if('a' != s[i])
		{

			return 1;
		}
	}

	Memset(s + 1, 'b', 4);	
	for(i = 1 ; i < 5; ++i)
	{	
		if('b' != s[i])
		{

			return 1;
		}	
	}	
	
	return 0;
}

int TestMemcpy()
{
	char *dest = malloc(16);
	char *src = "123456789A";
	
	Memcpy(dest + 1, src + 1, 10);
	if(0 != strcmp(dest +1, src + 1))
	{

		return 1;
	}
	Memcpy(dest, src + 1, 10);
	if(0 != strcmp(dest, src + 1))
	{

		return 1;
	}
	Memcpy(dest, src, 11);
	if(0 != strcmp(dest, src))
	{

		return 1;
	}

	Memcpy(dest, src + 8, 3);
	if(0 != strcmp(dest, src + 8))
	{

		return 1;
	}

	free(dest);
	
	return 0;
}

int TestMemmove()
{
	char s[] = "123456789A";

	Memmove(s, s, 11);
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
