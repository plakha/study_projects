#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "string-andrei.c"

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \



		
int TestStrlen();
int TestStrcmp();
int TestStrcpy();
int TestStrncpy();
int TestStrcasecmp();
int TestStrchr();
int TestStrdup();
int TestStrcat();
int TestStrncat();
int TestStrstr();
int TestStrspn();
int TestStrtok();

int main()
{	
	RUN_TEST(TestStrlen)
	RUN_TEST(TestStrcmp)
	RUN_TEST(TestStrcpy)
	RUN_TEST(TestStrncpy)
	RUN_TEST(TestStrcasecmp)
	RUN_TEST(TestStrchr)
	RUN_TEST(TestStrdup)
	RUN_TEST(TestStrcat)
	RUN_TEST(TestStrncat)
	RUN_TEST(TestStrstr)
	RUN_TEST(TestStrspn)
	RUN_TEST(TestStrtok)
	

	return 0;
}


int TestStrspn()
{
	if (2 == Strspn("Hell", "eH") 
		&& 3 == Strspn("LLL", "London")
		&& 0 == Strspn("Wow", "Corew") )
	{
		return 0;
	}
	return 1;
}

int TestStrtok()
{
	char input[] = "My name is Luka, I live on the second floor, I live upstairs from you. Yes, I think you've seen me before...";
	char *res = malloc(1000);
	res = strtok(input, ",");
	printf("%s\n ", res);
	printf("%s\n ", res);
	
	return 1;
}

int TestStrstr()
{
	int ret1 = 1;
	char haystack1[] = "He";
	char needle1[] = "Hell";
	int ret2 = 1;
	char haystack2[] = "!Hello";
	char needle2[] = "Hell";
	if('\0' == (strstr(haystack1, needle1)))
	{
		ret1 = 0;
	}	
	ret2 = strcmp("Hello", strstr(haystack2, needle2));
	
	return(ret1 || ret2);
}

int TestStrncat()
{
	char *dest = malloc(10 * sizeof(char));
	char src[]="1234";
	int ret = 1;
	/*printf("src %s\n", src);*/
	dest = Strcpy(dest, "abcde");
	/*printf("dest before %s\n", dest);*/
	dest = Strncat(dest, src, 3);
	/*printf("dest after %s\n", dest);*/
	ret = Strcmp(dest, "abcde123");
	free(dest);

	return ret;
}

int TestStrcat()
{
	char *dest = malloc(10 * sizeof(char));
	char src[]="fghi";
	int ret = 1;
	/*printf("src %s\n", src);*/
	dest = Strcpy(dest, "abcde");
	/*printf("dest before %s\n", dest);*/
	dest = Strcat(dest, src);
	/*printf("dest after %s\n", dest);*/
	ret = Strcmp(dest, "abcdefghi");
	free(dest);

	return ret;
}

int TestStrdup()
{
	char src[] = "Hello";
	char *res = Strdup(src);
	int	ret = Strcmp(src, res);
	free(res);

	return ret;
}

int TestStrchr()
{
	char *s = "Hello";

	return(!('H' == *((Strchr(s, 'l') - 2))));
}

int TestStrcasecmp()
{
	char s1[5] = {"Hello"};
	char s2[8] = {"hello"};
	if ((0 == Strcasecmp(s1, s1)) &&
	 (Strcasecmp(s1, s2) == 0) &&
	 (Strcasecmp(s2, s1) == 0))
	{

	return 0;
	}

	return 1;
}

int TestStrncpy()
{
	char src[5] = "Hello";
	char *dest = malloc (10 * sizeof(char));
	int ret = 0;
	int i = 0;

	dest = Strncpy(dest, src, 10);
	for(i = 0; i < 10; ++i)
	{
		if(src [i] != dest[i])
		{
			ret = 1; /*BAD*/
			break;
		}
	}
	free(dest);

	return ret;
}

int TestStrcpy()
{
	char src1[5] = "Hello";
	char *dest1 = (char *)malloc (6 * sizeof(char));
	int ret1 = 1;
	/*printf("%s\n", src1);*/
	dest1 = Strcpy(dest1, src1);

	
	/*printf("%s\n", dest1);*/
	ret1 = Strcmp(dest1, src1);/*O if same*/
	/*printf("%d\n", ret1);*/
	free(dest1);	
	
	
	
	return(ret1);
}

int TestStrcmp()
{
	char s1[5] = {"Hello"};
	char s2[8] = {"Good-Bye"};
	if ((0 == Strcmp(s1, s1)) &&
	 (Strcmp(s1, s2) > 0) &&
	 (Strcmp(s2, s1) < 0))
	{

	return 0;
	}

	return 1;
}

int TestStrlen()
{
	char s1[5] = {"Hello"};
	int length1 = Strlen(s1);
	char s2[1];
	int length2 = Strlen(s2);
	if(5 == length1 && 0 == length2)
	{

		return 0;	
	}
	else 
	{

		return 1;
	}
}
