
#ifndef GEEKS_HEAP_SORT_H
#define GEEKS_HEAP_SORT_H

#include "MaxHeap.h"
#include "IndexMaxHeap.h"

using namespace std;

template<typename T>
void heapSort1(T arr[], int n)
{

    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for(int i = 0; i < n; ++i)
        maxheap.insert(arr[i]);

    for(int i = n - 1; i >= 0; --i)
        arr[i] = maxheap.popMax();
}

template<typename T>
void heapSort2(T arr[], int n)
{

    MaxHeap<T> maxheap = MaxHeap<T>(arr,n);
    for(int i = n - 1 ; i >= 0; --i )
        arr[i] = maxheap.popMax();
}

template<typename T>
void __shiftDownV0(T arr[], int n, int k)
{
    while(2 * k + 1 < n )
	{
        int j = 2 * k + 1;
        if(j + 1 < n && arr[j + 1] > arr[j])
            j += 1;

        if( arr[k] >= arr[j] )
			break;

        swap(arr[k] , arr[j]);
        k = j;
    }
}

template<typename T>
void heapSort3(T arr[], int n)
{
    for(int i = (n - 1 - 1) / 2; i >= 0; --i)
        __shiftDownV0(arr, n, i);

    for(int i = n - 1; i > 0 ; --i)
	{
        swap(arr[0] , arr[i]);
        __shiftDownV0(arr, i, 0);
    }
}

template<typename T>
void __shiftDown(T arr[], int n, int k)
{
    T e = arr[k];
    while(2 * k + 1 < n )
	{
        int j = 2 * k + 1;
        if(j+1 < n && arr[j+1] > arr[j] )
            j += 1;

        if( e >= arr[j] ) 
			break;

        arr[k] = arr[j];
        k = j;
    }

    arr[k] = e;
}

template<typename T>
void heapSort4(T arr[], int n)
{
    // build the MaxHeap
	for(int i = (n - 1 - 1) / 2; i >= 0; --i)
        __shiftDown(arr, n, i);

	// get the max value and put it to the tail one by one
    for(int i = n - 1; i > 0 ; --i)
	{
        swap(arr[0] , arr[i]);
        __shiftDown(arr, i, 0);
    }
}

template<typename T>
void indexMaxHeapSort(T arr[], int n)
{

    IndexMaxHeap<T> indexMaxheap = IndexMaxHeap<T>(arr, n);
    for(int i = n - 1 ; i >= 0; --i)
        arr[i] = indexMaxheap.popMax();
}

#endif //GEEKS_HEAP_SORT_H
