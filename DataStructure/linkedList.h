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
		
		if (pos == num - 1) {
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

		listNode<T>* t = root;
		listNode<T>* pre = NULL;
		for (int i = 0; i < pos; i++) {
			pre = t;
			t = t->nxt;
		}

		if (pre == NULL) {
			head = t->nxt;
			delete head;
			return;
		}
		else if (t == tail) {
			delete tail;
			pre->nxt = NULL;
			tail = pre;
			return;
		}
		pre->nxt = t->nxt;
		delete t->nxt;
		return;
	}
}