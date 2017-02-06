#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

#include "Tree\BST.h"
#include "Tree\RBT.h"
#include "Tree\AVL.h"
#include "Tree\SequenceST.h"

#include "SortTestUtil.h"
#include "FileProcs.h"

void bstPerformanceTest(bool bTest)
{
    if(!bTest)
		return;

	string filename = "..\\TestData\\Algorithm.txt";
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

	cout << "After remove, size = " << bst.size();
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
        cout << "the floor of " << i << " is ";
        if( floorKey == nullptr )
            cout << "NULL" << endl;
        else
            cout << *floorKey << endl;

        int* ceilKey = bst.ceil(i);
        cout<<"the ceil of "<<i<<" is ";
        if( ceilKey == nullptr )
            cout << "NULL" << endl;
        else
            cout << *ceilKey << endl;

        cout << endl;
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
