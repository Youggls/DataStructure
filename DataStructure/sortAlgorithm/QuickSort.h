#pragma once

namespace dataStructure {
	namespace sort {
		template <class T>
		T* quickSort(T* src, int n) {
			partition(src, 0, n - 1);
			return src;
		}

		template <class T>
		void partition(T* src, int l, int r) {
			if (r >= l) return;

			int i = l + 1;
			int j = l;

			for (int i = l + 1; i <= right; i++) {
				if (src[i] < src[l]) {
					std::swap(src[i], src[j + 1]);
					j++;
				}
			}

			std::swap(src[l], src[j]);
			partition(src, l, j - 1);
			partition(src, j + 1, r);
		}
	}
}