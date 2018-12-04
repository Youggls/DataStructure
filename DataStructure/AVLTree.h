#pragma once

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
using std::cout;
#endif // !IOSTREAM

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "binaryTree.h"
using dataStructure::binaryTreeNode;
#endif // !BINARYTREE_H

#ifndef STLQUEUE
#define STLQUEUE
#include <queue>
using std::queue;
#endif // !STLQUEUE

namespace dataStructure {
	template <class T>
	class AVLTreeNode {
	private:
		T data;
		int bf;
		AVLTreeNode<T>* leftChildNode;
		AVLTreeNode<T>* rightChildNode;

	public:
//		friend class AVLTree<T>;
		AVLTreeNode(const T& dat) {
			bf = 0;
			leftChildNode = rightChildNode = NULL;
			data = dat;
		}
		AVLTreeNode<T>* getRight() { return rightChildNode; };
		AVLTreeNode<T>* getLeft() { return leftChildNode; };
		void setRight(AVLTreeNode<T>* node) { rightChildNode = node; };
		void setLeft(AVLTreeNode<T>* node) { leftChildNode = node; };
		const T& getData() { return data; };
		void setData(const T& dat) { data = dat; };
		void changeBf(const int& value) { bf = value; };
		const int& getBf() { return bf; };
	};

	template <class T>
	class AVLTree {
	private:
		AVLTreeNode<T>* root;
		size_t nodenum;
		size_t recursiveGetDepth(AVLTreeNode<T>* node);
		void recursivePreOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*));
		void recursiveInOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*));
		void recursivePostOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*));
		AVLTreeNode<T>* rightRotation(AVLTreeNode<T>* targetNode);
		AVLTreeNode<T>* leftRotation(AVLTreeNode<T>* targetNode);
		AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* targetNode);
		AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* targetNode);
//		void recursiveDelete(AVLTreeNode<T>* node, const T& theKey);
		//Will change the balance factor from the start postion to the insert position
		void changeTheBalanceFactor(AVLTreeNode<T>* startPos, AVLTreeNode<T>* insertPos, const T& element);
		//Will return the child's ancestor node, if not, return NULL
		AVLTreeNode<T>* findAncestor(AVLTreeNode<T>* child, AVLTreeNode<T>* start = NULL);
		void balanceTree(AVLTreeNode<T>* start, AVLTreeNode<T>* node);
	public:
		AVLTree();
		void insert(const T& element);
		void preOrder(void(*visit)(AVLTreeNode<T>*) = NULL);
		void inOrder(void(*visit)(AVLTreeNode<T>*) = NULL);
		void postOrder(void(*visit)(AVLTreeNode<T>*) = NULL);
		void levelOrder(void(*visit)(AVLTreeNode<T>*) = NULL);
		void deleteNode(const T& theKey);
		size_t size() { return nodenum; };
		bool isComplete();
		size_t depth();
	};

	template <class T>
	AVLTree<T>::AVLTree() {
		root = NULL;
		nodenum = 0;
	}

	template <class T>
	size_t AVLTree<T>::recursiveGetDepth(AVLTreeNode<T>* node) {
		if (node == NULL) return 0;
		size_t dl = recursiveGetDepth(node->getLeft());
		size_t dr = recursiveGetDepth(node->getRight());
		if (dl > dr) return ++dl;
		else return ++dr;
	}

	template<class T>
	void AVLTree<T>::recursivePreOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*)) {
		if (visit == NULL) {
			if (node) {
				cout << node->getData();
				recursivePreOrder(node->getLeft(), visit);
				recursivePreOrder(node->getRight(), visit);
			}
		}
		else {
			if (node) {
				visit(node);
				recursivePreOrder(node->getLeft(), visit);
				recursivePreOrder(node->getRight(), visit);
			}
		}
	}

	template <class T>
	void AVLTree<T>::recursiveInOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*)) {
		if (visit == NULL) {
			if (node) {
				recursiveInOrder(node->getLeft(), visit);
				cout << node->getData();
				recursiveInOrder(node->getRight(), visit);
			}
		}
		else {
			if (node) {
				recursiveInOrder(node->getLeft(), visit);
				visit(node);
				recursiveInOrder(node->getRight(), visit);
			}
		}
	}

	template <class T>
	void AVLTree<T>::recursivePostOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*)) {
		if (visit == NULL) {
			if (node) {
				recursivePostOrder(node->getLeft(), visit);
				recursivePostOrder(node->getRight(), visit);
				cout << node->getData();
			}
		}
		else {
			if (node) {
				recursivePostOrder(node->getLeft(), visit);
				recursivePostOrder(node->getRight(), visit);
				visit(node);
			}
		}
	}

	template <class T>
	void AVLTree<T>::levelOrder(void(*visit)(AVLTreeNode<T>*)) {
		if (root == NULL) return;
		queue<AVLTreeNode<T>*> prelist;
		prelist.push(root);
		size_t count = 0;
		while (prelist.size() != 0) {
			count++;
			AVLTreeNode<T>* front = prelist.front();
			if (visit == NULL) {
				cout << front->getData();
				if (count != nodenum) cout << ' ';
			}
			else visit(front);
			prelist.pop();
			if (front->getLeft() != NULL) prelist.push(front->getLeft());
			if (front->getRight() != NULL) prelist.push(front->getRight());
		}
	}

	template <class T>
	AVLTreeNode<T>* AVLTree<T>::rightRotation(AVLTreeNode<T>* t) {
		AVLTreeNode<T>* newTree = t->getLeft();
		t->setLeft(newTree->getRight());
		newTree->setRight(t);
		return newTree;
	}

	template <class T>
	AVLTreeNode<T>* AVLTree<T>::leftRotation(AVLTreeNode<T>* t) {
		AVLTreeNode<T>* newTree = t->getRight();
		t->setRight(newTree->getLeft());
		newTree->setLeft(t);
		return newTree;
	}

	template <class T>
	AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* t) {
		t->setRight(rightRotation(t->getRight()));
		return leftRotation(t);
	}

	template <class T>
	AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* t) {
		t->setLeft(leftRotation(t->getLeft()));
		return rightRotation(t);
	}

	template <class T>
	void AVLTree<T>::changeTheBalanceFactor(AVLTreeNode<T>* startPos, AVLTreeNode<T>* insertPos, const T& element) {
		AVLTreeNode<T>* t = startPos;
		while (t) {
			if (element > t->getData()) {
				t->changeBf(t->getBf() - 1);
				t = t->getRight();
			}
			else if (element < t->getData()) {
				t->changeBf(t->getBf() + 1);
				t = t->getLeft();
			}
			else return;
		}
	}

	template <class T>
	AVLTreeNode<T>* AVLTree<T>::findAncestor(AVLTreeNode<T>* child, AVLTreeNode<T>* start) {
		AVLTreeNode<T>* ancestor = NULL;
		AVLTreeNode<T>* t;
		if(start == NULL) t = root;
		else t = start;
		while (t) {
			if (t->getData() == child->getData()) break;
			ancestor = t;
			if (child->getData() < t->getData()) t = t->getLeft();
			else t = t->getRight();
		}

		return ancestor;
	}

	template <class T> 
	void AVLTree<T>::balanceTree(AVLTreeNode<T>* start, AVLTreeNode<T>* node) {
		AVLTreeNode<T>* ancestor = findAncestor(node, start);

		if (node->getBf() == 2) {
			//LL
			if (node->getLeft()->getBf() == 1) {
				AVLTreeNode<T>* newTree = rightRotation(node);
				if (ancestor->getLeft() == node) {
					ancestor->setLeft(newTree);
				}
				else ancestor->setRight(newTree);
				ancestor->changeBf(0);
			}
			//LR
			else if (node->getLeft()->getBf() == -1) {
				AVLTreeNode<T>* newTree = leftRightRotation(node);
				if (ancestor->getLeft() == node) {
					ancestor->setLeft(newTree);
				}
				else ancestor->setRight(newTree);

				if (newTree->getBf() == 0) {
					newTree->getLeft()->changeBf(0);
					newTree->getRight()->changeBf(0);
				}
				else if (newTree->getBf() == 1) {
					newTree->getLeft()->changeBf(0);
					newTree->getRight()->changeBf(-1);
				}
				else if (newTree->getBf() == -1) {
					newTree->getLeft()->changeBf(1);
					newTree->getRight()->changeBf(0);
				}
			}
		}
		else if (node->getBf() == -2) {
			//RR
			if(node->getRight()->getBf() == -1) {
				AVLTreeNode<T>* newTree = leftRotation(node);
				if (ancestor->getLeft() == node) {
					ancestor->setLeft(newTree);
				}
				else ancestor->setRight(newTree);
				ancestor->changeBf(0);
			}
			//RL
			else if (node->getRight()->getBf() == 1) {
				AVLTreeNode<T>* newTree = rightLeftRotation(node);
				if (ancestor->getLeft() == node) {
					ancestor->setLeft(newTree);
				}
				else ancestor->setRight(newTree);

				if (newTree->getBf() == 0) {
					newTree->getLeft()->changeBf(0);
					newTree->getRight()->changeBf(0);
				}
				else if (newTree->getBf() == 1) {
					newTree->getLeft()->changeBf(0);
					newTree->getRight()->changeBf(-1);
				}
				else if (newTree->getBf() == -1) {
					newTree->getLeft()->changeBf(1);
					newTree->getRight()->changeBf(0);
				}
			}
		}
		
		int dl = recursiveGetDepth(ancestor->getLeft());
		int dr = recursiveGetDepth(ancestor->getRight());

		ancestor->changeBf(dl - dr);
	}


	template <class T>
	void AVLTree<T>::preOrder(void(*visit)(AVLTreeNode<T>*)) {
		recursivePreOrder(root);
	}

	template <class T>
	void AVLTree<T>::inOrder(void(*visit)(AVLTreeNode<T>*)) {
		recursiveInOrder(root);
	}

	template <class T>
	void AVLTree<T>::postOrder(void(*visit)(AVLTreeNode<T>*)) {
		recursivePostOrder(root);
	}

	template <class T>
	size_t AVLTree<T>::depth() {
		return recursiveGetDepth(root);
	}

	template <class T>
	void AVLTree<T>::deleteNode(const T& theKey) {
		if (root == NULL) return;

		AVLTreeNode<T>* target = root, *ancestor = NULL;
		
		while (target) {
			if (target->getData() == theKey) break;
			ancestor = target;
			if (target->getData() > theKey) target = target->getLeft();
			else target = target->getRight();
		}
		if (target == NULL) return;

		if (target->getLeft() == NULL && target->getRight() == NULL) {
			if (ancestor == NULL) {
				delete root;
				root = NULL;
				return;
			}
			else {
				if (ancestor->getLeft() == target) {
					ancestor->setLeft(NULL);
					delete target;
					ancestor->changeBf(ancestor->getBf() - 1);
				}
				else {
					ancestor->setRight(NULL);
					delete target;
					ancestor->changeBf(ancestor->getBf() + 1);
				}
			}
		}
		else if (target->getLeft() != NULL && target->getRight() == NULL) {
			if (ancestor == NULL) {
				root = target->getLeft();
				delete target;
			}
			else {
				if (ancestor->getLeft() == target) {
					ancestor->setLeft(target->getLeft());
					delete target;
					ancestor->changeBf(ancestor->getBf() - 1);
				}
				else {
					ancestor->setRight(target->getLeft());
					delete target;
					ancestor->changeBf(ancestor->getBf() + 1);
				}
			}
		}
		else if (target->getLeft() == NULL && target->getRight() != NULL) {
			if (ancestor == NULL) {
				root = target->getRight();
				delete target;
			}
			else {
				if (ancestor->getLeft() == target) {
					ancestor->setLeft(target->getRight());
					delete target;
					ancestor->changeBf(ancestor->getBf() - 1);
				}
				else {
					ancestor->setRight(ancestor->getRight());
					delete target;
					ancestor->changeBf(ancestor->getBf() + 1);
				}
			}
		}
		else {
			AVLTreeNode<T>* maxOfLeft = target->getLeft();
			AVLTreeNode<T>* pOfMax = target;
			while (maxOfLeft->getRight()) {
				pOfMax = maxOfLeft;
				maxOfLeft = maxOfLeft->getRight();
			}

			target->setData(maxOfLeft->getData());
			pOfMax->setRight(NULL);
			pOfMax->changeBf(pOfMax->getBf() + 1);
			
			AVLTreeNode<T>* tempAncestor = pOfMax;
			while (pOfMax != target) {
				balanceTree(tempAncestor);
				tempAncestor = findAncestor(tempAncestorm, target);
			}
		}
	}

	template <class T>
	void AVLTree<T>::insert(const T& element) {
		nodenum++;
		AVLTreeNode<T>* newNode = new AVLTreeNode<T>(element);
		if (root == NULL) {
			root = newNode;
			return;
		}

		AVLTreeNode<T>* tmp = NULL;
		AVLTreeNode<T>* t = root;
		AVLTreeNode<T>* insertPos = root;

		while (t) {
			if (t->getBf() != 0) tmp = t;
			if (t->getData() < element) {
				if (t->getRight() == NULL) break;
				else t = t->getRight();
			}
			else if (t->getData() > element) {
				if (t->getLeft() == NULL) break;
				else t = t->getLeft();
			}
			else return;
		}

		insertPos = t;

		//Whatever the node is, insert it first!
		if (element > insertPos->getData()) insertPos->setRight(newNode);
		else insertPos->setLeft(newNode);

		//Not find the bf, after inserting will not change the balance factor(bf)
		if (tmp == NULL) {
			//After insertion, change the banance factor from the root node to the insertion node
			changeTheBalanceFactor(root, insertPos, element);
			return;
		}
		//Find the last node which isn't balanced, and it's balance factor is 1
		//That means this sutiuation is the "LL" or "LR"
		else if (tmp->getBf() == 1) {		
			//LL
			if (element < tmp->getLeft()->getData() && insertPos->getData() < tmp->getData()) {
				//Firstly, find the tmp's ancestor node
				AVLTreeNode<T>* ancestor = findAncestor(tmp);
				//Secondly, rorate to right, and set the ancestor's new child 
				AVLTreeNode<T>* newTree = rightRotation(tmp);
				if (ancestor == NULL) root = newTree;
				else if (ancestor->getData() > tmp->getData()) ancestor->setLeft(newTree);
				else ancestor->setRight(newTree);
				//Then, change the tmp node's balance factor to ZERO
				tmp->changeBf(0);
				//Lastly, change the balance factor from the tmp's left child to the insert node
				changeTheBalanceFactor(newTree->getLeft(), insertPos, element);
				return;
			}
			//LR
			else if (element > tmp->getLeft()->getData() && insertPos->getData() < tmp->getData()) {
				//Solve the new node's balance factor
				changeTheBalanceFactor(tmp->getLeft()->getRight(), insertPos, element);
				//Firstly, find the tmp's ancestor node
				AVLTreeNode<T>* ancestor = findAncestor(tmp);
				//Secondly, rorate to left and to right, and set the ancestor' new child
				AVLTreeNode<T>* newTree = leftRightRotation(tmp);
				if (ancestor == NULL) root = newTree;
				else if (ancestor->getData() > tmp->getData()) ancestor->setLeft(newTree);
				else ancestor->setRight(newTree);
				//Lastly, change the balance factor of the newTree node and is's childs
				if (newTree->getBf() == 0) {
					newTree->getLeft()->changeBf(0);
					newTree->getRight()->changeBf(0);
				}
				else if (newTree->getBf() == 1) {
					newTree->getLeft()->changeBf(0);
					newTree->getRight()->changeBf(-1);
				}
				else if (newTree->getBf() == -1) {
					newTree->getLeft()->changeBf(1);
					newTree->getRight()->changeBf(0);
				}
				return;
			}
			//Don't change the balance
			else {
				changeTheBalanceFactor(tmp, insertPos, element);
				return;
			}
		}
		//Find the last node which isn't balanced, and it's balance factor is -1
		//That means this sutiuation is the "RR" or "RL"
		else if (tmp->getBf() == -1) {
			//RR
			if (element > tmp->getRight()->getData() && insertPos->getData() > tmp->getData()) {
				//Firstly, find the ancestor node
				AVLTreeNode<T>* ancestor = findAncestor(tmp);
				//Secondly, rorate to left and set the ancestor's new child
				AVLTreeNode<T>* newTree = leftRotation(tmp);
				if (ancestor == NULL) root = newTree;
				else if (ancestor->getData() > tmp->getData()) ancestor->setLeft(newTree);
				else ancestor->setRight(newTree);
				//Then, change the tmp node's balance factor to ZERO
				tmp->changeBf(0);
				//Lastly, change the balance factor from the tmp's right child to the insert node
				changeTheBalanceFactor(newTree->getRight(), insertPos, element);
				return;
			}
			//RL
			else if (element < tmp->getRight()->getData() && insertPos->getData() > tmp->getData()) {
				//Change the balance factor
				changeTheBalanceFactor(tmp->getRight()->getLeft(), insertPos, element);
				//Firstly, find the tmp's ancestor node
				AVLTreeNode<T>* ancestor = findAncestor(tmp);
				//Secondly, rorate to right and to left, and set the ancestor' new child
				AVLTreeNode<T>* newTree = rightLeftRotation(tmp);
				if (ancestor == NULL) root = newTree;
				else if (ancestor->getData() > tmp->getData()) ancestor->setLeft(newTree);
				else ancestor->setRight(newTree);
				//Lastly, change the balance factor of the newTree node and is's childs
				if (newTree->getBf() == 0) {
					newTree->getLeft()->changeBf(0);
					newTree->getRight()->changeBf(0);
				}
				else if (newTree->getBf() == 1) {
					newTree->getLeft()->changeBf(0);
					newTree->getRight()->changeBf(-1);
				}
				else if (newTree->getBf() == -1) {
					newTree->getLeft()->changeBf(1);
					newTree->getRight()->changeBf(0);
				}
				return;
			}
			//Don't change the balance
			else {
				changeTheBalanceFactor(tmp, insertPos, element);
				return;
			}
		}
	}

	template <class T>
	bool AVLTree<T>::isComplete() {
		if (root == NULL) return true;
		if (root->getLeft() == NULL && root->getRight() == NULL) return true;
		queue<AVLTreeNode<T>*> nodeQueue;
		nodeQueue.push(root);

		while (nodeQueue.size() != 0) {
			AVLTreeNode<T>* front = nodeQueue.front();
			if (front == NULL && nodeQueue.size() != 1) return false;
			else if (front->getLeft() == NULL && front->getRight() != NULL) return false;

			if (front->getLeft() != NULL) {
				nodeQueue.push(front->getLeft());
				nodeQueue.push(front->getRight());
				nodeQueue.pop();
			}
			else nodeQueue.pop();
		}

		return true;
	}
}