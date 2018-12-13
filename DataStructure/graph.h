#pragma once
#ifndef VECTOR
#define VECTOR
#include <vector>
using std::vector;
#endif // !vector
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
namespace dataStructure {
	class edge {
	private:
		int u;
		int v;
		int len;
	public:
		edge(int n1, int n2, int l) { u = n1; v = n2; len = l; };
		edge(const edge& e) { u = e.u; v = e.v; len = e.len; };
		edge() { u = -1; v = -1; len = INT_MAX; };
		int& getU() { return u; };
		int& getV() { return v; };
		int& getlen() { return len; };
	};
}