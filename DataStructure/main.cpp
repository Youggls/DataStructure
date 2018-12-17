#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;
using dataStructure::sort::rankSort;
using dataStructure::generateArray;

int main() {
	//int* a = generateArray(10);
	//a = rankSort<int>(a, 10);
	int a[] = { 26,33,35,29,19,12,22 };
	rankSort<int>(a, 7);
	for (int i = 0; i < 7; i++) cout << a[i] << ' ';
	cout << endl;
	system("pause");
	return 0;
}