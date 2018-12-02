#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using dataStructure::AVLTree;
using dataStructure::binarySearchTree;

int main() {
	binarySearchTree<int> bst;
	int* a = new int[1000];
	for (int i = 0; i < 1000; i++) {
		a[i] = i;
	}
	for (int i = 0; i < 1000; i++) {
		bst.insert(a[i]);
	}
	system("pause");
	return 0;
}