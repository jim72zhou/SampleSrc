// https://en.wikipedia.org/wiki/Kruskal%27s_algorithm

#ifndef GEEKS_KRUSKALMST_H
#define GEEKS_KRUSKALMST_H

#include <iostream>
#include <vector>

#include "Edge.h"
#include "..\Heap\MinHeap.h"
#include "..\UnionFind\UnionFind.h"

using namespace std;


template <typename Graph, typename Weight>
class KruskalMST
{
private:
	vector<Edge<Weight>> m_mst;
    Weight m_mstWeight;

public:
    KruskalMST(Graph &graph)
	{
        MinHeap<Edge<Weight>> priorityQueue(graph.E());
        for(int i = 0 ; i < graph.V() ; ++i)
		{
            typename Graph::adjIterator adj(graph, i);
            for(Edge<Weight> *e = adj.begin(); !adj.end() ; e = adj.next())
                if(e->v() < e->w())
                    priorityQueue.insert(*e);
        }

        UnionFind uf = UnionFind(graph.V());
        while(!priorityQueue.isEmpty() && int(m_mst.size()) < graph.V() - 1)
		{
            Edge<Weight> e = priorityQueue.popMin();
            if(uf.isConnected(e.v(), e.w()))
                continue;

            m_mst.push_back(e);
            uf.unionElements(e.v(), e.w());
        }

        m_mstWeight = m_mst[0].weight();
        for(unsigned i = 1 ; i < m_mst.size() ; ++i)
            m_mstWeight += m_mst[i].weight();
    }

    ~KruskalMST()
	{

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

#endif // GEEKS_KRUSKALMST_H
