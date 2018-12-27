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

#include <queue>
using std::queue;

namespace dataStructure {
	class edge {
	public:
		edge(int a, int b, int ww = 1) { i = a; j = b; w = ww; }
		edge() { i = 1; j = 1; w = INT_MAX; }
		edge(const edge& e) { i = e.i; j = e.j; w = e.w; }
		int i;
		int j;
		int w;
	};

	class adjMatrixGraph {
	private:
		int** adjMatrix;
		int v;
		int e;
		void _dfs(int v, int* isVisit);
		void _bfs(int v, int* isVisit);
		void _floy(vector<vector<int> > & c, vector<vector<int> >& kay);
	public:
		adjMatrixGraph(int n = 0);
		int verticesSize() { return v; }
		int edgeSize() { return e; }
		bool existEdge(int i, int j);
		void insertEdge(const edge& e);
		void insertEdge(int i, int j, int w = 1);
		void eraseEdge(int i, int j);

		void dfsVisit(int v);
		void bfsVisit(int v);
		vector<edge> kruskal();
		vector<edge> prim();
		vector<int> dijkstra(int s);
		void floyd(vector<vector<int> >& c, vector<vector<int> >& kay);
		edge* getAllEdge();
	};

	void adjMatrixGraph::_floy(vector<vector<int> >& c, vector<vector<int> >& kay) {
		c.resize(v + 1);
		kay.resize(v + 1);

		for (int i = 1; i <= v; i++) {
			c[i].resize(v + 1);
			kay[i].resize(v + 1);
			for (int j = 1; j <= v; j++) {
				if (i == j) c[i][j] = 0;
				else 
					c[i][j] = adjMatrix[i][j];

				kay[i][j] = 0;
			}
		}

		for (int k = 1; k <= v; k++) {
			for (int i = 1; i <= v; i++) {
				for (int j = 1; j <= v; j++) {
					if (c[i][k] != INT_MAX && c[k][j] != INT_MAX && (c[i][k] + c[k][j] < c[i][j])) {
						c[i][j] = c[i][k] + c[k][j];
						kay[i][j] = k;
					}
				}
			}
		}
	}

	void adjMatrixGraph::_dfs(int v, int* isVisit) {
		int num = 0;
		for (int i = 1; i <= this->v; i++) {
			if (adjMatrix[v][i] != INT_MAX && isVisit[i] == 0) {
				cout << i << ' ';
				isVisit[i] = 1;
				_dfs(i, isVisit);
			}
		}
	}

	void adjMatrixGraph::_bfs(int v, int* isVisit) {
		queue<int> adjToV;
		adjToV.push(v);

		while (!adjToV.empty()) {
			int tempV = adjToV.front();
			adjToV.pop();
			for (int i = 1; i < this->v + 1; i++) {
				if (adjMatrix[tempV][i] != INT_MAX && isVisit[i] == 0) {
					cout << i << ' ';
					isVisit[i] = 1;
					adjToV.push(i);
				}
			}
		}
	}

	adjMatrixGraph::adjMatrixGraph(int n) {
		if (n < 0) throw "The input is wrong!";

		v = n;
		e = 0;

		adjMatrix = new int*[n + 1];
		for (int i = 1; i < n + 1; i++) {
			adjMatrix[i] = new int[n + 1];
			for (int j = 1; j < n + 1; j++) adjMatrix[i][j] = INT_MAX;
		}
	}

	bool adjMatrixGraph::existEdge(int i, int j) {
		if (i < 1 || j < 1 || i > v || j > v || adjMatrix[i][j] == INT_MAX) return false;
		else return true;
	}

	void adjMatrixGraph::insertEdge(int i, int j, int w) {
		if (i < 1 || j < 1 || i > v || j > v) return;
		else if (adjMatrix[i][j] != INT_MAX) return;

		e++;
		adjMatrix[i][j] = w;
	}

	void adjMatrixGraph::insertEdge(const edge& ed) {
		int i = ed.i;
		int j = ed.j;
		int w = ed.w;

		insertEdge(i, j, w);
	}

	void adjMatrixGraph::eraseEdge(int i, int j) {
		if (i < 1 || j < 1 || i > v || j > v) return;
		adjMatrix[i][j] = INT_MAX;
		e--;
	}

	edge* adjMatrixGraph::getAllEdge() {
		edge* rev = new edge[e];

		int k = 0;
		for (int i = 1; i <= v; i++) {
			for (int j = 1; j <= v; j++) {
				if (adjMatrix[i][j] != INT_MAX) {
					rev[k].i = i;
					rev[k].j = j;
					rev[k].w = adjMatrix[i][j];
					k++;
				}
				if (k == e) 
					return rev;
			}
		}
		return rev;
	}

	void adjMatrixGraph::dfsVisit(int v) {
		int* isVisit = new int[this->v + 1];
		for (int i = 0; i < this->v + 1; i++) isVisit[i] = 0;
		cout << v << ' ';

		_dfs(v, isVisit);
	}

	void adjMatrixGraph::bfsVisit(int v) {
		int* isVisit = new int[this->v + 1];
		for (int i = 0; i < this->v + 1; i++) isVisit[i] = 0;
		cout << v << ' ';
		_bfs(v, isVisit);
	}

	vector<edge> adjMatrixGraph::kruskal() {
		edge* allEdge = getAllEdge();
		vector<edge> rev;
		for (int i = 0; i < e - 1; i++) {
			for (int j = i; j >= 0; j--) {
				if (allEdge[j + 1].w < allEdge[j].w) {
					edge t = allEdge[j + 1];
					allEdge[j + 1] = allEdge[j];
					allEdge[j] = t;
				}
			}
		}

		int* pre = new int[this->v + 1];
		for (int i = 1; i <= this->v; i++) pre[i] = i;
		int k = 1;
		int j = 0;
		while (k < this->v) {
			int t1 = pre[allEdge[j].i];
			int t2 = pre[allEdge[j].j];

			if (t1 != t2) {
				edge temp(allEdge[j].i, allEdge[j].j, allEdge[j].w);
				rev.push_back(temp);
				k++;
				for (int i = 0; i < v; i++) {
					if (pre[i + 1] == t2) pre[i + 1] = t1;
				}
			}
			j++;
		}
		delete allEdge;
		if (rev.size() == v - 1) {
			rev.resize(0);
			return rev;
		}
		return rev;
	}

	vector<edge> adjMatrixGraph::prim() {
		edge* allEdge = getAllEdge();
		vector<edge> rev;
		for (int i = 1; i < v - 1; i++) {
			for (int j = i; j >= 0; j--) {
				if (allEdge[j + 1].w < allEdge[j].w) {
					edge t = allEdge[j + 1];
					allEdge[j + 1] = allEdge[j];
					allEdge[j] = t;
				}
			}
		}

		vector<int> tv;
		tv.push_back(1);
		int k = 0;
		while (rev.size() != v - 1) {
			int u;
			int min_from = -1;
			int min_index = -1;
			int min_len = INT_MAX;
			for (int k = 0; k < tv.size(); k++) {
				u = tv[k];
				for (int i = 1; i <= v; i++) {
					if (adjMatrix[u][i] < min_len) {
						bool flag = true;
						for (int j = 0; j < tv.size(); j++) {
							if (tv[j] == i) {
								flag = false;
								break;
							}
						}
						if (flag) {
							min_len = adjMatrix[u][i];
							min_index = i;
							min_from = u;
						}
					}

				}
			}
			if (min_index == -1) break;
			else {
				tv.push_back(min_index);
				edge t(min_from, min_index, adjMatrix[min_from][min_index]);
				rev.push_back(t);
			}
		}

		if (rev.size() == v - 1) {
			return rev;
		}
		else {
			rev.resize(0);
			return rev;
		}
	}

	vector<int> adjMatrixGraph::dijkstra(int s) {
		vector<int> rev(v + 1);
		for (int i = 1; i <= v; i++) {
			if (adjMatrix[s][i] != INT_MAX) {
				rev[i] = s;
			}
			else {
				rev[i] = -1;
			}
		}
		rev[s] = 0;

		vector<int> distance(v + 1, INT_MAX);
		
		for (int i = 1; i <= v; i++) {
			distance[i] = adjMatrix[s][i];
		}
		distance[s] = 0;

		vector<int> newReachable;
		for (int i = 1; i <= v; i++) {
			if (rev[i] > 0) newReachable.push_back(i);
		}

		while (!newReachable.empty()) {
			int minDistance = INT_MAX;
			int min_index = -1;
			int minNode = -1;
			for (int i = 0; i < newReachable.size(); i++) {
				if (distance[newReachable[i]] < minDistance) {
					minNode = newReachable[i];
					min_index = i;
				}
			}

			vector<int>::iterator it = newReachable.begin() + min_index;
			newReachable.erase(it);
			for (int i = 1; i <= v; i++) {
				if (adjMatrix[minNode][i] != INT_MAX) {
					if (distance[i] > distance[minNode] + adjMatrix[minNode][i]) {
						distance[i] = distance[minNode] + adjMatrix[minNode][i];
						rev[i] = minNode;
						bool flag = false;
						for (int j = 0; j < newReachable.size(); j++) {
							if (newReachable[j] == i) {
								flag = true;
								break;
							}
						}
						if (!flag) {
							newReachable.push_back(i);
						}
					}
				}
			}
		}
		return rev;
	}

	void adjMatrixGraph::floyd(vector<vector<int> > & c, vector<vector<int> > & kay) {
		_floy(c, kay);
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