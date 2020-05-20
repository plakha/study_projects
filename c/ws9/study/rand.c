/****
The C library function int rand(void) returns a pseudo-random number in the range of 0 to RAND_MAX.

RAND_MAX is a constant whose default value may vary between implementations but it is granted to be at least 32767.
***/

#include <stdio.h> /* printf */
#include <stdlib.h> /* rand */

int main()
{
;
	printf("%d %d\n", rand(), RAND_MAX);

	return 0;
}
