#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;
using dataStructure::BTree;


int main() {
	BTree<int> bt(4);
	for (int i = 0; i < 10; i++) 
		bt.insert(i);
	for (int i = 0; i < 10; i++) bt.deleteElement(i);
	system("pause");
	return 0;
}