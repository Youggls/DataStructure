#include <bits/stdc++.h>
#include "DataStructure.hpp"

using std::cin;
using std::cout;
using std::endl;
using dataStructure::sparseMatrix;
using std::vector;

int main() {
	sparseMatrix a(4, 4, 4);
	sparseMatrix b(3, 4, 4);
	a.insert(2, 1, 4);
	a.insert(3, 2, 2);
	a.insert(-4, 2, 4);
	a.insert(7, 4, 1);
	b.insert(6, 2, 2);
	b.insert(4, 2, 4);
	b.insert(5, 3, 4);
	sparseMatrix c = a.add(b);
	c.at(1, 2);
	system("pause");
	return 0;
}