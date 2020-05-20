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
#define TRUE 1
#define FALSE 0

void TPressed();
void APressed();
void EscPressed();

void InOut();

void FillLUT();

void (*lut[256])(void);

int main()
{

	FillLUT();	
	InOut();	

	return 0;
}

void InOut()
{
	system("stty -icanon -echo");
	
	while(TRUE)
	{
		lut[(int)getchar()]();
	}
	

}

void FillLUT()
{
	lut[ESC] = &EscPressed;
	lut['A'] = &APressed;
	lut['T'] = &TPressed;
}

void TPressed()
{
	puts("T pressed");
}


void APressed()
{
	puts("A pressed");
}

void EscPressed()
{
	system("stty icanon echo");	

	exit(0);
}
