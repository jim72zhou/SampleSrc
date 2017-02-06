#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

#include "UnionFindTestUtil.h"

void unionFindTest(bool bTest)
{
	if(!bTest)
		return;

	int n = 1000000;

    // Quick Find
//    UnionFindTestUtil::testQuickFind(n);

    // Quick Union
//    UnionFindTestUtil::testQuickUnion(n);

    // Quick Union + sz
    UnionFindTestUtil::testQuickUnionSize(n);

    // Quick Union + rank
    UnionFindTestUtil::testQuickUnionRank(n);

    // Quick Union + rank + path compression
    UnionFindTestUtil::testUnionFind(n);

}
