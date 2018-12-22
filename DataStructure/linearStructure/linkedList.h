#pragma once

namespace dataStructure {
	template <class T>
	class linkedList {
	private:
		template <class T>
		struct listNode {
		public:
			listNode(const T& d) { data = d; nxt = NULL; };
			T data;
			listNode<T>* nxt;
		};

		listNode<T>* head;
		listNode<T>* tail;
		int num;
	public:
		static const int npos = -1;

		linkedList() { head = NULL; tail = NULL; num = 0; };

		void insert(const T& theKey, int pos = -1);
		void erase(int pos, int len = 1);

		int size() { return num; };
		bool isEmpty() { return (head == NULL); };
		int find(const T& theKey);

		T& at(int pos);
		T& operator[](int pos);
		linkedList<T>& operator=(const linkedList<T>& another);
	};

	template <class T>
	void linkedList<T>::insert(const T& theKey, int pos) {
		if (pos == -1) pos = num - 1;
		if (head == NULL) {
			listNode<T>* newNode = new listNode<T>(theKey);
			head = newNode;
			tail = newNode;
			num++;
			return;
		}
		
		if (pos == 0) {
			listNode<T>* newNode = new listNode<T>(theKey);
			newNode->nxt = head;
			head = newNode;
			num++;
			return;
		}

		if (pos == num) {
			listNode<T>* newNode = new listNode<T>(theKey);
			tail->nxt = newNode;
			tail = newNode;
			num++;
			return;
		}
		
		listNode<T>* t = head;
		for (int i = 0; i < pos; i++) {
			t = t->nxt;
		}
		listNode<T>* next = t->nxt;
		listNode<T>* newNode = new listNode<T>(theKey);

		t->nxt = newNode;
		newNode->nxt = next;

		num++;
	}

	template <class T>
	void linkedList<T>::erase(int pos, int len) {
		if (pos + 1 > num) return;

		listNode<T>* t = head;
		listNode<T>* pre = NULL;
		for (int i = 0; i < pos; i++) {
			pre = t;
			t = t->nxt;
		}

		if (pre == NULL) {
			t = t->nxt;
			delete head;
			head = t;
			num--;
			return;
		}
		else if (t == tail) {
			delete tail;
			pre->nxt = NULL;
			tail = pre;
			num--;
			return;
		}
		pre->nxt = t->nxt;
		delete t->nxt;
		num--;
		return;
	}

	template <class T>
	T& linkedList<T>::at(int pos) {
		if (pos < 0 && pos >= num) throw "out of bounds";

		if (pos == num - 1) return tail->data;

		listNode<T>* t = head;
		for (int i = 0; i < pos; i++) {
			t = t->nxt;
		}
		return t->data;
	}

	template <class T>
	T& linkedList<T>::operator[](int pos) {
		return at(pos);
	}

	template <class T>
	linkedList<T>& linkedList<T>::operator=(const linkedList<T>& another) {
		linkedList<T> newList;

		for (int i = 0; i < another.num; i++) {
			newList[i] = another[i];
		}

		return newList;
	}
}