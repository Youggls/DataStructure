#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;
using dataStructure::RBTree;
using dataStructure::generateArray;

int main() {
	//int* a = generateArray(10);
	//a = rankSort<int>(a, 10);
	int n;
//r	n = 40;
	cin >> n;
	int* a = generateArray(n);
//	int a[40];
//	for (int i = 0; i < n; i++) cin >> a[i];
	
	RBTree<int> rbt;
	for (int i = 0; i < n; i++) {
		int t = a[i];
		rbt.insert(t);
	}

	cout << endl;
	system("pause");
	return 0;
}