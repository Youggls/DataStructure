#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace dataStructure;

int main() {
	int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
	arrayList<int> arr(a, 10);
	for (int i = 0; i < 10; i++) {
		cout << arr.at(i) << ' ';
	}
	system("pause");
	return 0;
}