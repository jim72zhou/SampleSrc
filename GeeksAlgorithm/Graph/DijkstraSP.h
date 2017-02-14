// https://en.wikipedia.org/wiki/DijkstraSP%27s_algorithm
// http://math.mit.edu/~rothvoss/18.304.3PM/Presentations/1-Melissa.pdf

// can only be used on graphs without negative edge weights to solve
// Single-Source Shortest Path Problem

#ifndef GEEKS_DIJKSTRASP_H
#define GEEKS_DIJKSTRASP_H

#include <iostream>
#include <vector>
#include <stack>
#include "Edge.h"
#include "..\Heap\IndexMinHeap.h"

using namespace std;

template<typename Graph, typename Weight>
class DijkstraSP
{
private:
    Graph &G;
    int m_source;
    Weight *m_distTo;
    bool *m_marked;
    vector<Edge<Weight>*> m_from;

public:
    DijkstraSP(Graph &graph, int source):G(graph)
	{
        this->m_source = source;
        m_distTo = new Weight[G.V()];
        m_marked = new bool[G.V()];
        for(int i = 0; i < G.V(); ++i)
		{
            m_distTo[i] = Weight();
            m_marked[i] = false;
            m_from.push_back(nullptr);
        }

        IndexMinHeap<Weight> priorityQueue(G.V());

        // start dijkstra
        m_distTo[source] = Weight();
        priorityQueue.insert(source, m_distTo[source]);
        m_marked[source] = true;
        while(!priorityQueue.isEmpty()){
            int v = priorityQueue.popMinIndex();

            // m_distTo[v] is the shortest distance frm source to v
            m_marked[v] = true;
            typename Graph::adjIterator adj(G, v);
            // Relaxation
            for(Edge<Weight>* e = adj.begin() ; !adj.end() ; e = adj.next())
			{
                int w = e->other(v);
                if(!m_marked[w])
				{
                    if(m_from[w] == nullptr || m_distTo[v] + e->weight() < m_distTo[w])
					{
                        m_distTo[w] = m_distTo[v] + e->weight();
                        m_from[w] = e;
                        if(priorityQueue.contain(w))
                            priorityQueue.update(w, m_distTo[w]);
                        else
                            priorityQueue.insert(w, m_distTo[w]);
                    }
                }
            }
        }
    }

    ~DijkstraSP()
	{
        delete[] m_distTo;
        delete[] m_marked;
    }

    Weight shortestPathTo(int w)
	{
        assert(w >= 0 && w < G.V());
        return m_distTo[w];
    }

    bool hasPathTo(int w)
	{
        assert(w >= 0 && w < G.V());
        return m_marked[w];
    }

    void shortestPath(int w, vector<Edge<Weight>> &vec)
	{
        assert(w >= 0 && w < G.V());

        stack<Edge<Weight>*> source;
        Edge<Weight> *e = m_from[w];
        while(e->v() != this->m_source)
		{
            source.push(e);
            e = m_from[e->v()];
        }
        source.push(e);

        while(!source.empty())
		{
            e = source.top();
            vec.push_back(*e);
            source.pop();
        }
    }

    void showPath(int w)
	{
        assert(w >= 0 && w < G.V());

        vector<Edge<Weight>> vec;
        shortestPath(w, vec);
        for(unsigned i = 0 ; i < vec.size() ; ++i)
		{
            cout << vec[i].v() << " -> ";
            if(i == vec.size() - 1)
                cout << vec[i].w() << endl;
        }
    }
};

#endif // GEEKS_DIJKSTRASP_H
