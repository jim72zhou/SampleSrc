// Sort.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>

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
#include "Tree\SequenceST.h"

#include "Book.h"
#include "SortTestUtil.h"
#include "FileProcs.h"

using namespace std;

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
	
	//auto pfQuickSort = [](int *pData, int n){quickSort(pData, 0, n);};
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
}

void bstTest(bool bTest)
{
    if(!bTest)
		return;

	string filename = "D:\\Temp\\Algorithm.txt";
    vector<string> words;
    if(FileProcs::readFile(filename, words))
	{
        cout << "There are totally " << words.size() << " words in " << filename << endl;
        cout << endl;

		// Almost random test
		{
			// test BST
			time_t startTime = clock();
			BST<string, int> bst = BST<string, int>();
			for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++)
			{
				int *res = bst.search(*iter);
				if (res == nullptr)
					bst.insert(*iter, 1);
				else
					(*res)++;
			}

			cout << "'Algorithm' : " << *bst.search("algorithm") << endl;
			time_t endTime = clock();
			cout << "BST(Almost random) time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

			cout << endl;

			// test SequenceST
			startTime = clock();
			SequenceST<string, int> sst = SequenceST<string, int>();
			for(vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) 
			{
				int *res = sst.search(*iter);
				if (res == nullptr)
					sst.insert(*iter, 1);
				else
					(*res)++;
			}

			cout << "'Algorithm' : " << *sst.search("algorithm") << endl;

			endTime = clock();
			cout << "SequenceST(Almost random) time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

			cout << endl;

			// test RBT
			startTime = clock();
			RBT<string, int> rbt = RBT<string, int>();

			for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) 
			{
				int *res = rbt.search(*iter);
				if (res == nullptr)
					rbt.insert(*iter, 1);
				else
					(*res)++;
			}

			cout << "'Algorithm' : " << *rbt.search("algorithm") << endl;
			endTime = clock();
			cout << "RBT(Almost random) time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

			cout << endl;
		}


		// sorted data test
        sort(words.begin() , words.end());
		{
			// test BST
			time_t startTime = clock();
			BST<string, int> bst = BST<string, int>();
			for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++)
			{
				int *res = bst.search(*iter);
				if (res == nullptr)
					bst.insert(*iter, 1);
				else
					(*res)++;
			}

			cout << "'Algorithm' : " << *bst.search("algorithm") << endl;
			time_t endTime = clock();
			cout << "BST(sorted) time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

			cout << endl;

			// test SequenceST
			startTime = clock();
			SequenceST<string, int> sst = SequenceST<string, int>();
			for(vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) 
			{
				int *res = sst.search(*iter);
				if (res == nullptr)
					sst.insert(*iter, 1);
				else
					(*res)++;
			}

			cout << "'Algorithm' : " << *sst.search("algorithm") << endl;

			endTime = clock();
			cout << "SequenceST(sorted) time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

			cout << endl;

			// test RBT
			startTime = clock();
			RBT<string, int> rbt = RBT<string, int>();

			for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) 
			{
				int *res = rbt.search(*iter);
				if (res == nullptr)
					rbt.insert(*iter, 1);
				else
					(*res)++;
			}

			cout << "'Algorithm' : " << *rbt.search("algorithm") << endl;
			endTime = clock();
			cout << "RBT(sorted) time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

			cout << endl;
		}
    }
}

void bstTraverseTest(bool bTest)
{
	if(!bTest)
		return;

	srand(unsigned(time(NULL)));

	BST<int,int> bst = BST<int,int>();

    int n = 3;
	cout << "BST Traverse Test" << endl;
	cout << "Test data:" << endl;
    for(int i = 0 ; i < n ; ++i)
	{
        int key = rand()%n;
        int value = key * key + 7;
        cout << key << " ";
        bst.insert(key, value);
    }
    cout << endl;

    // test size
    cout << "size: " << bst.size() << endl << endl;

    // test preOrder
    cout << "preOrder: " << endl;
    bst.preOrder();
    cout << endl << endl;

    // test inOrder
    cout << "inOrder: " << endl;
    bst.inOrder();
    cout << endl << endl;

    // test postOrder
    cout << "postOrder: " << endl;
    bst.postOrder();
    cout << endl << endl;

	// test levelOrder
    cout << "levelOrder: " << endl;
    bst.levelOrder();
    cout << endl << endl;

	// test min & max
    cout << "Min: " << bst.minimum() << ", Max: " << bst.maximum();
    cout << endl << endl;

	// test removeMin & max
	bst.removeMin();
	cout << "RemoveMin: " << endl;
	cout << "New size: " << bst.size() << endl;
	bst.inOrder();
    cout << endl << endl;

	bst.removeMax();
	cout << "RemoveMax: " << endl;
	cout << "New size: " << bst.size() << endl;
	bst.inOrder();
    cout << endl << endl;
}

void bstRemoveMinMaxTest(bool bTest)
{
	if(!bTest)
		return;

	srand(unsigned(time(NULL)));

	BST<int,int> bst = BST<int,int>();

    int n = 2000;
	cout << "Test data:" << endl;
    for(int i = 0 ; i < n ; ++i)
	{
        int key = rand()%n;
        int value = key * key + 7;
        cout << key << " ";
        bst.insert(key, value);
    }
    cout << endl;

    // test size
    cout << "Size: " << bst.size() << endl << endl;

    cout << "Sorted data: " << endl;
    bst.inOrder();
    cout << endl << endl;

	// test min & max
    cout << "Min: " << bst.minimum() << ", Max: " << bst.maximum();
    cout << endl << endl;

	// test removeMin & max
	cout << "Removing... " << endl;
	int size = bst.size();
	while(size)
	{
		cout << bst.maximum() << " ";
		bst.removeMax();
		size = bst.size();
		if(size)
		{
			cout << bst.minimum() << " ";
			bst.removeMin();
			size = bst.size();
		}
	}

	cout << endl << endl;
}

void bstRemoveTest(bool bTest)
{
	if(!bTest)
		return;

	srand(unsigned(time(NULL)));

	BST<int,int> bst = BST<int,int>();

    const int N = 100000;
	cout << "Test data:" << endl;
    for(int i = 0; i < N; ++i)
	{
        int key = rand()%N;
        int value = key * key + 7;
        //cout << key << " ";
        bst.insert(key, value);
    }

    cout << endl;

    // test size
    cout << "Size: " << bst.size() << endl << endl;

	// test remove
    // remove elements in random order
    int order[N];
    for(int i = 0; i < N; ++i)
        order[i] = i;
    SortTestUtil::shuffle(order , N);

    for(int i = 0; i < N; ++i)
	{
        if(bst.contain(order[i]))
		{
            bst.remove(order[i]);
        }
	}

	cout<<"After remove, size = " <<bst.size();
	cout << endl << endl;
}

void bstCeilFloorTest(bool bTest)
{
	if(!bTest)
		return;

    BST<int,int> bst;

    for(int i = 2 ; i < 20 ; i += 2)
        bst.insert(i, i);
    for( int i = 0 ; i <= 20 ; i ++ )
	{
        int* floorKey = bst.floor(i);
        cout<<"the floor of "<<i<<" is ";
        if( floorKey == nullptr )
            cout<<"NULL"<<endl;
        else
            cout<<*floorKey<<endl;

        int* ceilKey = bst.ceil(i);
        cout<<"the ceil of "<<i<<" is ";
        if( ceilKey == nullptr )
            cout<<"NULL"<<endl;
        else
            cout<<*ceilKey<<endl;

        cout<<endl;
    }
}

void rbtTest(bool bTest)
{
	if(!bTest)
		return;

	srand(unsigned(time(NULL)));
	const int N  = 20;

    RBT<int, int> rbt;
 
	cout << "data counting...";
    for(int i = 0; i < N; ++i)
	{
		rbt.insert(i, i * 3 - 7);
		cout << rbt.size() << " ";
	}

	for(int i = 0 ; i < 6; ++i)
	{
        int key = rand()%N;
		rbt.insert(key, key * 7);
		cout << "(" << key << ")" << rbt.size() << " ";
	}
 
    cout << endl;
	cout << "Inoder Traversal of Created Tree\n";
    rbt.inOrder();
 
    cout << "\n\nLevel Order Traversal of Created Tree\n";
    rbt.levelOrder();
}

void rbtRemoveTest(bool bTest)
{
	if(!bTest)
		return;

    srand(unsigned(time(NULL)));
	const int N  = 20;
	RBT<int, int> rbt;
 
    for(int i = 0; i < N; ++i)
	{
		rbt.insert(i, i * 3 - 7);
	}
 
    cout << "Inoder Traversal of Created Tree\n";
    rbt.inOrder();
 
    cout << "\n\nLevel Order Traversal of Created Tree\n";
    rbt.levelOrder();

	cout << "\nRemoving data";
	
    for(int i = 0 ; i < N ; ++i)
	{
        int key = rand()%N;
		cout << "..." << key;
		rbt.remove(key);
		cout << " -> " << rbt.size() << " ";
		//rbt.levelOrder();
		//cout << endl;
	}
	cout << endl;
	cout << "Remaining data:" << endl;
	rbt.inOrder();
	cout << endl;

	int remaining = rbt.size();
	for(int i = 0; i < remaining; ++i)
	{
		rbt.removeMax();
		cout << rbt.size() << " ";
		cout << endl;
		rbt.inOrder();
		cout << endl;
	}
}

void prototypeTest(bool bTest)
{
	if(!bTest)
		return;

	RBT<int, int> rbt;
 
    for(int i = 7; i > 0; --i)
	{
		rbt.insert(i, i);
	}
 
    cout << "Inoder Traversal of Created Tree\n";
    rbt.inOrder();
 
    cout << "\n\nLevel Order Traversal of Created Tree\n";
    rbt.levelOrder();
}
////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{

	prototypeTest(false);
	
	rbtTest(false);
	rbtRemoveTest(true);
	
	bstCeilFloorTest(false);
	bstRemoveTest(false);
	bstRemoveMinMaxTest(false);
	bstTraverseTest(false);
	bstTest(false);
	
	sortTest(false);

	//system("pause");
	return 0;
}
