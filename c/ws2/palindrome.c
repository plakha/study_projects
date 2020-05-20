#include <stdio.h>
#include <string.h>

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \
	return IsPalindrome("1a2s2a1");

int IsPalindrome(const char *str);
int TestIsPalindrome();

int main()
{
	RUN_TEST(TestIsPalindrome)
}

int TestIsPalindrome()
{
	return IsPalindrome("123aa321");
}

int IsPalindrome(const char *str)
{
	const char *left = str;
	const char *right = str + strlen(str) - 1;
	int ret = 0;
	while( (left <= right) 
			&& (*left == *right) )
	{		
		++left;
		--right;
	}
	if(left < right)
	{
		ret = 1;
	}	

	return ret;
}
