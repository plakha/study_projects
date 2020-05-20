/******************************************************************************
Author: Andy Plakhota
Date: 12/5/2019

Description: 
Return value is the place of the las soldier alive ( 0 to n-1 ). If failed, returns -1.
******************************************************************************/

#include <stdio.h>/*printf in test*/
#include <assert.h>/*assert in debug mode*/
#include <stdlib.h>/*malloc*/

void FillCompany(int *company, int n);
int Kill(int *company);
int LastSoldier(int n);

int main()
{
	printf("\n%d\n", LastSoldier(3));
	return 0;
}


int LastSoldier(int n)
{
	int *company = NULL;
	int res = -1;
	
	if(n<1)
	{
		return -1;
	}
	
	company = (int *)malloc(n * sizeof(int));
	if(NULL == company)
	{
		
		return -1;
	}

	FillCompany(company, n);
	res = Kill(company);
	
	free(company);	
	
	return res;
}

void FillCompany(int *company, int n)
{
	size_t i = 0;

	for(; (int)i < n - 1; ++i)
	{
		company[i] = (int)i + 1; 
		printf("%d", (int)i + 1);
	}
	company[n-1] = 0;
}

int Kill(int *company)
{
	int i = 0;	
	
	while(i != company[i])
	{
		company[i] = company[company[i]];
		i = company[i];
	}
	
	return i;
}

