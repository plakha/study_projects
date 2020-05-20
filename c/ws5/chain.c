/******************************************************************************






*******************************************************************************/

#include <stdio.h> /*fgets*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*strcmp*/
#include <errno.h> /*errno to implement*/
#include <assert.h>/*assert*/

#define MAX_LINE 90
#define LEN_RESP_CHAIN 5
#define UNUSED(X)  (void)(X)

enum status
{
	ok, error/*use ipper case OK, ERROR*/
};

struct item
{
	char *data;
	int (*compare)(char *line);
	enum status (*operate)(char *line, char *filename);
};

struct item chain[LEN_RESP_CHAIN];

enum status Append(char *line, char *filename);
int AlwaysTrue(char *line);
enum status AppendCount(char *line, char *filename);
int IsCount(char *line);
enum status Prepend(char *line, char *filename);
int IsPrepend(char *line);
enum status RemoveFile(char *line, char *filename);
int IsRemove(char *line);
enum status ExitProg(char *line, char *filename);
int IsExit (char *line);
int InitRespChain(struct item *chain);
int CreateFile(int argc, char **argv,char **filename);
char *GetUserInput(char *line, int n);


int main(int argc, char **argv)
{
	char *line = NULL;
	char *filename = NULL;
	int i = 0;
	
	/*start of program*/
	if( 0 != CreateFile(argc, argv, &filename))
	{
		puts("Couldn't create file\n");

		return 1;
	}
	
	InitRespChain(chain);
	if(NULL == chain)
	{
		puts("Couldn't load the program\n");		

		return 1;
	}

	line = (char *)malloc((MAX_LINE + 1) * sizeof(char));
	if(NULL == line)
	{
		puts("Not enough memory\n");
	} 
	
	
	/*chain*/		
	while(1)	
	{
		line = GetUserInput(line, MAX_LINE + 1);
		
		for(i = 0; i < LEN_RESP_CHAIN; ++i)
		{
			if(1 == chain[i].compare(line))
			{
				if(error == chain[i].operate(line, filename))
				{
					printf("%s", strerror(errno));
				}
				break;
			}
		}			
	}
	/*-exit chain*/

	/*end of program*/
	free(line);
	free(chain);

	return 0;

}


char *GetUserInput(char *line, int n)
{
	line = fgets(line, n, stdin);
	
	return line;
}

int CreateFile(int argc, char **argv,char **filename)
{
	FILE *file = NULL;

	if(argc > 1)
	{
		*filename = *(argv + 1);
	}
	else
	{
		*filename = "new_text";
	}

	file = fopen(*filename, "w");
	if(NULL == file)
	{
	
		return -1;
	}
	else
	{
		fclose(file);
	}

	return 0;
}


int InitRespChain(struct item *chain)
{
	chain[0].data = "-exit\n";
	chain[0].compare = IsExit;
	chain[0].operate = ExitProg;
	chain[1].data = "-remove\n";
	chain[1].compare = IsRemove;
	chain[1].operate = RemoveFile;
	chain[2].data = "<";
	chain[2].compare = IsPrepend;
	chain[2].operate = Prepend;
	chain[3].data = "-count\n";
	chain[3].compare = IsCount;
	chain[3].operate = AppendCount;
	chain[4].data = "-append\n";
	chain[4].compare = AlwaysTrue;
	chain[4].operate = Append;
	
	return 0;
}

int IsExit (char *line)
{
	assert(NULL != line);

	return(!strcmp("-exit\n", line));
}

enum status ExitProg(char *line, char *filename)
{
	UNUSED(filename);
	free(line);		
	
	exit(0);

	return ok;
}

int IsRemove(char *line)
{
	assert(NULL != line);

	return(!strcmp("-remove\n", line));
}

enum status RemoveFile(char *line, char *filename)
{
	UNUSED(line);
	if(0 != remove(filename))
	{
		
		return error;
	}

	return ok;	
}

int IsPrepend(char *line)
{
	assert(NULL != line);	

	return '<' == *line;
}

enum status Prepend(char *line, char *filename)
{
	FILE *file = NULL;
	FILE *temp = NULL;
	char ch = 0;

	file = fopen(filename, "r");	
	if(NULL == file)
	{

		return error;
	}
	temp = fopen(".temp", "w");
	if(NULL == temp)
	{
		fclose(file);

		return error;
	}

	/*copy from file to temp*/
	while(EOF != (ch = getc(file)))
	{
		if(EOF == fputc(ch, temp))
		{
			fclose(file);
			fclose(temp);

			return error;
		}		
	}
	if (0 != fclose(file) || 0 != fclose(temp))
	{
		
		return error;
	}
	
	file = fopen (filename, "w");
	if(NULL == file)
		{
			
			return error;
		}
	temp = fopen (".temp", "r");
	if(NULL == temp)
		{
			fclose(file);

			return error;
		}
	/*prepend user line to file*/
	if(0 >= fprintf(file, "%s", line + 1))
	{
		printf("couldn't prepend to file %s\n", filename);
	}
	/*recover from temp to file*/
	while(EOF != (ch = getc(temp)))
	{
		if(EOF == fputc(ch, file))
		{
			fclose(file);
			fclose(temp);

			return error;
		}
	}

	if (0 != fclose(file) || 0 != fclose(temp))
	{
		
		return error;
	}

	if(remove(".temp"))
	{

		return error;
	}

	return ok;
}

int IsCount(char *line)
{
	assert(NULL != line);

	return(!strcmp("-count\n", line));	
}

enum status AppendCount(char *line, char *filename)
{
	FILE *file = NULL;
	int count_new_line = 0;
	char ch = 0;
	
	UNUSED(line);	
	
	file = fopen(filename, "a+");	
	if(NULL == file)
	{

		return error;
	}

	do
	{
		ch = getc(file);
		if('\n' == ch)
		{
			++count_new_line;
		}
	}
	while(EOF != ch);
		
	if(0 >= fprintf(file, "line count is %d", count_new_line))
	{
		printf("couldn't write to file %s\n", filename);
	}
	if(0 != fclose(file))
	{

		return error;
	}
	
	return ok;
} 

int AlwaysTrue(char *line)
{	
	assert(NULL != line);
	
	return(1);
}

enum status Append(char *line, char *filename)
{
	FILE *file = NULL;
	
	assert(NULL != filename);
	assert(NULL != line);

	file = fopen(filename, "a");	
	if(NULL == file)
	{
		printf("Couldn't access the file%s\n", filename);
		return error;
	}

	if(0 >= fprintf(file, "%s", line))
	{
		printf("couldn't write to file %s", filename);
	}
	if(0 != fclose(file))
	{

		return error;
	}

	return ok;
}
