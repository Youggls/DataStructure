#pragma once
//#ifndef LINKEDLIST
//#define LINKEDLIST
//#include "DataStructure.hpp"
//using dataStructure::linkedList;
//#endif // !linkedList
#include "linkedList.h"
using dataStructure::linkedList;

namespace dataStructure {
	template <class T>
	class linkedStack :private linkedList<T> {
	public:
		linkedStack();
		void push(const T& theKey);
		T& top();
		void pop();
		bool empty();
		int size();
	};

	template <class T>
	linkedStack<T>::linkedStack() : linkedList<T>::linkedList() { }

	template <class T>
	void linkedStack<T>::push(const T& theKey) {
		linkedList<T>::insert(theKey, 0);
	}

	template <class T>
	T& linkedStack<T>::top() {
		if (linkedList<T>::isEmpty()) throw "The stack is empty";
		return linkedList<T>::at(0);
	}

	template <class T>
	void linkedStack<T>::pop() {
		if (linkedList<T>::isEmpty()) throw "The stack is empty";

		linkedList<T>::erase(0);
	}

	template <class T>
	bool linkedStack<T>::empty() {
		return linkedList<T>::isEmpty();
	}

	template <class T>
	int linkedStack<T>::size() {
		return linkedList<T>::size();
	}
}