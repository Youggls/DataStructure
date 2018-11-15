#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace dataStructure;

int main() {
	int n, m;
	cin >> n >> m;
	maxHeap<int> heap(n);
	int* arr = new int[m];
	int k = 0;
	while (true) {
		if (k > n - 1) break;
		int t;
		cin >> t;
		heap.insert(t);
		k++;
	}
	k = 0;
	while (true) {
		if (k > m - 1) break;
		cin >> arr[k];
		k++;
	}
	for (int i = 0; i < m; i++) {
		heap.printWayToRoot(arr[i]);
	}
	system("pause");
	return 0;
}