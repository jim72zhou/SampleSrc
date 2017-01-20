
// https://en.wikipedia.org/wiki/Graph_theory
// https://en.wikipedia.org/wiki/Adjacency_matrix


#ifndef GEEKS_DENSEGRAPH_H
#define GEEKS_DENSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// Adjacency_matrix
class DenseGraph{

private:
	int m_vertices;			// number of vertices
	int m_edges;			// number of edges
    bool m_directed;
    vector<vector<bool>> m_graph;

public:
    DenseGraph(int n , bool directed)
	{
        this->m_vertices = n;
        this->m_edges = 0;
        this->m_directed = directed;
        for(int i = 0 ; i < m_vertices ; i ++)
            m_graph.push_back(vector<bool>(m_vertices, false));
    }

    ~DenseGraph()
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

    void addEdge(int v , int w)
	{
        assert(v >= 0 && v < m_vertices);
        assert(w >= 0 && w < m_vertices);

        if(hasEdge(v , w))
            return;

        m_graph[v][w] = true;
        if(!m_directed)
            m_graph[w][v] = true;

        ++m_edges;
    }

    bool hasEdge(int v , int w)
	{
        assert(v >= 0 && v < m_vertices);
        assert(w >= 0 && w < m_vertices);
        return m_graph[v][w];
    }

    void show()
	{
        for(int i = 0 ; i < m_vertices ; ++i)
		{
            cout << "V" << i << ":\t";
			for(int j = 0 ; j < m_vertices ; ++j)
                cout << m_graph[i][j] << "  ";
            cout << endl;
        }
    }

	// Adjacent iterator
    class adjIterator
	{
    private:
        DenseGraph &G;
        int vertex;
        int index;
    public:
        adjIterator(DenseGraph &graph, int vertex): G(graph)
		{
            this->vertex = vertex;
            this->index = -1;
        }

        int begin()
		{
            index = -1;
            return next();
        }

        int next()
		{
            for(index += 1 ; index < G.V() ; ++index)
                if(G.m_graph[vertex][index])
                    return index;
            return -1;
        }

        bool end()
		{
            return index >= G.V();
        }
    };
};

#endif //GEEKS_DENSEGRAPH_H
