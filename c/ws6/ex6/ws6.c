/*******************************************************************************
Author: Andrei Plakhota
Reviewer: Yael Lotan
General info: some excercises on bit logic.
*******************************************************************************/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*sizeof*/
#include "ws6.h"


const unsigned char lut[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,  4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2,  3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 0};


static unsigned int Add(unsigned int x, unsigned int y);
static void CreateBitLUT(unsigned char *lut);
static void PrintIntByBit(unsigned int num);


unsigned int Pow2(unsigned int x, int y)
{
	if(0 > y)
	{

		return x >> -y;
	}
	
	return x << y;
}

int IsPow2(unsigned int x)
{

	return (1 == CountSetBits(x));
}

int IsPow2NoLoop(unsigned int x)
{
	if(0x0 == x)
	{
		
		return 0;
	}

	return !(x & (x - 1));
}

unsigned int Add1(unsigned int x)
{
	
	return Add(x, 1);
}

static unsigned int Add(unsigned int x, unsigned int y)
{
	if(!(x & y))
	{

		return x ^ y;
	}

	return Add(x ^ y, (x & y) << 1);
}

void Print3BitsOn(unsigned int *n, int length)
{

	int i = 0;
	for(; i < length; ++i)
	{
		if(3 == CountSetBits(n[i]))
		printf("%u ", n[i]);
	}
	puts("\n");
}

unsigned int ByteMirror(unsigned int num)
{
	unsigned int res = 0x0;
	unsigned int size = 8 * sizeof(unsigned int);
	unsigned int n = 0;
	
	for(; n < size; ++n)
	{
	res = res | (num & 0x1) << (size - 1 - n);
	num = num >> 1;
	}

	return res;
}

unsigned char ByteMirrorNoLoop(unsigned char num)
{
	
	return num << 7
		| (num & 0x2) << 5
		| (num & 0x4) << 3
		| (num & 0x8) << 1
		| (num & 0x10) >> 1
		| (num & 0x20) >> 3
		| (num & 0x30) >> 5
		| (num & 0x40) >> 7;
}

unsigned int ByteMirrorMask(unsigned int num)
{
	num = (num & 0x0000FFFF) << 16 | (num & 0xFFFF0000) >> 16;
	num = (num & 0x00FF00FF) << 8 | (num & 0xFF00FF00) >> 8;
	num = (num & 0x0F0F0F0F) << 4 | (num & 0xF0F0F0F0) >> 4;
	num = (num & 0x33333333) << 2 | (num & 0xCCCCCCCC) >> 2;
	
	return (num & 0x55555555) << 1 | (num & 0xAAAAAAAA) >> 1;
}

int AreB2andB6(unsigned char num)
{

	return ((num & 0x2) >> 1) & ((num & 0x20) >> 5);
}

int AreB2orB6(unsigned char num)
{

	return ((num & 0x2) >> 1) | ((num & 0x20) >> 5);
}

unsigned char SwapBit5with3(unsigned char num)
{

	return (num & 0xEB) | ((num & 0x4) << 2) | ((num & 0x10) >> 2);
}

unsigned int NextDiv16(unsigned int x)
{

	return (x >> 4) << 4;
}

void Swap(int *x, int *y)
{

	*x = (*x ^ *y);
	*y = *x ^ *y;
	*x = *x ^ *y;
}

unsigned int CountSetBits(unsigned int x)
{
	int i = 0;
	int count = 0;

	for(; i < 64; ++i)
	{
		if(x & 0x1)
		{

			++count;
		}
		x = x >> 1;
	}
	
	return count;
}

void PrintByBit(float num)
{	
	unsigned int offset = (sizeof(num) * 8 - 1);
	unsigned int copy = *((int *)&num);
	
	do
	{
	printf ("%1x", (copy >> offset) & 0x1);
	--offset;
	}
	while(0 < offset);
	printf ("%1x", copy & 0x1);
	puts("\n");
}

static void PrintIntByBit(unsigned int num)
{	
	unsigned int offset = (sizeof(num) * 8 - 1);
	unsigned int copy = *((unsigned int *)&num);
	
	do
	{
	printf ("%1x", (copy >> offset) & 0x1);
	--offset;
	}
	while(0 < offset);
	printf ("%1x", copy & 0x1);
	puts("\n");
}

static void CreateBitLUT(unsigned char *lut)
{
	unsigned char i = 0;
	for(; i < 255; ++i)
	{	
		lut[i] = (unsigned char)CountSetBits((unsigned int)i);
	}
}

unsigned int CountSetBitsNoLoop(unsigned int x)
{
	int count = 0;
	count += lut[(unsigned char)x & 0xFF];
	x >>= 8;
	count += lut[(unsigned char)x & 0xFF];
	x >>= 8;
	count += lut[(unsigned char)x & 0xFF];
	x >>= 8;
	count += lut[(unsigned char)x & 0xFF];
	return count;
}















