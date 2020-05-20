#include <stdio.h>
#include <math.h>

void BoomSeven(int from, int to);
int IsDivisible(int num, int divisor);
int HasDigit(int num, int digit);

int main()
{

	BoomSeven(78, 1);
	return 0;
}

void BoomSeven(int from, int to)
{
	const int seven = 7;
	if(from > to)
	{
		BoomSeven(to, from);
	}
	while(from <= to)
	{
		if( IsDivisible(from, seven) || HasDigit(from, seven))
		{
			printf("BOOM ");
		}
		else
		{
			printf("%d ", from);
		}
		++from;
	}	
	printf("\n");
}

int IsDivisible(int num, int divisor)
{
	if (0 == divisor)
	{
		return 0;/*forbidden division by 0*/
	}
	return (0 == (num % divisor));/*0 if is not divisible by divisor*/
}

/*Doesn't work for digit = 0*/
int HasDigit(int num, int digit)
{
	int tail = num % 10;
	const int ten = 10;
	if( (digit < 0) || (digit > 9 ) )/*no such digit*/
	{
		return 0;
	}
	
	while (num > 0)
	{
		if( digit == tail )
		{	
			return 1;/*has digit 7*/
		}
		num /= ten; 
		tail = num % ten; 
	}
	
	return 0;/*digit not found*/
}

