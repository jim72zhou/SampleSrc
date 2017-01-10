
#ifndef GEEKS_HEAP_SORT_H
#define GEEKS_HEAP_SORT_H

#include "MaxHeap.h"
#include "MinHeap.h"
#include "IndexMaxHeap.h"

using namespace std;


// use case1:
// find firt Nth smallest/lagest elements by MinHeap/MaxHeap

template<typename T>
T* findMaxNs(T arr[], int n, int Ns)
{
    MinHeap<T> minHeap = MinHeap<T>(Ns);
    for(int i = 0; i < Ns; ++i)
        minHeap.insert(arr[i]);

	for(int i = Ns; i < n; ++i)
	{
		if(arr[i] > minHeap.getMin())
		{
			minHeap.popMin();
			minHeap.insert(arr[i]);
		}
	}

	T* pRet = new T[Ns];
    for(int i = Ns - 1; i >= 0; --i)
        pRet[i] = minHeap.popMin();

	return pRet;
}

template<typename T>
void maxHeapSort1(T arr[], int n)
{

    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for(int i = 0; i < n; ++i)
        maxheap.insert(arr[i]);

    for(int i = n - 1; i >= 0; --i)
        arr[i] = maxheap.popMax();
}

template<typename T>
void maxHeapSort2(T arr[], int n)
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
void maxHeapSort3(T arr[], int n)
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
void maxHeapSort4(T arr[], int n)
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

template<typename T>
void minHeapSort1(T arr[], int n)
{

    MinHeap<T> minheap = MinHeap<T>(n);
    for(int i = 0; i < n; ++i)
        minheap.insert(arr[i]);

    for(int i = 0; i < n; ++i)
        arr[i] = minheap.popMin();
}

template<typename T>
void minHeapSort2(T arr[], int n)
{
    MinHeap<T> minheap = MinHeap<T>(arr,n);
    for(int i = 0; i < n; ++i)
        arr[i] = minheap.popMin();
}

#endif //GEEKS_HEAP_SORT_H
