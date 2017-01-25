// Sort.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

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

#include "Graph\DenseGraph.h"
#include "Graph\SparseGraph.h"
#include "Graph\WeightedDenseGraph.h"
#include "Graph\WeightedSparseGraph.h"
#include "Graph\Components.h"
#include "Graph\Path.h"
#include "Graph\ShortestPath.h"
#include "Graph\LazyPrimMST.h"

#include "Book.h"
#include "SortTestUtil.h"
#include "UnionFindTestUtil.h"
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

void bstPerformanceTest(bool bTest)
{
    if(!bTest)
		return;

	string filename = "D:\\Temp\\Algorithm.txt";
	string keyword = "algorithm";
    vector<string> words;
    if(FileProcs::readFile(filename, words))
	{
        cout << "There are totally " << words.size() << " words in " << filename << endl;
        cout << endl;

		for(int t = 1; t <= 2; ++t)
		{
			if( t== 1)
				cout << "Almost random case:" << endl;
			else
			{
				cout << endl << "Sorted data case:" << endl;
				sort(words.begin() , words.end());
			}

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

			cout << keyword << " count : " << *bst.search(keyword) << endl;
			time_t endTime = clock();
			cout << "BST time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

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

			cout << keyword << " count : " << *sst.search(keyword) << endl;

			endTime = clock();
			cout << "SequenceST time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

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

			cout << keyword << " count : " << *rbt.search(keyword) << endl;
			endTime = clock();
			cout << "RBT time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

			cout << endl;

			// test AVL
			startTime = clock();
			AVL<string, int> avl = AVL<string, int>();

			for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) 
			{
				int *res = avl.search(*iter);
				if (res == nullptr)
					avl.insert(*iter, 1);
				else
					(*res)++;
			}

			cout << keyword << " count : " << *avl.search(keyword) << endl;
			endTime = clock();
			cout << "AVL time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

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

void avlTest(bool bTest)
{
	if(!bTest)
		return;

	srand(unsigned(time(NULL)));
	const int N  = 100;

    AVL<int, int> avl;
 
    for(int i = 0; i < N; ++i)
	{
		//avl.insert(i, i * 3 - 7);
	}

	for(int i = 0 ; i < N; ++i)
	{
        int key = rand()%N;
		avl.insert(key, key * 7);
		//cout << "(" << key << ")" << avl.size() << " ";
	}
 
    cout << endl;
	cout << "Inoder Traversal of Created Tree\n";
    avl.inOrder();
 
    cout << "\n\nLevel Order Traversal of Created Tree\n";
    avl.levelOrder();
}

void avlRemoveTest(bool bTest)
{
	if(!bTest)
		return;

    srand(unsigned(time(NULL)));
	const int N  = 100;
	AVL<int, int> avl;
 
    for(int i = 0; i < N; ++i)
	{
		avl.insert(i, i );
	}
 
    cout << "Inoder Traversal of Created Tree\n";
    avl.inOrder();
 
    cout << "\n\nLevel Order Traversal of Created Tree\n";
    avl.levelOrder();

	cout << "\nRemoving data" << endl;
	
    for(int i = 0 ; i < N ; ++i)
	{
        int key = rand()%N;
		//cout << "..." << key;
		avl.remove(key);
		//cout << " -> " << avl.size() << " ";
		//avl.levelOrder();
		cout << endl;
	}

	cout << endl;
	cout << "Remaining data:" << endl;
	avl.levelOrder();
	cout << endl;

	int remaining = avl.size();
	for(int i = 0; i < remaining; ++i)
	{
		avl.removeMax();
		cout << avl.size() << " ";
		cout << endl;
		//avl.levelOrder();
		//cout << endl;
	}
}

void unionFindTest(bool bTest)
{
	if(!bTest)
		return;

	int n = 1000000;

    // Quick Find
//    UnionFindTestUtil::testQuickFind(n);

    // Quick Union
//    UnionFindTestUtil::testQuickUnion(n);

    // Quick Union + sz
    UnionFindTestUtil::testQuickUnionSize(n);

    // Quick Union + rank
    UnionFindTestUtil::testQuickUnionRank(n);

    // Quick Union + rank + path compression
    UnionFindTestUtil::testUnionFind(n);

}

void graphReadTest(bool bTest)
{
	if(!bTest)
		return;

    string filename = "d:\\temp\\dataG2.txt";

	int N = 13;

    SparseGraph g1(N, false);
    FileProcs::readGraph<SparseGraph>(g1 , filename);
	cout << "Sparse Graph:" << endl;
    g1.show();

	cout << endl << "Show by iterator:" << endl;
    for(int v = 0 ; v < N ; ++v)
	{
        cout << v << ": ";
        SparseGraph::adjIterator adj(g1 , v);
        for(int w = adj.begin() ; !adj.end() ; w = adj.next())
            cout << w << " ";
        cout<<endl;
    }

    cout<<endl;

    DenseGraph g2(N , false);
    FileProcs::readGraph<DenseGraph>(g2 , filename );
	cout << "Dense Graph:" << endl;
    g2.show();

	cout << endl << "Show by iterator:" << endl;
    for(int v = 0 ; v < N ; ++v)
	{
        cout << v << ": ";
        DenseGraph::adjIterator adj(g2 , v);
        for(int w = adj.begin() ; !adj.end() ; w = adj.next())
            cout << w << " ";
        cout<<endl;
    }
}

void componentPathTest(bool bTest)
{
    if(!bTest)
		return;

	// dataG1.txt
    string filename1 = "d:\\temp\\dataG1.txt";
    SparseGraph g1 = SparseGraph(6, false);
    FileProcs::readGraph<SparseGraph>(g1, filename1);
    g1.show();
	cout << endl;
	Component<SparseGraph> component1(g1);
    cout << "TestG1, Component Count: " << component1.count() << endl;

	Path<SparseGraph> dfs(g1, 0);
    cout << "DFS: ";
    dfs.showPath(4);

	ShortestPath<SparseGraph> bfs(g1, 0);
    cout << "BFS: ";
    bfs.showPath(4);

    cout << endl;

    // dataG2.txt
    string filename2 = "d:\\temp\\dataG2.txt";
    SparseGraph g2 = SparseGraph(13, false);
    FileProcs::readGraph<SparseGraph>(g2, filename2);
	g2.show();
	cout << endl;
    Component<SparseGraph> component2(g2);
    cout << "TestG2, Component Count: " << component2.count() << endl;

	cout << "Is V0 connected with V6? " << (component2.isConnected(0, 6) ? "Yes" : "No") << endl;
	cout << "Is V0 connected with V7? " << (component2.isConnected(0, 7) ? "Yes" : "No") << endl;

	Path<SparseGraph> dfs2(g2, 0);
    cout << "DFS: ";
    dfs2.showPath(6);
	dfs2.showPath(7);

	ShortestPath<SparseGraph> bfs2(g2, 0);
    cout << "BFS: ";
    bfs2.showPath(6);
	bfs2.showPath(7);

}

void weightedGraphTest(bool bTest)
{
    if(!bTest)
		return;

    string filename = "d:\\temp\\dataWeightG1.txt";
    int V = 8;
    cout << fixed << setprecision(2);

    // Test Weighted Dense Graph
    WeightedDenseGraph<double> g1 = WeightedDenseGraph<double>(V, false);
    FileProcs::readGraphEx<WeightedDenseGraph<double>, double>(g1, filename);
    g1.show();
    cout<<endl;

	 // Test Lazy Prim MST
    cout << "Test Lazy Prim MST-Dense" << endl;
    LazyPrimMST<WeightedDenseGraph<double>, double> lazyPrimMST1(g1);
    vector<Edge<double>> mst1 = lazyPrimMST1.mstEdges();
    for(unsigned i = 0 ; i < mst1.size() ; ++i)
        cout << mst1[i] << endl;
    cout<<"The MST weight is: " << lazyPrimMST1.result() << endl;

    // Test Weighted Sparse Graph
    WeightedSparseGraph<double> g2 = WeightedSparseGraph<double>(V, false);
    FileProcs::readGraphEx<WeightedSparseGraph<double>, double>(g2, filename);
    g2.show();
    cout<<endl;

	cout << "Test Lazy Prim MST-Sparse:" << endl;
    LazyPrimMST<WeightedSparseGraph<double>, double> lazyPrimMST2(g2);
    vector<Edge<double>> mst2 = lazyPrimMST2.mstEdges();
    for(unsigned i = 0 ; i < mst2.size() ; ++i)
        cout << mst2[i] << endl;
    cout<<"The MST weight is: " << lazyPrimMST2.result() << endl;

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

	weightedGraphTest(true);
	componentPathTest(false);
	graphReadTest(false);

	unionFindTest(false);
	
	avlTest(false);
	avlRemoveTest(false);

	rbtTest(false);
	rbtRemoveTest(false);
	
	bstCeilFloorTest(false);
	bstRemoveTest(false);
	bstRemoveMinMaxTest(false);
	bstTraverseTest(false);
	bstPerformanceTest(false);
	
	sortTest(false);

	//system("pause");
	return 0;
}
