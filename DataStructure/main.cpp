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
	char* aa = const_cast<char*>(a.c_str());
	char* bb = const_cast<char*>(b.c_str());
	bst.makeTree(bb, aa, a.size());
	cout << bst.depth();
	system("pause");
	return 0;
}