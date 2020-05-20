#include <stdlib.h>
#include <stdio.h>
#include <stddef.h> /* size_t */

#include "../include/stack.h"

typedef struct point
{
	double x;
	double y;
}point_t;

typedef struct city
{
	point_t location;
	unsigned long population;
}city_t;

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \

int TestPeek()
{
	stack_t *stack = STACKCreate(1, sizeof(int));
	if(NULL == stack)
	{
		perror("alloc failure: ");
		
		return 1;
	}

	if(NULL == STACKPeek(stack))
	{
		puts("Peek Underflow Check OK");
		STACKDestroy(stack);
		
		return 0;
	}

	puts("Peed Unferflow check FAIL");
	
	return 1;
}

int TestZeroSize()
{
	stack_t *stack = STACKCreate(1, sizeof(int));
	if(NULL == stack)
	{
		perror("alloc failure: ");
		
		return 1;
	}

	if(0 == STACKSize(stack))
	{	
		printf("0 elements pushed, size = %lu\n", STACKSize(stack));
		STACKDestroy(stack);

		return 0;
	}
	printf("wrong size %lu\n", STACKSize(stack));

	return 1;
}

int main()
{
	char num = 90;
	int inum = 2000;
	city_t York = {{5584541.564, -64649.5848}, 8000000000};
	stack_t *stack = NULL;

	puts("\nchar element");
	stack = STACKCreate(1, sizeof(char));
	printf("0 elements pushed, size = %lu\n", STACKSize(stack));
	if(0 != STACKPush(stack, &num))
	{
		puts("couldn't push an int - fail");
	}
	++num;
	printf("1 elements pushed, size = %lu\n", STACKSize(stack));
	if(0 != STACKPush(stack, &num))
	{
		puts("Check overflow - OK");
	}
	else
	{
		puts("overflowed - FAIL");
	}
	printf("Entered num %d, Peek %d\n", (num - 1), *(char *)STACKPeek(stack));
	STACKDestroy(stack);	
	
	puts("\nint element");
	stack = STACKCreate(1, sizeof(int));
	printf("0 elements pushed, size = %lu\n", STACKSize(stack));
	if(0 != STACKPush(stack, &inum))
	{
		puts("couldn't push an int - fail");
	}
	++inum;
	printf("1 elements pushed, size = %lu\n", STACKSize(stack));
	if(0 != STACKPush(stack, &inum))
	{
		puts("Check overflow - OK");
	}
	else
	{
		puts("overflowed - FAIL");
	}
	printf("Entered num %d, Peek %d\n", (inum - 1), *(int *)STACKPeek(stack));
	STACKDestroy(stack);	

	puts("\n struct element");
	stack = STACKCreate(1, sizeof(York));
	printf("0 elements pushed, size = %lu\n", STACKSize(stack));
	if(0 != STACKPush(stack, &York))
	{
		puts("couldn't push an int - fail");
	}
	printf("1 elements pushed, size = %lu\n", STACKSize(stack));
	if(0 != STACKPush(stack, &York))
	{
		puts("Check overflow - OK");
	}
	else
	{
		puts("overflowed - FAIL");
	}
	/*printf("Entered num %d, Peek %d\n", (inum - 1), *(int *)STACKPeek(stack));*/
	STACKDestroy(stack);	

	puts("");
	RUN_TEST(TestPeek);
	RUN_TEST(TestZeroSize);

	return 0;
}
