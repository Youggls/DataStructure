#pragma once

namespace dataStructure {
	namespace sort {
		template <class T>
		T* rankSort(T* src, int n) {
			int* rank = new int[n];
			for (int i = 0; i < n; i++) rank[i] = 0;

			for (int i = 1; i < n; i++) {
				for (int j = 0; j < i; j++) {
					if (src[j] <= src[i]) rank[i]++;
					else rank[j]++;
				}
			}

			for (int i = 0; i < n; i++) {
				if (rank[i] == i) continue;
				else {
					T temp = src[i];
					src[i] = src[rank[i]];
					src[rank[i]] = temp;
					int rt = rank[i];
					rank[i] = rank[rank[i]];
					rank[rt] = rt;
					i--;
				}
			}

			delete rank;
			return src;
		}
	}
}