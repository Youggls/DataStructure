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


namespace dataStructure {
	int* generateArray(int size, int swaptimes = -1) {
		int* n = new int[size];
		if (swaptimes == -1) swaptimes = size;
		for (int i = 0; i < size; i++) {
			n[i] = i;
		}

		srand(time(NULL));
		for (int i = 0; i < swaptimes; i++) {
			int x = rand() % size;
			int y = rand() % size;
			swap(n[x], n[y]);
		}

		return n;
	}
}