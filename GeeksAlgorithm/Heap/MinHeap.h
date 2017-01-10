#ifndef GEEKS_MIN_HEAP_H
#define GEEKS_MIN_HEAP_H

#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

// put the elements from data[1]
// child of item k is at 2k, 2k + 1
// parent of item k is at k/2

template<typename Item>
class MinHeap
{
public:
	MinHeap(int capacity)
	{
		m_pData = new Item[capacity + 1];
		this->m_capacity = capacity;
		m_count = 0;
	}

	MinHeap(Item arr[], int n){
        m_pData = new Item[n + 1];
        m_capacity = n;

        for(int i = 0 ; i < n ; ++i)
            m_pData[i + 1] = arr[i];
        m_count = n;

		// Starting from the lowest level and moving upwards, shift the root of each subtree 
		// downward as in the deletion algorithm until the heap property is restored. 
        for(int i = m_count / 2 ; i >= 1; --i)
            shiftDown(i);
    }

	~MinHeap()
	{
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
		shiftUp(m_count);
	}

	Item popMin()
	{
        assert(m_count > 0);
        Item ret = m_pData[1];

        m_pData[1] = m_pData[m_count];
        --m_count;
        shiftDown(1);

        return ret;
    }

    Item getMin()
	{
        assert(m_count > 0);
        return m_pData[1];
    }

private:
	int m_capacity;
	int m_count;
	Item* m_pData;

	void shiftUp(int k)
	{
		while(k > 1 && m_pData[k] < m_pData[k / 2]) 
		{
			swap(m_pData[k / 2], m_pData[k]);
			k = k / 2;
		}
	}

	void shiftDown(int k)
	{
		while(2 * k <= m_count)
		{
            int j = 2 * k;
            if(j + 1 <= m_count && m_pData[j + 1] < m_pData[j])
                ++j;
            // now, m_pData[j] is the min in m_pData[2*k] and m_pData[2*k+1]

            if( m_pData[k] <= m_pData[j] )
				break;
            swap(m_pData[k], m_pData[j]);
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
            cout<<m_pData[i]<<" ";
			if(pow(2, level) == i)
			{
				++level;
				cout<<endl;
			}
		}
        cout<<endl;
    }

};

#endif //GEEKS_MIN_HEAP_H