#include <stdio.h> /* printf */

#include "../include/calculator.h" /* bst header file */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \


int TestCalc()
{
	const char *expression1 ="(20-17*7^2+7/14)*(8-8.5)";
	const double real_res1 =  406.25;
	double res = 0;

	printf("\tExpression: %s\n", expression1);

	Calculate(expression1, &res);
        
	if(real_res1 != res)
	{
		printf("\tLine %d - Expected result %f, actual res %f\n", __LINE__, real_res1, res);
		return 1;
	}
	else
	{
		printf("\tResult: %.2f\n", real_res1);
		printf("\t--------------------\n");
	}
    

    return 0;
}

int main()
{
    RUN_TEST(TestCalc); 

    return 0;
}
