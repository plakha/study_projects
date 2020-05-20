/***************************************************
*                                                  *
*   Author: Roi Kramer                             *
*   Date: 01/06/2019                               *
*   Description: Unit tests for the dynamic vector *
*                Library                           *
*                                                  *
***************************************************/
#include <stdio.h>

#include "../include/dvec.h"

#define RUN_TEST(test) \
if(test()){ printf("\x1B[32m%-24s| %5s\n\033[0m", "["#test"]","OK!"); } \
else{ printf("\x1B[31m%-24s| %7s\n\033[0m", "["#test"]", "FAIL!"); }

#define SUCCESS (0)
#define FAILURE (1)

int Test_Int_DvecCreate(void);
int Test_Int_DvecSize(void);
int Test_Int_DvecPush(void);
int Test_Int_DvecPop(void);
int Test_Int_DvecGetItem(void);
int Test_Int_DvecReserve(void);

int Test_Struct_DvecCreate(void);
int Test_Struct_DvecSize(void);
int Test_Struct_DvecPush(void);
int Test_Struct_DvecPop(void);
int Test_Struct_DvecGetItem(void);
int Test_Struct_DvecReserve(void);

typedef struct Doggie
{
	int id;
	char *name;
	int age;
	int gender;	
	int color;
	char *breed;
	enum fur_types
	{
		FURRY,
		VERRY_FURRY,
		FURRIEST,
		AMAZING
	} fur_type;
} doggie_t; 

int main() 
{
	puts("\x1B[36mTest Results:\033[0m");
	puts("\x1B[33m--- Basic Type Test Results: ---\033[0m");

/*	RUN_TEST(Test_Int_DvecCreate);*/
/*	RUN_TEST(Test_Int_DvecSize);*/
/*	RUN_TEST(Test_Int_DvecPush);*/
/*	RUN_TEST(Test_Int_DvecPop);*/
/*	RUN_TEST(Test_Int_DvecGetItem);*/
/*	RUN_TEST(Test_Int_DvecReserve);*/

	puts("\x1B[33m--- Doggie Struct Test Results: ---\033[0m");

/*	RUN_TEST(Test_Struct_DvecPush);*/
/*	RUN_TEST(Test_Struct_DvecCreate);*/
/*	RUN_TEST(Test_Struct_DvecSize);*/
	RUN_TEST(Test_Struct_DvecPop);
/*	RUN_TEST(Test_Struct_DvecGetItem);*/
/*	RUN_TEST(Test_Struct_DvecReserve);*/
/*	*/
	return 0;
}

int Test_Int_DvecCreate(void)
{
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	dvec = DVECCreate(sizeof(int), n_elements);	
	
	/* test1 */
	res = (dvec != NULL);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_Int_DvecSize(void)
{
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	dvec = DVECCreate(sizeof(int), n_elements);	
	
	/* test1 */
	res = DVECSize(dvec);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_Int_DvecPush(void)
{
	int result = 1;
	int num = 3;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	dvec = DVECCreate(sizeof(int), n_elements);	
	
	/* test1 */
	res = DVECSize(dvec);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPushBack(dvec, &num);

	/* test2 */
	res = DVECSize(dvec);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPushBack(dvec, &num);

	/* test3 */
	res = DVECSize(dvec);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test4 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);

	/* test5 */
	res = DVECSize(dvec);
	expect = 4;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test6 */
	res = DVECCapacity(dvec);
	expect = 6;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_Int_DvecPop(void)
{
	int result = 1;
	int num = 3;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	dvec = DVECCreate(sizeof(int), n_elements);

	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);
	
	/* test1 */
	res = DVECSize(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test2 */
	res = DVECCapacity(dvec);
	expect = 6;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPopBack(dvec);

	/* test3 */
	res = DVECSize(dvec);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test4 */
	res = DVECCapacity(dvec);
	expect = 6;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPopBack(dvec);

	/* test5 */
	res = DVECSize(dvec);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test6 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_Int_DvecGetItem(void)
{
	int result = 1;
	int num = 3;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	dvec = DVECCreate(sizeof(int), n_elements);
	
	DVECPushBack(dvec, &num);
	num = 4;
	DVECPushBack(dvec, &num);
	num = -9;
	DVECPushBack(dvec, &num);
	
	/* test1 */
	res = *(int *)DVECGetItemAddress(dvec, 0);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test2 */
	res = *(int *)DVECGetItemAddress(dvec, 1);
	expect = 4;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test3 */
	res = *(int *)DVECGetItemAddress(dvec, 2);
	expect = -9;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_Int_DvecReserve(void)
{
	int result = 1;
	int num = 3;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;

	dvec = DVECCreate(sizeof(int), n_elements);
	
	DVECPushBack(dvec, &num);
	DVECPushBack(dvec, &num);
	
	/* test1 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECReserve(dvec, 2);

	/* test2 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECReserve(dvec, 1000);

	/* test3 */
	res = DVECCapacity(dvec);
	expect = 1000;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECReserve(dvec, 1);

	/* test4 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECReserve(dvec, 3);

	/* test5 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_Struct_DvecCreate(void)
{
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 100;

	dvec = DVECCreate(sizeof(doggie_t), n_elements);	
	
	/* test1 */
	res = (dvec != NULL);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_Struct_DvecSize(void)
{
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 100;

	dvec = DVECCreate(sizeof(doggie_t), n_elements);	
	
	/* test1 */
	res = DVECSize(dvec);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_Struct_DvecPush(void)
{
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;
	doggie_t dog1 = {1, NULL, 1, 2, 3, NULL, 1};

	dvec = DVECCreate(sizeof(doggie_t), n_elements);	
	
	/* test1 */
	res = DVECSize(dvec);
	expect = 0;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPushBack(dvec, &dog1);

	/* test2 */
	res = DVECSize(dvec);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPushBack(dvec, &dog1);

	/* test3 */
	res = DVECSize(dvec);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test4 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPushBack(dvec, &dog1);
	DVECPushBack(dvec, &dog1);

	/* test5 */
	res = DVECSize(dvec);
	expect = 4;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test4 */
	res = DVECCapacity(dvec);
	expect = 6;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);


	DVECDestroy(dvec);

	return result;
}


int Test_Struct_DvecPop(void)
{
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;
	doggie_t dog1 = {1, NULL, 1, 2, 3, NULL, 1};

	dvec = DVECCreate(sizeof(doggie_t), n_elements);

	DVECPushBack(dvec, &dog1);
	DVECPushBack(dvec, &dog1);
	DVECPushBack(dvec, &dog1);
	
	/* test1 */
	res = DVECSize(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test2 */
	res = DVECCapacity(dvec);
	expect = 6;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPopBack(dvec);

	/* test3 */
	res = DVECSize(dvec);
	expect = 2;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test4 */
	res = DVECCapacity(dvec);
	expect = 6;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECPopBack(dvec);

	/* test5 */
	res = DVECSize(dvec);
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test6 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_Struct_DvecGetItem(void)
{
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;
	doggie_t dog1 = {1, NULL, 1, 2, 3, NULL, 1};
	doggie_t dog2 = {5, NULL, 1, 2, 3, NULL, 1};
	doggie_t dog3 = {-20, NULL, 1, 2, 3, NULL, 1};


	dvec = DVECCreate(sizeof(doggie_t), n_elements);
	
	DVECPushBack(dvec, &dog1);
	DVECPushBack(dvec, &dog2);
	DVECPushBack(dvec, &dog3);
	
	/* test1 */
	res = ((doggie_t *)DVECGetItemAddress(dvec, 0))->id;
	expect = 1;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test2 */
	res = ((doggie_t *)DVECGetItemAddress(dvec, 1))->id;
	expect = 5;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	/* test3 */
	res = ((doggie_t *)DVECGetItemAddress(dvec, 2))->id;
	expect = -20;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

int Test_Struct_DvecReserve(void)
{
	int result = 1;
	int res = 0;
	dvec_t *dvec = NULL;
	int expect = 0;
	size_t test_no = 0;
	size_t n_elements = 3;
	doggie_t dog1 = {1, NULL, 1, 2, 3, NULL, 1};

	dvec = DVECCreate(sizeof(doggie_t), n_elements);
	
	DVECPushBack(dvec, &dog1);
	DVECPushBack(dvec, &dog1);
	
	/* test1 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECReserve(dvec, 2);

	/* test2 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECReserve(dvec, 1000);

	/* test3 */
	res = DVECCapacity(dvec);
	expect = 1000;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECReserve(dvec, 1);

	/* test4 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECReserve(dvec, 3);

	/* test5 */
	res = DVECCapacity(dvec);
	expect = 3;
	++test_no;
	printf("\ttest %lu: expected: %d, got: %d\n", test_no, expect, res);
	result *= (expect == res);

	DVECDestroy(dvec);

	return result;
}

