#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace dataStructure;

int main() {
	binarySearchTree<char> bst;
	//string a, b;
	//cin >> a >> b;
	//char* aa = const_cast<char*>(a.c_str());
	//char* bb = const_cast<char*>(b.c_str());
	//bst.makeTree(bb, aa, a.size());
	//char c = 'A';
	//binaryTreeNode<char>* t = bst.search(c);
	//cout << t;
	char a[] = "asdfasdfasdf";
	bst.insert(a[0]);
	bst.insert(a[1]);
	bst.insert(a[2]);
//	bst.insert(a[0]);
	cout << bst.depth();
	system("pause");
	return 0;
}