
#include <stdio.h> /* printf */

char s[50] = "dd";



int main()
{
	extern auto char a;

	printf("%d\n", a);

	return 0;
}
