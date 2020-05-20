#include "voiddata.h"
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */

void AddToInt(void **data, int num)
{
	*(int *)data = *(int *)data + num;
}

void PrintInt(const void *data)
{
	printf("%d\n", *(int *)&data);
}

void AddToFloat(void **data, int num)
{
	*(float *)data = *(float *)data + (float)num;
}

void PrintFloat(const void *data)
{
	printf("%f\n", *(float *)&data);
}

void AddToStr(void **data, int num)
{
	sprintf(*(char **)data, "%s%d", *(char **)data, num);
}

void PrintStr(const void *data)
{
	printf("%s\n", (char *)data);
}

void ResetToZero(void **data)
{
	*data = NULL;
}

void FreeStr(void **data)
{
	free(*data);
}
