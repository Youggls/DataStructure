#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;
using dataStructure::RBTree;

int main() {
	//int* a = generateArray(10);
	//a = rankSort<int>(a, 10);
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		a[i] = t;
	}

	RBTree<int> rbt;
	for (int i = 0; i < n; i++) {
		rbt.insert(a[i]);
	}
	cout << endl;
	system("pause");
	return 0;
}