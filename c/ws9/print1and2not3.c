#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <errno.h> /* perror */
#include <stdlib.h> /* calloc */

int Print1and2not3(const char *a, const char *b, const char *x)
{
	int i = 0;
	int *print_lut = (int *)calloc(256, sizeof(int));
	if(NULL == print_lut)
	{
		perror("allocation error: ");

		return errno;
	}
	
	while('\0' != *a)
	{
		print_lut[(int)*a] = 1;
		++a;
	}	
	while('\0' != *b)
	{
		print_lut[(int)*b] *= 2;
		++b;
	}
	while('\0' != *x)
	{
		print_lut[(int)*x] = 0;
		++x;
	}

	for(; i <= 255; ++i)
	{
		if('\0' != print_lut[i])
		{
			putchar(i);
		}
	}
	putchar('\n');

	free(print_lut);	
	
	return 0;
}

char *a = "1aa2b3451";
char *b = "345ab61";
char *x = "0123bb";

int main()
{

	return Print1and2not3(a, b, x);
}
