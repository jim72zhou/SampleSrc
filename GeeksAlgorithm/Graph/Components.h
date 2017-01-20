
// https://en.wikipedia.org/wiki/Connected_component_(graph_theory)

#ifndef GEEKS_COMPONENTS_H
#define GEEKS_COMPONENTS_H

#include <iostream>
#include <cassert>

using namespace std;

template <typename Graph>
class Component
{
private:
    Graph &G;
    bool *m_visited;
    int m_compCount;
    int *m_id;

    void dfs(int v)
	{
        m_visited[v] = true;
        m_id[v] = m_compCount;
        typename Graph::adjIterator adj(G, v);
        for(int i = adj.begin() ; !adj.end() ; i = adj.next())
		{
            if(!m_visited[i])
                dfs(i);
        }
    }

public:
    Component(Graph &graph): G(graph)
	{
        m_visited = new bool[G.V()];
        m_id = new int[G.V()];
        m_compCount = 0;
        for(int i = 0 ; i < G.V() ; ++i)
		{
            m_visited[i] = false;
            m_id[i] = -1;
        }

        for(int i = 0 ; i < G.V() ; ++i)
		{
            if(!m_visited[i])
			{
                dfs(i);
                ++m_compCount;
            }
		}
    }

    ~Component()
	{
        delete[] m_visited;
        delete[] m_id;
    }

    int count()
	{
        return m_compCount;
    }

    bool isConnected(int v , int w)
	{
        assert(v >= 0 && v < G.V());
        assert(w >= 0 && w < G.V());
        return m_id[v] == m_id[w];
    }
};

#endif // GEEKS_COMPONENTS_H
