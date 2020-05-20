#include <stddef.h>
struct point 
{
	unsigned char x : 1;
	unsigned char y : 1;
	unsigned char truth_value : 1;
};

typedef struct point point_type;

typedef struct
{
	int par1, par2;
} p_type;

int main()
{
	point_type b = {1, 2,-0}; /*what prints when uninitialized?*/
	p_type a;
	unsigned int max = 0xffffffff;
/*	a = {10, 20}; cannot access thusly*/

	/*printf("%d %d %d \n", b.x, b.y, b.truth_value);
	printf("%u\n", sizeof(b));*/
	/*printf("%u\n", offsetof(NULL, b));*/
	printf("%u", max);
}
