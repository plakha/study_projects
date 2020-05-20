/******************************
15/7/2019
Recursive int Mergesort

21/7
QSort, HeapSort, BinarySearch, JumpSearch
Reviewer - Alex
*******************************/

#ifndef SORTS_H
#define SORTS_H

#include <stddef.h> /* size_t */

enum direction
{
	ASC = 0,
	DSC
};

int MergeSort(int *arr, size_t len);
void QuickSort(int arr[], size_t n_membs, enum direction dir);
void HeapSort(int arr[], size_t n_membs, enum direction dir);

int BinarySearch(const int arr[], int key, size_t n_membs, size_t *found_index);
int JumpSearch(const int arr[], int key, size_t n_membs, size_t *found_index);

#endif /* SORTS_H */























