#include <stdio.h> /* printf for test*/
#include <string.h> /* strcmp for test */
#include <stdlib.h>/* malloc for test */
#include <errno.h> /* perror for test */

#include <stddef.h> /* sizeof */
#include <assert.h> /* assert */

#define IS_LITTLE_ENDIAN \
	*(char *)&((short)"@A" 0x1 ; \

main()
{
	printf("%d", IS_LITTLE_ENDIAN);

	return 0;
}
