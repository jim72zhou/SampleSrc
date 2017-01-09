#ifndef GEEKS_SORT_BASIC_H
#define GEEKS_SORT_BASIC_H

#include <algorithm>


/* Notes
* 1.Because swap cost much time, selectionSort performs better than insertionSort.
*	If changes swap to lower cost method2, insertionSort works better than selectionSort
*/

template<typename T>
void selectionSort(T * pData, int length)
{
	for(int i = 0; i < length; ++i)
	{
		int minPos = i;
		for(int j = i + 1; j < length; ++j)
		{
			if(pData[j] < pData[minPos])
				minPos = j;
		}
		swap(pData[i], pData[minPos]);
	}
}

template<typename T>
void insertionSort(T * pData, int left, int right)
{
	for(int i = left + 1; i <= right; ++i)
	{
		T data = pData[i];
		int j = 0;
		for(j = i; j > left && data < pData[j - 1]; --j)
		{
			pData[j] = pData[j - 1];
		}
		pData[j] = data;
	}
}

template<typename T>
void insertionSort(T * pData, int length)
{
	insertionSort(pData, 0, length -1);	
}

template<typename T>
void shellSort(T * pData, int length)
{
	int interval = 1;
    while( interval < length / 3 )
        interval = 3 * interval + 1;
    //increment sequence: 1, 4, 13, 40, 121, 364, 1093...
	
	while(interval >= 1)
	{
		for(int i = interval; i < length; ++i)
		{
			T data = pData[i];
			int j = 0;
			for(j = i; j >= interval && data < pData[j - interval]; j -= interval)
			{
				pData[j] = pData[j - interval];
			}
			pData[j] = data;
		}
		interval /= 3;
	}
}

template<typename T>
void bubbleSort(T *pData, int length) 
{
	bool swapped = true;
    int i = 0;

    while (swapped) {
		swapped = false;
        ++i;
        for (int j = 0; j < length - i; ++j) 
		{
            if (pData[j + 1] < pData[j]) 
			{
                swap(pData[j + 1], pData[j]);
                swapped = true;
            }
		}
	}
}

#endif //GEEKS_SORT_BASIC_H