
// https://en.wikipedia.org/wiki/Graph_theory
// https://en.wikipedia.org/wiki/Adjacency_matrix


#ifndef GEEKS_WEIGHTED_DENSEGRAPH_H
#define GEEKS_WEIGHTED_DENSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

#include "Edge.h"

using namespace std;

// Adjacency_matrix
template <typename Weight>
class WeightedDenseGraph{

private:
	int m_vertices;			// number of vertices
	int m_edges;			// number of edges
    bool m_directed;
    vector<vector<Edge<Weight> *>> m_graph;

public:
    WeightedDenseGraph(int n , bool directed)
	{
        this->m_vertices = n;
        this->m_edges = 0;
        this->m_directed = directed;
        for(int i = 0 ; i < m_vertices ; i ++)
            m_graph.push_back(vector<Edge<Weight> *>(n, nullptr));
    }

    ~WeightedDenseGraph()
	{
		for(int i = 0 ; i < m_vertices ; ++i)
            for(int j = 0 ; j < m_vertices ; ++j)
                if( m_graph[i][j] != nullptr )
                    delete m_graph[i][j];

    }

    int V()
	{ 
		return m_vertices;
	}

    int E()
	{ 
		return m_edges;
	}

    void addEdge(int v , int w, Weight weight)
	{
        assert(v >= 0 && v < m_vertices);
        assert(w >= 0 && w < m_vertices);

        if(hasEdge(v , w))
		{
			delete m_graph[v][w];
			if(!m_directed)
				delete m_graph[w][v];
			--m_edges;
		}

        m_graph[v][w] = new Edge<Weight>(v, w, weight);
        if(!m_directed)
            m_graph[w][v] = new Edge<Weight>(w, v, weight);;

        ++m_edges;
    }

    bool hasEdge(int v , int w)
	{
        assert(v >= 0 && v < m_vertices);
        assert(w >= 0 && w < m_vertices);
        return m_graph[v][w] != nullptr;
    }

    void show()
	{
        for(int i = 0 ; i < m_vertices ; ++i)
		{
            cout << "V" << i << ":\t";
			for(int j = 0 ; j < m_vertices ; ++j)
				if(m_graph[i][j])
					cout << m_graph[i][j]->weight() << "\t";
				else
					cout << "SP\t";
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

        Edge<Weight>* begin()
		{
            index = -1;
            return next();
        }

        Edge<Weight>* next()
		{
            for(index += 1 ; index < G.V() ; ++index)
                if(G.m_graph[vertex][index])
                    return G.m_graph[vertex][index];
            return -1;
        }

        bool end()
		{
            return index >= G.V();
        }
    };
};

#endif //GEEKS_WEIGHTED_DENSEGRAPH_H
