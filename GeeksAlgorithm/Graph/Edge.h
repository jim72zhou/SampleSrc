// https://en.wikipedia.org/wiki/Graph_(discrete_mathematics)

#ifndef GEEKS_GRAPH_EDGE_H
#define GEEKS_GRAPH_EDGE_H

#include <iostream>
#include <cassert>

using namespace std;

template<typename Weight>
class Edge
{
private:
    int m_x, m_y;
    Weight m_weight;

public:
    Edge(int x, int y, Weight weight)
	{
        this->m_x = x;
        this->m_y = y;
        this->m_weight = weight;
    }

    Edge(){}

    ~Edge(){}

    int v(){ return m_x;}

    int w(){ return m_y;}

    Weight weight(){ return m_weight;}

    int other(int x)
	{
        assert(x == m_x || x == m_y);
        return x == x ? y : x;
    }

    friend ostream& operator<<(ostream &os, const Edge &e)
	{
        os << e.m_x << "-" << e.m_y << ": " << e.m_weight;
        return os;
    }

    bool operator<(Edge<Weight>& e)
	{
        return m_weight < e.weight();
    }

    bool operator<=(Edge<Weight>& e)
	{
        return m_weight <= e.weight();
    }

    bool operator>(Edge<Weight>& e)
	{
        return m_weight > e.weight();
    }

    bool operator>=(Edge<Weight>& e)
	{
        return m_weight >= e.weight();
    }

    bool operator==(Edge<Weight>& e)
	{
        return m_weight == e.weight();
    }
};

#endif // GEEKS_GRAPH_EDGE_H
