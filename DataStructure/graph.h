#pragma once
#ifndef VECTOR
#define VECTOR
#include <vector>
using std::vector;
#endif // !vector

namespace dataStructure {
	class graph {
	private:
		vector<vector<int>> adjMatrix;
		int edge;
		int node;
		bool isReached(vector<int> reach, int n);
	public:
		graph(int n);
		int prim();
	};

	graph::graph(int n) {
		adjMatrix.resize(n);
		for (int i = 0; i < n; i++) adjMatrix.at(i).resize(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				adjMatrix.at(i).at(j) = 0;
			}
		}
	}

	int graph::prim() {

	}

	bool graph::isReached(vector<int> reach, int n) {
		for (int i = 0; i < reach.size(); i++) {
			if (n == reach.at(i)) return true;
		}
		return false;
	}
}