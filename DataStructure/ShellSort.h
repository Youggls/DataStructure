#pragma once

namespace dataStructure {
	template <class T>
	T* shellSort(T* src, int n) {
		int j;
		for (int d = n / 2; d >= 1; d = d / 2) {
			for (int i = d + 1; i < n; i++) {
				src[0] = src[i];
				j = i - d;
				while (j > 0 && src[0] < src[j]) {
					src[j + d] = src[j];
					j = j - d;
				}
				src[j + d] = src[0];
			}
		}
		return src;
	}
}