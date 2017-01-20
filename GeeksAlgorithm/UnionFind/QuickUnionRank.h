
// https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf

#ifndef GEEKS_QUICKUNION_RANK_H
#define GEEKS_QUICKUNION_RANK_H

#include <cassert>

using namespace std;

// Quick Union with rank
namespace QuickUnionRank
{
class UnionFind
{
    private:
        int* m_parent;
        int* m_rank;
        int m_count;

    public:
        UnionFind(int count)
		{
            m_parent = new int[count];
            m_rank = new int[count];
            this->m_count = count;
            for(int i = 0 ; i < count ; i ++)
			{
                m_parent[i] = i;
                m_rank[i] = 1;
            }
        }

        ~UnionFind(){
            delete[] m_parent;
            delete[] m_rank;
        }

        int size()
		{
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

            if(m_rank[pRoot] < m_rank[qRoot])
                m_parent[pRoot] = qRoot;
            else if(m_rank[qRoot] < m_rank[pRoot])
                m_parent[qRoot] = pRoot;
            else{ // rank[pRoot] == rank[qRoot]
                m_parent[pRoot] = qRoot;
                ++m_rank[qRoot];
            }
        }
};
}

#endif //GEEKS_QUICKUNION_RANK_H
