
#ifndef GEEKS_SORT_SORTTESTUTIL_H
#define GEEKS_SORT_SORTTESTUTIL_H

#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;


namespace SortTestUtil
{
    // generate n random elements, every element is in [rangeLo, rangeHi]
    int *generateRandomArray(int n, int rangeLo, int rangeHi) 
	{

        assert(rangeLo <= rangeHi);

        int *arr = new int[n];

        srand(unsigned int(time(NULL)));
        for (int i = 0; i < n; i++)
            arr[i] = rand() % (rangeLo - rangeHi + 1) + rangeLo;
        return arr;
    }

    int *generateNearlyOrderedArray(int n, int swapTimes)
	{

        int *arr = new int[n];
        for(int i = 0 ; i < n ; i ++ )
            arr[i] = i;

        srand(unsigned int(time(NULL)));
        for( int i = 0 ; i < swapTimes ; i ++ ){
            int posx = rand()%n;
            int posy = rand()%n;
            swap( arr[posx] , arr[posy] );
        }

        return arr;
    }

	int *copyIntArray(int a[], int n)
	{
        int *arr = new int[n];
		memcpy_s(arr, sizeof(int) * n, a, sizeof(int) * n);
        return arr;
    }

	void reverseIntArray(int a[], int n)
	{
        for(int i = 0; i < n / 2; ++i)
			swap(a[i], a[n - i - 1]);
    }

	void shuffle(int arr[], int n)
	{
		srand(unsigned(time(NULL)));
		for(int i = n - 1; i >= 0; --i)
		{
			int x = rand() % (i + 1);
			swap(arr[i] , arr[x]);
		}
	}

    template<typename T>
    void printArray(T arr[], int n) 
	{
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;

        return;
    }

    template<typename T>
    bool isSorted(T arr[], int n) 
	{
        for (int i = 0; i < n - 1; i++)
            if (arr[i] > arr[i + 1])
                return false;

        return true;
    }

    void testSort(const string &sortName, void (*sort)(int *, int), int* arr, int n) 
	{
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

        assert(isSorted(arr, n));
        cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

        return;
    }

};

#endif //GEEKS_SORT_SORTTESTUTIL_H
