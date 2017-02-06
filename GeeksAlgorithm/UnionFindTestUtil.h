
#ifndef GEEKS_UNIONFINDTESTUTIL_H
#define GEEKS_UNIONFINDTESTUTIL_H

#include <iostream>
#include <ctime>
#include "UnionFind\QuickFind.h"
#include "UnionFind\QuickUnion.h"
#include "UnionFind\QuickUnionSize.h"
#include "UnionFind\QuickUnionRank.h"
#include "UnionFind\UnionFind.h"

using namespace std;

namespace UnionFindTestUtil
{
    void testQuickFind(int n)
	{
        srand(unsigned(time(NULL)));
        QuickFind::UnionFind uf = QuickFind::UnionFind(n);

        time_t startTime = clock();

        for(int i = 0 ; i < n ; i ++){
            int a = rand()%n;
            int b = rand()%n;
            uf.unionElements(a,b);
        }
        for(int i = 0 ; i < n ; i ++){
            int a = rand()%n;
            int b = rand()%n;
            uf.isConnected(a,b);
        }
        time_t endTime = clock();

        cout << "QuickFind, " << 2*n << " ops, " << double(endTime-startTime)/CLOCKS_PER_SEC << " s" << endl;
    }

    void testQuickUnion(int n)
	{
        srand(unsigned(time(NULL)));
        QuickUnion::UnionFind uf = QuickUnion::UnionFind(n);

        time_t startTime = clock();

        for(int i = 0 ; i < n ; i ++){
            int a = rand()%n;
            int b = rand()%n;
            uf.unionElements(a,b);
        }
        for(int i = 0 ; i < n ; i ++){
            int a = rand()%n;
            int b = rand()%n;
            uf.isConnected(a,b);
        }

        time_t endTime = clock();

        cout << "QuickUnion, " << 2*n << " ops, " << double(endTime-startTime)/CLOCKS_PER_SEC << " s" << endl;
    }

    void testQuickUnionSize(int n)
	{
        srand(unsigned(time(NULL)));
        QuickUnionSize::UnionFind uf = QuickUnionSize::UnionFind(n);

        time_t startTime = clock();

        for(int i = 0 ; i < n ; i ++){
            int a = rand()%n;
            int b = rand()%n;
            uf.unionElements(a,b);
        }
        for(int i = 0 ; i < n ; i ++){
            int a = rand()%n;
            int b = rand()%n;
            uf.isConnected(a,b);
        }

        time_t endTime = clock();

        cout << "QuickUnionSize, " << 2*n << " ops, " << double(endTime-startTime)/CLOCKS_PER_SEC << " s" << endl;
    }

    void testQuickUnionRank(int n)
	{
        srand(unsigned(time(NULL)));
        QuickUnionRank::UnionFind uf = QuickUnionRank::UnionFind(n);

        time_t startTime = clock();

        for(int i = 0 ; i < n ; i ++){
            int a = rand()%n;
            int b = rand()%n;
            uf.unionElements(a,b);
        }
        for(int i = 0 ; i < n ; i ++){
            int a = rand()%n;
            int b = rand()%n;
            uf.isConnected(a,b);
        }
        time_t endTime = clock();

        cout << "QuickUnionRank, " << 2*n << " ops, " << double(endTime-startTime)/CLOCKS_PER_SEC << " s" << endl;
    }

    void testUnionFind(int n)
	{
        srand(unsigned(time(NULL)));
        UnionFind uf = UnionFind(n);

        time_t startTime = clock();

        for(int i = 0 ; i < n ; i ++){
            int a = rand()%n;
            int b = rand()%n;
            uf.unionElements(a,b);
        }
        for(int i = 0 ; i < n ; i ++){
            int a = rand()%n;
            int b = rand()%n;
            uf.isConnected(a,b);
        }
        time_t endTime = clock();

        cout << "UninFindPathCompress , " << 2*n << " ops, " << double(endTime-startTime)/CLOCKS_PER_SEC << " s" << endl;
    }
}
#endif //GEEKS_UNIONFINDTESTUTIL_H
