#pragma once

#ifndef STRING_H
#define STRING_H
#include <string>
using std::string;
#endif // !STRING_H

namespace dataStructure {
	template <class T>
	class maxHeap;
}
using dataStructure::maxHeap;
template <class T>
class dataStructure::maxHeap {
private:
	T* arr;
	size_t size;
	size_t capacity;
	void shiftUp(size_t index);
	//	void shiftDowm(size_t index);
public:
	maxHeap();
	//	maxHeap(T* arr, size_t size);
	maxHeap(size_t capacity);
	bool insert(T& element);
	void printWayToRoot(size_t index);
};

template <class T>
maxHeap<T>::maxHeap() {
	arr = NULL;
	size = capacity = 0;
}

template <class T>
maxHeap<T>::maxHeap(size_t cap) {
	capacity = cap;
	arr = new T[capacity + 1];
	size = 0;
}

template <class T>
void maxHeap<T>::shiftUp(size_t index) {
	if (index == 1) return;
	else if (arr[index] > arr[index / 2]) {
		T temp = arr[index / 2];
		arr[index / 2] = arr[index];
		arr[index] = temp;
		shiftUp(index / 2);
	}
	else return;
}

template <class T>
bool maxHeap<T>::insert(T& element) {
	size++;
	arr[size] = element;
	shiftUp(size);
	return true;
}

template <class T>
void maxHeap<T>::printWayToRoot(size_t index) {
	while (index >= 1)
	{
		std::cout << arr[index];
		if (index != 1) std::cout << ' ';
		index /= 2;
	}
	std::cout << std::endl;
}