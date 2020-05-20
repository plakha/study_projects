#include <string.h> /* strlen */
#include <assert.h> /* assert */

static float PowPos (float x, int y)
{
	int counter = 0;
	float result = 1.0;
	for (counter = 0; counter < y; ++counter)
	{
		result *= x;
	}

	return result;
}

static float Power (float x, int y)
{
	if (x >= 0)
	{

		return PowPos(x, y);
	}

	return 1/PowPos(x, (-1) * y);
}

static void Swap(char *c1, char *c2)
{
	char hold = *c1;
	*c1 = *c2;
	*c2 = hold;
}

static char *InvertStr(char *left, char *right)
{
	char *run_left = left;
	char *run_right = right;
	
	while(run_left < run_right)
	{
	Swap(run_left, run_right);
	++run_left;
	--run_right;
	}

	return left;
}

char *ItoA10(char *s, unsigned int n)
{
	char *run = s;

	while(n > 0)
	{
		*run = (n % 10) + '0' ;
		n /= 10; 
		++run;
	}
	*run = '\0';
	
	return InvertStr(s, run - 1);
}

int AtoI10(const char *s)
{
	unsigned int len = strlen(s);
	const char *end = s + len - 1;
	unsigned int n = *end - '0';
	
	do
	{
	--end;
	n += (*end - '0') * 10 * (len - 1 - (long)end + (long)s);
	}
	while(end > s);

	return n;
}

static const char digits_lut[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', 
	'9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};

char *ItoA(char *s, unsigned int n, unsigned int base)
{
	char *run = s;
	
	assert (0 != base);

	while(n > 0)
	{
		*run = digits_lut[n % base];
		n /= base; 
		++run;
	}
	*run = '\0';
	
	return InvertStr(s, run - 1);
}

int AtoI(const char *s, unsigned int base)
{
	unsigned int len = strlen(s);
	const char *end = s + len - 1;
	unsigned int n = (long)strchr(digits_lut, *end) - (long)digits_lut;
	
	do
	{
	--end;
	n += ((long)strchr(digits_lut, *end) - (long)digits_lut) * Power(base, len - 1 - (long)end + (long)s);
	}
	while(end > s);

	return n;
}
