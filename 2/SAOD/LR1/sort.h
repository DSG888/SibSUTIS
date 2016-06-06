#ifndef sort
#define sort

#include <stdint.h>
void InsertionSort(uint32_t a[], uint32_t size);
void Bubble_Sort(uint32_t a[], uint32_t size);
void CountingSort(uint32_t array[], uint32_t n);
void MergeSort(uint32_t arr[], uint32_t Left, uint32_t Right);
void QuickSort(uint32_t array[], long int left, long int right);
void HeapSort(uint32_t *array, uint32_t size);
void RadixSort(uint32_t a[], uint32_t n);

#endif
