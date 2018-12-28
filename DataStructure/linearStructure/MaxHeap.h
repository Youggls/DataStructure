#pragma once

#ifndef STRING_H
#define STRING_H
#include <string>
using std::string;
#endif // !STRING_H

namespace dataStructure {
	template <class T>
	class maxHeap {
	private:
		T* heap;
		int currentSize;
		int maxCapacity;

		void shiftUp(int index);
		void shiftDown(int index);
	public:
		maxHeap(int cap = -1);

		void insert(T& dat);
		void erase(T& dat);
		void pop_max();
		void makeHeap(T* src, int size, int arraySize = -1);
		void heapSort();

		T& at(int index);

		inline int size() { return currentSize; }
		inline int capacity() { return maxCapacity; }
	};

	template<class T>
	maxHeap<T>::maxHeap(int cap) {
		if (cap == -1) maxCapacity = 100;
		currentSize = 0;
		heap = new T[maxCapacity + 1];
	}

	template <class T>
	void maxHeap<T>::shiftUp(int index) {
		if (heap[index] <= heap[index / 2] && index == 1) return;

		if (heap[index] > heap[index / 2]) {
			std::swap(heap[index], heap[index / 2]);
			shiftUp(index / 2);
		}
	}

	template <class T>
	void maxHeap<T>::shiftDown(int index) {
		if ((heap[index] >= heap[index * 2] && heap[index] >= heap[index * 2 + 1]) || index > currentSize / 2) return;
		else if (index * 2 == currentSize) {
			if (heap[index] < heap[index * 2]) {
				std::swap(heap[index], heap[index * 2]);
				shiftDown(index * 2);
			}
		}
		else {
			if (heap[index * 2 + 1] >= heap[index * 2] && heap[index * 2 + 1] > heap[index]) {
				std::swap(heap[index], heap[index * 2 + 1]);
				shiftDown(index * 2 + 1);
			}
			else if (heap[index * 2] > heap[index * 2 + 1] && heap[index * 2] > heap[index]) {
				std::swap(heap[index], heap[index * 2]);
				shiftDown(index * 2);
			}
		}
	}

	template <class T>
	void maxHeap<T>::insert(T& dat) {
		heap[++currentSize] = dat;
		shiftUp(currentSize);
	}

	template <class T>
	void maxHeap<T>::erase(T& dat) {
		int index;
		for (index = 1; index < currentSize + 1; index++) {
			if (heap[index] == dat) break;
		}
		if (heap[index] != dat) return;

		std::swap(heap[index], heap[currentSize--]);
		shiftDown(index);
	}

	template <class T>
	void maxHeap<T>::pop_max() {
		std::swap(heap[1], heap[currentSize--]);
		shiftDown(1);
	}

	template <class T>
	void maxHeap<T>::makeHeap(T* src, int size, int arraySize) {
		delete heap;
		if (arraySize == -1) arraySize = size;
		heap = src;
		currentSize = size;
		maxCapacity = arraySize;

		int index = currentSize / 2;
		while (true) {
			if (index == 0) return;
			shiftDown(index--);
		}
	}

	template <class T>
	T& maxHeap<T>::at(int index) {
		if (index <= 0 || index > maxCapacity) throw "index out of range";

		return heap[index];
	}

	template <class T>
	void maxHeap<T>::heapSort() {
		int temp = currentSize;
		for (int i = 1; i <= temp; i++) {
			pop_max();
		}
	}
}
