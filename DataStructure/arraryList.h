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
		size_t elementNum;
		size_t capacity;
		static const size_t upperBound = pow(2, sizeof(size_t)) - 1000;

		float load_factor;
		const char* outOfBound();
		const char* outOfMaxsize();
	public:
		static const int npos = -1;

		arrayList(float factor = 1.5);
		arrayList(T* a, size_t size, float factor = 1.5);
		arrayList(size_t cap, float factor = 1.5);
		arrayList(const arrayList<T>& another);

		bool isEmpty();
		int find(const T& target);
		size_t size() { return elementNum; };
		void erase(size_t start, size_t len = 1);
		void insert(const T& element, size_t index);
		T& at(size_t index);
		arrayList<T>& operator=(const arrayList<T>& another);
		T& operator[](const size_t& index);
	};

	template <class T>
	arrayList<T>::arrayList(float factor) {
		//	upperBound = pow(2, sizeof(size_t)) - 1000;
		load_factor = factor;
		capacity = 0;
		elementNum = 0;
		data = nullptr;
	}

	template <class T>
	arrayList<T>::arrayList(T* a, size_t size, float factor) {
		//	upperBound = pow(2, sizeof(size_t)) - 1000;
		if (size >= upperBound) throw outOfMaxsize();
		elementNum = size;
		load_factor = factor;
		capacity = static_cast<int>(load_factor * size);
		data = new T[capacity];

		for (size_t i = 0; i < size; i++) {
			data[i] = a[i];
		}
	}

	template <class T>
	arrayList<T>::arrayList(size_t cap, float factor) {
		//	upperBound = pow(2, sizeof(size_t)) - 1000;
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
		for (size_t i = 0; i < elementNum; i++) {
			newDataSpace[i] = another.at(i);
		}
		delete data;
		data = newDataSpace;
	}

	template <class T>
	bool arrayList<T>::isEmpty() {
		if (elementNum == 0) return false;
		else return true;
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
	void arrayList<T>::erase(size_t start, size_t len) {
		if (start + len > elementNum) throw outOfBound();
		for (size_t i = start; i < elementNum - start - len + 2; i++) {
			data[i] = data[i + len];
		}
		elementNum -= len;
	}

	template <class T>
	void arrayList<T>::insert(const T& element, size_t index) {
		if (elementNum + 1 >= upperBound) throw outOfMaxsize();
		if (elementNum + 1 >= capacity) {
			capacity = load_factor * (elementNum + 1);
			T* newdata = new T[capacity];
			for (size_t i = 0; i < elementNum + 1; i++) {
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
		for (size_t i = index; i < elementNum; i++) {
			tmp1 = data[i + 1];
			data[i + 1] = data[i];
			tmp2 = tmp1;
		}
		data[index] = element;
		elementNum++;
	}

	template <class T>
	T& arrayList<T>::at(size_t index) {
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
		for (size_t i = 0; i < elementNum; i++) {
			newDataSpace[i] = another.at(i);
		}
		delete data;
		data = newDataSpace;

		return *this;
	}

	template <class T>
	T& arrayList<T>::operator[](const size_t& index) {
		return this->at(index);
	}
}