#pragma once

namespace dataStructure {
	enum nodeColor { red, black };

	template <class T>
	class RBTreeNode {
	private:
		T data;
		RBTreeNode<T>* left;
		RBTreeNode<T>* right;
		RBTreeNode<T>* ancestor;
		nodeColor color;
	public:
		RBTreeNode(T dat, nodeColor c = black) { data = dat; color = c; left = NULL; right = NULL; ancestor = NULL; };
		RBTreeNode<T>* getLeft() { return left; };
		RBTreeNode<T>* getRight() { return right; };
		RBTreeNode<T>* getAncestor() { return ancestor; };

		void setLeft(RBTreeNode<T>* l) { left = l; };
		void setRight(RBTreeNode<T>* r) { right = r; };
		void setAncestor(RBTreeNode<T>* a) { ancestor = a; };

		void setColor(nodeColor c) { color = c; };
		nodeColor getColor() { return color; };

		void setData(const T& theKey) { data = theKey; };
		T getData() { return data; };
	};

	template <class T>
	class RBTree {
	private:
		RBTreeNode<T>* root;
		int nodeNum;

	public:
		RBTree() { root = NULL; nodeNum = 0; };

		RBTreeNode<T>* find(const T& theKey);
		bool isExist(const T& theKey);

		void insert(const T& theKey);
		void deleteNode(const T& theKey);
	};

	template <class T>
	RBTreeNode<T>* RBTree<T>::find(const T& theKey) {
		if (root == NULL) return NULL;

		RBTreeNode<T>* t = root;
		while (t) {
			if (t->getData() == theKey) return t;

			if (theKey < t->getData()) t = t->getLeft();
			else if (theKey > t->getData()) t = t->getRight();
		}

		return t;
	}

	template <class T>
	bool RBTree<T>::isExist(const T& theKey) {
		if (root == NULL) return false;

		RBTreeNode<T> t = root;
		while (t) {
			if (t.getData() == theKey) return true;
			
			if (theKey < t.getData()) t = t.getLeft();
			else if (theKey > t.getData()) t = t.getRight();
		}

		return false;
	}

	template <class T>
	void RBTree<T>::insert(const T& theKey) {
		BTreeNode<T>* newNode = new BTreeNode<T>(theKey);

		if (root = NULL) {
			root = newNode;
			root->setColor(black);
			return;
		}

		BTreeNode<T>* target = 
	}
}