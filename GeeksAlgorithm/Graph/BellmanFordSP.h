// https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
// http://www.cs.rpi.edu/~musser/gp/algorithm-concepts/bellman-ford-screen.pdf

#ifndef GEEKS_BELLMANFORDSP_H
#define GEEKS_BELLMANFORDSP_H

#include <stack>
#include <vector>
#include "Edge.h"

using namespace std;


template <typename Graph, typename Weight>
class BellmanFordSP
{
private:
    Graph &G;
    int m_source;
    Weight* m_distTo;
    vector<Edge<Weight>*> m_from;
    bool m_hasNegativeCycle;

    bool detectNegativeCycle()
	{
        for(int i = 0 ; i < G.V() ; ++i)
		{
            typename Graph::adjIterator adj(G,i);
            for(Edge<Weight>* e = adj.begin() ; !adj.end() ; e = adj.next())
                if(!m_from[e->w()] || m_distTo[e->v()] + e->weight() < m_distTo[e->w()])
                    return true;
        }

        return false;
    }

public:
    BellmanFordSP(Graph &graph, int source):G(graph)
	{
        this->m_source = source;
        m_distTo = new Weight[G.V()];
        for(int i = 0 ; i < G.V() ; ++i)
		{
			m_from.push_back(nullptr);
        }

        // Bellman-Ford
        m_distTo[source] = Weight();

        for(int pass = 1 ; pass < G.V() ; ++pass)
		{
            // Relaxation
            for(int i = 0 ; i < G.V() ; i ++)
			{
                typename Graph::adjIterator adj(G,i);
                for(Edge<Weight>* e = adj.begin() ; !adj.end() ; e = adj.next())
                    if(!m_from[e->w()] || m_distTo[e->v()] + e->weight() < m_distTo[e->w()])
					{
                        m_distTo[e->w()] = m_distTo[e->v()] + e->weight();
                        m_from[e->w()] = e;
                    }
            }
        }

        m_hasNegativeCycle = detectNegativeCycle();
    }

    ~BellmanFordSP()
	{
        delete[] m_distTo;
    }

    bool isNegativeCycle()
	{
        return m_hasNegativeCycle;
    }

    Weight shortestPathTo(int w)
	{
        assert(w >= 0 && w < G.V());
        assert(!m_hasNegativeCycle);
        return m_distTo[w];
    }

    bool hasPathTo(int w)
	{
        assert(w >= 0 && w < G.V());
        return m_from[w] != nullptr;
    }

    void shortestPath(int w, vector<Edge<Weight>> &vec)
	{
        assert(w >= 0 && w < G.V());
        assert(!m_hasNegativeCycle);

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
        assert(!m_hasNegativeCycle);

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

#endif // GEEKS_BELLMANFORDSP_H
