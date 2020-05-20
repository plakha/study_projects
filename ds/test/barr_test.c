#include <stdio.h> /* printf */

#include "../include/barr.h"

#define RUN_TEST(test) \
	if(!test()) \
	{ \
		printf(#test"[OK]\n"); \
	} \
	else \
	{ \
		printf(#test"[FAIL]\n"); \
	} \

int TestBARRSetBit()
{
	if(2 == BARRSetBit(0x0, 1, 1)
		&& 3 == BARRSetBit(1, 1, 1)
		&& 524288 == BARRSetBit(0, 19, 1)
		&& 0 == BARRSetBit(0x1, 0, 0))
	{

		return 0;
	}
	
	return 1;
}

int TestBARRSetOn()
{
	if(2 == BARRSetOn(0x0, 1)
		&& 3 == BARRSetOn(1, 1)
		&& 524288 == BARRSetOn(0, 19))
	{

	return 0;
	}
	
	return 1;
}

int TestBARRSetOff()
{
	if(0 == BARRSetOff(0x1, 0))
	{

	return 0;
	}
	
	return 1;
}

int TestBARRFlip()
{
	if(0x0 == BARRFlip(0x1, 0))
	{

		return 0;
	}

	return 1;
}

int TestBARRMirror()
{
	if( (0x0 == BARRMirror(0x0)) 
		&& (0xFFFFFFFF00000000 == BARRMirror(0xFFFFFFFF)))
	{

		return 0;
	}

	return 1;
}

int TestBARRIsOn()
{
	if(BARRIsOn(0x1, 0))
	{

		return 0;
	}

	return 1;
}

int TestBARRIsOff()
{
	if(0 != BARRIsOff(0x1LU, 1))
	{

		return 0;
	}

	return 1;
}

int TestBARRotateLeft()
{
	if(0x2 == BARRotateLeft(0x1, 1))
	{

		return 0;
	}

	return 1;
}

int TestBARRotateRight()
{
	if(0x1 == BARRotateRight(0x2, 1))
	{

	return 0;
	}
	
	return 1;
}

int TestBARRCountOn()
{
	if(2 == BARRCountOn(0x3))
	{

		return 0;
	}

	return 1;
}

int TestBARRCountOff()
{
	if( (64 == BARRCountOff(0x0))
		&& (63 == BARRCountOff(0x1)))
	{

	return 0;
	}

	return 1;
}

int TestBARRMirrorLUT()
{
	if( 0xFFFFFFFF00000000 == BARRMirrorLUT(0x00000000FFFFFFFFLU))
	{
	
		return 0;
	}

	return 1;
}

int TestBARRCountOnLUT()
{
	
	if(2 == BARRCountOnLUT(0x3)
		&& (32 == BARRCountOnLUT(0x6666666666666666))
		&& (31 == BARRCountOnLUT(0x6666666666666662)))
	{

		return 0;
	}

	return 1;
}

int main()
{

	RUN_TEST(TestBARRSetOn);
	RUN_TEST(TestBARRSetOff);
	RUN_TEST(TestBARRSetBit);
	RUN_TEST(TestBARRFlip);
	RUN_TEST(TestBARRMirror);
	RUN_TEST(TestBARRIsOn);
	RUN_TEST(TestBARRIsOff);
	RUN_TEST(TestBARRotateLeft);
	RUN_TEST(TestBARRotateRight);
	RUN_TEST(TestBARRCountOn)
	RUN_TEST(TestBARRCountOff);
	RUN_TEST(TestBARRMirrorLUT);
	RUN_TEST(TestBARRCountOnLUT);



	return 0;
}

