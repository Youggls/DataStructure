//#include <bits/stdc++.h>
//using std::cin;
//using std::cout;
//using std::endl;
//using std::vector;
//using std::string;
//using std::stack;
//using std::stringstream;
//
//vector<vector<int> > graph;
//vector<int> inDegree;
//vector<int> outDegree;
//vector<int> ve;
//vector<int> vl;
//bool hasCircle;
//
//void initialization(int);
//
//bool judge() {
//	for (int i = 0; i < graph.size(); i++) {
//		int od = 0;
//		int id = 0;
//		for (int j = 0; j < graph.size(); j++) {
//			if (graph.at(i).at(j) != INT_MAX) od++;
//		}
//		for (int j = 0; j < graph.size(); j++) {
//			if (graph.at(j).at(i) != INT_MAX) id++;
//		}
//
//		inDegree[i] = id;
//		outDegree[i] = od;
//	}
//
//	stack<int> zero;
//	for (int i = 0; i < inDegree.size(); i++) {
//		if (inDegree.at(i) == 0) zero.push(i);
//	}
//
//	while (!zero.empty()) {
//		int top = zero.top();
//		zero.pop();
//		for (int i = 0; i < graph.size(); i++) {
//			if (graph.at(top).at(i) != INT_MAX) {
//				inDegree[i]--;
//				if (inDegree[i] == 0) zero.push(i);
//			}
//		}
//	}
//
//	for (int i = 0; i < inDegree.size(); i++) {
//		if (inDegree[i] != 0) return false;
//	}
//
//	return true;
//}
//
//int calve(int pos, int n) {
//	if (ve[pos] == -1) {
//		int max = 0;
//		for (int i = 0; i < n + 2; i++) {
//			if (graph.at(i).at(pos) != INT_MAX) {
//				int preve = 0;
//				if (ve[i] == -1) preve = calve(i, n);
//				else preve = ve[i];
//				if (max < preve + graph.at(i).at(pos)) max = preve + graph.at(i).at(pos);
//			}
//		}
//		return max;
//	}
//	else return ve[pos];
//}
//
//int aoe(int n) {
//	initialization(n);
//	ve[0] = 0;
//	if (!judge())
//		return INT_MAX;
//
//	for (int i = 1; i < n + 2; i++) {
//		vector<int> temp;
//		for (int j = 0; j < n + 2; j++) {
//
//			if (graph.at(j).at(i) != INT_MAX) {
//				temp.push_back(j);
//			}
//		}
//
//		//Find the max
//		int max = 0;
//		for (int j = 0; j < temp.size(); j++) {
//			int t = temp[j];
//			int k = t;
//			int preve = calve(t, n);
//			if ((max < graph.at(t).at(i) + preve) && (graph.at(t).at(i) != INT_MAX))
//				max = graph.at(t).at(i) + preve;
//		}
//
//		ve[i] = max;
//	}
//
//	return ve[n + 1];
//}
//
//vector<int> split(string& src) {
//	vector<int> rev;
//	for (int i = 1; i < src.size();) {
//		int k = 0;
//		if (src[i] == ' ' || src[i] == ';') {
//			i++;
//			continue;
//		}
//		while (src[i + k] >= '0' && src[i + k] <= '9') {
//			k++;
//			if (k >= src.size()) break;
//		}
//		string substr = src.substr(i, k);
//		stringstream sstream(substr);
//		int fromNode;
//		sstream >> fromNode;
//		i += k;
//		rev.push_back(fromNode);
//	}
//
//	return rev;
//}
//
//void initialization(int n) {
//	graph.resize(n + 2);
//	inDegree.resize(n + 2, 0);
//	outDegree.resize(n + 2, 0);
//	ve.resize(n + 2);
//	vl.resize(n + 2);
//	for (int i = 0; i < n + 2; i++) {
//		graph.at(i).resize(n + 2);
//		ve.at(i) = -1;
//		vl.at(i) = 0;
//	}
//
//	for (int i = 0; i < n + 2; i++) {
//		for (int j = 0; j < n + 2; j++) {
//			graph.at(i).at(j) = INT_MAX;
//		}
//	}
//
//	int m = 0;
//	while (m < n)
//	{
//		int tonum;
//		cin >> tonum;
//		int lennum;
//		cin >> lennum;
//		string fromstring;
//		getline(cin, fromstring);
//		vector<int> from = split(fromstring);
//
//		if (from.size() == 0) {
//			graph.at(0).at(tonum) = lennum;
//		}
//
//		for (int j = 0; j < from.size(); j++) {
//			graph.at(from.at(j)).at(tonum) = lennum;
//		}
//		m++;
//	}
//
//	for (int i = 0; i < n + 1; i++) {
//		bool flag = false;
//		for (int j = 0; j < n + 2; j++) {
//			if (graph.at(i).at(j) != INT_MAX) {
//				flag = true;
//				break;
//			}
//		}
//		if (!flag) {
//			graph.at(i).at(n + 1) = 0;
//		}
//	}
//}
//
////int main() {
////	int n;
////	cin >> n;
////	int t = aoe(n);
////	if (t != INT_MAX) {
////		cout << t;
////	}
////	else cout << "error";
////	system("pause");
////	return 0;
////}