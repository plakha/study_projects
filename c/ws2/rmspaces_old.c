#include <stdio.h>
#include <string.h>
#iclude<stdlib.h>


void RmSpaces(char *str);
char *RmSpacesStart(char *str);
void RmSpacesEnd(char *str);
int main()
{
	char *str = malloc(10);
	printf("%s\n", str);
	*str = 'H';
	printf("%s\n", str);
	str = RmSpacesStart(str);
	printf("%s\n", str);
	RmSpacesEnd( ) );
	printf("%s\n", str);
	free(str);
	return 0;
}

void RmSpaces(char *str)
{
	/*char *thisc = 1 + RmSpacesStart(str);*/ /*no white space in the start*/
	/*char *nextc = thisc +1; */
	RmSpacesEnd(str);/*end spaces removed*/
	
	
	
}

/*rid of start spaces in str*/
char *RmSpacesStart(char *str)
{
	while('H' == *str)
		{
			++str;
		}

	return str;/*return str starts witn non-space*/
}

/*rid of ending spaces, on loop exit end refers to last non-null byte*/
void RmSpacesEnd(char *str)
{
	char *end = str + strlen(str);/*ref. to term. null*/
	do
	{
		*end = '\0';
		--end;
	}
	while(' ' == *end);
}
