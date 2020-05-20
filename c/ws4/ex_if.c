/*******************************************************************************
Author: Andy Plakhota 14/5/19
Reviewer: Inbar Namdar

	system("stty -icanon -echo") - no terminal echoing, 
so o enter needed after char input

	system("stty icanon echo") - return terminal to default state

*******************************************************************************/

#include <stdio.h>/*getchar*/
#include <stdlib.h>/*exit, system*/

#define ESC 0x1B

void InOut();

int main()
{
	InOut();	

	return 0;
}

void InOut()
{
	char *template = " pressed";
	char input = 0;
	
	system("stty -icanon -echo");	
	
	while(ESC != (input = (char)getchar()))	
	{
		if(('T' == input) || ('A' == input))
		{
			printf("%c%s\n", input, template);
		}
	}
	
	system("stty icanon echo");
	return;
}
