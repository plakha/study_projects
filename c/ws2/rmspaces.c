#include <stdio.h>
#include <string.h>/*strcat*/
#include <stdlib.h>
#include <ctype.h>/*isspace*/


void RmSpaces(char *str);
char *RmSpacesStart(char *str);
char *RmSpacesEnd(char *str);
void ShiftLeftOnce(char *str);
int main()
{
	char s_test[] = "   He   llo     ";
	char *s_space = malloc(sizeof(char) * strlen(s_test));
	s_space = strcpy(s_space, s_test);
	printf("before%sendstr\n", s_space);
	/*s_space = RmSpacesStart(s_space);
	s_space = RmSpacesEnd(s_space);*/
	RmSpaces(s_space);
	printf("[%s]\n", s_space);
	free(s_space);
	return 0;
}

/*
the str pointer will not change, because return void
*/
void RmSpaces(char *str)
{
	char *thisc = NULL;
	char *endstr = NULL;
	str = RmSpacesEnd(str);
	str = RmSpacesStart(str);
	thisc = str;


	printf ("inside%sendstr\n", str);

	/*rid of spaces in the middle*/
	while ( '\0' != *(thisc + 1) )
	{	
		if ( (isspace(*thisc)) && (isspace(*(thisc + 1))) )
		{
				ShiftLeftOnce(thisc);
		}
		else
		{
		++thisc;
		}
	}
}

/*rid of start spaces*/
char *RmSpacesStart(char *str)
{
	char *space_runner = str;
	while( isspace(*space_runner) )
	{
		*str = '\0';
		++space_runner;
	}
	/*if ( space_runner != str)*/
	str = strcat(str, space_runner);
	return str;
	/*won't do! implementation mustn't move str pointer, because the user wants function to return void, not char*!
	while(' ' == *str)
		{
			++str;
		}

	return str;
	*/
}

/*rid of ending spaces, on loop exit end pointer refers to last non-null byte*/
char *RmSpacesEnd(char *str)
{
	char *end = str + strlen(str);/*ref. to term. null*/
	do
	{
		*end = '\0';
		--end;
	}
	while( isspace(*end));
	
	return str;
}

void ShiftLeftOnce(char *str)
{
	while('\0' != *str)
	{
		*str = *(str + 1);
		++str;
	}	
}
