#pragma once

namespace dataStructure {
	template <class T>
	T* mergeSort(T* src, int n) {
		T* rv = new T[n];
		for (int len = 1; len < n; len = len * 2) {
			for (int i = 0;i * len <= n; i++) {
				for (int j = i * len; j < (i + 1)*len; j++) {

				}
			}
		}
		
	}

	template <class T>
	void _merge(T* src, int left, int mid, int right) {
		T* aux = new T[right - left + 1];
		for (int i = left; i <= right; i++) aux[i - left] = src[i];
		int i = left;
		int j = mid + 1;
		for (int k = left; k <= right; k++) {
			if (i > mid) {
				src[k] = aux[j - left];
				j++;
			}
			else if (j > right) {
				src[k] = aux[i - left];
				i++;
			}
			else if (aux[i - left] < aux[j - left]) {
				src[k] = aux[i - left];
				i++;
			}
			else if (aux[i - left] >= aux[j - left]) {
				src[k] = aux[j - left];
				j++;
			}
		}
	}
}