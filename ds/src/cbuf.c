/* 
4.6.2019
Author Andrei
Reviewer Sasha
*/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <errno.h> /* errno */

#include "../include/cbuf.h" /* cbuf header */

struct CBUF
{
    size_t capacity;
    size_t size;/* bytes written not read*/
    size_t read_offset;/* read bytes from "start" of buffer */
    void *buff; /* "start" of "circular" buffer */
};

cbuf_t *CBUFCreate(size_t nbytes)
{
	cbuf_t *cbuf = NULL;

	assert(0 < nbytes);
	
	cbuf = (cbuf_t *)malloc(sizeof(*cbuf));
	if(NULL == cbuf)
	{

		return NULL;
	}

	cbuf->buff = malloc(nbytes);
	if(NULL == cbuf->buff)
	{
		free(cbuf);

		return NULL;
	}
	
	cbuf->capacity = nbytes;
	cbuf->size = 0;
	cbuf->read_offset = 0;

	return cbuf;
}

void CBUFDestroy(cbuf_t *cbuf)
{
	assert(NULL != cbuf);

	free(cbuf->buff);
	free(cbuf);
}

size_t CBUFWrite(cbuf_t *cbuf, const void *data, size_t nbytes)
{
	size_t count = ((cbuf->capacity - cbuf->size) < nbytes) ? 
										(cbuf->capacity - cbuf->size) : nbytes;
		
	assert(NULL != cbuf);
	assert(cbuf->capacity >= cbuf->size);
	
	nbytes = count;

	while(0 < count) 
	{
		((char *)(cbuf->buff))[(cbuf->read_offset 
								+ cbuf->size) % cbuf->capacity] = *(char *)data;
		data = (char *)data + 1;
		++(cbuf->size);
		--count;
	}

	if(cbuf->size >= cbuf->capacity)
	{
		errno = EOVERFLOW;
	}
	
	return nbytes;
		
}

size_t CBUFRead(cbuf_t *cbuf, void *data, size_t nbytes)
{
	size_t count = (nbytes < cbuf->size) ? nbytes : cbuf->size;

	assert(NULL != cbuf);
	assert(cbuf->capacity >= cbuf->size);

	nbytes = count;
	
	while(0 < count)
	{
		*(char *)data = 
				((char *)(cbuf->buff))[(cbuf->read_offset) % cbuf->capacity];
		data = (char *)data + 1;
		++(cbuf->read_offset);
		--cbuf->size;
		--count;
	}
	if(0 == cbuf->size)
	{
		errno = ENODATA;
	}

	return nbytes;
}

size_t CBUFCapacity(cbuf_t *cbuf)
{
	assert(NULL != cbuf);

	return cbuf->capacity;
}

int CBUFIsEmpty(const cbuf_t *cbuf)
{
	assert(NULL != cbuf);

	return 0 == cbuf->size;
}

size_t CBUFFreeSpace(cbuf_t *cbuf)
{
	assert(NULL != cbuf);

	return cbuf->capacity - cbuf->size;
}
