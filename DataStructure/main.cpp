#include <bits/stdc++.h>
#include "DataStructure.hpp"
#include <windows.h>  
LARGE_INTEGER t1, t2, tc;
using std::cin;
using std::cout;
using std::endl;
using dataStructure::generateArray;
using dataStructure::BTree;
using dataStructure::binarySearchTree;
using dataStructure::printArr;

int main() {
	binarySearchTree<int> bt;

	int n = 20;
	cin >> n;
	int* a = generateArray(n, -1);
//	printArr(a, n);
//	int a[] = { 2, 7, 16, 12, 10, 15, 14, 9, 17, 20, 6, 11, 19, 3, 8, 1, 4, 13, 18, 5, };
	for (int i = 0; i < n; i++)
		bt.insert(a[i]);

	for (int i = 0; i < n; i++)
		bt.deleteNode(a[i]);

	system("pause");
	return 0;
}