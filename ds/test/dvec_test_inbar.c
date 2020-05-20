/*************************************************************************************/
/* Author- Inbar Namdar                                                              */
/* Reviewer - Daniel                                                                 */
/* Date - 28/5/2019                                                                  */
/*************************************************************************************/

#include <stdio.h> /* size_t */

#include "../include/dvec.h"

#define getName(var)  #var

#define RUN_TEST(test) \
{ \
if (test) \
{ printf("%s\033[1;32m-OK\033[0m\n",getName(test)); } \
else \
{ printf("%s\033[1;31m-ERROR\033[0m\n",getName(test) ); } \
}

int DVECCreateTest1()
{
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,3);
	
	if (NULL != dynamic_vector)
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		return 0;
	}
}

int DVECGetItemAddressTest()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,3);
	DVECPushBack(dynamic_vector, &x);
	DVECPushBack(dynamic_vector, &x);
	
	if (5 == *(int *)DVECGetItemAddress(dynamic_vector, 0))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		return 0;
	}
}

int DVECPushBackTest1()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,3);
	
	if (0 == DVECPushBack(dynamic_vector, &x))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}
	
}

int DVECPushBackTest2()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,1);
	
	DVECPushBack(dynamic_vector, &x);
	DVECPushBack(dynamic_vector, &x);
	
	if (0 == DVECPushBack(dynamic_vector, &x))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}
	
	return 1;
}

int DVECPopBackTest1()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,1);
	DVECPushBack(dynamic_vector, &x);
	DVECPopBack(dynamic_vector);
	if (0 == DVECSize(dynamic_vector))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}
	
}

int DVECSizeTest1()
{
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,1);
	
	if (0 == DVECSize(dynamic_vector))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}
	
}

int DVECSizeTest2()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,1);
	DVECPushBack(dynamic_vector, &x);
	
	if (1 == DVECSize(dynamic_vector))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}
	
}

int DVECSizeTest3()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,1);
	DVECPushBack(dynamic_vector, &x);
	DVECPushBack(dynamic_vector, &x);
	if (2 == DVECSize(dynamic_vector))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}
}

int DVECCapacityTest1()
{
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,1);
	
	if (1 == DVECCapacity(dynamic_vector))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}	
}

int DVECCapacityTest2()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,1);
	DVECPushBack(dynamic_vector, &x);
	if (2 == DVECCapacity(dynamic_vector))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}	
}

int DVECCapacityTest3()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,2);
	DVECPushBack(dynamic_vector, &x);
	DVECPushBack(dynamic_vector, &x);
	DVECPopBack(dynamic_vector);
	
	if (2 == DVECCapacity(dynamic_vector))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}	
}

int DVECReserveTest1()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,4);
	DVECPushBack(dynamic_vector, &x);
	DVECPushBack(dynamic_vector, &x);
	DVECReserve(dynamic_vector, 8);
		
	if (8 == DVECCapacity(dynamic_vector))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}	
}

int DVECReserveTest2()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,4);
	DVECPushBack(dynamic_vector, &x);
	DVECPushBack(dynamic_vector, &x);
	DVECReserve(dynamic_vector, 1);
		
	if (3 == DVECCapacity(dynamic_vector))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}	
}

int DVECReserveTest3()
{
	int x = 5;
	dvec_t *dynamic_vector = NULL;
	
	dynamic_vector = DVECCreate(4,4);
	DVECPushBack(dynamic_vector, &x);
	DVECPushBack(dynamic_vector, &x);
	DVECReserve(dynamic_vector, 3);
		
	if (3 == DVECCapacity(dynamic_vector))
	{
		DVECDestroy(dynamic_vector);
		return 1;
	}
	else
	{
		DVECDestroy(dynamic_vector);
		return 0;
	}	
}
int main()
{
	RUN_TEST(DVECCreateTest1());
	printf("\n");
	
	RUN_TEST(DVECGetItemAddressTest());
	printf("\n");
	
	RUN_TEST(DVECPushBackTest1());
	RUN_TEST(DVECPushBackTest2());
	printf("\n");
	RUN_TEST(DVECPopBackTest1());
	printf("\n");
	RUN_TEST(DVECSizeTest1());
	RUN_TEST(DVECSizeTest2());
	RUN_TEST(DVECSizeTest3());
	printf("\n");
	RUN_TEST(DVECCapacityTest1());
	RUN_TEST(DVECCapacityTest2());
	RUN_TEST(DVECCapacityTest3());
	printf("\n");
	RUN_TEST(DVECReserveTest1());
	RUN_TEST(DVECReserveTest2());
	RUN_TEST(DVECReserveTest3());
	return 0;
}
