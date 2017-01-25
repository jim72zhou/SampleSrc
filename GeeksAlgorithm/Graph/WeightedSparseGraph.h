
// https://en.wikipedia.org/wiki/Graph_theory
// https://en.wikipedia.org/wiki/Adjacency_list

#ifndef GEEKS_WEIGHTED_SPARSEGRAPH_H
#define GEEKS_WEIGHTED_SPARSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

#include "Edge.h"

using namespace std;

// Adjacency list
template<typename Weight>
class WeightedSparseGraph
{
private:
    int m_vertices;			// number of vertices
	int m_edges;			// number of edges
    bool m_directed;
    vector<vector<Edge<Weight> *>> m_graph;

public:
    WeightedSparseGraph(int m_vertices , bool directed)
	{
        this->m_vertices = m_vertices;
        this->m_edges = 0;
        this->m_directed = directed;
        for(int i = 0 ; i < m_vertices ; i ++)
            m_graph.push_back(vector<Edge<Weight> *>());
    }

    ~WeightedSparseGraph()
	{
		 for(int i = 0 ; i < m_vertices; ++i)
            for(unsigned j = 0 ; j < m_graph[i].size() ; ++j)
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

    void addEdge(int v, int w, Weight weight)
	{
        assert(v >= 0 && v < m_vertices);
        assert(w >= 0 && w < m_vertices);

        m_graph[v].push_back(new Edge<Weight>(v, w, weight));
        if(v != w && !m_directed)
            m_graph[w].push_back(new Edge<Weight>(w, v, weight));

        ++m_edges;
    }

    bool hasEdge(int v , int w)
	{
        assert(v >= 0 && v < m_vertices);
        assert(w >= 0 && w < m_vertices);

        for(unsigned i = 0 ; i < m_graph[v].size() ; ++i)
            if(m_graph[v][i]->other(v) == w)
                return true;
        return false;
    }

    void show()
	{
        for(int i = 0 ; i < m_vertices ; i ++)
		{
            cout << "V" << i << ":\t";
            for(unsigned j = 0 ; j < m_graph[i].size() ; ++j)
				cout << "(To:" << m_graph[i][j]->w() << ", Wt:" << m_graph[i][j]->weight() << ") ";
            cout<<endl;
        }
    }

	// Adjacent iterator
    class adjIterator
	{
    private:
        WeightedSparseGraph &G;
        int vertex;
        unsigned index;
    public:
        adjIterator(WeightedSparseGraph &graph, int vertex): G(graph)
		{
            this->vertex = vertex;
            this->index = 0;
        }

        Edge<Weight>* begin()
		{
            index = 0;
            if(G.m_graph[vertex].size())
                return G.m_graph[vertex][index];
            return nullptr;
        }

        Edge<Weight>* next()
		{
            ++index;
            if(index < G.m_graph[vertex].size())
                return G.m_graph[vertex][index];
            return nullptr;
        }

        bool end(){
            return index >= G.m_graph[vertex].size();
        }
    };
};

#endif //GEEKS_WEIGHTED_SPARSEGRAPH_H
