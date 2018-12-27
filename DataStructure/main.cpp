#include <bits/stdc++.h>
#include "DataStructure.hpp"

using std::cin;
using std::cout;
using std::endl;
using dataStructure::adjMatrixGraph;

int main() {
	adjMatrixGraph adj(10);
	for (int i = 0; i < 15; i++) {
		int from;
		int to;
		int len;
		cin >> from >> to >> len;
		adj.insertEdge(from, to, len);
	}

	vector<vector<int> > c;
	vector<vector<int> > kay;
	adj.floyd(c, kay);
	cout << c[1][1];
	system("pause");
	return 0;
}