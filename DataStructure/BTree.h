#pragma once

namespace dataStructure {
	template <class T>
	class BTreeNode;
	template <class T>
	class BTreeElement {
	private:
		T dat;
		BTreeNode<T>* child;
		bool isNull;
	public:
		BTreeElement(const T& d, bool isnull = true) { dat = d; child = NULL; isNull = isnull; };
		BTreeElement(bool isnull = true) { child = NULL; isNull = isnull; };
		T& getData() { return dat; };
		void setData(const T& d) { dat = d; };
		BTreeNode<T>* getChild() { return child; };
		void setChild(BTreeNode<T>* c) { child = c; };
	};
	template <class T>
	class BTreeNode {
	private:
		size_t datNum;
		BTreeElement<T>* data;
	public:
		BTreeNode(size_t order);
		bool isNull() { return (datNum == 0); };
		size_t find(const T& theKey);
		size_t size() { return datNum; };
		void insert(BTreeElement<T>* e);
		const T& getData(size_t pos) { return data[pos]; };
		void split(size_t order, BTreeNode<T>* ancestor);
	};

	template <class T>
	BTreeNode<T>::BTreeNode(size_t order) {
		datNum = 0;
		//one more is null
		//another is for slay
		data = new BTreeElement<T>[order + 1];
	}

	template <class T>
	size_t BTreeNode<T>::find(const T& theKey) {
		for (size_t i = 0; i < datNum - 1; i++) {
			BTreeElement<T>* temp = data[i];
			BTreeElement<T>* tempnxt = data[i + 1];
			
			if (temp->getData() == theKey) return i;
			else if (temp->getData() < theKey && tempnxt->getData() > theKey) return i;
			else if (i == datNum - 2 && tempnxt->getData() < theKey) return datNum - 1;
		}
	}

	template <class T>
	void BTreeNode<T>::insert(BTreeElement<T>* e) {
		size_t pos = find(e->getData());
		if (this->getData(pos) == getData()) return;
		datNum++;

		BTreeElement<T>* temp = new BTreeElement<T>(e->getData());
		for (size_t i = pos + 1; i < datNum - 1; i++) {
			BTreeElement<T>* t = data[i + 1];
			data[i + 1] = temp;
			temp = t;
		}
		data[datNum - 1] = temp;
	}

	template <class T>
	void BTreeNode<T>::split(size_t order, BTreeNode<T>* ancestor) {
		size_t num = order - 1;
		size_t mid = int(num / 2 + (num / 2.0 - num / 2) * 2));

		BTreeNode<T>* left, *right;

		//Up the mid
		BTreeElement<T>* mide = this->data[mid];
		ancestor->insert(mide->getData());
		size_t key = ancestor->find(mide);
		
		left = new BTreeNode<T>(order);
		right = new BTreeNode<T>(order);

		for (size_t i = 0; i < mid - 1; i++) {
			left->data[i] = this->data[i];
		}
		for (size_t i = mid; i < order - 1; i++) {
			right->data[i - mid] = this->data[i];
		}

		BTreeElement<T>* up = ancestor->data[key];
		up->setChild(left);
		up = ancestor->data[key + 1];
		up->setChild(right);
	}

	template <class T>
	class BTree {

	};
}