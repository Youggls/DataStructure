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
		BTreeNode<T>* ancesotr;
		int num;
	public:
		BTreeNode(int order);
		int find(const T& theKey);
		BTreeNode<T>* split(int order, BTreeNode<T>* ancestor);
		void insert(const T& theKey);
		void insert(BTreeElement<T>* theKey);
		void deleteSingle(int pos);
		void changeNum(int n) { num -= n; };
		void setAncestor(BTreeNode<T>* a) { ancesotr = a; };
		BTreeNode<T>* getAncestor() { return ancesotr; };
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
		ancesotr = NULL;
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
			else if (i == num - 2 && theKey <= nxt->getData()) return i + 1;
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
		BTreeElement<T>* t1 = left->data[mid - 1];
		BTreeElement<T>* t2 = this->data[mid - 1];
		t1->setChild(t2->getChild());
		t1->setFalse();

		for (int i = mid; i < num + 1; i++) {
			right->data[i - mid] = this->data[i];
		}
		t1 = right->data[num - mid];
		t2 = this->data[num];
		t1->setChild(t2->getChild());
		t1->setFalse();

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
		for (int i = pos; i < num; i++) {
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
		BTreeElement<T>* t1 = this->data.at(num);
		BTreeElement<T>* t2 = t1;
		for (int i = num - 1; i >= pos + 1; i--) {
			t2 = this->data.at(i);
			this->data.at(i) = t1;
			t1 = t2;
		}
		this->data.at(pos) = t1;

		BTreeElement<T>* newe = new BTreeElement<T>;
		this->data[num] = newe;
		num--;
	}

	template <class T>
	class BTree {
	private:
		BTreeNode<T>* root;
		int order;
		int min;
		void insertBalanceTree(BTreeNode<T>* node);
//		void deleteBalanceTree(BTreeNode<T>* node);
		void getFromLeft(BTreeNode<T>* node, BTreeNode<T>* left, BTreeNode<T>* ancestor);
		void getFromRight(BTreeNode<T>* node, BTreeNode<T>* right, BTreeNode<T>* ancestor);
		void merge(BTreeNode<T>* left, BTreeNode<T>* right, BTreeNode<T>* ancestor);
//		void shiftUpDown(BTreeNode<T>* from, BTreeNode<T>* to, BTreeNode<T>* ancestor, int pos1, int pos2);
		BTreeNode<T>* findAncestor(BTreeNode<T>* temp);
	public:
		BTree(int o) { order = o; root = NULL; min = int(o / 2 + (o / 2.0 - o / 2) * 2) - 1; };
		void insert(const T& theKey);
		void erase(const T& theKey);
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
			te = t->getElement(pos);
			t = te->getChild();
		}

		return ancestor;
	}

	template <class T>
	void BTree<T>::insertBalanceTree(BTreeNode<T>* node) {
		if (node->size() == order) {
			BTreeNode<T>* ancestor = findAncestor(node);
			BTreeNode<T>* ret = node->split(order, ancestor);
			if (ret) root = ret;
			if (ancestor) insertBalanceTree(ancestor);
		}
		else if (node->size() < order) return;
	}

	template <class T>
	void BTree<T>::getFromLeft(BTreeNode<T>* node, BTreeNode<T>* left, BTreeNode<T>* ancestor) {
		int pos = ancestor->find(left->getElement(0)->getData());
		//Lend a T from the ancestor
		T temp = ancestor->getData(pos);
		node->insert(temp);
		//Lend a T from left to ancestor
		temp = left->getData(left->size() - 1);
		ancestor->getData(pos) = temp;

		//Set the child
		BTreeElement<T>* t = node->getElement(0);
//		t->setChild(node->getElement(1)->getChild());
		t->setChild(left->getElement(left->size())->getChild());
		left->getElement(left->size())->setChild(NULL);
//		node->getElement(1)->setChild(left->getElement(left->size() - 1)->getChild());
		
		//delete the element from the left
		BTreeNode<T>* temp1 = left->getElement(left->size() - 1)->getChild();
		left->deleteSingle(left->size() - 1);
		left->getElement(left->size())->setChild(temp1);
	}

	template <class T>
	void BTree<T>::getFromRight(BTreeNode<T>* node, BTreeNode<T>* right, BTreeNode<T>* ancestor) {
		int pos = ancestor->find(right->getElement(0)->getData());

		//Lend a T from the ancestor
		T temp = ancestor->getData(pos - 1);
		node->insert(temp);
		//Lend a T from right to ancestor
		temp = right->getData(0);
		ancestor->getData(pos - 1) = temp;

		//Set the child
		BTreeElement<T>* t = node->getElement(node->size() - 1);
		t->setChild(node->getElement(node->size())->getChild());
		node->getElement(node->size())->setChild(right->getElement(0)->getChild());

		//delete the element from right
		right->deleteSingle(0);
	}

	template <class T>
	void BTree<T>::merge(BTreeNode<T>* left, BTreeNode<T>* right, BTreeNode<T>* ancestor) {
		if (ancestor == NULL) return;
		int prepos = 0;

//		BTreeNode<T>* an = findAncestor(ancestor);

		BTreeNode<T>* t = root;
		BTreeNode<T>* an = NULL;

		while (t) {
			int p = t->find(ancestor->getData(0));
			if (t->getData(p) == ancestor->getData(0)) break;
			an = t;
			t = t->getElement(p)->getChild();
			prepos = p;
		}

		int pos = 0;
		if (left->size()) pos = ancestor->find(left->getData(0));
		else if (right->size()) pos = ancestor->find(right->getData(0)) - 1;

		//Merge from ancestor
		int start = left->size();
		T temp = ancestor->getData(pos);
		left->insert(temp);
		left->getElement(left->size() - 1)->setChild(left->getElement(left->size())->getChild());
		left->getElement(left->size())->setChild(NULL);
		queue<BTreeNode<T>*> childs;

		//Get childs from the right
		int k = 0;
		while (k < right->size() + 1) {
			childs.push(right->getElement(k)->getChild());
			k++;
		}

		//Move the right value to the left
		for (int i = 0; i < right->size(); i++) {
			temp = right->getData(i);
			left->insert(temp);
		}

		//Set the new elements' child
		k = start + 1;
		while (!childs.empty()) {
			BTreeNode<T>* c = childs.front();
			childs.pop();

			left->getElement(k)->setChild(c);
			k++;
		}

		//Delete right
		delete right;
		//Delete the ancestor[pos]
		ancestor->getElement(pos + 1)->setChild(left);
		ancestor->deleteSingle(pos);


		if (ancestor->size() < min && an != NULL) {
			BTreeNode<T>* left = NULL, *right = NULL;
			int pos = prepos;
			if (pos - 1 >= 0 && pos - 1 < an->size()) {
				left = an->getElement(pos - 1)->getChild();
			}
			if (pos + 1 <= an->size() && pos + 1 >= 0) {
				right = an->getElement(pos + 1)->getChild();
			}

			if (left != NULL && left->size() - 1 >= min) {
				getFromLeft(ancestor, left, an);
			}
			else if (right != NULL && right->size() - 1 >= min) {
				getFromRight(ancestor, right, an);
			}
			else {
				if (left != NULL) {
					merge(left, ancestor, an);
				}
				else if (right != NULL) {
					merge(ancestor, right, an);
				}
				else {
					cout << "left and right is NULL";
					system("pause");
				}
			}
		}
		else if (ancestor->size() < min && an == NULL) {
			if (ancestor->size() == 0) {
				root = left;
			}
			else {
				root = ancestor;
			}
		}

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
		insertBalanceTree(target);
	}

	template <class T>
	void BTree<T>::erase(const T& theKey) {
		if (root == NULL || root->size() == 0) return;

		BTreeNode<T>* t = root;
		BTreeNode<T>* ancestor = NULL;
		BTreeNode<T>* target = NULL;
		int pos;
		int prepos;
		BTreeElement<T>* te;
		while (t) {
			pos = t->find(theKey);
			te = t->getElement(pos);
			if (te->getData() == theKey) {
				target = t;
				break;
			}
			target = t;
			te = t->getElement(pos);
			t = te->getChild();
			if (t) {
				ancestor = target;
				prepos = pos;
			}
		}

		

		if (target->getElement(pos)->getChild() != NULL) {
			T max;
			t = target;
			te = target->getElement(pos);

			while (t && te) {
				t = te->getChild();
				te = t->getElement(t->size());
				if(te->getChild()) t = te->getChild();
				else break;
			}

			ancestor = findAncestor(t);

			max = t->getData(t->size() - 1);
			target->getData(pos) = max;
			
			target = t;
			prepos = ancestor->find(t->getData(0));
			pos = t->size() - 1;
		}

		target->deleteSingle(pos);
		if (target->size() >= min) {
			return;
		}
		else if (ancestor != NULL) {
			BTreeNode<T>* left = NULL, *right = NULL;
			pos = prepos;
			if (pos - 1 >= 0 && pos - 1 < ancestor->size()) {
				left = ancestor->getElement(pos - 1)->getChild();
			}
			if (pos + 1 <= ancestor->size() && pos + 1 >= 0) {
				right = ancestor->getElement(pos + 1)->getChild();
			}

			if (left != NULL && left->size() - 1 >= min) {
				getFromLeft(target, left, ancestor);
			}
			else if (right != NULL && right->size() - 1 >= min) {
				getFromRight(target, right, ancestor);
			}
			else {
				if (left != NULL) {
					merge(left, target, ancestor);
				}
				else if (right != NULL) {
					merge(target, right, ancestor);
				}
				else {
					cout << "left and right is NULL";
					system("pause");
				}
			}
		}
		else if (ancestor == NULL) {
			root = target;
		}
	}
}