#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using dataStructure::binarySearchTree;

int main() {
	binarySearchTree<int> bst;
	bst.insert(1);
	bst.insert(-1);
	bst.insert(2);
	bst.deleteNode(1);
	system("pause");
	return 0;
}