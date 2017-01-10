#ifndef GEEKS_INDEX_MAX_HEAP_H
#define GEEKS_INDEX_MAX_HEAP_H

#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

// Note

// Put the elements from data[1]
// child of item k is at 2k, 2k + 1
// parent of item k is at k/2

// If the data included so much info that data swapping should be avoid,
// new field m_pIndex for data is added

// For the heaps that often need be updated, 
// new field m_pReverse for data index in m_pIndex is added
// m_pReverse[i] represents index of data[i] in m_pIndex
//
// m_pIndex[i]   = j
// m_pReverse[j] = i
//
// m_pIndex[m_pReverse[i]] = i
// m_pReverse[m_pIndex[i]] = i
//

template<typename Item>
class IndexMaxHeap
{
public:
	IndexMaxHeap(int capacity)
	{
		m_pData = new Item[capacity + 1];
		m_pIndex = new int[capacity + 1];
		m_pReverse = new int[capacity + 1];
		this->m_capacity = capacity;
		m_count = 0;

		for(int i = 0 ; i < n ; ++i)
		{
			m_pIndex[i + 1] = 0;
			m_pReverse[i + 1] = 0;
		}
	}

	IndexMaxHeap(Item arr[], int n){
        m_pData = new Item[n + 1];
		m_pIndex = new int[n + 1];
		m_pReverse = new int[n + 1];
        m_capacity = n;

        for(int i = 0 ; i < n ; ++i)
		{
            m_pData[i + 1] = arr[i];
			m_pIndex[i + 1] = i + 1;
			m_pReverse[i + 1] = i + 1;
		}
        m_count = n;

		// Starting from the lowest level and moving upwards, shift the root of each subtree 
		// downward as in the deletion algorithm until the heap property is restored. 
        for(int i = m_count / 2 ; i >= 1; --i)
            shiftDown(i);
    }

	~IndexMaxHeap()
	{
		delete [] m_pIndex;
		delete [] m_pReverse;
		delete [] m_pData;
	}

	bool isEmpty()
	{
		return m_count == 0;	
	}

	bool isFull()
	{
		return m_count == m_capacity - 1;
	}

	int size()
	{
		return m_count;
	}

	int capacity()
	{
		return m_capacity;
	}
	
	void insert(Item item)
	{
		assert(m_count + 1 <= m_capacity);
		m_pData[++m_count] = item;
		m_pIndex[m_count] = m_count;
		m_pReverse[m_count] = m_count;
		shiftUp(m_count);
	}

    bool contain(int i)
	{
        assert(i + 1 >= 1 && i + 1 <= m_capacity);
        return m_pReverse[i + 1] != 0;
    }

    Item getItem(int i)
	{
        assert(contain(i));
        return m_pData[i + 1];
    }

	void update(int i, Item newItem)
	{
        assert(contain(i));
		m_pData[++i] = newItem;

        // find m_pIndex[j] = i, j the heap position for m_pData[i]
        // then shiftUp(j), and shiftDown(j)
		/* no reverse field version 
        for(int j = 1; j <= m_count; ++j)
		{
            if(m_pIndex[j] == i)
			{
                shiftUp(j);
                shiftDown(j);
                return;
            }
		}
		*/

		// has reverse filed version
		int j = m_pReverse[i];
        shiftUp( j );
        shiftDown( j );
    }

	Item popMax()
	{
        assert(m_count > 0);
        Item ret = m_pData[m_pIndex[1]];

        m_pIndex[1] = m_pIndex[m_count];
		m_pReverse[m_pIndex[m_count]] = 0;
        m_pReverse[m_pIndex[1]] = 1;
        --m_count;
        shiftDown(1);

        return ret;
    }

	int popMaxIndex()
	{
        assert(m_count > 0);
        Item ret = m_pIndex[1] -1;

        m_pIndex[1] = m_pIndex[m_count];
		m_pReverse[m_pIndex[m_count]] = 0;
        m_pReverse[m_pIndex[1]] = 1;
        --m_count;
        shiftDown(1);

        return ret;
    }

    Item getMax()
	{
        assert(m_count > 0);
        return m_pData[m_pIndex[1]];
    }

private:
	int m_capacity;
	int m_count;
	int* m_pIndex;
	int* m_pReverse;
	Item* m_pData;

	void shiftUp(int k)
	{
		while(k > 1 && m_pData[m_pIndex[k / 2]] < m_pData[m_pIndex[k]])
		{
			swap(m_pIndex[k / 2], m_pIndex[k]);
			m_pReverse[m_pIndex[k / 2]] = k / 2;
			m_pReverse[m_pIndex[k]] = k;
			k = k / 2;
		}
	}

	void shiftDown(int k)
	{
		while(2 * k <= m_count)
		{
            int j = 2 * k;
            if(j + 1 <= m_count && m_pData[m_pIndex[j + 1]] > m_pData[m_pIndex[j]])
                ++j;
            // now, data in m_pIndex[j] is the max in m_pIndex[2*k] and m_pIndex[2*k+1]

            if( m_pData[m_pIndex[k]] >= m_pData[m_pIndex[j]] )
				break;
            swap(m_pIndex[k], m_pIndex[j]);
			m_pReverse[m_pIndex[k]] = k;
			m_pReverse[m_pIndex[j]] = j;
            k = j;
        }	
	}

// functions to test the heap
public:
    void printData(){        

        cout<<"The Heap size is: " << size() << endl;
        cout<<"Data in heap: ";
		int level = 0;
        for(int i = 1 ; i <= size() ; ++i)
		{
            cout << "(" << m_pIndex[i] << "," << m_pData[m_pIndex[i]] << ") ";
			if(pow(2, level) == i)
			{
				++level;
				cout<<endl;
			}
		}
        cout<<endl;
    }

};

#endif //GEEKS_INDEX_MAX_HEAP_H