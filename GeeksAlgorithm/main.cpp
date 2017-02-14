#include "stdafx.h"
#include "testSort.h"
#include "testTree.h"
#include "testUnionFind.h"
#include "testGraph.h"

using namespace std;

void prototypeTest(bool bTest)
{
	if(!bTest)
		return;

}
////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{

	prototypeTest(false);

	shortestPathTest(true);
	mstPerformanceTest(false);
	mstPerformanceDenseTest(false);
	weightedGraphTest(false);
	componentPathTest(false);
	graphReadTest(false);

	unionFindTest(false);
	
	avlTest(false);
	avlRemoveTest(false);

	rbtTest(false);
	rbtRemoveTest(false);
	
	bstCeilFloorTest(false);
	bstRemoveTest(false);
	bstRemoveMinMaxTest(false);
	bstTraverseTest(false);
	bstPerformanceTest(false);
	
	sortTest(false);

	//system("pause");
	return 0;
}
