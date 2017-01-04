// Sort.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>

#include "Book.h"
#include "SortTestUtil.h"

using namespace std;

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
void insertionSort(T * pData, int length)
{
	for(int i = 1; i < length; ++i)
	{
		// method 1
		/*
		for(int j = i; j > 0 && pData[j] < pData[j - 1]; --j)
		{
			swap(pData[j], pData[j -1]);
		}
		*/

		// method 2, reduce swap times
		T data = pData[i];
		int j = 0;
		for(j = i; j > 0 && data < pData[j - 1]; --j)
		{
			pData[j] = pData[j - 1];
		}
		pData[j] = data;
	}
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

template<typename T>
T getPivot(T* pData, int left, int right)
{
	return pData[(left + right) / 2];
}

template<typename T>
void quickSort(T * pData, int left, int right)
{	
	T pivot = getPivot(pData, left, right);

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
		quickSort(pData, left, j);
    if (i < right)
		quickSort(pData, i, right);
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int NUM = 10000;
	const int MAX = 10000;

	typedef struct
	{
		string sortName;
		void(*pfSort)(int *, int);
		int *pData;
		int length;
	} TestData;
	
	auto pfQuickSort = [](int *pData, int n){quickSort(pData, 0, n);};
	TestData sortArray[] = {
		{"Selection Sort", selectionSort, NULL, NUM},
		{"Insertion Sort", insertionSort, NULL, NUM},
		{"Quick Sort", pfQuickSort, NULL, NUM - 1},
		{"Bubble Sort", bubbleSort, NULL, NUM},
		{"Shell Sort", shellSort, NULL, NUM},
	};

	const int SORTS = sizeof(sortArray) / sizeof(sortArray[0]);

	int *pData[SORTS];

    pData[0] = SortTestUtil::generateRandomArray(NUM, 0, MAX);
	sortArray[0].pData = pData[0];

	for(int i = 1; i < SORTS; ++i)
	{
		pData[i] = SortTestUtil::copyIntArray(pData[0], NUM);
		sortArray[i].pData = pData[i];
	}

	cout << "Performace for random data" << endl;
	for(int i = 0; i < SORTS; ++i)
	{
		SortTestUtil::testSort(sortArray[i].sortName, sortArray[i].pfSort, sortArray[i].pData, sortArray[i].length);
	}

	cout << endl << "Performace for sorted data" << endl;
	for(int i = 0; i < SORTS; ++i)
	{
		SortTestUtil::testSort(sortArray[i].sortName, sortArray[i].pfSort, sortArray[i].pData, sortArray[i].length);
	}

	cout << endl << "Performace for sorted data(reversed case)" << endl;
	for(int i = 0; i < SORTS; ++i)
	{
		SortTestUtil::reverseIntArray(pData[i], NUM);
		SortTestUtil::testSort(sortArray[i].sortName, sortArray[i].pfSort, sortArray[i].pData, sortArray[i].length);
	}

	// release the memory
	for(int i = 0; i < SORTS; ++i)
	{
		delete[] pData[i];
	}

	/* verification for other cases
	float data[6] = {2.6f, 1, 5.2f, 3, 2, 4};
	selectionSort(data, 6);
	for(int i = 0; i < 6; ++i)
	{
		cout << data[i] << ", ";
	}

	cout<<endl;

	Book d[4] = { {"D",90} , {"C",100} , {"B",95} , {"A",95} };
    selectionSort(d, 4);
    for( int i = 0 ; i < 4 ; i ++ )
        cout<<d[i];
    cout<<endl;
	*/

	//system("pause");
	return 0;
}
