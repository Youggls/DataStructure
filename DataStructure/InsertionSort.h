#pragma once

namespace dataStructure {
	template <class T>
	T* insertionSort(T* src, int n) {
		for (int i = 0; i < n - 1; i++) {
			for (int j = i; j >= 0; j--) {
				if (src[j + 1] < src[j]) {
					T t = src[j + 1];
					src[j + 1] = src[j];
					src[j] = t;
				}
			}
		}

		return src;
	}
}