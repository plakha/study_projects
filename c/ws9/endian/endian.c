#include <stdio.h> /* printf for test*/
#include <string.h> /* strcmp for test */
#include <stdlib.h>/* malloc for test */
#include <errno.h> /* perror for test */

#include <stddef.h> /* sizeof */
#include <assert.h> /* assert */

#define IS_LITTLE_ENDIAN \
		0x2928 == (unsigned short *)&"()"\


int IsLittleEndian()
{
	short int tmp = 0x1;
	
	return 0x1 == *(char *)&n;
}

