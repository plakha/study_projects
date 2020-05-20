#include <stdio.h> /*printf*/
#include <stdlib.h> /*sizeof*/
#include "ws6.h"

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \

int TestPow2()
{

	return(!(0 == Pow2(0, 1)));
}

int TestIsPow2()
{ 
	
	return !IsPow2(4);
}


int TestIsPow2NoLoop()
{
	
	return !IsPow2NoLoop(2);
}

int TestAdd1()
{
	
	return !(11 == Add1(10));
}

int TestByteMirror()
{
	
	return !(2147483648 == ByteMirror(1));
}

int TestByteMirrorNoLoop()
{

	return !(16 == ByteMirrorNoLoop(8));
}

int TestByteMirrorMask()
{

	return !(2147483648 == ByteMirrorMask(1));
}


int TestAreB2orB6()
{

	return !AreB2orB6(19);
}

int TestAreB2andB6()
{

	return !AreB2andB6(34);
}

int TestSwapBit5with3()
{

	return !(5 == SwapBit5with3(17));
}

int TestNextDiv16()
{

	return !(32 == NextDiv16(40));
}

int TestSwap()
{
	int	a = 1, b = 2;
	Swap(&a, &b);
	return !(2 == a && 1 == b);
}

int TestCountSetBits()
{

	return !(4 == CountSetBits(23));
}

int TestCountSetBitsNoLoop()
{

	return !(4 == CountSetBitsNoLoop(23));
}

int main()
{
	RUN_TEST(TestPow2);
	RUN_TEST(TestIsPow2);
	RUN_TEST(TestIsPow2NoLoop);
	RUN_TEST(TestAdd1);
	RUN_TEST(TestByteMirror);
	RUN_TEST(TestByteMirrorNoLoop);
	RUN_TEST(TestByteMirrorMask);	
	RUN_TEST(TestAreB2andB6);
	RUN_TEST(TestAreB2orB6);
	RUN_TEST(TestSwapBit5with3);
	RUN_TEST(TestNextDiv16);
	RUN_TEST(TestSwap);
	RUN_TEST(TestCountSetBits);
	RUN_TEST(TestCountSetBitsNoLoop);

	return 0;
}

