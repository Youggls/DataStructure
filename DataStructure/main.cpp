#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using dataStructure::AVLTree;

int main() {
	AVLTree<int> avl;
	int a[5] = { 88, 70, 61, 63, 65 };
	for (int i = 0; i < 5; i++) {
		avl.insert(a[i]);
	}
	avl.levelOrder();
	system("pause");
	return 0;
}