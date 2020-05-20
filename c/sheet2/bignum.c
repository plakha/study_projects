#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>



int ChToNum(char c);
char NumToCh(int n);
char *AddBigNum(const char *num1, const char *num2, char *res);

int main()
{
	char *res = (char *)malloc(4);
	char num1[] = "189";
	char num2[] = "911";
	res = AddBigNum(num1, num2, res);
	printf ("%s\n", res); 
	return 0;
	
}
/*The digit are placed in string left to right! E.g. 128 will be "821", striing of sane lenghth*/
char *AddBigNum(const char *num1, const char *num2, char *res)
{
	const char *runner_num1 = num1;
	const char *runner_num2 = num2;
	char *runner_res = res;
	int remain = 0;
	int sum_digits = 0;

	/*add until the shorter num is "over"*/	
	do
	{
		sum_digits = ChToNum(*runner_num1) + ChToNum(*runner_num2) + remain;
		if(sum_digits >= 10)
		{
			remain = 1;
			sum_digits -= 10;
		}
		else
		{
			remain = 0;
		}
		*runner_res = NumToCh(sum_digits);
		++runner_res;
		++runner_num1;
		++runner_num2;
	}
	while( ('\0' != *runner_num1) && ('\0' != *runner_num2) );
	
	*runner_res = NumToCh(remain);	
	++runner_res;
	*runner_res = '\0';	
	
	return res;
}

int ChToNum(char c)
{

	return (c - '0');
}

char NumToCh(int n)
{

	return (n + '0');
}
