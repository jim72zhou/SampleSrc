#ifndef GEEKS_SORT_USECASE_H
#define GEEKS_SORT_USECASE_H

#include <algorithm>

using namespace std;

// use case2:
// find Nth element by quick sort

int __quickSort(int pData[], int Nth, int left, int right)
{
    if(left >= right)
		return pData[Nth];

	swap(pData[left] , pData[rand() % (right - left + 1) + left]);
	int v = pData[left];

    int i = left;
	int j = right + 1;
	int le = left;
    int re = right + 1;

	while(true)
	{
		// From left, find the first element greater than or equal to v. 
		// This loop will definitely terminate as v is last element.
		while(pData[++i] < v && i < j);

		// From right, find the first element smaller than or equal to v
		while(v < pData[--j] && i < j);

		// If i and j cross, then we are done
		if(i >= j)
			break;

		// Swap, so that smaller goes on left greater goes on right
		swap(pData[i], pData[j]);

		// Move all same left occurrence of pivot to beginning of array and keep count using lt
		if(pData[i] == v)
		{
			++le;
			swap(pData[le], pData[i]);
		}

		// Move all same right occurrence of pivot to end of array and keep count using gt
		if(pData[j] == v)
		{
			--re;
			swap(pData[re], pData[j]);
		}
	}

	swap(pData[left], pData[i - 1]);

	// Move all left same occurrences from beginning to adjacent to data[j]
	j = i -1;
	for(int k = left + 1; k <= le; ++k, --j)
		swap(pData[k], pData[j]);

	 // Move all right same occurrences from end to adjacent to data[i]
	for(int k = right; k >= re; --k, ++i)
		swap(pData[k], pData[i]);

	if(Nth > j && Nth < i)
		return v;
	else if(Nth <= j)
		return __quickSort(pData, Nth, left, j);
	else
		return __quickSort(pData, Nth, i, right);
}

int findNth(int arr[], int Nth, int len)
{
	srand(unsigned int(time(NULL)));
	return __quickSort(arr, Nth, 0, len - 1);
}

// use case1:
// Count Inversions in an array, Using Merge Sort
// http://www.geeksforgeeks.org/counting-inversions/

// merge arr[l, mid - 1] & arr[mid, r]
int __merge(int arr[], int temp[], int l, int mid, int r)
{
	int inv_cnt = 0;
	int i, j, k;

	i = l;			// index for left subarr
	j = mid;		// index for right subarr
	k = l;			// index for result arr

	while((i < mid) && (j <= r))
	{
		if(arr[i] <= arr[j])
		{
			temp[k++] = arr[i++];			
		}
		else
		{
			temp[k++] = arr[j++];
			inv_cnt += mid - i;
		}
	}

	while(i < mid)
		temp[k++] = arr[i++];
	while(j <= r)
		temp[k++] = arr[j++];

	for(i = l; i < r; ++i)
		arr[i] = temp[i];

	return inv_cnt;
}

int __mergeSort(int arr[], int temp[], int l, int r)
{
	int mid, inv_cnt = 0;

	if(l < r)
	{
		// mid = l + (r - l) / 2;    // it would resunt in overflow issue
		mid = l + (r - l) / 2;
		inv_cnt = __mergeSort(arr, temp, l, mid);
		inv_cnt += __mergeSort(arr, temp, mid + 1, r);

		inv_cnt += __merge(arr, temp, l, mid + 1, r);
	}
	return inv_cnt;
}

int countInversions(int arr[], int len)
{
	int *temp = new int[len];
	return __mergeSort(arr, temp, 0, len - 1);
}

#endif // GEEKS_SORT_USECASE_H