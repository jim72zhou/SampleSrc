// https://en.wikipedia.org/wiki/Prim%27s_algorithm
// https://en.wikipedia.org/wiki/Minimum_spanning_tree

#ifndef GEEKS_PRIMMST_H
#define GEEKS_PRIMMST_H

#include <iostream>
#include <vector>
#include <cassert>

#include "Edge.h"
#include "WeightedDenseGraph.h"
#include "WeightedSparseGraph.h"
#include "..\Heap\IndexMinHeap.h"

using namespace std;

template<typename Graph, typename Weight>
class PrimMST
{
private:
    Graph &G;
    IndexMinHeap<Weight> m_priorityQueue;
    bool *m_marked;
    vector<Edge<Weight>> m_mst;
    Weight m_mstWeight;
	vector<Edge<Weight>*> m_edgeTo;

    void visit(int v)
	{
        assert(!m_marked[v]);
        m_marked[v] = true;

        typename Graph::adjIterator adj(G,v);
		for(Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next())
		{
            int w = e->other(v);
            if(!m_marked[w])
			{
                if(!m_edgeTo[w])
				{
                    m_edgeTo[w] = e;
                    m_priorityQueue.insert(w, e->weight());
                }
                else if(e->weight() < m_edgeTo[w]->weight())
				{
                    m_edgeTo[w] = e;
                    m_priorityQueue.update(w, e->weight());
                }
            }
        }
    }

public:
	// Assume graph is connected
    PrimMST(Graph &graph):G(graph), m_priorityQueue(IndexMinHeap<Weight>(graph.V()))
	{
        m_marked = new bool[G.V()];
        for(int i = 0 ; i < G.V() ; ++i)
		{
            m_marked[i] = false;
			m_edgeTo.push_back(nullptr);
		}
        m_mst.clear();

        // Prim
        visit(0);
        while(!m_priorityQueue.isEmpty())
		{
            int v = m_priorityQueue.popMinIndex();
			assert(m_edgeTo[v]);

            m_mst.push_back(*m_edgeTo[v]);
            visit(v);
        }

        m_mstWeight = m_mst[0].weight();
        for(unsigned i = 1 ; i < m_mst.size() ; ++i)
            m_mstWeight += m_mst[i].weight();
    }

    ~PrimMST()
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

#endif // GEEKS_PRIMMST_H
