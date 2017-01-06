#ifndef SORT_MERGE_H
#define SORT_MERGE_H

#include <algorithm>
#include "BasicSort.h"

template<typename T>
void _merge(T* pData, int left, int middle, int right)
{
	T* tmp = new T[right - left + 1];
	for(int k = left; k <= right; ++k)
	{
		tmp[k - left] = pData[k];
	}

	int i = left;
	int j = middle + 1;
	for(int k = left; k <= right; ++k)
	{
		// left side has finished
		if(i > middle)
		{
			pData[k] = tmp[j - left];
			++j;
		}
		// right side ahs finished
		else if(j > right)
		{
			pData[k] = tmp[i - left];
			++i;
		}
		// merge left side
		else if(tmp[i - left] < tmp[j - left])
		{
			pData[k] = tmp[i - left];
			++i;
		}
		// merge right side
		else
		{
			pData[k] = tmp[j - left];
			++j;
		}
	}

	delete[] tmp;
}

template<typename T>
void _mergeSort(T* pData, int left, int right)
{
	if(left < right)
	{
		int middle = (left + right) / 2;
		_mergeSort(pData, left, middle);
		_mergeSort(pData, middle + 1, right);
		_merge(pData, left, middle, right);
	}
}

// initial version
template<typename T>
void mergeSort(T* pData, int length)
{
	_mergeSort(pData, 0, length - 1);
}

template<typename T>
void _mergeSort2(T* pData, int left, int right)
{
    // for size size data, use insertion sort is better
	// which value is the best, it decides by the data, it need be tuned 
	// http://stackoverflow.com/questions/12622015/why-should-insertion-sort-be-used-after-threshold-crossover-in-merge-sort
	// http://blog.csdn.net/wu_yihao/article/details/8038998    
	const int INSERTION_SORT_THRESHOLD = 16;
	if(right - left <= INSERTION_SORT_THRESHOLD)
	{
        insertionSort(pData, left, right);
        return;
    }

    int middle = (left + right ) / 2;
    _mergeSort2(pData, left, middle);
    _mergeSort2(pData, middle + 1, right);
    
	// for data[middle] <= data[middle + 1] case, don't merge
    // it's efficient for almost sorted case, but for general cases, the judge costs extra time
    if(pData[middle] > pData[middle + 1])
        _merge(pData, left, middle, right);
}

// improved version
template<typename T>
void mergeSort2(T* pData, int length)
{
	_mergeSort2(pData, 0, length - 1);
}

// Bottom Up Merge Sort 
// http://stackoverflow.com/questions/17417887/where-is-bottom-up-merge-sort-useful
template <typename T>
void mergeSortBU(T* pData, int length)
{
    const int INSERTION_SORT_THRESHOLD = 16;
	for(int i = 0 ; i < length ; i += INSERTION_SORT_THRESHOLD)
        insertionSort(pData, i, min(i + INSERTION_SORT_THRESHOLD - 1, length - 1));

    for(int step = INSERTION_SORT_THRESHOLD; step < length ; step += step)
        for(int i = 0 ; i < length - step ; i += step + step)
            if(pData[i + step - 1] > pData[i + step] )
                _merge(pData, i, i + step - 1, min(i + step + step - 1, length - 1));
}

#endif //SORT_MERGE_H