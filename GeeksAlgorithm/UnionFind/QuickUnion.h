// https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf

#ifndef GEEKS_QUICKUNION_H
#define GEEKS_QUICKUNION_H

#include <cassert>

using namespace std;


// Quick Union Version
namespace QuickUnion
{
class UnionFind
{
    private:
        int* m_parent;
        int m_count;

    public:
        UnionFind(int count)
		{
            m_parent = new int[count];
            this->m_count = count;
            for(int i = 0 ; i < count ; i ++)
                m_parent[i] = i;
        }

        ~UnionFind(){
            delete[] m_parent;
        }

        int size(){
            return m_count;
        }

        bool isConnected(int p , int q)
		{
            return root(p) == root(q);
        }

        int root(int p)
		{
            assert(p >= 0 && p < m_count);
            while(p != m_parent[p])
                p = m_parent[p];
            return p;
        }

        void unionElements(int p, int q)
		{
            int pRoot = root(p);
            int qRoot = root(q);

            if(pRoot == qRoot)
                return;

            m_parent[pRoot] = qRoot;
        }
};
}

#endif //GEEKS_QUICKUNION_H
