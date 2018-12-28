#include <bits/stdc++.h>
#include "DataStructure.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using dataStructure::maxHeap;

int main() {
	maxHeap<int> m(100);
	int a[] = { 0,1,3,4,2,1,78,8,2,5,6 };
	m.makeHeap(a, 10, 10);
	m.heapSort();
	for (int i = 0; i < 10; i++) {
		cout << a[i] << ' ';
	}
	system("pause");
	return 0;
}


//#include<iostream>
//#include<cstdio>
//#include<math.h>
//#include<string>
//using namespace std;
//
//int main()
//{
//	string a, b;
//	getline(cin, a);
//	char sign = a[0];
//	getline(cin, a);
//	for (int i = 0; i < a.size(); i++)
//	{
//		if (a[i] == sign && !b.empty())
//		{
//			cout << b << endl;
//			b.clear();
//			continue;
//		}
//		else if (a[i] == sign && b.empty())
//		{
//			continue;
//		}
//		b.push_back(a[i]);
//	}
//	if (!b.empty())
//		cout << b;
//	return 0;
//}
