#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

vector<vector<int>> graph;
vector<int> ve;
vector<int> vl;

int aoe(int n) {
	initialization(n);
	vector<int> temp;
	for (int i = 1; i < n + 2; i++) {
		for (int j = 0; j < n + 2; j++) {
			if (graph.at(j).at(i) != INT_MAX) {
				temp.push_back(j);
			}
		}

		//Find the max
		int max = 0;
		for (int j = 0; j < temp.size(); j++) {
			if (max < graph.at(j).at(i)) max = graph.at(j).at(i);
		}

		ve[i] = max + ve[i - 1];
	}


}

void initialization(int n) {
	graph.resize(n + 2);
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

		if (t.size() == 3) {
			graph.at(0).at(t[0] - '0') = t[2] - '0';
		}
		else if (t.size() > 3) {
			vector<int> from;
			int to = t[0];
			int len = t[2];
			int k = 3;
			while (k < t.size()) {
				if (t[k] == ' ' && t[k] == ';') {
					k++;
					continue;
				}
				else if (t[k] > '0' && t[k] < '9') {
					from.push_back(t[k] - '0');
				}
			}

			for (int i = 0; i < from.size(); i++) {
				graph.at(from.at(i)).at(to) = len;
			}
		}
	}

	for (int i = 0; i < n + 2; i++) {
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

int main() {
	int n;
	cin >> n;
	system("pause");
	return 0;
}