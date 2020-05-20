/******************************************************************************
Author Andy Plakhota, 12/5/2019
Reviewer



Functions:

	- void TxtPrint(char **txt) - prints the values inside texts[][].
Each strings text[i][] has a terminating null (banal).
The array text[][] itself has a terminating NULL-pointer (not banal). 
As a matter of fact, env[][] does have a termibating null.

	- char **TxtCopy(char **txt) - the calling function must free!!

	- char *ParagraphCopy(char *paragraph) - the calling function must free!!

	- void CleanText(char **txt) - 
	
	- size_t ArrLen(void *item) - returns length of custom array 
(excl terminating NULL), conditioned the have a terminating NULL!!


*******************************************************************************/

#include <stddef.h>/*size_t*/
#include <stdlib.h>/*calloc*/
#include <stdio.h>/*printf*/
#include <assert.h>/*assert*/
#include <ctype.h>/*tolower*/

#define UNUSED(x) (void)(x)

void TxtPrint(char **txt);
char **TxtCopy(char **txt);
char *ParagraphCopy(char *paragraph);
size_t ArrLen(char **item);
void CleanText(char **txt);
char *StrLowCpy(char *dest, const char *src);

int main(int argc, char **argv, char **env)
{
	char **copy_env = TxtCopy(env);
	UNUSED(argc);
	UNUSED(argv);
	
	if(NULL == copy_env)
	{
		
		return 1;
	}
	
	TxtPrint(copy_env);
	CleanText(copy_env);	
	
	return 0;
}

void TxtPrint( char **txt)
{
	char **run_txt = txt;

	while(NULL != *run_txt)
	{	
		printf("%s\n", *run_txt); 
		++run_txt;
	}	
}

char **TxtCopy( char **txt)
{
	/*assert(NULL != txt);*/

	size_t len_txt = ArrLen(txt);
	char **run_txt = txt;
	char **copy_txt = (char **)calloc(1 + len_txt, sizeof(char *));
	char **run_copy_txt = copy_txt;
	
	if(NULL == copy_txt)
	{
		
		return NULL;
	}
	
	while(NULL != *run_txt)
	{
		*run_copy_txt = ParagraphCopy(*run_txt);
		if (NULL == *run_copy_txt)
		{
			CleanText(copy_txt);
			return NULL;	
		}
		++run_copy_txt;
		++run_txt;
	}
	*run_copy_txt = NULL;

	return copy_txt;
}

char *ParagraphCopy(char *paragraph)
{
	/*assert(NULL != paragraph);*/
	
	size_t len_paragraph = strlen(paragraph);
	char *copy_paragraph = (char *)calloc(1 + len_paragraph, sizeof(char));
	
	if(NULL == copy_paragraph)
	{

		return NULL;
	}
	
	return	StrLowCpy(copy_paragraph, paragraph);
}

char *StrLowCpy(char *dest, const char *src)
{
	char *runner = dest;
	do
	{
		*runner = tolower(*src);
		++runner;
		++src;
	}
	while('\0' != *src);
	*runner = '\0';
	runner = NULL;

	return dest;
}

size_t ArrLen(char **item)
{
	/*assert (NULL != item);*/

	size_t len = 0;

	while(NULL != *item)
	{
		++len;
		++item;
	}

	return len;
}

void CleanText(char **txt)
{
	char **run_txt = txt;

	while(NULL != *run_txt)
	{
		free(*run_txt);
		++run_txt;
	}

	free(txt);
}
