/*******************************************************************************
+ unsigned int Pow2(unsigned int x, int y);
+ int IsPow2(unsigned int x);
+ int IsPow2NoLoop(unsigned int x); - implement division of unsigned int
+-  unsigned int Add1(unsigned int x); - reimplement witout recursion
+ void Print3BitsOn(unsigned int *n, int length);
+ char ByteMirror(unsigned char *num);
+ char ByteMirrorNoLoop(unsigned char *num);
+ unsigned int ByteMirrorMask(unsigned int *num)
+ int AreB2andB6(unsigned char num);
+ int AreB2orB6(unsigned char num);
+ unsigned char SwapBit5with3(unsigned char num);
+ unsigned int NextDiv16(unsigned int x);
+ void Swap(unsigned long int *x,unsigned long int *y);
+ unsigned int CountSetBits(unsigned int x);
unsigned int CountSetBitsNoLoop(unsigned int x);
void PrintBitLUT(char *lut);

	
*******************************************************************************/
#include <stdio.h> /*printf*/

char lut[257];

unsigned int Pow2(unsigned int x, int y);
int IsPow2(unsigned int x);
int IsPow2NoLoop(unsigned int x);
unsigned int Add1(unsigned int x);
unsigned int Add(unsigned int x, unsigned int y);
void Print3BitsOn(unsigned int *n, int length);
unsigned int ByteMirror(unsigned int *num);
unsigned char ByteMirrorNoLoop(unsigned char *num);
unsigned int ByteMirrorMask(unsigned int *num);
int AreB2andB6(unsigned char num);
int AreB2orB6(unsigned char num);
unsigned char SwapBit5with3(unsigned char num);
unsigned int NextDiv16(unsigned int x);
void Swap(int *x, int *y);
unsigned int CountSetBits(unsigned int x);
unsigned int CountSetBitsNoLoop(unsigned int x);
void CreateBitLUT(char *lut);

int main()
{

	/*CreateBitLUT(lut);
	
	printf("%d \n", (int)lut[1]);*/
	/*unsigned int arr[] = {1, 19, 5, 7};
	Print3BitsOn(arr, 4);*/
	/*printf("%u", Pow2(8, -1));*/
	/*printf("%u", IsPow2(1));*/
	/*printf("And %u\n", AreB2andB6(0x65));
	printf("Or %u\n", AreB2orB6(0x65));*/
	/*printf("0x%x\n", SwapBit5with3(0xF0));*/
	
	/*int x = 1, y = 2;
	printf("%d %d\n", x, y);
	Swap(&x, &y);
	printf("%d %d\n", x, y);*/
	/*unsigned int x = 0x80000000;
	printf("0x%x", ByteMirrorMask(&x));*/

	return 0;
}

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

unsigned int Add1(unsigned int x)/*reimplement on its own*/
{
	
	return Add(x, 1);
}

unsigned int Add(unsigned int x, unsigned int y)
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

unsigned int ByteMirror(unsigned int *num)
{
	unsigned int res = 0x0;
	unsigned int size = 8 * sizeof(unsigned int);
	unsigned int n = 0;
	
	for(; n < size; ++n)
	{
	*num = *num >> n; 
	res =res | (*num & 0x1) << (size - 1 - n);
	}

	return *num = res;
}

unsigned char ByteMirrorNoLoop(unsigned char *num)
{
	
	return *num = *num << 7
				| (*num & 0x2) << 5
				| (*num & 0x4) << 3
				| (*num & 0x8) << 1
				| (*num & 0x10) >> 1
				| (*num & 0x20) >> 3
				| (*num & 0x30) >> 5
				| (*num & 0x40) >> 7;
}

unsigned int ByteMirrorMask(unsigned int *num)
{
	*num = (*num & 0x0000FFFF) << 16 | (*num & 0xFFFF0000) >> 16;
	*num = (*num & 0x00FF00FF) << 8 | (*num & 0xFF00FF00) >> 8;
	*num = (*num & 0x0F0F0F0F) << 4 | (*num & 0xF0F0F0F0) >> 4;
	*num = (*num & 0x33333333) << 2 | (*num & 0xCCCCCCCC) >> 2;
	
	return *num = (*num & 0x55555555) << 1 | (*num & 0xAAAAAAAA) >> 1;
}

/*BUG!!
unsigned char ByteMirrorNoLoop(unsigned char *num) 
{

	return *num = (((*num << 4) << 2) << 1)
				| (((*num << 4) << 2) >> 1)
				| (((*num << 4) >> 2) << 1)
				| (((*num << 4) >> 2) >> 1)
				| (((*num >> 4) << 2) << 1)
				| (((*num >> 4) << 2) >> 1)
				| (((*num >> 4) >> 2) << 1)
				| (((*num >> 4) >> 2) >> 1);
}*/

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

void CreateBitLUT(char *lut)
{
	unsigned char i = 0;
	for(; i < 255; ++i)
	{	
		lut[i] = (char)CountSetBits((unsigned int)i);
	}
}

unsigned int CountSetBitsNoLoop(unsigned int x)
{
	
	return x;
}





















