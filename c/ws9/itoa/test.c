#include "itoa.h"

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */
#include <errno.h> /* perror */
#include <stdlib.h> /* malloc */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \

int TestItoA10();
int TestAtoI10();
int TestItoA();
int TestAtoI();

int main()
{
	RUN_TEST(TestItoA10); 
	RUN_TEST(TestAtoI10); 
	RUN_TEST(TestItoA); 
	RUN_TEST(TestAtoI); 

	return 0;
}

int TestItoA10()
{
	char a[10];
	if(0 == a)
	{
		perror("Allocation problem: ");

		return 1;
	}
	puts(ItoA10(a, 1230));

	return 0 != strcmp("1230", a);
}

int TestAtoI10()
{
	
	return 123 == AtoI10("123");
}

int TestItoA()
{
	char a[10];
	puts(ItoA(a, 17, 2));

	return 0 != strcmp(a, "10001");
}

int TestAtoI()
{
	char a[] = "10001";
	return !(17 == AtoI("10001", 2));
}

