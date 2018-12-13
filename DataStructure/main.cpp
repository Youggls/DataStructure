#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;

vector<vector<int> > graph;
vector<int> inDegree;
vector<int> outDegree;
vector<int> ve;
vector<int> vl;
bool hasCircle;

void initialization(int);

bool judge() {
	for (int i = 0; i < graph.size(); i++) {
		int od = 0;
		int id = 0;
		for (int j = 0; j < graph.size(); j++) {
			if (graph.at(i).at(j) != INT_MAX) od++;
		}
		for (int j = 0; j < graph.size(); j++) {
			if (graph.at(j).at(i) != INT_MAX) id++;
		}

		inDegree[i] = id;
		outDegree[i] = od;
	}

	stack<int> zero;
	for (int i = 0; i < inDegree.size(); i++) {
		if (inDegree.at(i) == 0) zero.push(i);
	}

	while (!zero.empty()) {
		int top = zero.top();
		zero.pop();
		for (int i = 0; i < graph.size(); i++) {
			if (graph.at(top).at(i) != INT_MAX) {
				inDegree[i]--;
				if (inDegree[i] == 0) zero.push(i);
			}
		}
	}

	for (int i = 0; i < inDegree.size(); i++) {
		if (inDegree[i] != 0) return false;
	}

	return true;
}

int aoe(int n) {
	initialization(n);
	if (!judge()) 
		return -1;

	for (int i = 1; i < n + 2; i++) {
		vector<int> temp;
		for (int j = 0; j < n + 2; j++) {

			if (graph.at(j).at(i) != INT_MAX) {
				temp.push_back(j);
			}
		}

		//Find the max
		int max = 0;
		for (int j = 0; j < temp.size(); j++) {
			int t = temp[j];
			if ((max < graph.at(t).at(i) + ve[t]) && (graph.at(t).at(i) != INT_MAX)) 
				max = graph.at(t).at(i) + ve[t];
		}

		ve[i] = max;
	}
	//vl[n + 1] = ve[n + 1];
	//temp.clear();
	//for (int i = n + 1; i >= 0; i--) {
	//	for (int j = 0; j < n + 2; j++) {
	//		if (graph.at(j).at(i) != INT_MAX) {
	//			temp.push_back(j);
	//		}
	//	}
	//	//Find the min
	//	int min = 0;
	//	for (int j = 0; j < temp.size(); j++) {
	//		if (min > vl[j] - graph.at(j).at(i) && graph.at(j).at(i) != INT_MAX)
	//			min = vl[j] - graph.at(j).at(i);
	//	}
	//	vl[i] = min;
	//}

	return ve[n + 1];
}

void initialization(int n) {
	graph.resize(n + 2);
	inDegree.resize(n + 2, 0);
	outDegree.resize(n + 2, 0);
	ve.resize(n + 2);
	vl.resize(n + 2);
	for (int i = 0; i < n + 2; i++) {
		graph.at(i).resize(n + 2);
		ve.at(i) = 0;
		vl.at(i) = 0;
	}

	for (int i = 0; i < n + 2; i++) {
		for (int j = 0; j < n + 2; j++) {
			graph.at(i).at(j) = INT_MAX;
		}
	}

	for (int i = 0; i < n; i++) {
		string t;
		getline(cin, t);
		if (t == "") {
			i--;
			continue;
		}
		if (t.size() == 3) {
			graph.at(0).at(t[0] - '0') = t[2] - '0';
		}
		else if (t.size() > 3) {
			vector<int> from;
			int to = t[0] - '0';
			int len = t[2] - '0';
			int k = 3;
			while (k < t.size()) {
				if (t[k] == ' ' && t[k] == ';') {
					k++;
					continue;
				}
				else if (t[k] > '0' && t[k] < '9') {
					from.push_back(t[k] - '0');
				}
				k++;
			}

			for (int i = 0; i < from.size(); i++) {
				graph.at(from.at(i)).at(to) = len;
			}
		}
	}

	for (int i = 0; i < n + 1; i++) {
		bool flag = false;
		for (int j = 0; j < n + 2; j++) {
			if (graph.at(i).at(j) != INT_MAX) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			graph.at(i).at(n + 1) = 0;
		}
	}
}

void intialize(int* p, int r) {
	for (int i = 0; i < 9; i++) {
		if(p[i] != 0) graph.at(r).at(i) = p[i];
		else graph.at(r).at(i) = INT_MAX;
	}
}

int main() {
	//graph.resize(9);
	//inDegree.resize(9);
	//outDegree.resize(9);
	//ve.resize(9);
	//for (int i = 0; i < 7 + 2; i++) {
	//	graph.at(i).resize(7 + 2);
	//}
	//int r1[] = { 0,6,4,5,0,0,0,0,0 };
	//int r2[] = { 0,0,0,0,1,0,0,0,0 };
	//int r3[] = { 0,0,0,0,1,0,0,0,0 };
	//int r4[] = { 0,0,0,0,0,2,0,0,0 };
	//int r5[] = { 0,0,0,0,0,0,9,7,0 };
	//int r6[] = { 0,0,0,0,0,0,0,4,0 };
	//int r7[] = { 0,0,0,0,0,0,0,0,2 };
	//int r8[] = { 0,0,0,0,0,0,0,0,4 };
	//int r9[] = { 0,0,0,0,0,0,0,0,0 };
	//intialize(r1, 0);
	//intialize(r2, 1);
	//intialize(r3, 2);
	//intialize(r4, 3);
	//intialize(r5, 4);
	//intialize(r6, 5);
	//intialize(r7, 6);
	//intialize(r8, 7);
	//intialize(r9, 8);
	int n;
	cin >> n;
	int ans = aoe(n);
	if (ans == -1) cout << "error";
	else cout << ans;
	system("pause");
	return 0;
}