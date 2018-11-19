#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace dataStructure;

int main() {
	binarySearchTree<char> bst;
	string a, b;
	cin >> a >> b;
	bst.makeTree(b, a);
	cout << bst.depth();
	system("pause");
	return 0;
}