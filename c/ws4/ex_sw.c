/*******************************************************************************
Author: Andy Plakhota 14/5/19
Reviewer: Inbar Namdar


	system("stty -icanon -echo") - no terminal echoing, 
so o enter needed after char input

	system("stty icanon echo") - return terminal to default state

*******************************************************************************/

#include <stdio.h>/*getchar*/
#include <stdlib.h>/*system*/

#define ESC 0x1B
#define TRUE 1
#define FALSE 0


int InOut();

int main()
{
	InOut();
	
	return 0;
}


int InOut()
{
	char *template = " pressed";
	char input = 0;

	system("stty -icanon -echo");

	while(TRUE)	
	{
		switch(input = getchar())
		{
			case 'A':
				printf("%c%s\n", input, template);
				break;
			case 'T':
				printf("%c%s\n", input, template);
				break;
			case ESC:
				system("stty icanon echo");

				return 0;
		}
	}
	
	system("stty -icanon -echo");
	return(1);
}
