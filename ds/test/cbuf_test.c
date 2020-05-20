#include <stdio.h> /* printf */

#include "../include/cbuf.h"

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n\n"); \
	} \

/* 
typedef struct CBUF cbuf_t;

cbuf_t *CBUFCreate(size_t nbytes);
void CBUFDestroy(cbuf_t *cbuf);
size_t CBUFWrite(cbuf_t *cbuf, const void *data, size_t nbytes);
size_t CBUFRead(cbuf_t *cbuf, void *data, size_t nbytes);
size_t CBUFCapacity(cbuf_t *cbuf);
int CBUFIsEmpty(const cbuf_t *cbuf);
size_t CBUFFreeSpace(cbuf_t *cbuf);
*/

int FlowCreate()
{
	int ret = 0;
	size_t capacity = 12;
	cbuf_t *cbuf = CBUFCreate(capacity);

	puts("Begin FlowCreate");

	if(capacity != CBUFCapacity(cbuf))
	{
		ret = 1;
	}
	printf("set capacity %lu checked %lu\n", capacity, CBUFCapacity(cbuf));

	if(0 == CBUFIsEmpty(cbuf))
	{
		ret = 1;
	}
	printf("set capacity %lu non written. IsEmpty = %d\n", capacity, CBUFIsEmpty(cbuf));

	if(0 == CBUFFreeSpace(cbuf))
	{
		ret = 1;
	}
	printf("set capacity %lu non written. FreeSpace = %lu\n", capacity, 
													 CBUFFreeSpace(cbuf));

	CBUFDestroy(cbuf);
	
	return ret;
}

int FlowReadNone()
{
	int ret = 0;
	size_t capacity = 12;
	cbuf_t *cbuf = CBUFCreate(capacity);
	char buffer[50];

	puts("Begin FlowReadNone");

	printf("set capacity %lu non written. Read = %lu\n", capacity, 
											 CBUFRead(cbuf, buffer, capacity));
	perror("errno");

	CBUFDestroy(cbuf);

	return ret;
}

int FlowWriteReadByte()
{
	int ret = 0;
	size_t capacity = 2;
	cbuf_t *cbuf = CBUFCreate(capacity);
	char write_buffer[] = "abcdefg";
	char read_buffer[50];
	
	puts("Begin FlowWriteReadByte");

	if(capacity != CBUFCapacity(cbuf))
	{
		ret = 1;
	}
	printf("set capacity %lu non written. FreeSpace = %lu\n", capacity,	CBUFFreeSpace(cbuf));
	printf("written %lu\n", CBUFWrite(cbuf, write_buffer, capacity));

	printf("set capacity and writte %lu. FreeSpace = %lu\n", capacity, CBUFFreeSpace(cbuf));
	printf("read %lu\n", CBUFRead(cbuf, read_buffer, capacity));
	
	puts(read_buffer);
	
	CBUFDestroy(cbuf);
	
	return ret;
}

int main()
{
	RUN_TEST(FlowCreate);
	RUN_TEST(FlowReadNone);
	RUN_TEST(FlowWriteReadByte);
	
	return 0;
}
