#include <stdlib.h>
#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <errno.h> /* perror */

#include "../include/dvec.h"

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \

int TestCreate()
{
	if(NULL != DVECCreate(1, 1))
	{

		return 0;
	}

	return 1;
}

int TestDestroy()
{

	DVECDestroy(DVECCreate(1, 1));
	return 1;
}


int TestPushBack()
{
	return 1;
}


int TestPopBack()
{

	return 1;
}


int TestGetItemAddress()
{
	dvec_t *dvec = NULL;
	char c = 'P';
	int ret = 0;

	if(NULL == (dvec = DVECCreate(1, 1)))
	{
		perror("Didnt create Dvec: ");
		
		return 1;
	}
	
/*	DVECPopBack(dvec);*/
	DVECPushBack(dvec, &c);

/*	if(c == *(char *)DVECGetItemAddress(dvec, 0))*/
/*	{*/
/*		ret = 0;*/
/*	}*/
/*	printf("pushed %c got %c\n", c, *(char *)DVECGetItemAddress(dvec, 0));*/
	DVECDestroy(dvec);
	return ret;
}


int TestCapacity()
{
	dvec_t *dvec = NULL;
	int ret = 0;
	char c = 'P';

	if(NULL == (dvec = DVECCreate(1, 1)))
	{
		perror("Didnt create Dvec: ");
		
		return 1;
	}

	if(1 != DVECCapacity(dvec))
	{
		ret = 1;
	}
	printf("init 1 element, capacity  %lu\n", DVECCapacity(dvec));

	DVECPushBack(dvec, &c);
	if(2 != DVECCapacity(dvec))
	{
		ret = 1;
	}
	printf("pushed 1 element, capacity  %lu\n", DVECCapacity(dvec));

	DVECPopBack(dvec);
	if(2 != DVECCapacity(dvec))
	{
		ret = 1;
	}
	printf("popped 1 element, capacity %lu\n", DVECCapacity(dvec));

	DVECDestroy(dvec);
	return ret;
}

int TestReserve()
{
	dvec_t *dvec = NULL;
	int ret = 0;
	
	if(NULL == (dvec = DVECCreate(1, 1)))
	{
		perror("Didnt create Dvec: ");
		
		return 1;
	}

	if(1 != DVECCapacity(dvec))
	{
		ret = 1;
	}
	printf("init 1 element, capacity  %lu\n", DVECCapacity(dvec));

	DVECReserve(dvec, 100);
	if(100 != DVECCapacity(dvec))
	{
		ret = 1;
	}
	printf("reserved 100, capacity  %lu\n", DVECCapacity(dvec));

	DVECPopBack(dvec);
/*	DVECPopBack(dvec);*/
	if(50 != DVECCapacity(dvec))
	{
		ret = 1;
	}
	printf("popped 1 element, capacity %lu\n", DVECCapacity(dvec));

	DVECDestroy(dvec);

	return ret;
}

int TestSize()
{
	dvec_t *dvec = NULL;
	int ret = 0;
	char c = 'P';

	if(NULL == (dvec = DVECCreate(1, 1)))
	{
		perror("Didnt create Dvec: ");
		
		return 1;
	}

	if(0 != DVECSize(dvec))
	{
		ret = 1;
	}
	printf("pushed 0, size  %lu\n", DVECSize(dvec));

	DVECPushBack(dvec, &c);
	
	if(1 != DVECSize(dvec))
	{
		ret = 1;
	}
	printf("pushed 1, size  %lu\n", DVECSize(dvec));
	/*DVECPopBack(dvec);*/
	DVECDestroy(dvec);
	return ret;

}

/*
dvec_t *DVECCreate(size_t size_of_element, size_t num_elements);
void DVECDestroy(dvec_t *dvec);
int DVECPushBack(dvec_t *devc, const void *element);
void DVECPopBack(dvec_t *dvec);
void *DVECGetItemAddress(dvec_t *dvec, size_t index);
size_t DVECSize(const dvec_t *dvec);
int DVECReserve(dvec_t *dvec, size_t new_capacity);
size_t DVECCapacity(const dvec_t *devc);
*/
int main()
{
	dvec_t *dvec = NULL;
	char c = 'P';

	if(NULL == (dvec = DVECCreate(1, 1)))
	{
		perror("Didnt create Dvec: ");
		
		return 1;
	}
	
	DVECPopBack(dvec);
	DVECPushBack(dvec, &c);
	DVECPopBack(dvec);
	
	DVECPopBack(dvec);


	DVECDestroy(dvec);


/*	RUN_TEST(TestCreate);*/
/*	RUN_TEST(TestDestroy);*/
/*	RUN_TEST(TestPushBack);*/
/*	RUN_TEST(TestPopBack);*/
	RUN_TEST(TestGetItemAddress);
/*	RUN_TEST(TestSize);*/
/*	RUN_TEST(TestReserve);*/
/*	RUN_TEST(TestCapacity);*/

	return 0;
}
