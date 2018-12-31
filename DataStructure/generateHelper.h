#pragma once

#ifndef ALGORITHM
#define ALGORITHM
#include <algorithm>
using std::swap;
#endif // !ALGORITHM

#ifndef CTIME
#define CTIME
#include <ctime>
#endif // !CTIME

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#endif // !IOSTREAM



namespace dataStructure {
	int* generateArray(int size, int order, int swaptimes = -1) {
		int* n = new int[size];
		if (swaptimes == -1) swaptimes = size / 2;
		if (order == 1) {
			for (int i = 0; i < size; i++) {
				n[i] = i + 1;
			}
		}
		else if (order == -1) {
			for (int i = 0; i < size; i++) {
				n[i] = size - i;
			}
		}

		srand(time(NULL));
		for (int i = 0; i < swaptimes; i++) {
			int x = rand() % size;
			int y = rand() % size;
			swap(n[x], n[y]);
		}

		return n;
	}

	void printArr(int* src, int n) {
		for (int i = 0; i < n; i++) {
			std::cout << src[i];
			if (i != n - 1) cout << ' ';
		}
		cout << endl;
	}
}