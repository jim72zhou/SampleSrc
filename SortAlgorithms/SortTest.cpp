// Sort.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>

#include "BasicSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "Book.h"
#include "SortTestUtil.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	const int NUM = 100000;
	const int MAX = 100;

////////////////////////////////////////
// placehold to verify for special test
#if 0
	int *data = SortTestUtil::generateRandomArray(NUM, 0, MAX);
	quickSort(data, NUM);
	for(int i = 0; i < NUM; ++i)
	{
		cout << data[i] << ", ";
	}

	cout<<endl;
#endif
////////////////////////////////////////

	typedef struct
	{
		string sortName;
		void(*pfSort)(int *, int);
		int *pData;
		int length;
	} TestData;
	
	//auto pfQuickSort = [](int *pData, int n){quickSort(pData, 0, n);};
	TestData sortArray[] = {
		//{"Selection Sort",	selectionSort,	NULL, NUM},
		//{"Bubble Sort",		bubbleSort,		NULL, NUM},
		//{"Shell Sort",		shellSort,		NULL, NUM},
		//{"Insertion Sort",	insertionSort,	NULL, NUM},		
		{"Merge Sort",			mergeSort,		NULL, NUM},
		{"Merge Sort2",			mergeSort2,		NULL, NUM},
		{"Merge SortBU",		mergeSortBU,	NULL, NUM},
		{"Quick Sort",			quickSort,		NULL, NUM},
		{"Quick SortV1",		quickSortV1,	NULL, NUM},
		{"Quick SortV2",		quickSortV2,	NULL, NUM},
		
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
