#include <bits/stdc++.h>
#include "DataStructure.hpp"
#include <windows.h>  


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using dataStructure::maxHeap;
using dataStructure::AVLTree;
using dataStructure::generateArray;

int main() {
	int n;
	cin >> n;
	int* arr = generateArray(n, 1, 0);
	AVLTree<int> avl;
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < n; i++) {
		avl.insert(arr[i]);
	}
	QueryPerformanceCounter(&t2);
	cout << "AVLTree insert n = " << n << " time " << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < n; i++) {
		avl.erase(arr[i]);
	}
	QueryPerformanceCounter(&t2);
	cout << "AVLTree delete n = " << n << " time " << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
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
