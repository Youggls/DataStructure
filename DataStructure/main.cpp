#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using dataStructure::AVLTree;
using dataStructure::AVLTreeNode;

void visit(AVLTreeNode<int>* node) {
	cout << node->getData() << ' ';
}

int main() {
	AVLTree<int> avl;
	int a[10] = { 62, 88, 58, 47, 35, 73, 51, 99, 37, 93, };
	for (int i = 0; i < 10; i++) {
		avl.insert(a[i]);
	}
	avl.levelOrder(visit);
	system("pause");
	return 0;
}