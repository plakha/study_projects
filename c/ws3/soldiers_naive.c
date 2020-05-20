/******************************************************************************
Author: Andy Plakhota
Date: 12/5/2019

Description: 
Return value is the place of the las soldier alive ( 0 to n-1 ). If failed, returns -1.
******************************************************************************/

#include <stdio.h>/*printf in test*/
#include <assert.h>/*assert in debug mode*/
#include<stdlib.h>/*malloc*/

char *FindKill(char *killer, char *company);
char *FindLive(char *victim, char *company);
void FillWithL(char *str, size_t length);
int LastSoldier(int n);

int main()
{
	int res = LastSoldier(0);
	printf("\n%d\n", res);
	
	return 0;
}


int LastSoldier(int n)
{
	int res = -1;
	char *company = NULL;
	char *has_sword = company+1;
	char *victim = company;
	char *next = company;
	
	assert( 0 < n);
	if(1 == n)
	{
		
		return 0;
	}
	
	company = (char *)malloc((n + 1) * sizeof(char));
	if(NULL == company)
	{

		return -1;
	}

	has_sword = company+1;
	victim = company;
	next = company;
	
	
	FillWithL(company, n);
	
	while(next != has_sword)
	{
		has_sword = next;
		victim = FindKill(has_sword, company);
		next = FindLive(victim, company);
	}
	
	res = (int)(has_sword - company);
	free(company);

	return res;
}

char *FindLive(char *victim, char *company)
{	
	char *next = victim;

	while('d' == *next)
	{
		++next;

		if('\0' == *next)
		{
			next = company;
		}
	}

	return next;
	
}

char *FindKill(char *killer, char *company)
{
	char *victim = killer + 1;
	
	if('\0' == *victim)
		{
			victim = company;
		}

	while('d' == *victim)
	{		
		if('\0' == *victim)
		{
			victim = company;
		}	
		++victim;
	}
	*victim = 'd';
	
	return victim;
}


void FillWithL(char *str, size_t length)
{
	size_t i = 0;	

	for(; i < length; ++i)
	{
		*(str + i) = 'l';
	}
	*(str + i) = '\0';
}
