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
		bool isNull;
	public:
		RBTreeNode(T dat, nodeColor c = black) { data = dat; color = c; left = NULL; right = NULL; ancestor = NULL; isNull = false};
		RBTreeNode() { isNull = true; left = NULL; right = NULL; ancestor = NULL; color = black; };
		RBTreeNode<T>* getLeft() { return left; };
		RBTreeNode<T>* getRight() { return right; };
		RBTreeNode<T>* getAncestor() { return ancestor; };

		void setLeft(RBTreeNode<T>* l) { left = l; };
		void setRight(RBTreeNode<T>* r) { right = r; };
		void setAncestor(RBTreeNode<T>* a) {
			ancestor = a;
		};
		bool isNULL() { return isNull; };
		void setNull() { isNull = true; };
		void setUnNull() { isNull = false; };

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

		RBTreeNode<T>* getUncle(RBTreeNode<T>* node);

		void insertCase1(RBTreeNode<T>* node);
		void insertCase2(RBTreeNode<T>* node);
		void insertCase3(RBTreeNode<T>* node);
		void insertCase4(RBTreeNode<T>* node);
		void insertCase5(RBTreeNode<T>* node);

		void rePaintColor(RBTreeNode<T>* node, RBTreeNode<T>* brother, nodeColor c = black);
	public:
		RBTree() { root = NULL; nodeNum = 0; };

		RBTreeNode<T>* find(const T& theKey);
		bool isExist(const T& theKey);

		void insert(const T& theKey);
		void deleteNode(const T& theKey);
	};

	template <class T>
	void RBTree<T>::insertCase1(RBTreeNode<T>* node) {
		if (node->getAncestor() == NULL) {
			node->setColor(black);
		}
		else insertCase2(node);
	}

	template <class T>
	void RBTree<T>::insertCase2(RBTreeNode<T>* node) {
		if (node->getAncestor()->getColor() == black)
			return;
		else insertCase3(node);
	}

	template <class T>
	void RBTree<T>::insertCase3(RBTreeNode<T>* node) {
		//node's ancestor is red, it must have a black ancestor
		if (!getUncle(node)->isNULL() && getUncle(node)->getColor() == red) {
			node->getAncestor()->setColor(black);
			getUncle(node)->setColor(black);
			node->getAncestor()->getAncestor()->getColor() = red;
			insertCase1(node->getAncestor()->getAncestor());
		}
		else insertCase4(node);
	}

	template <class T>
	void RBTree<T>::insertCase4(RBTreeNode<T>* node) {
		RBTreeNode<T>* ancestor = node->getAncestor();
		if (ancestor->getRight() == node && ancestor == ancestor->getAncestor()->getLeft()) {
			RBTreeNode<T>* newTree = leftRotation(node->getAncestor());
			ancestor->setRight(newTree);

			newTree->setColor(red);
			newTree->getLeft()->setColor(red);

			node = newTree->getLeft();	
		}
		else if (ancestor->getLeft() == node && ancestor == ancestor->getAncestor()->getRight()) {
			RBTreeNode<T>* newTree = rightRotation(node->getAncestor());
			ancestor->setLeft(newTree);

			newTree->setColor(red);
			newTree->getLeft()->setColor(red);

			node = newTree->getRight();
		}
		insertCase5(node);
	}

	template <class T>
	void RBTree<T>::insertCase5(RBTreeNode<T>* node) {
		node->getAncestor()->setColor(black);
		node->getAncestor()->getAncestor()->setColor(red);

		RBTreeNode<T>* newTree = NULL;
		if (node == node->getAncestor()->getLeft() && node->getAncestor() == node->getAncestor()->getAncestor()->getLeft()) {
			newTree = rightRotation(node->getAncestor()->getAncestor());
		}
		else {
			leftRotation(node->getAncestor()->getAncestor());
		}
		newTree->setColor(black);
		newTree->getRight()->setColor(red);
		newTree->getLeft()->setColor(red);
		if (node->getAncestor()->getAncestor() != root) {
			if (node->getAncestor()->getAncestor()->getAncestor()->getData() > newTree->getData()) {
				node->getAncestor()->getAncestor()->getAncestor()->setRight(newTree);
			}
			else node->getAncestor()->getAncestor()->getAncestor()->setLeft(newTree);
		}
		else root = newTree;
	}

	template <class T>
	RBTreeNode<T>* RBTree<T>::leftRotation(RBTreeNode<T>* node) {
		RBTreeNode<T>* newTree = node->getRight();
		node->setRight(newTree->getLeft());
		if (!node->getRight()->isNULL()) node->getRight()->setAncestor(node);
		newTree->setLeft(node);
		node->setAncestor(newTree);
		newTree->setColor(black);
		node->setColor(red);

		return newTree;
	}

	template <class T>
	RBTreeNode<T>* RBTree<T>::rightRotation(RBTreeNode<T>* node) {
		RBTreeNode<T>* newTree = node->getLeft();
		node->setLeft(newTree->getRight());
		if (!node->getLeft()->isNULL()) node->getLeft()->setAncestor(node);

		newTree->setRight(node);
		node->setAncestor(newTree);
		newTree->setColor(black);
		node->setColor(red);

		return newTree;
	}

	template <class T>
	RBTreeNode<T>* RBTree<T>::leftRightRotation(RBTreeNode<T>* node) {
		RBTreeNode<T>* newTree = leftRotation(node->getLeft());
		node->setLeft(newTree);
		newTree = rightRotation(node);

		newTree->setColor(black);
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
	RBTreeNode<T>* RBTree<T>::getUncle(RBTreeNode<T>* node) {
		if (node->getAncestor() == node->getAncestor()->getAncestor()->getLeft()) {
			return node->getAncestor()->getAncestor()->getRight();
		}
		else return node->getAncestor()->getAncestor()->getLeft();
	}

 	//template <class T>
	//void RBTree<T>::rePaintColor(RBTreeNode<T>* node, RBTreeNode<T>* brother, nodeColor c) {
	//	if (node->getColor() != red || brother->getColor() != red) cout << "the nodes aren't all red";

	//	RBTreeNode<T>* ancestor = node->getAncestor();
	//	node->setColor(c);
	//	brother->setColor(c);
	//	if (ancestor != root) {
	//		ancestor->setColor(red);
	//		RBTreeNode<T>* grandAncestor = ancestor->getAncestor();
	//		RBTreeNode<T>* grandAncestorBrother = NULL;

	//		////ancestor != root, means it must have an ancestor
	//		//if (grandAncestor->getLeft() == ancestor) ancestorBrother = grandAncestor->getRight();
	//		//else ancestorBrother = grandAncestor->getLeft();

	//		//Judge the repaint situation

	//		//If the grandAncestor is black, don't need change
	//		if (grandAncestor->getColor() == black) {
	//			return;
	//		}
	//		else {
	//			//If grandAncestor is red, it must have an ancestor
	//			RBTreeNode<T>* greatGrandAncestor = grandAncestor->getAncestor();
	//			RBTreeNode<T>* newNode = NULL;
	//			RBTreeNode<T>* temp = greatGrandAncestor->getAncestor();
	//			if (greatGrandAncestor->getLeft() == grandAncestor) grandAncestorBrother = greatGrandAncestor->getRight();
	//			else grandAncestorBrother = greatGrandAncestor->getLeft();
	//			if (grandAncestorBrother == NULL || grandAncestorBrother->getColor() == black) {
	//				if (greatGrandAncestor->getLeft() == grandAncestor) {
	//					if (grandAncestor->getLeft() == ancestor) {
	//						newNode = rightRotation(greatGrandAncestor);
	//					}
	//					else if (grandAncestor->getRight() == ancestor) {
	//						newNode = leftRightRotation(greatGrandAncestor);
	//					}
	//				}
	//				else if (greatGrandAncestor->getRight() == grandAncestor) {
	//					if (grandAncestor->getRight() == ancestor) {
	//						newNode = leftRotation(greatGrandAncestor);
	//					}
	//					else if (grandAncestor->getLeft() == ancestor) {
	//						newNode = rightLeftRotation(greatGrandAncestor);
	//					}
	//				}

	//				if (temp != NULL) {
	//					T t = temp->getData();
	//					t = t;
	//					if (temp->getData() > newNode->getData()) {
	//						temp->setLeft(newNode);
	//						newNode->setAncestor(temp);
	//					}
	//					else if (temp->getData() < newNode->getData()) {
	//						temp->setRight(newNode);
	//						newNode->setAncestor(temp);
	//					}
	//				}
	//				else {
	//					root = newNode;
	//					newNode->setAncestor(NULL);
	//				}
	//			}
	//			else if (grandAncestorBrother != NULL && grandAncestorBrother->getColor() == red) {
	//				rePaintColor(grandAncestor, grandAncestorBrother, black);
	//			}
	//		}
	//	}
	//	else {
	//		return;
	//	}
	//}

	template <class T>
	RBTreeNode<T>* RBTree<T>::find(const T& theKey) {
		if (root == NULL) return NULL;

		RBTreeNode<T>* t = root;
		while (!t->isNULL()) {
			if (t->getData() == theKey) return t;

			if (theKey < t->getData()) {
				if (!t->getLeft()->isNULL()) t = t->getLeft();
				else return t;
			}
			else if (theKey > t->getData()) {
				if (!t->getRight()->isNULL()) t = t->getRight();
				else return t;
			}
		}

		return t;
	}

	template <class T>
	bool RBTree<T>::isExist(const T& theKey) {
		if (root == NULL) return false;

		RBTreeNode<T>* t = root;
		while (!t->isNULL()) {
			if (t->getData() == theKey) return true;

			if (theKey < t->getData()) t = t->getLeft();
			else if (theKey > t->getData()) t = t->getRight();
		}

		return false;
	}

	template <class T>
	void RBTree<T>::insert(const T& theKey) {
		if (root == NULL) {
			root = new RBTreeNode<T>(theKey);
			RBTreeNode<T>* outNode1 = new RBTreeNode<T>;
			RBTreeNode<T>* outNode2 = new RBTreeNode<T>;

			root->setLeft(outNode1);
			root->setRight(outNode2);
			outNode1->setAncestor(root);
			outNode2->setAncestor(root);
		}
		else {

		}
	}

	//template <class T>
	//void RBTree<T>::insert(const T& theKey) {
	//	RBTreeNode<T>* newNode = new RBTreeNode<T>(theKey);

	//	if (root == NULL) {
	//		root = newNode;
	//		root->setColor(black);
	//		newNode->setAncestor(NULL);
	//		RBTreeNode<T>* left = new RBTreeNode<T>;
	//		RBTreeNode<T>* right = new RBTreeNode<T>;
	//		newNode->setLeft(left);
	//		newNode->setRight(left);
	//		return;
	//	}

	//	newNode->setColor(red);
	//	RBTreeNode<T>* target = find(theKey);
	//	//The insert T has existed!
	//	if (target->getData() == theKey) return;

	//	//Whatever the sitiuation is, insert firstly
	//	if (theKey < target->getData()) target->setLeft(newNode);
	//	else target->setRight(newNode);
	//	newNode->setAncestor(target);

	//	RBTreeNode<T>* ancestor = target->getAncestor();

	//	if (target->getColor() == black) {
	//		return;
	//	}
	//	else if (target->getColor() == red) {
	//		//If target is red, target must have a black ancestor
	//		//Target is the left child of it's ancestor

	//		RBTreeNode<T>* tempNewNode = NULL;
	//		RBTreeNode<T>* targetGrandAncestor = target->getAncestor()->getAncestor();

	//		if ((target->getAncestor()->getLeft() == NULL || target->getAncestor()->getRight() == NULL) &&
	//			!(target->getAncestor()->getLeft() == NULL && target->getAncestor()->getRight() == NULL)) {

	//			//The target is at the left of it's ancestor
	//			if (target->getAncestor()->getLeft() == target) {
	//				//The insertPos is at the left(just like AVL LL)
	//				if (theKey < target->getData()) tempNewNode = rightRotation(target->getAncestor());
	//				//The new node is at the right of the insertpos just like AVL LR
	//				else if (theKey > target->getData()) tempNewNode = leftRightRotation(target->getAncestor());
	//			}

	//			//The target is at the right of it's ancestor
	//			else if (target->getAncestor()->getRight() == target) {
	//				//The insert position is at the right of the target(just like AVL RR)
	//				if (theKey > target->getData()) tempNewNode = leftRotation(target->getAncestor());
	//				//The insert position is at the left of the target(just like AVL RL)
	//				else if (theKey < target->getData())
	//					tempNewNode = rightLeftRotation(target->getAncestor());
	//			}

	//			//Set the target's grandancestor's child
	//			if (targetGrandAncestor == NULL) {
	//				root = tempNewNode;
	//				tempNewNode->setAncestor(NULL);
	//			}
	//			else {
	//				if (tempNewNode->getData() < targetGrandAncestor->getData()) targetGrandAncestor->setLeft(tempNewNode);
	//				else targetGrandAncestor->setRight(tempNewNode);
	//				tempNewNode->setAncestor(targetGrandAncestor);
	//			}
	//		}
	//		else if (target->getAncestor()->getLeft()->getColor() == red && target->getAncestor()->getRight()->getColor() == red) {
	//			RBTreeNode<T>* brother = NULL;
	//			if (target->getAncestor()->getLeft() == target) brother = target->getAncestor()->getRight();
	//			else brother = target->getAncestor()->getLeft();

	//			rePaintColor(target, brother, black);
	//		}
	//	}
	//}

}