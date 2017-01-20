
// https://en.wikipedia.org/wiki/Shortest_path_problem

#ifndef GEEKS_SHORTESTPATH_H
#define GEEKS_SHORTESTPATH_H

#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <cassert>

using namespace std;

template <typename Graph>
class ShortestPath
{
private:
    Graph &G;
    int m_start;	// start search vertex
    bool* m_visited;
    int * m_from;
    int * m_order;

	void bfs(int start)
	{        
		queue<int> q;

        q.push(start);
        m_visited[start] = true;
        m_order[start] = 0;

		while(!q.empty())
		{
            int v = q.front();
            q.pop();

            typename Graph::adjIterator adj(G, v);
            for(int i = adj.begin() ; !adj.end() ; i = adj.next())
			{
                if(!m_visited[i])
				{
                    q.push(i);
                    m_visited[i] = true;
                    m_from[i] = v;
                    m_order[i] = m_order[v] + 1;
                }
			}
        }
    }

public:
    ShortestPath(Graph &graph, int start):G(graph)
	{
        assert(start >= 0 && start < graph.V());

        m_visited = new bool[graph.V()];
        m_from = new int[graph.V()];
        m_order = new int[graph.V()];
        for(int i = 0 ; i < graph.V() ; i ++)
		{
            m_visited[i] = false;
            m_from[i] = -1;
            m_order[i] = -1;
        }
        this->m_start = start;

		bfs(start);
    }

    ~ShortestPath()
	{
        delete [] m_visited;
        delete [] m_from;
        delete [] m_order;
    }

    bool hasPath(int w)
	{
        assert(w >= 0 && w < G.V());
        return m_visited[w];
    }

    void path(int w, vector<int> &vec)
	{
        assert(w >= 0 && w < G.V());

        stack<int> ss;

        int p = w;
        while(p != -1)
		{
            ss.push(p);
            p = m_from[p];
        }

        vec.clear();
        while(!ss.empty())
		{
            vec.push_back(ss.top());
            ss.pop();
        }
    }

    void showPath(int w)
	{
        assert(w >= 0 && w < G.V());

        vector<int> vec;
        path(w, vec);
        for(unsigned i = 0 ; i < vec.size() ; i ++)
		{
            cout << vec[i];
            if(i == vec.size()-1)
                cout << endl;
            else
                cout << " -> ";
        }
    }

    int length(int w)
	{
        assert(w >= 0 && w < G.V());
        return m_order[w];
    }
};

#endif // GEEKS_SHORTESTPATH_H
