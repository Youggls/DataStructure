#pragma once
#ifndef ARRAYLIST
#define ARRAYLIST
#include "DataStructure.hpp"
using dataStructure::arrayList;
#endif // !linkedList

namespace dataStructure {
	template <class T>
	class arrayStack:private arrayList<T> {
	public:
		arrayStack();
		void push(const T& theKey);
		int size();
		T& top();
		void pop();
		bool empty();
	};

	template <class T>
	arrayStack<T>::arrayStack() : arrayList<T>() { }

	template <class T>
	void arrayStack<T>::push(const T& theKey) {
		arrayList<T>::insert(theKey, arrayList<T>::size());
	}

	template <class T>
	T& arrayStack<T>::top() {
		if (arrayList<T>::isEmpty()) throw "The stack is empty";

		return arrayList<T>::at(arrayList<T>::size() - 1);
	}

	template <class T>
	void arrayStack<T>::pop() {
		if (arrayList<T>::isEmpty()) throw "The stack is empty";

		arrayList<T>::erase(arrayList<T>::size() - 1);
	}

	template <class T>
	int arrayStack<T>::size() {
		return arrayList<T>::size();
	}

	template <class T>
	bool arrayStack<T>::empty() {
		return arrayList<T>::isEmpty();
	}
}