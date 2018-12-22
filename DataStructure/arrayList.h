#pragma once

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#endif // !IOSTREAM

namespace dataStructure {

	template <class T>
	class arrayList {
	private:
		T* data;
		int elementNum;
		int capacity;
		static const int upperBound = INT_MAX - 1000;

		float load_factor;
		const char* outOfBound();
		const char* outOfMaxsize();
	public:
		static const int npos = -1;

		arrayList(float factor = 1.5);
		arrayList(T* a, int size, float factor = 1.5);
		arrayList(int cap, float factor = 1.5);
		arrayList(const arrayList<T>& another);

		bool isEmpty();
		int find(const T& target);
		int size() { return elementNum; };
		void erase(int start, int len = 1);
		void insert(const T& element, int index = -1);
		T& at(int index);
		arrayList<T>& operator=(const arrayList<T>& another);
		T& operator[](const int& index);
	};

	template <class T>
	arrayList<T>::arrayList(float factor) {
		//	upperBound = pow(2, sizeof(int)) - 1000;
		load_factor = factor;
		capacity = 0;
		elementNum = 0;
		data = nullptr;
	}

	template <class T>
	arrayList<T>::arrayList(T* a, int size, float factor) {
		//	upperBound = pow(2, sizeof(int)) - 1000;
		if (size >= upperBound) throw outOfMaxsize();
		elementNum = size;
		load_factor = factor;
		capacity = static_cast<int>(load_factor * size);
		data = new T[capacity];

		for (int i = 0; i < size; i++) {
			data[i] = a[i];
		}
	}

	template <class T>
	arrayList<T>::arrayList(int cap, float factor) {
		//	upperBound = pow(2, sizeof(int)) - 1000;
		if (cap >= upperBound) throw outOfMaxsize();
		load_factor = factor;
		capacity = cap;
		elementNum = 0;
		data = new T[capacity];
	}

	template <class T>
	arrayList<T>::arrayList(const arrayList<T>& another) {
		elementNum = another.elementNum;
		capacity = another.capacity;
		load_factor = another.load_factor;

		T* newDataSpace = new T[capacity];
		for (int i = 0; i < elementNum; i++) {
			newDataSpace[i] = another.at(i);
		}
		delete data;
		data = newDataSpace;
	}

	template <class T>
	bool arrayList<T>::isEmpty() {
		if (elementNum == 0) return true;
		else return false;
	}

	template <class T>
	int arrayList<T>::find(const T& target) {
		if (!data) return npos;
		else {
			for (int i = 0; i < elementNum; i++) {
				if (data[i] == target) return i;
			}
			return npos;
		}
	}

	template <class T>
	void arrayList<T>::erase(int start, int len) {
		if (start + len > elementNum) throw outOfBound();
		for (int i = start; i < elementNum - start - len + 2; i++) {
			data[i] = data[i + len];
		}
		elementNum -= len;
	}

	template <class T>
	void arrayList<T>::insert(const T& element, int index) {
		if (index == -1) index = elementNum;
		if (elementNum + 1 >= upperBound) throw outOfMaxsize();
		if (elementNum + 1 >= capacity) {
			capacity = load_factor * (elementNum + 1);
			T* newdata = new T[capacity];
			for (int i = 0; i < elementNum + 1; i++) {
				if (i != index) newdata[i] = data[i];
				else {
					newdata[i] = element;
				}
			}
			delete data;
			data = newdata;
			elementNum++;
			return;
		}
		T tmp1, tmp2;
		tmp1 = data[index];
		tmp2 = data[index];
		for (int i = index; i < elementNum; i++) {
			tmp1 = data[i + 1];
			data[i + 1] = data[i];
			tmp2 = tmp1;
		}
		data[index] = element;
		elementNum++;
	}

	template <class T>
	T& arrayList<T>::at(int index) {
		if (index >= elementNum) throw outOfBound();
		return data[index];
	}

	template<class T>
	const char* arrayList<T>::outOfBound() {
		const char* s = "out of bound!\n";
		cout << s;
		return s;
	}

	template <class T>
	const char* arrayList<T>::outOfMaxsize() {
		const char* s = "the element numbers or the expected capacity is larger than UINT32_MAX\n";
		cout << s;
		return s;
	}

	template <class T>
	arrayList<T>& arrayList<T>::operator=(const arrayList<T>& another) {
		elementNum = another.elementNum;
		capacity = another.capacity;
		load_factor = another.load_factor;

		T* newDataSpace = new T[capacity];
		for (int i = 0; i < elementNum; i++) {
			newDataSpace[i] = another.at(i);
		}
		delete data;
		data = newDataSpace;

		return *this;
	}

	template <class T>
	T& arrayList<T>::operator[](const int& index) {
		return this->at(index);
	}
}