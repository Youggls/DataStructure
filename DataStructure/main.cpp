#include <bits/stdc++.h>
#include "DataStructure.hpp"
#include <windows.h>  
LARGE_INTEGER t1, t2, tc;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using dataStructure::adjMatrixGraph;
using dataStructure::edge;
//using dataStructure::generateArray;
//using dataStructure::BTree;
//using dataStructure::binarySearchTree;
//using dataStructure::printArr;
//using dataStructure::sparseMatrix;

int main() {
	adjMatrixGraph adj(5);
	for (int i = 0; i < 7; i++) {
		int a;
		int b;
		int w;
		cin >> a >> b >> w;
		adj.insertEdge(a, b, w);
	}
	vector<int> v = adj.dijkstra(1);
	v.size();
	system("pause");
	return 0;
}