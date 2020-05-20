/*******************************************************************************
Author: Andrei Plakhota
Reviewer: Daniel Maizel



*******************************************************************************/
#include <stdio.h> /* printf */

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \

#define SIZEOF_VAR(x) (int)(&x + 1) - (int)&x
	
#define SIZEOF_T(type)  (int)((type *)1 + 1) - (int)(type *)1

int TestSizeVar();

int TestSizeT();

union numbers
{
	int i;/* 4B */
	float f;/* 4B */
	double d;/* 8B */
};/* 16B */

struct x
{
	int i;/* 4B */
	char c;/* 1 B */
	/* char pad[3] */
	double d;/* 8B */
	short s;/* 2B */
	/* char pad[6] */
};/* 24B */

struct card
{
	unsigned int suit : 2;/* 2b */
	unsigned int face_value : 4;/* 4b */ 
	// pad 2b
	//char pad[3]
};//4B

int main()
{
	RUN_TEST(TestSizeVar);
	RUN_TEST(TestSizeT);

	return 0;	
}

int TestSizeVar()
{
	char c;
	short int s;
	int i;
	unsigned int u;
	long int l;
	float f;
	double d;
	
	return !(SIZEOF_VAR(c) == sizeof(c)
			&& SIZEOF_VAR(s) == sizeof(s)
			&& SIZEOF_VAR(i) == sizeof(i)
			&& SIZEOF_VAR(u) == sizeof(u)
			&& SIZEOF_VAR(l) == sizeof(l)
			&& SIZEOF_VAR(f) == sizeof(f)
			&& SIZEOF_VAR(d) == sizeof(d));
}

int TestSizeT()
{
	return !(SIZEOF_T(char) == sizeof(char)
			&& SIZEOF_T(short int) == sizeof(short int)
			&& SIZEOF_T(int) == sizeof(int)
			&& SIZEOF_T(unsigned int) == sizeof(unsigned int)
			&& SIZEOF_T(long int) == sizeof(long int)
			&& SIZEOF_T(float) == sizeof(float)
			&& SIZEOF_T(double) == sizeof(double)
			&& SIZEOF_T(union numbers) == sizeof(union numbers)
			&& SIZEOF_T(struct x) == sizeof(struct x)
			&& SIZEOF_T(struct card) == sizeof(struct card));
}
