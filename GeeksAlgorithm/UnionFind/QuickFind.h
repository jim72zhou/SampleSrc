// https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf

#ifndef GEEKS_QUICKFIND_H
#define GEEKS_QUICKFIND_H

#include <cassert>

using namespace std;


// Quick Find Version
namespace QuickFind
{
class UnionFind
{
    private:
        int* m_id;
        int m_count;

    public:
        UnionFind(int count)
		{
            m_id = new int[count];
            this->m_count = count;
            for(int i = 0 ; i < count ; i ++)
                m_id[i] = i;
        }

        ~UnionFind()
		{
            delete[] m_id;
        }

        int size()
		{
            return m_count;
        }

        bool isConnected(int p , int q)
		{
            return m_id[p] == m_id[q];
        }

        int root(int p)
		{
            assert(p >= 0 && p < m_count);
            return m_id[p];
        }

        void unionElements(int p, int q)
		{
            int pID = root(p);
            int qID = root(q);

            if(pID == qID)
                return;

            for(int i = 0 ; i < m_count ; i ++)
                if(m_id[i] == pID)
                    m_id[i] = qID;
        }
};
}

#endif //GEEKS_QUICKFIND_H
