#pragma once
namespace dataStructure {
	template <class T>
	class abstractQueue {
	public:
		virtual void push(const T& theKey) = 0;
		virtual T& front() = 0;
		virtual void pop() = 0;
		virtual int size() = 0;
		virtual bool empty() = 0;
	};
}