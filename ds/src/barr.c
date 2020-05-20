/*******************************************************************************


*******************************************************************************/

#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */

#include "barr.h"

static const long unsigned int mask1lut[] = {0x1LU, 0x2LU, 0x4, 0x8, 0x10, 0x20, 
	0x40, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 
	0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000, 
	0x1000000, 0x2000000, 0x4000000, 0x8000000, 0x10000000, 0x20000000, 
	0x40000000, 0x80000000, 0x100000000, 0x200000000, 0x400000000, 
	0x800000000, 0x1000000000, 0x2000000000, 0x4000000000, 0x8000000000, 
	0x10000000000, 0x20000000000, 0x40000000000, 0x80000000000, 0x100000000000, 
	0x200000000000, 0x400000000000, 0x800000000000, 0x1000000000000, 
	0x2000000000000, 0x4000000000000, 0x8000000000000, 0x10000000000000, 
	0x20000000000000, 0x40000000000000, 0x80000000000000, 0x100000000000000, 
	0x200000000000000, 0x400000000000000, 0x800000000000000, 
	0x1000000000000000,	0x2000000000000000, 0x4000000000000000, 
	0x8000000000000000};

static const long unsigned int mask0lut[] = {0xfffffffffffffffe, 
	0xfffffffffffffffd, 0xfffffffffffffffb, 0xfffffffffffffff7, 
	0xffffffffffffffef, 0xffffffffffffffdf, 0xffffffffffffffbf, 
	0xffffffffffffff7f, 0xfffffffffffffeff, 0xfffffffffffffdff, 
	0xfffffffffffffbff,	0xfffffffffffff7ff, 0xffffffffffffefff, 
	0xffffffffffffdfff, 0xffffffffffffbfff, 0xffffffffffff7fff, 
	0xfffffffffffeffff,	0xfffffffffffdffff, 0xfffffffffffbffff, 
	0xfffffffffff7ffff, 0xffffffffffefffff, 0xffffffffffdfffff, 
	0xffffffffffbfffff, 0xffffffffff7fffff, 0xfffffffffeffffff, 
	0xfffffffffdffffff, 0xfffffffffbffffff, 0xfffffffff7ffffff, 
	0xffffffffefffffff, 0xffffffffdfffffff, 0xffffffffbfffffff, 
	0xffffffff7fffffff, 0xfffffffeffffffff, 0xfffffffdffffffff, 
	0xfffffffbffffffff, 0xfffffff7ffffffff, 0xffffffefffffffff, 
	0xffffffdfffffffff, 0xffffffbfffffffff, 0xffffff7fffffffff, 
	0xfffffeffffffffff, 0xfffffdffffffffff, 0xfffffbffffffffff, 
	0xfffff7ffffffffff, 0xffffefffffffffff, 0xffffdfffffffffff, 
	0xffffbfffffffffff, 0xffff7fffffffffff, 0xfffeffffffffffff, 
	0xfffdffffffffffff, 0xfffbffffffffffff, 0xfff7ffffffffffff, 
	0xffefffffffffffff, 0xffdfffffffffffff, 0xffbfffffffffffff, 
	0xff7fffffffffffff, 0xfeffffffffffffff, 0xfdffffffffffffff, 
	0xfbffffffffffffff, 0xf7ffffffffffffff, 0xefffffffffffffff, 
	0xdfffffffffffffff, 0xbfffffffffffffff, 0x7fffffffffffffff};

size_t BARRSetBit(size_t arr, int index, int value)
{
	assert(0 == value || 1 == value);
	assert((0 <= index) && (63 >= index));

	if(0 == value)
	{
	
		return arr & mask0lut[index];
	}
	
	return arr | mask1lut[index];
}

size_t BARRSetOn(size_t arr, int index)
{	
	assert((0 <= index) && (63 >= index));
	
	return arr | mask1lut[index];
}

size_t BARRSetOff(size_t arr, int index)
{	
	assert((0 <= index) && (63 >= index));
	
	return arr & mask0lut[index];
}

size_t BARRFlip(size_t arr, int index)
{
	assert((0 <= index) && (63 >= index));

	return arr ^ mask1lut[index];
}

size_t BARRMirror(size_t arr)
{
	arr = ((arr & 0x00000000FFFFFFFF) << 32) 
		| ((arr & 0xFFFFFFFF00000000) >> 32);
	arr = ((arr & 0x0000FFFF0000FFFF) << 16) 
		| ((arr & 0xFFFF0000FFFF0000) >> 16);
	arr = ((arr & 0x00FF00FF00FF00FF) << 8) | ((arr & 0xFF00FF00FF00FF00) >> 8);
	arr = ((arr & 0x0F0F0F0F0F0F0F0F) << 4) | ((arr & 0xF0F0F0F0F0F0F0F0) >> 4);
	arr = ((arr & 0x3333333333333333) << 2) | ((arr & 0xCCCCCCCCCCCCCCCC) >> 2);
	
	return arr = ((arr & 0x5555555555555555) << 1) 
				| ((arr & 0xAAAAAAAAAAAAAAAA) >> 1);
}

int BARRIsOn(size_t arr, int index)
{
	assert((0 <= index) && (63 >= index));

	return 0x0 != (arr & mask1lut[index]);
}

int BARRIsOff(size_t arr, int index)
{
	assert((0 <= index) && (63 >= index));
	
	return 0x0 == (arr & mask1lut[index]);
}

size_t BARRRotateLeft(size_t arr, size_t amount)
{
	size_t mask = 0x8000000000000000;
	size_t shift = 8 * sizeof(arr) - 1;
	
	amount %= 8 * sizeof(arr);
	while(0 < amount)
	{
		arr = ((arr & mask) >> shift) | (arr << 1);
		--amount;
	}

	return arr;
}

size_t BARRRotateRight(size_t arr, size_t amount)
{
	size_t mask = 0x1;
	size_t shift = 8 * sizeof(arr) - 1;

	amount %= 8 * sizeof(arr);
	while(0 < amount)
	{
		arr = ((arr & mask) << shift) | (arr >> 1);
		--amount;
	}

	return arr;
}

size_t BARRCountOn(size_t arr)
{
	
	
	arr = (arr & 0x5555555555555555) + ((arr >> 1) & 0x5555555555555555);
	arr = (arr & 0x3333333333333333) + ((arr >> 2) & 0x3333333333333333);
	arr = (arr & 0x0F0F0F0F0F0F0F0F) + ((arr >> 4) & 0x0F0F0F0F0F0F0F0F);
	arr = (arr & 0x00FF00FF00FF00FF) + ((arr >> 8) & 0x00FF00FF00FF00FF);
	arr = (arr & 0x0000FFFF0000FFFF) + ((arr >> 16) & 0x0000FFFF0000FFFF);
	
	return arr = (arr & 0x00000000FFFFFFFF) 
				+ ((arr >> 32) & 0x00000000FFFFFFFF);

}

size_t BARRCountOff(size_t arr)
{
	
	return 8 * sizeof(arr) - BARRCountOn(arr);
}

static unsigned char ByteMirror(unsigned char num)
{
	unsigned char res = 0x0;
	unsigned char size = 8 * sizeof(unsigned char);
	unsigned char n = 0;
	
	for(; n < size; ++n)
	{
		res = res | ((num & 0x1) << (size - 1 - n));
		num = num >> 1;
	}

	return res;
}

static unsigned char *CreateMirrorLUT()
{
	static unsigned char *mirror_lut = NULL;
	unsigned char i = 0;

	if(NULL == mirror_lut)
	{
		mirror_lut = (unsigned char *)malloc(256 * sizeof(char));
		if(NULL == mirror_lut)
		{
			
			return NULL;
		}
	
		for(; 255 > i; ++i)
		{
			mirror_lut[i] = ByteMirror(i);
		
		}
		mirror_lut[255] = ByteMirror(255);
	}

	return mirror_lut;
}

size_t BARRMirrorLUT(size_t arr)
{
	size_t res = 0;
	size_t char_shift = 8lu * sizeof(arr);
	unsigned char *char_lut = CreateMirrorLUT();
	if(NULL == char_lut)
	{
		
		return 0;
	}
	
	while(0 < char_shift)
	{
		char_shift -= 8;
		res |= (size_t)char_lut[(unsigned char)arr] << char_shift;
		arr >>= 8;
	}

	return res;
}

static size_t *CreateCountOnLUT()
{
	static size_t *bitcount_lut = NULL;
	size_t i = 0;

	if(NULL == bitcount_lut)
	{
		bitcount_lut = (size_t *)malloc(256 * sizeof(*bitcount_lut));
		if(NULL == bitcount_lut)
		{
			
			return NULL;
		}
	
		for(; 255 > i; ++i)
		{
			bitcount_lut[i] = BARRCountOn(i);
		}
		bitcount_lut[255] = BARRCountOn(255);
	}
	
	return bitcount_lut;
}

size_t BARRCountOnLUT(size_t arr)
{
	size_t res = 0;
	size_t *bit_lut = CreateCountOnLUT();
	if(NULL == bit_lut)
	{

		return -1;
	}
	
	while(0 < arr)
	{
		res += bit_lut[arr & 0xFF];
		arr >>= 8;
	}	

	return res;
}
