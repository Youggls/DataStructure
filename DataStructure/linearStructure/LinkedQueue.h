#pragma once

#include "linkedList.h"
#include "abstractQueue.h"
using dataStructure::linkedList;

namespace dataStructure {
	template <class T>
	class linkedQueue: public dataStructure::abstractQueue<T>, private linkedList<T> {
	public:
		linkedQueue() : linkedList<T>() { };
		void push(const T& theKey);
		T& front();
		void pop();
		bool empty();
		int size();
	};

	template <class T>
	void linkedQueue<T>::push(const T& theKey) {
		linkedList<T>::insert(theKey);
	}

	template <class T>
	T& linkedQueue<T>::front() {
		if (linkedList<T>::size() == 0) throw "The queue is empty!";

		return linkedList<T>::at(0);
	}

	template <class T>
	void linkedQueue<T>::pop() {
		if (linkedList<T>::size() == 0) throw "The queue is empty!";

		linkedList<T>::erase(0);
	}

	template <class T>
	bool linkedQueue<T>::empty() {
		return (linkedList<T>::size() == 0);
	}

	template <class T>
	int linkedQueue<T>::size() {
		return linkedList<T>::size();
	}
}