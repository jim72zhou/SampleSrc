
//https://en.wikipedia.org/wiki/Path_(graph_theory)

#ifndef GEEKS_PATH_H
#define GEEKS_PATH_H

#include <vector>
#include <stack>
#include <iostream>
#include <cassert>

using namespace std;

template <typename Graph>
class Path
{
private:
    Graph &G;
    int m_source;	// source search vertex
    bool* m_visited;
    int * m_from;

    void dfs(int v)
	{
        m_visited[v] = true;

        typename Graph::adjIterator adj(G, v);
        for(int i = adj.begin() ; !adj.end() ; i = adj.next())
		{
            if(!m_visited[i])
			{
                m_from[i] = v;
                dfs(i);
            }
        }
    }

public:
    Path(Graph &graph, int source):G(graph)
	{
        assert(source >= 0 && source < G.V());

        m_visited = new bool[G.V()];
        m_from = new int[G.V()];
        for(int i = 0 ; i < G.V() ; ++i)
		{
            m_visited[i] = false;
            m_from[i] = -1;
        }
        this->m_source = source;

        dfs(source);
    }

    ~Path()
	{
        delete [] m_visited;
        delete [] m_from;
    }

    bool hasPath(int w)
	{
        assert(w >= 0 && w < G.V());
        return m_visited[w];
    }

    void path(int w, vector<int> &vec)
	{
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
        vector<int> vec;
        path(w , vec);
        for(unsigned i = 0 ; i < vec.size() ; ++i)
		{
            cout << vec[i];
            if(i == vec.size() - 1)
                cout << endl;
            else
                cout << " -> ";
        }
    }
};

#endif //GEEKS_PATH_H
