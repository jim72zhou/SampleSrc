#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

#include "Graph\DenseGraph.h"
#include "Graph\SparseGraph.h"
#include "Graph\WeightedDenseGraph.h"
#include "Graph\WeightedSparseGraph.h"
#include "Graph\Components.h"
#include "Graph\Path.h"
#include "Graph\ShortestPath.h"
#include "Graph\LazyPrimMST.h"
#include "Graph\PrimMST.h"

#include "FileProcs.h"

using namespace std;

void graphReadTest(bool bTest)
{
	if(!bTest)
		return;

    string filename = "..\\TestData\\dataG2.txt";

	int N = 13;

    SparseGraph g1(N, false);
    FileProcs::readGraph<SparseGraph>(g1 , filename);
	cout << "Sparse Graph:" << endl;
    g1.show();

	cout << endl << "Show by iterator:" << endl;
    for(int v = 0 ; v < N ; ++v)
	{
        cout << v << ": ";
        SparseGraph::adjIterator adj(g1 , v);
        for(int w = adj.begin() ; !adj.end() ; w = adj.next())
            cout << w << " ";
        cout<<endl;
    }

    cout<<endl;

    DenseGraph g2(N , false);
    FileProcs::readGraph<DenseGraph>(g2 , filename );
	cout << "Dense Graph:" << endl;
    g2.show();

	cout << endl << "Show by iterator:" << endl;
    for(int v = 0 ; v < N ; ++v)
	{
        cout << v << ": ";
        DenseGraph::adjIterator adj(g2 , v);
        for(int w = adj.begin() ; !adj.end() ; w = adj.next())
            cout << w << " ";
        cout<<endl;
    }
}

void componentPathTest(bool bTest)
{
    if(!bTest)
		return;

	// dataG1.txt
    string filename1 = "..\\TestData\\dataG1.txt";
    SparseGraph g1 = SparseGraph(6, false);
    FileProcs::readGraph<SparseGraph>(g1, filename1);
    g1.show();
	cout << endl;
	Component<SparseGraph> component1(g1);
    cout << "TestG1, Component Count: " << component1.count() << endl;

	Path<SparseGraph> dfs(g1, 0);
    cout << "DFS: ";
    dfs.showPath(4);

	ShortestPath<SparseGraph> bfs(g1, 0);
    cout << "BFS: ";
    bfs.showPath(4);

    cout << endl;

    // dataG2.txt
    string filename2 = "..\\TestData\\dataG2.txt";
    SparseGraph g2 = SparseGraph(13, false);
    FileProcs::readGraph<SparseGraph>(g2, filename2);
	g2.show();
	cout << endl;
    Component<SparseGraph> component2(g2);
    cout << "TestG2, Component Count: " << component2.count() << endl;

	cout << "Is V0 connected with V6? " << (component2.isConnected(0, 6) ? "Yes" : "No") << endl;
	cout << "Is V0 connected with V7? " << (component2.isConnected(0, 7) ? "Yes" : "No") << endl;

	Path<SparseGraph> dfs2(g2, 0);
    cout << "DFS: ";
    dfs2.showPath(6);
	dfs2.showPath(7);

	ShortestPath<SparseGraph> bfs2(g2, 0);
    cout << "BFS: ";
    bfs2.showPath(6);
	bfs2.showPath(7);

}

void weightedGraphTest(bool bTest)
{
    if(!bTest)
		return;

    string filename = "..\\TestData\\dataWeightG1.txt";
    int V = 8;
    cout << fixed << setprecision(2);

    // Test Weighted Dense Graph
    WeightedDenseGraph<double> g1 = WeightedDenseGraph<double>(V, false);
    FileProcs::readGraphEx<WeightedDenseGraph<double>, double>(g1, filename);
    g1.show();
    cout<<endl;

	// Test Lazy Prim MST
    cout << "Test Lazy Prim MST-Dense" << endl;
    LazyPrimMST<WeightedDenseGraph<double>, double> lazyPrimMST1(g1);
    vector<Edge<double>> mst1 = lazyPrimMST1.mstEdges();
    for(unsigned i = 0 ; i < mst1.size() ; ++i)
        cout << mst1[i] << endl;
    cout<<"The MST weight is: " << lazyPrimMST1.result() << endl;

	// Test Prim MST
    cout<<"Test Prim MST-Dense:"<<endl;
    PrimMST<WeightedDenseGraph<double>, double> primMST1(g1);
    vector<Edge<double>> mst10 = primMST1.mstEdges();
    for(unsigned i = 0 ; i < mst10.size() ; ++i)
        cout << mst10[i] << endl;
    cout<<"The Prim MST weight is: " << primMST1.result() << endl;
	cout<<endl;

    // Test Weighted Sparse Graph
    WeightedSparseGraph<double> g2 = WeightedSparseGraph<double>(V, false);
    FileProcs::readGraphEx<WeightedSparseGraph<double>, double>(g2, filename);
    g2.show();
    cout<<endl;

	cout << "Test Lazy Prim MST-Sparse:" << endl;
    LazyPrimMST<WeightedSparseGraph<double>, double> lazyPrimMST2(g2);
    vector<Edge<double>> mst2 = lazyPrimMST2.mstEdges();
    for(unsigned i = 0 ; i < mst2.size() ; ++i)
        cout << mst2[i] << endl;
    cout<<"The MST weight is: " << lazyPrimMST2.result() << endl;
	cout<<endl;

	// Test Prim MST
    cout<<"Test Prim MST-Dense:"<<endl;
    PrimMST<WeightedSparseGraph<double>, double> primMST2(g2);
    vector<Edge<double>> mst20 = primMST1.mstEdges();
    for(unsigned i = 0 ; i < mst20.size() ; ++i)
        cout << mst20[i] << endl;
    cout<<"The Prim MST weight is: " << primMST1.result() << endl;

}

void mstPerformanceTest(bool bTest)
{
    if(!bTest)
		return;

    string filename1 = "..\\TestData\\dataWeightG250.txt";
    int V1 = 250;

    string filename2 = "..\\TestData\\dataWeightG1000.txt";
    int V2 = 1000;

    string filename3 = "..\\TestData\\dataWeightG10000.txt";
    int V3 = 10000;


    WeightedSparseGraph<double> g1 = WeightedSparseGraph<double>(V1, false);
	FileProcs::readGraphEx<WeightedSparseGraph<double>, double>(g1, filename1);
    cout << filename1 << " load successfully." << endl;

	WeightedSparseGraph<double> g2 = WeightedSparseGraph<double>(V2, false);
	FileProcs::readGraphEx<WeightedSparseGraph<double>, double>(g2, filename2);
    cout << filename2 << " load successfully." << endl;

	WeightedSparseGraph<double> g3 = WeightedSparseGraph<double>(V3, false);
	FileProcs::readGraphEx<WeightedSparseGraph<double>, double>(g3, filename3);
    cout << filename3 << " load successfully." << endl;
   
    cout<<endl;

    clock_t startTime, endTime;

    // Test Lazy Prim MST
    cout << "Test Lazy Prim MST:" << endl;

    startTime = clock();
    LazyPrimMST<WeightedSparseGraph<double>, double> lazyPrimMST1(g1);
    endTime = clock();
    cout<<"Test for G1: "<< (double)(endTime-startTime)/CLOCKS_PER_SEC << " s." << endl;

    startTime = clock();
    LazyPrimMST<WeightedSparseGraph<double>, double> lazyPrimMST2(g2);
    endTime = clock();
    cout<<"Test for G2: "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    LazyPrimMST<WeightedSparseGraph<double>, double> lazyPrimMST3(g3);
    endTime = clock();
    cout<<"Test for G3: "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    cout<<endl;

    // Test Prim MST
    cout<<"Test Prim MST:"<<endl;

    startTime = clock();
    PrimMST<WeightedSparseGraph<double>, double> PrimMST1(g1);
    endTime = clock();
    cout<<"Test for G1: "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    PrimMST<WeightedSparseGraph<double>, double> PrimMST2(g2);
    endTime = clock();
    cout<<"Test for G2: "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    PrimMST<WeightedSparseGraph<double>, double> PrimMST3(g3);
    endTime = clock();
    cout<<"Test for G3: "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    cout<<endl;

}
