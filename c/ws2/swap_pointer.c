#include <stdio.h>
#include <string.h>

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf("[OK]\n"); \
	} \
	else \
	{ \
		printf("[FAIL]\n"); \
	} \

int SwapPointers(int **p, int **q);
int TestSwapPointers();

int main()
{
	RUN_TEST(TestSwapPointers)

	return 0;
}

int SwapPointers(int **pp1, int **pp2)
{
	int *placehold = *pp1;
	*pp1 = *pp2;
	*pp2 = placehold;
	placehold = '\0';

	return 0;
}

int TestSwapPointers()
{
	int n1 = 45;
	int n2 = 100;
	int *p1 = &n1;
	int *p2 = &n2;
	char before[100];
	char after[100];
	sprintf(before, "Before %p %p\n", (void *)p1, (void *)p2);
	SwapPointers(&p1, &p2);
	sprintf(after, "After %p %p\n", (void *)p1, (void *)p2);
	if(!strcmp(before, after))
	{
	return 1;
	}
	return 0;
	 
}
