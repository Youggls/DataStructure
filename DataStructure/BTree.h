#pragma once

#ifndef VECTOR
#define VECTOR
#include <vector>
using std::vector;
#endif // !VECTOR

#ifndef QUEUE
#define QUEUE
#include <queue>
using std::queue;
#endif // !QUEUE


#ifndef VCRUNTIME_H
#define VCRUNTIME_H
#include <vcruntime.h>
#endif // !VCRUNTIME_H



namespace dataStructure {
	template <class T>
	class BTreeNode;

	template <class T>
	class BTreeElement {
	private:
		T data;
		BTreeNode<T>* child;
		bool isNull;
	public:
		BTreeElement(const T& dat, bool is = false) { data = dat; child = NULL; isNull = is; };
		BTreeElement(bool is = false) { child = NULL; isNull = is; };
		bool isNULL() { return isNull; };
		void setTrue() { isNull = true; };
		void setFalse() { isNull = false; };
		void setData(const T& dat) { data = dat; };
		void setChild(BTreeNode<T>* c) { child = c; };
		T& getData() { return data; };
		BTreeNode<T>* getChild() { return child; };
	};

	template <class T>
	class BTreeNode {
	private:
		vector<BTreeElement<T>*> data;
		int num;
	public:
		BTreeNode(int order);
		int find(const T& theKey);
		BTreeNode<T>* split(int order, BTreeNode<T>* ancestor);
		void insert(const T& theKey);
		void insert(BTreeElement<T>* theKey);
		void deleteSingle(int pos);
		void changeNum(int n) { num -= n; };
		T& getData(int pos) { BTreeElement<T>* t = data.at(pos); return t->getData(); };
		BTreeElement<T>* getElement(int pos) { return data.at(pos); };
		int size() { return num; };
	};

	template <class T>
	BTreeNode<T>::BTreeNode(int order) {
		//预留两个多余的指针，一个为溢出准备，另外一个作为一个空元素作为多出来的那个指针指向孩子节点
		data.resize(order + 1);
		for (int i = 0; i < order + 1; i++) {
			data[i] = new BTreeElement<T>(true);
		}
		num = 0;
	}

	template <class T>
	int BTreeNode<T>::find(const T& theKey) {
		if (num == 0) return 0;
		if (num == 1) {
			BTreeElement<T>* t = data.at(0);
			if (theKey <= t->getData()) return 0;
			else return 1;
		}
		for (int i = 0; i < num - 1; i++) {
			BTreeElement<T>* t = data.at(i);
			BTreeElement<T>* nxt = data.at(i + 1);
			if (t->getData() == theKey) return i;
			else if (t->getData() > theKey && nxt->getData() > theKey) return i;
			//Larger than the last one
			else if (i == num - 2 && theKey > nxt->getData()) return i + 2;
			else if (i == num - 2 && theKey == nxt->getData()) return i + 1;
			//Less than the first one
			else if (i == 0 && theKey < t->getData()) return i;
		}
	}

	template <class T>
	BTreeNode<T>* BTreeNode<T>::split(int order, BTreeNode<T>* ancestor) {
		BTreeNode<T>* left = new BTreeNode<T>(order);
		BTreeNode<T>* right = new BTreeNode<T>(order);
		int s = order - 1;
		int mid = int((s / 2) + (s / 2.0 - s / 2) * 2);

		BTreeNode<T>* newTree = NULL;
		//If ancestor is NULL, means that current node is root, make a new node and return it
		if (ancestor == NULL) {
			newTree = new BTreeNode<T>(order);
			ancestor = newTree;
		}

		BTreeElement<T>* m = data.at(mid - 1);
		ancestor->insert(m->getData());

		int pos = ancestor->find(m->getData());

		for (int i = 0; i < mid - 1; i++) {
			left->data[i] = this->data[i];
		}
		for (int i = mid; i < num; i++) {
			right->data[i - mid] = this->data[i];
		}
		left->num = mid - 1;
		right->num = this->num - mid;
		BTreeElement<T>* up = ancestor->data[pos];
		up->setChild(left);
		up = ancestor->data[pos + 1];
		up->setChild(right);

		return newTree;
	}

	template <class T>
	void BTreeNode<T>::insert(const T& theKey) {
		//has no element
		if (this->size() == 0) {
			BTreeElement<T>* newElement = new BTreeElement<T>(theKey);
			BTreeElement<T>* t = this->data[0];
			this->data[0] = newElement;
			this->data[1] = t;
			num++;
			return;
		}
		//has a same element
		int pos = find(theKey);
		if (getData(pos) == theKey) return;

		BTreeElement<T>* newElement = new BTreeElement<T>(theKey);
		BTreeElement<T>* pre = newElement;
		BTreeElement<T>* nxt;
		BTreeElement<T>* t = this->data[num];
		for (int i = pos + 1; i < num; i++) {
			nxt = data.at(i);
			data.at(i) = pre;
			pre = nxt;
		}
		data.at(num) = pre;
		data.at(num + 1) = t;
		num++;
	}

	template <class T>
	void BTreeNode<T>::insert(BTreeElement<T>* theKey) {
		//has no element
		if (this->size() == 0) {
			BTreeElement<T>* newElement = theKey;
			BTreeElement<T>* t = this->data[0];
			this->data[0] = newElement;
			this->data[1] = t;
			num++;
			return;
		}
		//has a same element
		int pos = find(theKey);
		if (getData(pos) == theKey) return;

		BTreeElement<T>* newElement = theKey;
		BTreeElement<T>* pre = newElement;
		BTreeElement<T>* nxt;
		BTreeElement<T>* t = this->data[num];
		for (int i = pos + 1; i < num; i++) {
			nxt = data.at(i);
			data.at(i) = pre;
			pre = nxt;
		}
		data.at(num) = pre;
		data.at(num + 1) = t;
		num++;
	}

	template <class T>
	void BTreeNode<T>::deleteSingle(int pos) {
		BTreeElement<T>* t1 = this->data.at(num - 1);
		BTreeElement<T>* t2;
		for (int i = num - 1; i > pos + 1; i--) {
			t1 = t2;
			t2 = this->data.at(i - 1);
			this->data.at(i - 1) = t1;
		}
		this->data.at(pos) = t2;

		num--;
		t1 = this->data.at(num - 1);
		t1->setFalse();
	}

	template <class T>
	class BTree {
	private:
		BTreeNode<T>* root;
		int order;
		int min;
		void balanceTree(BTreeNode<T>* node);
		void merge(BTreeNode<T>* left, BTreeNode<T>* right, BTreeNode<T>* ancestor);
		void shiftUpDown(BTreeNode<T>* from, BTreeNode<T>* to, BTreeNode<T>* ancestor, int pos1, int pos2);
		BTreeNode<T>* findAncestor(BTreeNode<T>* temp);
	public:
		BTree(int o) { order = o; root = NULL; min = int(o / 2 + (o / 2.0 - o / 2) * 2); };
		void insert(const T& theKey);
		void deleteElement(const T& theKey);
	};

	template <class T>
	BTreeNode<T>* BTree<T>::findAncestor(BTreeNode<T>* temp) {
		if (temp == root) return NULL;

		BTreeNode<T>* t = root;
		BTreeNode<T>* ancestor = NULL;
		BTreeElement<T>* e = temp->getElement(0);
		BTreeElement<T>* te;
		while (t) {
			int pos = t->find(e->getData());
			te = t->getElement(pos);
			if (te->getData() == e->getData()) return ancestor;
			ancestor = t;
			te = t->getElement(pos + 1);
			t = te->getChild();
		}

		return ancestor;
	}

	template <class T>
	void BTree<T>::balanceTree(BTreeNode<T>* node) {
		if (node->size() == order) {
			BTreeNode<T>* ancestor = findAncestor(node);
			BTreeNode<T>* ret = node->split(order, ancestor);
			if (ret) root = ret;
			if (ancestor) balanceTree(ancestor);
		}
		else if (node->size() < order) return;
	}

	template <class T>
	void BTree<T>::merge(BTreeNode<T>* left, BTreeNode<T>* right, BTreeNode<T>* ancestor) {
		if (ancestor == NULL) return;

		int pos = ancestor->find(right->getData(0));
		BTreeNode<T>* newNode = new BTreeNode<T>(order);



		delete left;
		delete right;
		ancestor->changeNum(-1);
		ancestor->deleteSingle(pos);
		
		BTreeElement<T>* t = ancestor->getElement(pos);
		t->setChild(newNode);
	}

	template <class T>
	void BTree<T>::shiftUpDown(BTreeNode<T>* from, BTreeNode<T>* to, BTreeNode<T>* ancestor, int pos1, int pos2) {

	}

	template <class T>
	void BTree<T>::insert(const T& theKey) {
		if (root == NULL) {
			BTreeNode<T>* newTree = new BTreeNode<T>(order);
			newTree->insert(theKey);
			root = newTree;
			return;
		}
		BTreeNode<T>* t = root;
		BTreeNode<T>* target = NULL;
		BTreeElement<T>* te;
		while (t) {
			int pos = t->find(theKey);
			te = t->getElement(pos);
			if (te->getData() == theKey && te->isNULL() != true) return;
			target = t;
			te = t->getElement(pos);
			t = te->getChild();
		}

		target->insert(theKey);
		balanceTree(target);
	}

	template <class T>
	void BTree<T>::deleteElement(const T& theKey) {

	}
}