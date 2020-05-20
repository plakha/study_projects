/*******************************
		Alex Zilberman
	Reviewer: Roi Kramer
  		  01/06/2019
********************************/
#include <stdio.h> /* printf */
#include <string.h> /* memcmp */

#include "dvec.h"

/*******************************
		Alex Zilberman
	Reviewer: Roi Kramer
  		  01/06/2019
********************************/
#include <stdio.h> /*printf*/

/*** Declerations and Definitions ***/
#define RUN_TEST(test) \
printf("\033[0;34m" "Running " #test "()...\n" "\033[0m");\
if (test() == PASS)\
{\
	printf("\033[0;32m" #test "() - PASSED");\
}	\
else\
{\
	printf("\033[0;31m" #test "() - FAIL");\
}\
printf("\033[0m" "\n\n");

typedef enum
{
	PASS = 0,
	FAIL = 1
}testStatus_e;

testStatus_e Test_DVECCreate();
testStatus_e Test_DVECCapacity();
testStatus_e Test_DVECSize();
testStatus_e Test_DVECPushBack();
testStatus_e Test_DVECPopBack();
testStatus_e Test_DVECGetItemAddress();
testStatus_e Test_DVECReserve();


/* this struct below is for the whitebox refernce */
/*struct Dvec
{
	void *array;
	size_t size_of_element;
	size_t num_of_elements;
	size_t capacity;
};*/

int main()
{
	RUN_TEST(Test_DVECCreate);
	RUN_TEST(Test_DVECPushBack);
	RUN_TEST(Test_DVECCapacity);
	RUN_TEST(Test_DVECSize);
	RUN_TEST(Test_DVECPopBack);
	RUN_TEST(Test_DVECGetItemAddress);
	RUN_TEST(Test_DVECReserve);
	
	return 0;
}

testStatus_e Test_DVECCreate()
{
	/* A whitebox test for DVECCreate */
	testStatus_e flag = PASS;
	dvec_t *dvec = NULL;
	size_t element_size = 0, array_size = 0;
	char *field_ptr = NULL;

	/* First Case */
	element_size = 1;
	array_size = 2;

	printf("Case (%lu, %lu):\n", element_size, array_size);

	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	printf("dvec->array != NULL - ");
	field_ptr = (char*)dvec; /* &(dvec->array) */
	if (NULL == *(void **)field_ptr)
	{
		printf("Fail\n");
		flag = FAIL;
	}
	else
	{
		printf("PASS\n");
	}
	
	printf("dvec->size_of_element == %lu - ", element_size);
	field_ptr += sizeof(void *); /* &(dvec->size_of_element) */
	if (element_size!= *(size_t *)field_ptr)
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	else
	{
		printf("PASS\n");
	}

	printf("dvec->num_of_elements == %lu - ", 0lu);
	field_ptr += sizeof(size_t); /* &(dvec->num_of_elements) */
	if (0 != *(size_t *)field_ptr)
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	else
	{
		printf("PASS\n");
	}

	printf("dvec->capacity == %lu - ", array_size);
	field_ptr += sizeof(size_t); /* &(dvec->capacity) */
	if (array_size != *(size_t *)field_ptr)
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	else
	{
		printf("PASS\n");
	}
	
	DVECDestroy(dvec);
	printf("\n");
	
	/* Second case */
	element_size = 10;
	array_size = 5;

	printf("Case (%lu, %lu):\n", element_size, array_size);

	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	printf("dvec->array != NULL - ");
	field_ptr = (char*)dvec; /* &(dvec->array) */
	if (NULL == *(void **)field_ptr)
	{
		printf("Fail\n");
		flag = FAIL;
	}
	else
	{
		printf("PASS\n");
	}
	
	printf("dvec->size_of_element == %lu - ", element_size);
	field_ptr += sizeof(void *); /* &(dvec->size_of_element) */
	if (element_size!= *(size_t *)field_ptr)
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	else
	{
		printf("PASS\n");
	}

	printf("dvec->num_of_elements == %lu - ", 0lu);
	field_ptr += sizeof(size_t); /* &(dvec->num_of_elements) */
	if (0 != *(size_t *)field_ptr)
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	else
	{
		printf("PASS\n");
	}

	printf("dvec->capacity == %lu - ", array_size);
	field_ptr += sizeof(size_t); /* &(dvec->capacity) */
	if (array_size != *(size_t *)field_ptr)
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	else
	{
		printf("PASS\n");
	}
	
	DVECDestroy(dvec);

	return flag;
}

testStatus_e Test_DVECCapacity()
{
	testStatus_e flag = PASS;
	dvec_t *dvec = NULL;
	size_t element_size = 0, array_size = 0;

	/* First Case */
	element_size = 100;
	array_size = 123;

	printf("Case (%lu, %lu):\n", element_size, array_size);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}
	
	printf("Result == %lu - ", array_size);
	if (DVECCapacity(dvec) == array_size)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}	
	printf("\n");

	DVECDestroy(dvec);

	/* Second Case */
	element_size = 32;
	array_size = 85;

	printf("Case (%lu, %lu):\n", element_size, array_size);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}
	
	printf("Result == %lu - ", array_size);
	if (DVECCapacity(dvec) == array_size)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	
	printf("\n");

	DVECDestroy(dvec);

	/* Third Case */
	element_size = 99999;
	array_size = 1;

	printf("Case (%lu, %lu):\n", element_size, array_size);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}
	
	printf("Result == %lu - ", array_size);
	if (DVECCapacity(dvec) == array_size)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	
	printf("\n");

	DVECDestroy(dvec);
	
	return flag;	
}

testStatus_e Test_DVECPushBack()
{
	testStatus_e flag = PASS;
	dvec_t *dvec = NULL;
	size_t element_size = 0, array_size = 0;
	char *mock_element = "";
	char *cpy_check = NULL;
	char *field_ptr = NULL;
	size_t expected_capacity = 0;
	size_t expected_num_of_elements = 0;

	/* First Case - two pushes*/
	mock_element = "a";
	element_size = 1;
	array_size = 4;
	expected_capacity = 4;
	expected_num_of_elements = 2;
	
	printf("Case create(%lu, %lu) push(dvec, \"%s\") * %lu:\n", element_size, array_size, mock_element, expected_num_of_elements);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}
	
	DVECPushBack(dvec, mock_element);
	DVECPushBack(dvec, mock_element);

	field_ptr = (char *)dvec + sizeof(void *) + sizeof(size_t); /* &(dvec->num_of_elements) */	
	printf("dvec->num_of_elements == %lu - RESULTED: %lu - ", expected_num_of_elements, *(size_t *)field_ptr);
	if (expected_num_of_elements == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	
	field_ptr += sizeof(size_t); /* &(dvec->capacity) */	
	printf("dvec->capacity == %lu - RESULTED: %lu - ", expected_capacity, *(size_t *)field_ptr);
	if (expected_capacity == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}

	/* First Case, third push and realloc */
	expected_capacity = 8;
	expected_num_of_elements = 3;

	DVECPushBack(dvec, mock_element);

	printf("Third Push. Capacity extension check\n");
	printf("dvec->capacity == %lu - RESULTED: %lu - ", expected_capacity, *(size_t *)field_ptr);
	if (expected_capacity == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}

	/* Checking Of the copy */
	cpy_check = "aaa";

	field_ptr = (char *)dvec; /* &(dvec->array) */
	(*(char **)field_ptr)[3] = '\0'; /* hacks, just to print %s */ 
	printf("Checking copy:\n");
	printf("dvec->array == \"%s\" - RESULTED: %s - ", cpy_check, *(char **)field_ptr);
	if (0 == memcmp(*(char **)field_ptr, cpy_check, 3))
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	printf("\n");

	DVECDestroy(dvec);

	/* Second Case - two pushes*/
	mock_element = "abc";
	element_size = 3;
	array_size = 4;
	expected_capacity = 4;
	expected_num_of_elements = 2;
	
	printf("Case create(%lu, %lu) push(dvec, \"%s\") * %lu:\n", element_size, array_size, mock_element, expected_num_of_elements);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}
	
	DVECPushBack(dvec, mock_element);
	DVECPushBack(dvec, mock_element);

	field_ptr = (char *)dvec + sizeof(void *) + sizeof(size_t); /* &(dvec->num_of_elements) */	
	printf("dvec->num_of_elements == %lu - RESULTED: %lu - ", expected_num_of_elements, *(size_t *)field_ptr);
	if (expected_num_of_elements == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	
	field_ptr += sizeof(size_t); /* &(dvec->capacity) */	
	printf("dvec->capacity == %lu - RESULTED: %lu - ", expected_capacity, *(size_t *)field_ptr);
	if (expected_capacity == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}

	/* Second Case, 5 more pushes and realloc*2 */
	expected_capacity = 16;
	expected_num_of_elements = 7;

	DVECPushBack(dvec, mock_element);
	DVECPushBack(dvec, mock_element);
	DVECPushBack(dvec, mock_element);
	DVECPushBack(dvec, mock_element);
	DVECPushBack(dvec, mock_element);

	printf("Five extra pushes. Capacity extension check\n");
	printf("dvec->capacity == %lu - RESULTED: %lu - ", expected_capacity, *(size_t *)field_ptr);
	if (expected_capacity == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}

	/* Checking Of the copy */
	cpy_check = "abcabcabcabcabcabcabc";

	field_ptr = (char *)dvec; /* &(dvec->array) */
	(*(char **)field_ptr)[7*3] = '\0'; /* hacks, just to print %s */ 
	printf("Checking copy:\n");
	printf("dvec->array == \"%s\" - RESULTED: %s - ", cpy_check, *(char **)field_ptr);
	if (0 == memcmp(*(char **)field_ptr, cpy_check, 21))
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	printf("\n");

	DVECDestroy(dvec);

	return flag;
}

testStatus_e Test_DVECSize()
{
	testStatus_e flag = PASS;
	dvec_t *dvec = NULL;
	size_t element_size = 0, array_size = 0;
	size_t expected = 0;

	/* First Case: Did not push */
	element_size = 5;
	array_size = 123;
	expected = 0;

	printf("Case (%lu, %lu):\n", element_size, array_size);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}
	
	printf("Result == %lu - ", expected);
	if (DVECSize(dvec) == expected)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}	
	printf("\n");

	DVECDestroy(dvec);

	/* Second Case: Pushed Once */
	element_size = 2;
	array_size = 123;
	expected = 1;

	printf("Case (%lu, %lu):\n", element_size, array_size);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	DVECPushBack(dvec ,"a");	

	printf("Result == %lu - ", expected);
	if (DVECSize(dvec) == expected)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}	
	printf("\n");
	
	DVECDestroy(dvec);

	/* Third Case: Satisfaction */
	element_size = 2;
	array_size = 123;
	expected = 10;

	printf("Case (%lu, %lu):\n", element_size, array_size);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	*(size_t *)((char *)dvec + sizeof(void *) + sizeof(size_t)) = 10;
	/* dvec->num_of_elements = 10 */

	printf("Result == %lu - ", expected);
	if (DVECSize(dvec) == expected)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}	
	printf("\n");
	
	DVECDestroy(dvec);

	return flag;
}

testStatus_e Test_DVECPopBack()
{
	testStatus_e flag = PASS;
	dvec_t *dvec = NULL;
	size_t element_size = 0, array_size = 0;
	size_t expected_size = 0;
	size_t expected_capacity = 0;
	char *field_ptr = NULL;

	/* First Case*/
	element_size = 5;
	array_size = 123;
	expected_size = 0;

	printf("Case (%lu, %lu):\n", element_size, array_size);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	DVECPushBack(dvec, "aaaaa");
	DVECPopBack(dvec);

	field_ptr = ((char *)dvec + sizeof(void *) + sizeof(size_t)); /* ^dvec->num_of_elements. */
	printf("1 push 1 pop:\n");
	printf("dvec->num_of_elements == %lu - RESULTED: %lu - ", expected_size, *(size_t *)field_ptr);
	if (expected_size == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	
	DVECDestroy(dvec);
	printf("\n");

	/* Second Case - no push back*/
	element_size = 2;
	array_size = 4;
	expected_size = 9;

	printf("Case (%lu, %lu)\n", element_size, array_size);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	field_ptr = ((char *)dvec + sizeof(void *) + sizeof(size_t)); /* ^dvec->num_of_elements. */
	*(size_t *)field_ptr = 11;

	DVECPopBack(dvec);
	DVECPopBack(dvec);

	printf("No PushBack (- direct set to 11), Two pops:\n");
	printf("dvec->num_of_elements == %lu - RESULTED: %lu - ", expected_size, *(size_t *)field_ptr);
	if (expected_size == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	
	DVECDestroy(dvec);
	printf("\n");

	/* Third - no reallocation test*/
	element_size = 3;
	array_size = 16;
	expected_size = 5;
	expected_capacity = 16;

	printf("Case (%lu, %lu)\n", element_size, array_size);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	field_ptr = ((char *)dvec + sizeof(void *) + sizeof(size_t)); /* ^dvec->num_of_elements. */
	*(size_t *)field_ptr = 7;

	DVECPopBack(dvec);
	DVECPopBack(dvec);

	printf("No PushBack (- direct set to 7), Two pops:\n");
	printf("dvec->num_of_elements == %lu - RESULTED: %lu - ", expected_size, *(size_t *)field_ptr);
	if (expected_size == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}

	field_ptr += sizeof(size_t); /* &(array->capacity) */
	printf("No Reallocation test\n");
	printf("dvec->capacity == %lu - RESULTED: %lu - ", expected_capacity, *(size_t *)field_ptr);
	if (expected_capacity == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	
	DVECDestroy(dvec);
	printf("\n");

	/* Third - no reallocation test*/
	element_size = 9;
	array_size = 16;
	expected_size = 4;
	expected_capacity = 8;

	printf("Case (%lu, %lu)\n", element_size, array_size);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	field_ptr = ((char *)dvec + sizeof(void *) + sizeof(size_t)); /* ^dvec->num_of_elements. */
	*(size_t *)field_ptr = 7;

	DVECPopBack(dvec);
	DVECPopBack(dvec);
	DVECPopBack(dvec);

	printf("No PushBack (- direct set to 7), Three pops:\n");
	printf("dvec->num_of_elements == %lu - RESULTED: %lu - ", expected_size, *(size_t *)field_ptr);
	if (expected_size == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}

	field_ptr += sizeof(size_t); /* &(array->capacity) */
	printf("Reallocation test\n");
	printf("dvec->capacity == %lu - RESULTED: %lu - ", expected_capacity, *(size_t *)field_ptr);
	if (expected_capacity == *(size_t *)field_ptr)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	
	DVECDestroy(dvec);
	printf("\n");

	return flag;
}

testStatus_e Test_DVECGetItemAddress()
{
	testStatus_e flag = PASS;
	dvec_t *dvec = NULL;
	size_t element_size = 0, array_size = 0;
	char *field_ptr = NULL;
	void *expected_address = NULL;
	void *item_address = NULL;
	size_t index = 0;

	/* First Case*/
	element_size = 21;
	array_size = 4;
	index = 1;

	printf("Case (%lu, %lu), index: %lu\n", element_size, array_size, index);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	field_ptr = (char *)dvec; /* &(dvec->array) */
	expected_address = (void *)(*(char **)field_ptr + element_size * index);
	item_address = DVECGetItemAddress(dvec, index);
	printf("GetItemAddtess == %p - RESULTED: %p - ", expected_address ,item_address );
	if ( item_address == expected_address)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}

	DVECDestroy(dvec);
	printf("\n");

	/* Second Case*/
	element_size = 100;
	array_size = 4;
	index = 0;

	printf("Case (%lu, %lu), index: %lu\n", element_size, array_size, index);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	field_ptr = (char *)dvec; /* &(dvec->array) */
	expected_address = (void *)(*(char **)field_ptr + element_size * index);
	item_address = DVECGetItemAddress(dvec, index);
	printf("GetItemAddtess == %p - RESULTED: %p - ", expected_address ,item_address );
	if ( item_address == expected_address)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	
	DVECDestroy(dvec);
	printf("\n");

	/* Third Case*/
	element_size = 500;
	array_size = 20;
	index = 10;

	printf("Case (%lu, %lu), index: %lu\n", element_size, array_size, index);
	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allcation failure\n");
		return FAIL;
	}

	field_ptr = (char *)dvec; /* &(dvec->array) */
	expected_address = (void *)(*(char **)field_ptr + element_size * index);
	item_address = DVECGetItemAddress(dvec, index);
	printf("GetItemAddtess == %p - RESULTED: %p - ", expected_address ,item_address );
	if ( item_address == expected_address)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}

	DVECDestroy(dvec);
	printf("\n");
	
	return flag;	
}

testStatus_e Test_DVECReserve()
{
	testStatus_e flag = PASS;
	dvec_t *dvec = NULL;
	size_t expected_capacity = 0;
	size_t reserve = 0;
	size_t result = 0;
	size_t array_size = 0;
	size_t element_size = 0;
	char *field_ptr = NULL;

	/* First Case - Capacity Expension */
	element_size = 5;
	array_size = 4;
	reserve = 15;
	expected_capacity = reserve;

	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allocation failure\n");
		return FAIL;
	}

	printf("Capacity expension: create(%lu, %lu), reserve(dvec, %lu)\n", element_size, array_size, reserve);

	DVECReserve(dvec, reserve);
	field_ptr = (char *)dvec + sizeof(void *) + sizeof(size_t) * 2; /*&(dvec->capacity)*/
	result = *(size_t *)field_ptr;
	printf("Expected = %lu - Resulted = %lu - ", expected_capacity, result);
	if (result == expected_capacity)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}

	DVECDestroy(dvec);
	printf("\n");

	/* Second Case - Capacity Expension */
	element_size = 5;
	array_size = 30;
	reserve = 2;
	expected_capacity = reserve;

	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allocation failure\n");
		return FAIL;
	}

	printf("Capacity Decrease, unlblocked: create(%lu, %lu), reserve(dvec, %lu)\n", element_size, array_size, reserve);

	DVECReserve(dvec, reserve);
	field_ptr = (char *)dvec + sizeof(void *) + sizeof(size_t) * 2; /*&(dvec->capacity)*/
	result = *(size_t *)field_ptr;
	printf("Expected = %lu - Resulted = %lu - ", expected_capacity, result);
	if (result == expected_capacity)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	DVECDestroy(dvec);
	printf("\n");

	/* Third Case - Capacity Expension */
	element_size = 5;
	array_size = 30;
	reserve = 5;
	expected_capacity = 8;

	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allocation failure\n");
		return FAIL;
	}

	printf("Capacity Decrease, Blocked, 7 members: create(%lu, %lu), reserve(dvec, %lu)\n", element_size, array_size, reserve);

	field_ptr = (char *)dvec + sizeof(void *) + sizeof(size_t);
	*(size_t *)field_ptr = 7;

	DVECReserve(dvec, reserve);
	field_ptr += sizeof(size_t); /*&(dvec->capacity)*/
	result = *(size_t *)field_ptr;
	printf("Expected = %lu - Resulted = %lu - ", expected_capacity, result);
	if (result == expected_capacity)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	DVECDestroy(dvec);
	printf("\n");

	/* Third Case - Capacity Expension */
	element_size = 5;
	array_size = 30;
	reserve = 5;
	expected_capacity = 6;

	dvec = DVECCreate(element_size, array_size);
	if (NULL == dvec)
	{
		perror("allocation failure\n");
		return FAIL;
	}

	printf("Capacity Decrease, Blocked exact number of members: create(%lu, %lu), reserve(dvec, %lu)\n", element_size, array_size, reserve);

	field_ptr = (char *)dvec + sizeof(void *) + sizeof(size_t);
	*(size_t *)field_ptr = 5;

	DVECReserve(dvec, reserve);
	field_ptr += sizeof(size_t); /*&(dvec->capacity)*/
	result = *(size_t *)field_ptr;
	printf("Expected = %lu - Resulted = %lu - ", expected_capacity, result);
	if (result == expected_capacity)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		flag = FAIL;
	}
	DVECDestroy(dvec);
	printf("\n");

	return flag;
}
