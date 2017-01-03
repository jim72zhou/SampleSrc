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
void selectionSort(T * pData, int count)
{
	for(int i = 0; i < count; ++i)
	{
		int minPos = i;
		for(int j = i + 1; j < count; ++j)
		{
			if(pData[j] < pData[minPos])
				minPos = j;
		}
		swap(pData[i], pData[minPos]);
	}
}

template<typename T>
void insertionSort(T * pData, int count)
{
	for(int i = 1; i < count; ++i)
	{
		// method 1
		/*
		for(int j = i; j > 0 && pData[j] < pData[j - 1]; --j)
		{
			swap(pData[j], pData[j -1]);
		}
		*/

		// method 2
		T data = pData[i];
		int j = 0;
		for(j = i; j > 0 && data < pData[j - 1]; --j)
		{
			pData[j] = pData[j-1];
		}
		pData[j] = data;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N = 10000;
    int *pData = SortTestUtil::generateRandomArray(N, 0, 100000);
	int *pData2 = SortTestUtil::copyIntArray(pData, N);
	int *pData3 = SortTestUtil::copyIntArray(pData, N);

	cout << "Performace for random data" << endl;
	SortTestUtil::testSort("Selection Sort", selectionSort<int>, pData, N);
	SortTestUtil::testSort("Insertion Sort", insertionSort<int>, pData2, N);
//	SortTestUtil::testSort("Insertion Sort2", insertionSort<int>, pData3, N);
//	SortTestUtil::printArray(pData, N);

	cout << "Performace for sorted data" << endl;
	SortTestUtil::testSort("Selection Sort", selectionSort<int>, pData, N);
	SortTestUtil::testSort("Insertion Sort", insertionSort<int>, pData2, N);
//	SortTestUtil::testSort("Insertion Sort2", insertionSort<int>, pData3, N);

	cout << "Performace for sorted data(reversed case)" << endl;
	SortTestUtil::reverseIntArray(pData, N);
	SortTestUtil::reverseIntArray(pData2, N);
	SortTestUtil::reverseIntArray(pData3, N);

	SortTestUtil::testSort("Selection Sort", selectionSort<int>, pData, N);
	SortTestUtil::testSort("Insertion Sort", insertionSort<int>, pData2, N);
//	SortTestUtil::testSort("Insertion Sort2", insertionSort<int>, pData3, N);


    delete[] pData;
    delete[] pData2;
	delete[] pData3;

    cout<<endl;


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
