#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

#include "Sort\BasicSort.h"
#include "sort\MergeSort.h"
#include "Sort\QuickSort.h"
#include "Sort\SortUseCase.h"

#include "Heap\MaxHeap.h"
#include "Heap\MinHeap.h"
#include "Heap\IndexMaxHeap.h"
#include "Heap\HeapSort.h"

#include "Tree\BST.h"
#include "Tree\RBT.h"
#include "Tree\AVL.h"
#include "Tree\SequenceST.h"

#include "Book.h"
#include "SortTestUtil.h"
#include "FileProcs.h"

void sortTest(bool bTest)
{
	if(!bTest)
		return;
	
	const int NUM = 100000;
	const int MAX = 10;

	typedef struct
	{
		string sortName;
		void(*pfSort)(int *, int);
		int *pData;
		int length;
	} TestData;

	TestData sortArray[] = {
		//{"Selection Sort",	selectionSort,		nullptr, NUM},
		//{"Bubble Sort",		bubbleSort,			nullptr, NUM},
		//{"Shell Sort",		shellSort,			nullptr, NUM},
		//{"Insertion Sort",	insertionSort,		nullptr, NUM},		
		//{"Merge SortV0",		mergeSortV0,		nullptr, NUM},
		{"Merge Sort",			mergeSort,			nullptr, NUM},
		{"Merge SortBU",		mergeSortBU,		nullptr, NUM},
		//{"Quick SortV0",		quickSortV0,		nullptr, NUM},
		{"Quick SortV1",		quickSortV1,		nullptr, NUM},
		{"Quick Sort",			quickSort,			nullptr, NUM},
		{"MaxHeap Sort1",		maxHeapSort1,		nullptr, NUM},
		{"MaxHeap Sort2",		maxHeapSort2,		nullptr, NUM},
		//{"MaxHeap Sort3",		maxHeapSort3,		nullptr, NUM},
		//{"MaxHeap Sort4",		maxHeapSort4,		nullptr, NUM},
		//{"IndexMaxHeap Sort",	indexMaxHeapSort,	nullptr, NUM},
		{"MinHeap Sort1",		minHeapSort1,		nullptr, NUM},
		{"MinHeap Sort2",		minHeapSort2,		nullptr, NUM},
		
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

	/* verification for template cases(float and user defined class */
	cout << endl << "Float case:" << endl;
	float data[6] = {2.6f, 1, 5.2f, 3, 2, 4};
	selectionSort(data, 6);
	for(int i = 0; i < 6; ++i)
	{
		cout << data[i] << ", ";
	}

	cout << endl << endl << "User defined class:" << endl;
	Book d[4] = { {"D",90} , {"C",100} , {"B",95} , {"A",95} };
    selectionSort(d, 4);
    for(int i = 0 ; i < 4 ; i ++)
        cout << d[i];
    cout << endl;

}
