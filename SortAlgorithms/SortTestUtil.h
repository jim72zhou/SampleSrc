
#ifndef SORT_SORTTESTUTIL_H
#define SORT_SORTTESTUTIL_H

#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;


namespace SortTestUtil {

    // generate n random elements, every element is in [rangeLo, rangeHi]
    int *generateRandomArray(int n, int rangeLo, int rangeHi) {

        assert(rangeLo <= rangeHi);

        int *arr = new int[n];

        srand(time(NULL));
        for (int i = 0; i < n; i++)
            arr[i] = rand() % (rangeLo - rangeHi + 1) + rangeLo;
        return arr;
    }

	int *copyIntArray(int a[], int n){
        int *arr = new int[n];
		memcpy_s(arr, sizeof(int) * n, a, sizeof(int) * n);
        return arr;
    }

	void reverseIntArray(int a[], int n){
        for(int i = 0; i < n / 2; ++i)
			swap(a[i], a[n - i - 1]);
    }

    template<typename T>
    void printArray(T arr[], int n) {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;

        return;
    }

    template<typename T>
    bool isSorted(T arr[], int n) {

        for (int i = 0; i < n - 1; i++)
            if (arr[i] > arr[i + 1])
                return false;

        return true;
    }

    template<typename T>
    void testSort(const string &sortName, void (*sort)(T *, int), T* arr, int n) {

        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

        assert(isSorted(arr, n));
        cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

        return;
    }

};
#endif //SORT_SORTTESTUTIL_H
