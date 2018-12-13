#include <bits/stdc++.h>
#include <algorithm>
#include "DataStructure.hpp"
#include <Windows.h>
using std::cin;
using std::cout;
using std::endl;
using dataStructure::edge;
using std::sort;

int pre[105];
edge graph[105];

int find(int u) {
	int x = u;
	while (x != pre[x]) {
		x = pre[x];
	}
	return x;
}

void swap(int x, int y) {
	edge t = graph[x];
	graph[x] = graph[y];
	graph[y] = t;
}

int minimum(edge* g, int n, int e) {
	return 0;
}

int main() {
	int n, e;
	cin >> n >> e;
	for (int i = 1; i <= n; i++) {
		int u, v, l;
		cin >> u >> v >> l;
		graph[i].getU() = u;
		graph[i].getV() = v;
		graph[i].getlen() = l;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n - 1; j++) {
			if (graph[j].getlen() < graph[j + 1].getlen()) swap(j, j + 1);
		}
	}

	system("pause");
	return 0;
}