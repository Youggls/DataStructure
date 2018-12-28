#include <bits/stdc++.h>
#include "DataStructure.hpp"

using std::cin;
using std::cout;
using std::endl;
using dataStructure::mergeSort;

int main() {
	int a[] = { 9,3,4,5,6,1,0,3 };
	mergeSort<int>(a, 8);
	for (int i = 0; i < 8; i++) cout << a[i] << ' ';
	system("pause");
	return 0;
}