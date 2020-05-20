/****************************************
Reimplementation of string.h library 
in accordance with respective gnu manuals:
strlen V
strcmp V
strcpy V strncpy V-----------------!!!!!! RETEST against string.h !!!!!!
strcasecmp V
strchr V
strdup V
strcat V strncat 
strstr
strspn
strtok
*****************************************/

#include <stdlib.h> /*malloc()*/
#include <ctype.h> /*toupper()*/

/*Calculate length os string, not including the NULL-terminator*/
size_t Strlen(const char *s)
{
	const char *runner = s;
	while('\0' != *runner)
	{
		++runner;
	}
	return (runner - s);
}

/*Compare strings. Return 0 on match, 
return negative value if s1 is less than s2, 
return positive value if s1 is greater than s2*/
int Strcmp(const char *s1, const char *s2)
{
	const char *runner1 = s1;
	const char *runner2 = s2;
	while(('\0' != *runner1) && ('\0' != *runner2) && (*runner1 == *runner2))
	{
		++runner1;
		++runner2;
	}
	return (*runner1 - *runner2);
	
}

/*Copy strings, see man strcpy*/
char *Strcpy(char *dest, const char *src)
{
	char *runner = dest;
	do
	{
		*runner = *src;
		++runner;
		++src;
	}
	while('\0' != *src);
	*runner = '\0';
	runner = NULL;

	return dest;
}

/*Copy strings, up to n bytes, see man strncpy*/
char *Strncpy(char *dest, const char *src, size_t n)
{
	char *runner = dest;
	do
	{
		*runner = *src;
		++runner;
		++src;
	}
	while('\0' != *src || (runner - dest) < (int)n);
	++runner;	
	while((runner - dest) < (int)n)
	{
		*runner = '\0';
	}
	runner = NULL;	

	return dest;
}

/*Compare strings, no matter the case*/
int Strcasecmp(const char *s1, const char *s2)
{
	
	const char *runner1 = s1;
	const char *runner2 = s2;
	while(('\0' != *runner1) && 
	 ('\0' != *runner2) && 
	 (toupper(*runner1) == toupper(*runner2)))
	{
		++runner1;
		++runner2;
	}
	return(toupper(*runner1) - toupper(*runner2));
}

/*Locate char c in string s*/
char *Strchr(const char *s, int c)
{
	const char *runner = s;
	
	while((c != *runner) && ('\0' != *runner))
	{
		++runner;
	}
	if (c == *runner)
	{	

	return (char *)runner;
	}

	return NULL;/*c not found*/
}

/*Return pointer to new string with same content. 
The user is responsible to free the allocated memory*/
char *Strdup(const char *s)
{
	char *res = (char *)malloc((Strlen(s) + 1) * sizeof(char));
	char *runner = res;
	do
	{
	*runner = *s;
	++runner;
	++s;
	}
	while('\0' != *s);
	*runner = '\0';
	runner = NULL;

	return res;
}

/*Concatenate strings dest and src, overwrite dest's terminating null.
The user accounts for dest's memory allocation!
*/
char *Strcat(char *dest, const char *src)
{
	char *end_dest = dest + Strlen(dest);/*point to dest's terminating null*/
	end_dest = Strcpy(end_dest, src);
	
	return dest;
}


/*Concatenate strings dest and n bytes from src, 
overwrite dest's terminating null. Add terminating null in the funal string. 
*/
char *Strncat(char *dest, const char *src, size_t n)
{
	char *end_dest = dest + Strlen(dest);/*point to dest's terminating null*/
	end_dest = Strncpy(end_dest, src, n);
	*(end_dest + n) = '\0';	
	
	return dest;
}

/*Find occurence of string needle in string haystack.
The refers to strncmp from string.h*/
char *Strstr(const char *haystack, const char *needle)
{	
	const char *runner = haystack;
	int length_needle = Strlen(needle);

	while( ('\0' != *runner)  
	 		&& ('\0' != strncmp(runner, needle, length_needle)) )
	{
		++runner;
	}
	if('\0' == *runner)
	{

		return NULL;/*didn't find the needle*/
	}
	
	return (char *)runner;/*found the needle*/
}

/*Get length of a prefix substring*/
size_t Strspn(const char *str, const char *accept)
{
	int res = 0;
	const char *runner = str;	
	while ( ('\0' != *runner) && (NULL != strchr(accept, *runner)) )
	{
		++res;
		++runner;
	}

	return res;
}
