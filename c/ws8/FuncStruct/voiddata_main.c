/*******************************************************************************
Author: Andrei Plakhota
Reviewer: Daniel Maizel

About: Program to implement function to data inside array of structs.
*******************************************************************************/
#include "voiddata.h" /* item_t */
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <errno.h> /* errno */

/* it is better in tis case to use malloc, because global arrays should only be used for read only data */
item_t info[] = { {NULL, AddToInt, PrintInt, ResetToZero}, 
					{NULL, AddToFloat, PrintFloat, ResetToZero},
					{NULL, AddToStr, PrintStr, FreeStr} };

int main()
{
	float num = 15.36;
	int i = 0;
	
	if(NULL == (info[2].data = (char *)malloc(1 * sizeof(char *))))
	{
		perror("Error: ");

		return 1;
	}
	
	for(; 3 > i; ++i)
	{
		info[i].add(&info[i].data, num);
		info[i].print(info[i].data);
	}	
	for(i = 0; 3 > i; ++i)
	{
		info[i].free(&info[i].data);
	}
	
	for(i = 0; 3 > i; ++i)
	{
		info[i].print(info[i].data);
	}

	return 0;
}
