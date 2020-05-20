/*******************************************************************************
Author: Andrei Plakhota
Reviewer: Yael Lotan
General info: some excercises on bit logic.
*******************************************************************************/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*sizeof*/


unsigned int Pow2(unsigned int x, int y);
int IsPow2(unsigned int x);
int IsPow2NoLoop(unsigned int x);
unsigned int Add1(unsigned int x);
void Print3BitsOn(unsigned int *n, int length);
unsigned int ByteMirror(unsigned int num);
unsigned char ByteMirrorNoLoop(unsigned char num);
unsigned int ByteMirrorMask(unsigned int num);
int AreB2andB6(unsigned char num);
int AreB2orB6(unsigned char num);
unsigned char SwapBit5with3(unsigned char num);
unsigned int NextDiv16(unsigned int x);
void Swap(int *x, int *y);
unsigned int CountSetBits(unsigned int x);
unsigned int CountSetBitsNoLoop(unsigned int x);
void PrintByBit(float x);

