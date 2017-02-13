// https://en.wikipedia.org/wiki/Prim%27s_algorithm
// https://en.wikipedia.org/wiki/Minimum_spanning_tree

#ifndef GEEKS_LAZYPRIMMST_H
#define GEEKS_LAZYPRIMMST_H

#include <iostream>
#include <vector>
#include <cassert>

#include "Edge.h"
#include "WeightedDenseGraph.h"
#include "WeightedSparseGraph.h"
#include "..\Heap\MinHeap.h"

using namespace std;

template<typename Graph, typename Weight>
class LazyPrimMST
{
private:
    Graph &G;
    MinHeap<Edge<Weight>> m_priorityQueue;
    bool *m_marked;
    vector<Edge<Weight>> m_mst;
    Weight m_mstWeight;

    void visit(int v)
	{
        assert(!m_marked[v]);
        m_marked[v] = true;

        typename Graph::adjIterator adj(G,v);
        for(Edge<Weight>* e = adj.begin() ; !adj.end() ; e = adj.next())
            if(!m_marked[e->other(v)])
                m_priorityQueue.insert(*e);
    }

public:
    LazyPrimMST(Graph &graph):G(graph), m_priorityQueue(MinHeap<Edge<Weight>>(graph.E()))
	{
        m_marked = new bool[G.V()];
        for(int i = 0 ; i < G.V() ; ++i)
            m_marked[i] = false;
        m_mst.clear();

        // Lazy Prim
        visit(0);
        while(!m_priorityQueue.isEmpty())
		{
            Edge<Weight> e = m_priorityQueue.popMin();
            if(m_marked[e.v()] == m_marked[e.w()])
                continue;

            m_mst.push_back(e);
            if(!m_marked[e.v()])
                visit(e.v());
            else
                visit(e.w());
        }

        m_mstWeight = m_mst[0].weight();
        for(unsigned i = 1 ; i < m_mst.size() ; ++i)
            m_mstWeight += m_mst[i].weight();
    }

    ~LazyPrimMST()
	{
        delete[] m_marked;
    }

    vector<Edge<Weight>> mstEdges()
	{
        return m_mst;
    }

    Weight result()
	{
        return m_mstWeight;
    }
};

#endif // GEEKS_LAZYPRIMMST_H
