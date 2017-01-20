
// https://en.wikipedia.org/wiki/Graph_theory
// https://en.wikipedia.org/wiki/Adjacency_list

#ifndef GEEKS_SPARSEGRAPH_H
#define GEEKS_SPARSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// Adjacency list
class SparseGraph{

private:
    int m_vertices;			// number of vertices
	int m_edges;			// number of edges
    bool m_directed;
    vector<vector<int>> m_graph;

public:
    SparseGraph(int m_vertices , bool directed)
	{
        this->m_vertices = m_vertices;
        this->m_edges = 0;
        this->m_directed = directed;
        for(int i = 0 ; i < m_vertices ; i ++)
            m_graph.push_back(vector<int>());
    }

    ~SparseGraph()
	{

    }

    int V()
	{ 
		return m_vertices;
	}

    int E()
	{ 
		return m_edges;
	}

    void addEdge(int v, int w)
	{
        assert(v >= 0 && v < m_vertices);
        assert(w >= 0 && w < m_vertices);

        m_graph[v].push_back(w);
        if(v != w && !m_directed)
            m_graph[w].push_back(v);

        ++m_edges;
    }

    bool hasEdge(int v , int w)
	{
        assert(v >= 0 && v < m_vertices);
        assert(w >= 0 && w < m_vertices);

        for(unsigned i = 0 ; i < m_graph[v].size() ; ++i)
            if(m_graph[v][i] == w)
                return true;
        return false;
    }

    void show()
	{
        for(int i = 0 ; i < m_vertices ; i ++)
		{
            cout << "V" << i << ":\t";
            for(unsigned j = 0 ; j < m_graph[i].size() ; ++j)
                cout << m_graph[i][j] << "  ";
            cout<<endl;
        }
    }

	// Adjacent iterator
    class adjIterator
	{
    private:
        SparseGraph &G;
        int vertex;
        unsigned index;
    public:
        adjIterator(SparseGraph &graph, int vertex): G(graph)
		{
            this->vertex = vertex;
            this->index = 0;
        }

        int begin()
		{
            index = 0;
            if(G.m_graph[vertex].size())
                return G.m_graph[vertex][index];
            return -1;
        }

        int next()
		{
            ++index;
            if(index < G.m_graph[vertex].size())
                return G.m_graph[vertex][index];
            return -1;
        }

        bool end(){
            return index >= G.m_graph[vertex].size();
        }
    };
};

#endif //GEEKS_SPARSEGRAPH_H
