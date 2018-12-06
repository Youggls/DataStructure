#include <bits/stdc++.h>
#include "DataStructure.hpp"
#include <Windows.h>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using dataStructure::AVLTree;
using dataStructure::binarySearchTree;

int main() {
	int n;
	cin >> n;
	AVLTree<int> avl;
	binarySearchTree<int> bst;
	LARGE_INTEGER t1, t2, tc;

	int* a = dataStructure::generateArray(n, 0);
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < n; i++) {
		avl.insert(a[i]);
	}
	QueryPerformanceCounter(&t2);
	cout << "AVLTree time:" << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
	cout << endl;

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < n; i++) {
		bst.insert(a[i]);
	}
	QueryPerformanceCounter(&t2);
	cout << "BSTree time:" << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
	cout << endl;

	delete a;
	system("pause");
	return 0;
}