#pragma once
#ifndef VECTOR
#define VECTOR
#include <vector>
using std::vector;
#endif // !vector

#ifndef STRING
#define STRING
#include <string>
using std::string;
#endif // !STRING

#define DIRECTED_GRAPH 0;
#define UNDIRECTED_GRAPH 1;

namespace dataStructure {
	class edge {
	private:
		int from;
		int to;
		int len;
	public:
		edge(int n1, int n2, int l) { from = n1; to = n2; len = l; };
		edge(const edge& e) { from = e.from; to = e.to; len = e.len; };
		edge() { from = -1; to = -1; len = INT_MAX; };
		int getFrom() const { return from; };
		int getTo() const { return to; };
		int getLen() const { return len; };

		void setFrom(const int& f) { from = f; };
		void setTo(const int& t) { to = t; };
		void setLen(const int& l) { len = l; };
	};
	class graph {
	private:
		vector<vector<int>> adjMatrix;
		int nodeNum;
		int edgeNum;
	public:
		graph(int n);
		void insertEdge(const edge& e);
		void insertEdge(const int& from, const int& to, const int& len = 1);
	};

	graph::graph(int n) {
		adjMatrix.resize(n);
		for (int i = 0; i < n; i++) {
			adjMatrix.at(i).resize(n);
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				adjMatrix.at(i).at(j) = INT_MAX;
			}
		}

		nodeNum = 0;
		edgeNum = 0;
	}

	void graph::insertEdge(const edge& e) {
		int from = e.getFrom();
		int to = e.getTo();
		int len = e.getLen();

		adjMatrix.at(from).at(to) = len;
	}
	
	void graph::insertEdge(const int& f, const int& t, const int& l) {
		adjMatrix.at(f).at(t) = l;
	}

	
}

//#include <bits/stdc++.h>
//using std::cin;
//using std::cout;
//using std::endl;
//using std::vector;
//
//class edge {
//private:
//	int u;
//	int v;
//	int len;
//public:
//	edge(int n1, int n2, int l) { u = n1; v = n2; len = l; };
//	edge(const edge& e) { u = e.u; v = e.v; len = e.len; };
//	edge() { u = -1; v = -1; len = INT_MAX; };
//	int& getU() { return u; };
//	int& getV() { return v; };
//	int& getlen() { return len; };
//};
//
//int pre[105];
//edge graph[105];
//
//int find(int u) {
//	int x = u;
//	while (x != pre[x]) {
//		x = pre[x];
//	}
//	return x;
//}
//
//void swap(int x, int y) {
//	edge t = graph[x];
//	graph[x] = graph[y];
//	graph[y] = t;
//}
//
//bool haveCircle(edge* e) {
//	if (find(e->getU()) == find(e->getV())) return true;
//	else return false;
//}
//
//int minimum(int n, int e) {
//	for (int i = 1; i <= n; i++) {
//		pre[i] = i;
//	}
//	int k = 1;
//	vector<edge*> minimumTree;
//	while (e - k + 1 != 0 && minimumTree.size() != n - 1) {
//		edge* temp = &graph[k];
//		k++;
//		if (haveCircle(temp)) continue;
//		else {
//			int fx = find(temp->getU());
//			int fy = find(temp->getV());
//			pre[fx] = fy;
//			minimumTree.push_back(temp);
//		}
//	}
//	if (minimumTree.size() == n - 1) {
//		int sum = 0;
//		for (int i = 0; i < minimumTree.size(); i++) {
//			sum += minimumTree.at(i)->getlen();
//		}
//		return sum;
//	}
//	else return -1;
//}
//
//int main() {
//	int n, e;
//	cin >> n >> e;
//	for (int i = 1; i <= e; i++) {
//		int u, v, l;
//		cin >> u >> v >> l;
//		graph[i].getU() = u;
//		graph[i].getV() = v;
//		graph[i].getlen() = l;
//	}
//
//	for (int i = 1; i <= e; i++) {
//		for (int j = 1; j <= e - 1; j++) {
//			if (graph[j].getlen() > graph[j + 1].getlen()) swap(j, j + 1);
//		}
//	}
//
//	int ans = minimum(n, e);
//	if (ans != -1) cout << ans;
//	else cout << "Impossible";
//
//	system("pause");
//	return 0;
//}