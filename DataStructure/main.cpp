#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace dataStructure;

int main() {
	binaryTree<char> tree;
	string a, b;
	cin >> a >> b;
	tree.makeTree(b, a);
	cout << tree.depth();
	system("pause");
	return 0;
}