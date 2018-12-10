#include <bits/stdc++.h>
#include "DataStructure.hpp"
#include <Windows.h>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;
using dataStructure::BTree;

int main() {
	//AVLTree<int> avl;
	//int n;
	//cin >> n;
	//int* a = dataStructure::generateArray(n, 0);
	//LARGE_INTEGER t1, t2, tc;
	//QueryPerformanceFrequency(&tc);
	//QueryPerformanceCounter(&t1);
	//for (int i = 0; i < n; i++) {
	//	avl.insert(a[i]);
	//}
	//QueryPerformanceCounter(&t2);
	//cout << "AVL insert time:" << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << 's' << endl;
	//QueryPerformanceFrequency(&tc);
	//QueryPerformanceCounter(&t1);
	//for (int i = 0; i < n; i++) {
	//	avl.deleteNode(a[i]);
	//}
	//QueryPerformanceCounter(&t2);
	//cout << "AVL delete time:" << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << 's' << endl;
	BTree<int> bt(4);
	int n;
	cin >> n;
	int* a = dataStructure::generateArray(n, 0);
	for (int i = 0; i < n; i++) {
		bt.insert(a[i]);
	}
	system("pause");
	return 0;
}