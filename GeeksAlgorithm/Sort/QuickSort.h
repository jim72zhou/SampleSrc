#ifndef GEEKS_SORT_QUICK_H
#define GEEKS_SORT_QUICK_H

#include <algorithm>
#include <ctime>
#include "BasicSort.h"

// Note
// quickSort would be faster than quickSort1, but from the test, it's not so. 
// the reason is quickSort cost so much on swap data, but quickSort1 has no such extra swap.
// if reduce swap by below method(*1), the speed will improve greatly and 
// would quicker than quickSort1 when there are almost repeated elements

// some topics about 3 ways quick sort
// http://stackoverflow.com/questions/941447/quicksort-with-3-way-partition
// http://www.geeksforgeeks.org/3-way-quicksort/
// https://www.cs.princeton.edu/~rs/talks/QuicksortIsOptimal.pdf

// 3 ways, optimized version
template<typename T>
void _quickSort(T pData[], int left, int right)
{
	const int INSERTION_SORT_THRESHOLD = 15;
	if( right - left <= INSERTION_SORT_THRESHOLD )
	{
        insertionSort(pData, left, right);
        return;
    }

    swap(pData[left] , pData[rand() % (right - left + 1) + left]);
	T v = pData[left];

    int i = left;
	int j = right + 1;
	int le = left;
    int re = right + 1;

	while(true)
	{
		// From left, find the first element greater than or equal to v. 
		// This loop will definitely terminate as v is last element.
		while(pData[++i] < v && i < j);

		// From right, find the first element smaller than or equal to v
		while(v < pData[--j] && i < j);

		// If i and j cross, then we are done
		if(i >= j)
			break;

		// Swap, so that smaller goes on left greater goes on right
		if(pData[i] < pData[j])				// *1 reduce data swap
			swap(pData[i], pData[j]);

		// Move all same left occurrence of pivot to beginning of array and keep count using lt
		if(pData[i] == v)
		{
			++le;
			//swap(pData[le], pData[i]);	// *1 reduce data swap
			pData[i] = pData[le];
		}

		// Move all same right occurrence of pivot to end of array and keep count using gt
		if(pData[j] == v)
		{
			--re;
			//swap(pData[re], pData[j]);	// *1 reduce data swap
			pData[j] = pData[re];
		}
	}

	swap(pData[left], pData[i - 1]);

	// Move all left same occurrences from beginning to adjacent to data[j]
	j = i -1;
	for(int k = left + 1; k <= le; ++k, --j)
		//swap(pData[k], pData[j]);			// *1 reduce data swap
		pData[k] = v;

	 // Move all right same occurrences from end to adjacent to data[i]
	for(int k = right; k >= re; --k, ++i)
		//swap(pData[k], pData[i]);			// *1 reduce data swap
		pData[k] = v;

    _quickSort(pData, left, j);
    _quickSort(pData, i, right);
}

// 3 ways, initial version
template<typename T>
void _quickSort3WaysV1(T * pData, int left, int right)
{
	const int INSERTION_SORT_THRESHOLD = 32;
	if( right - left <= INSERTION_SORT_THRESHOLD )
	{
        insertionSort(pData, left, right);
        return;
    }

    swap(pData[left] , pData[rand() % (right - left + 1) + left]);	
	T v = pData[left];

	int lt = left;			// data[left+1...lt] < v
    int gt = right + 1;		// data[gt...right]	 > v
    int i = left + 1;		// data[lt+1...i)   == v

	while(i < gt)
	{
		if(pData[i] < v)
		{
            swap(pData[i], pData[lt + 1]);
			++i;
			++lt;
        }
		else if(v < pData[i])
		{
            swap(pData[i], pData[gt - 1]);
			--gt;
        }
		else
		{
			++i;
		}
	}

	swap(pData[left], pData[lt]);

    _quickSort3WaysV1(pData, left, lt - 1);
    _quickSort3WaysV1(pData, gt, right);
}

// 3 ways quick sort
template<typename T>
void quickSort(T * pData, int length)
{
	srand(unsigned int(time(NULL)));
	_quickSort3WaysV1(pData, 0, length - 1);
}

// execute partition for data[left...right] parts
// return pilot
// make data[left...pilot-1] < data[pilot], data[pilot+1...right] > data[pilot]
template <typename T>
int _partitionV2(T* pData, int left, int right)
{
	swap(pData[left] , pData[rand() % (right - left + 1) + left]);
	
	T v = pData[left];

    // data[left+1...j] < v, data[j+1...i) > v
	int i = left + 1;
	int j = right;
    while(true)
	{
        while(pData[i] < v && i <= j)
		{
            ++i;
        }
		while(v < pData[j] && i <= j)
		{
            --j;
        }

		if(i >= j)
			break;

		swap(pData[j], pData[i]);
		++i;
		--j;
	}

	swap(pData[left], pData[j]);

    return j;
}

template <typename T>
int _partitionV0(T* pData, int left, int right)
{
    // to avoid error for all data are greater than data[left] case
	swap(pData[left] , pData[rand() % (right - left + 1) + left]);
	
	T v = pData[left];

    int j = left; // data[left+1...j] < v, data[j+1...i) > v
    for(int i = left + 1; i <= right; ++i)
	{
        if(pData[i] < v)
		{
            ++j;
            swap(pData[j], pData[i]);
        }
	}

	// to avoid error for all data are greater than data[left] case
	// and if there are too much data, it would result in stack overflow
    if(j > left)
		swap(pData[left], pData[j]);

    return j;
}

// improved version2
template<typename T>
void _quickSortV1(T * pData, int left, int right)
{
	const int INSERTION_SORT_THRESHOLD = 32;
	if( right - left <= INSERTION_SORT_THRESHOLD )
	{
        insertionSort(pData, left, right);
        return;
    }

    int pilot = _partitionV2(pData, left, right);
    _quickSortV1(pData, left, pilot - 1);
    _quickSortV1(pData, pilot + 1, right);
}

// improved version2
template<typename T>
void quickSortV1(T * pData, int length)
{
	srand(unsigned int(time(NULL)));
	_quickSortV1(pData, 0, length - 1);
}

// initial version
template<typename T>
void _quickSortV0(T * pData, int left, int right)
{	
	T pivot = pData[(left + right) / 2];

	int i = left;
	int j = right;

	while(i < j)
	{
		while(pData[i] < pivot)
			++i;
		while(pData[j] > pivot)
			--j;

		if(i <= j)
		{
			swap(pData[i], pData[j]);
			++i;
			--j;
		}
	}

	// recursion
    if (left < j)
		_quickSortV0(pData, left, j);
    if (i < right)
		_quickSortV0(pData, i, right);
}

// initial version
template<typename T>
void quickSortV0(T * pData, int length)
{
	_quickSortV0(pData, 0, length - 1);
}

#endif //GEEKS_SORT_QUICK_H