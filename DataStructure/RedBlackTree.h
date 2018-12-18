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

		RBTreeNode<T>* leftRotation(RBTreeNode<T>* node);
		RBTreeNode<T>* rightRotation(RBTreeNode<T>* node);
		RBTreeNode<T>* leftRightRotation(RBTreeNode<T>* node);
		RBTreeNode<T>* rightLeftRotation(RBTreeNode<T>* node);

		void rePaintColor(RBTreeNode<T>* node, RBTreeNode<T>* brother, nodeColor c = red);
	public:
		RBTree() { root = NULL; nodeNum = 0; };

		RBTreeNode<T>* find(const T& theKey);
		bool isExist(const T& theKey);

		void insert(const T& theKey);
		void deleteNode(const T& theKey);
	};

	template <class T>
	RBTreeNode<T>* RBTree<T>::leftRotation(RBTreeNode<T>* node) {
		RBTreeNode<T>* newTree = node->getRight();
		node->setRight(newTree->getLeft());
		newTree->setLeft(node);
		newTree->setColor(red);

		return newTree;
	}

	template <class T>
	RBTreeNode<T>* RBTree<T>::rightRotation(RBTreeNode<T>* node) {
		RBTreeNode<T>* newTree = node->getLeft();
		node->setLeft(newTree->getRight());
		newTree->setRight(node);
		newTree->setColor(black);

		return newTree;
	}

	template <class T>
	RBTreeNode<T>* RBTree<T>::leftRightRotation(RBTreeNode<T>* node) {
		RBTreeNode<T>* newTree = leftRotation(node->getLeft());
		node->setLeft(newTree);
		newTree = rightRotation(node);
		newTree->setColor(balck);
		newTree->getLeft()->setColor(red);
		newTree->getRight()->setColor(red);

		return newTree;
	}

	template <class T>
	RBTreeNode<T>* RBTree<T>::rightLeftRotation(RBTreeNode<T>* node) {
		RBTreeNode<T>* newTree = rightRotation(node->getRight());
		node->setRight(newTree);
		newTree = leftRotation(node);

		newTree->setColor(black);
		newTree->getLeft()->setColor(red);
		newTree->getRight()->setColor(red);

		return newTree;
	}

	template <class T>
	void RBTree<T>::rePaintColor(RBTreeNode<T>* node, RBTreeNode<T>* brother, nodeColor c) {
		if (node->getColor() != red || brother->getColor() != red) cout << "the nodes aren't all red";

		RBTreeNode<T>* ancestor = node->getAncestor();
		node->setColor(c);
		brother->setColor(c);
		if (ancestor != root) {
			ancestor->setColor(c);
			RBTreeNode<T>* grandAncestor = ancestor->getAncestor();
			RBTreeNode<T>* ancestorBrother = NULL;

			//ancestor != root, means it must have a ancestor
			if (grandAncestor->getLeft() == ancestor) ancestorBrother = grandAncestor->getRight();
			else ancestorBrother = grandAncestor->getLeft();

			//Judge the repaint situation

			//If the grandAncestor is black, don't need change
			if (grandAncestor->getColor() == black) {
				return;
			}
			else {

			}
		}


		return;
	}

	template <class T>
	RBTreeNode<T>* RBTree<T>::find(const T& theKey) {
		if (root == NULL) return NULL;

		RBTreeNode<T>* t = root;
		while (t) {
			if (t->getData() == theKey) return t;

			if (theKey < t->getData()) {
				if (t->getLeft()) t = t->getLeft();
				else return t;
			}
			else if (theKey > t->getData()) {
				if(t->getRight()) t = t->getRight();
				else return t;
			}
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
		RBTreeNode<T>* newNode = new RBTreeNode<T>(theKey);

		if (root = NULL) {
			root = newNode;
			root->setColor(black);
			newNode.setAncestor(NULL);
			return;
		}

		newNode->setColor(red);
		RBTreeNode<T>* target = find(theKey);
		//The insert T has existed!
		if (target->getData() == theKey) return;

		//Whatever the sitiuation is, insert firstly
		if (theKey < target->getColor()) target->setLeft(newNode);
		else target->setRight(newNode);
		newNode->setAncestor(target);

		RBTreeNode<T>* ancestor = target->getAncestor();

		if (target->getColor() == black) {
			return;
		}
		else if (target->getColor() == red) {
			//If target is red, target must have a black ancestor
			//Target is the left child of it's ancestor

			RBTreeNode<T>* tempNewNode = NULL;
			RBTreeNode<T>* targetGrandAncestor = target->getAncestor()->getAncestor();		

			if ((target->getAncestor()->getLeft() == NULL || target->getAncestor()->getRight() == NULL) &&
				!(target->getAncestor()->getLeft() == NULL && target->getAncestor()->getRight() == NULL)) {

				//The target is at the left of it's ancestor
				if (target->getAncestor()->getLeft() == target) {
					//The insertPos is at the left(just like AVL LL)
					if (theKey < target->getData()) {
						tempNewNode = rightRotation(target->getAncestor());
					}
					//The new node is at the right of the insertpos just like AVL LR
					else if (theKey > target->getData()) {
						tempNewNode = leftRightRotation(target->getAncestor());
					}
				}

				//The target is at the right of it's ancestor
				else if (target->getAncestor()->getRight() == taregt) {
					//The insert position is at the right of the target(just like AVL RR)
					if (theKey > target->getData()) {
						tempNewNode = leftRotation(target->getAncestor());
					}
					//The insert position is at the left of the target(just like AVL RL)
					else if (theKey < target->getData()) {
						tempNewNode = rightLeftRotation(target->getAncestor());
					}
				}

				//Set the target's grandancestor's child
				if (targetGrandAncestor == NULL) { 
					root = tempNewNode;
					tempNewNode->setAncestor(NULL);
				}
				else {
					if (tempNewNode->getData() < targetGrandAncestor->getData()) targetGrandAncestor->setLeft(tempNewNode);
					else targetGrandAncestor->setRight(tempNewNode);
					tempNewNode->setAncestor(targetGrandAncestor);
				}
			}
			else if (target->getAncestor()->getLeft()->getColor() == red && target->getAncestor()->getRight()->getColor() == red) {
				RBTreeNode<T>* brother = NULL;
				if (target->getAncestor()->getLeft() == target) brother = target->getAncestor()->getRight();
				else brother = target->getAncestor()->getLeft();

				rePaintColor(target, brother, red);
			}
		}
	}
}