#pragma once

#include <iostream>
using std::string;

namespace dataStructure {
	int kmpFind(string& src, string& pattern) {
		int* next = new int[src.size()];
		next[0] = -1;
		int i = 0;
		int j = -1;
		while (i < src.size()) {
			if (j == -1 | src[i] == pattern[j]) {
				i++;
				j++;
				next[i] = j;
			}
			else j = next[j];
		}

		i = 0;
		j = 0;
		while (i < src.size() && j < pattern.size()) {
			if (j == -1 || src[i] == pattern[j]) {
				i++;
				j++;
			}
			else j = next[j];
		}

		if (j == pattern.size()) return i - j;
		else return -1;
	}
}