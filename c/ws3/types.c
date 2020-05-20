/*******************************************************************************
List of all data types in C.




*******************************************************************************/


#include <stdio.h>/*printf*/
#include <stddef.h>/*size_t*/



int main()
{
	
	printf("%s  \n", "types	 	sizes");
	printf("%s 		 %lu-bytes\n", "char", sizeof(char));
	printf("%s  	 %lu-bytes\n", "short int", sizeof(short int));
	printf("%s 		 %lu-bytes\n", "int", sizeof(int));
	printf("%s 		 %lu-bytes\n", "long int", sizeof(long int));
	printf("%s 		 %lu-bytes\n", "void*", sizeof(void *));
	printf("%s 		 %lu-bytes\n", "float", sizeof(float));
	printf("%s 		 %lu-bytes\n", "double", sizeof(double));
	printf("%s 		 %lu-bytes\n", "long double", sizeof(long double));

	return 0;
}

