#pragma once

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "binaryTree.h"
using dataStructure::binaryTreeNode;
#endif // !BINARYTREE_H


namespace dataStructure {
	template <class T>
	class AVLTreeNode {
	private:
		T data;
		int bf;
		AVLTreeNode<T>* leftChildNode;
		AVLTreeNode<T>* rightChildNode;
	public:
		AVLTreeNode(const T& dat) {
			bf = 0;
			leftChildNode = rightChildNode = NULL;
		}
		AVLTreeNode<T>* getRightChildNode() { return rightChildNode; };
		AVLTreeNode<T>* getLeftChildNode() { return leftChildNode; };
		void setRightChildNode(const AVLTreeNode<T>* node) { rightChildNode = node; };
		void setLeftChildNode(const AVLTreeNode<T>* node) { leftChildNode = node; };
		const T& getData() { return data; };
		void setData(const T& dat) { data = dat; };
		void changeBf(const int& value) { bf = value; };
		const int& getBf() { return bf; };
	};

	template <class T>
	class AVLTree {
	private:
		AVLTreeNode<T>* root;
		size_t num;
		size_t recursiveGetDepth(AVLTreeNode<T>* node);
	public:
		AVLTree();
		void insert(const T& element);
		size_t depth();
	};

	template <class T>
	AVLTree<T>::AVLTree() {
		root = NULL;
		num = 0;
	}
	
	template <class T>
	size_t AVLTree<T>::recursiveGetDepth(AVLTreeNode<T>* node) {
		if (node == NULL) return 0;
		size_t dl = recursiveGetDepth(node->getLeftChildNode());
		size_t dr = recursiveGetDepth(node->getRightChildNode());
		if (dl > dr) return ++dl;
		else return ++dr;
	}

	template <class T>
	size_t AVLTree<T>::depth() {
		return recursiveGetDepth(root);
	}

	template <class T>
	void AVLTree<T>::insert(const T& element) {
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
			insertPos = t;
			if (element > t->getData()) t = t->getRightChildNode();
			else if (t < t->getData()) t = t->getLeftChildNode();
			else return;
		}

		if (tmp == NULL) {
			if (element > insertPos->getData()) insertPos->setRightChildNode(newNode);
			else if (element < insertPos->getData()) insertPos->setLeftChildNode(newNode);
			else return;

			t = root;
			while (t) {
				if (element > t->getData()) {
					t->changeBf(-1);
					t = t->getRightChildNode();
				}
				else if (element < t->getData()) {
					t->changeBf(1);
					t = t->getLeftChildNode();
				}
				else return;
			}
			return;
		}
		else {
			//insert element
			if (element < insertPos->getData()) insertPos->setLeftChildNode(newNode));
			else if (element > insertPos->getData()) insertPos->setRightChildNode(newNode));

			//find the tmp's nearest ancestor
			AVLTreeNode<T>* ancestor = NULL;
			t = root;
			while (t) {
				if (t == tmp) break;
				ancestor = t;
				if (element < t->getData()) t = t->getLeftChildNode();
				else t = t->getRightChildNode();
			}

			//LL&LR
			if (tmp->getBf() == 1)
			{
				//LL
				if ((insertPos->getData() < tmp->getData()) &&						
					(element < tmp->getLeftChildNode()->getData()))
				{
					//tmp is at the left side of it's ancestor
					if (tmp->getData() < ancestor->getData()) 
					{
						ancestor->setLeftChildNode(tmp->getLeftChildNode());
						tmp->setLeftChildNode(ancestor->getLeftChildNode()->getRightChildNode());
						ancestor->getLeftChildNode()->setRightChildNode(tmp);
						tmp->changeBf(0);
						ancestor->getLeftChildNode(0);
					}
					//tmp is at the right side of it's ancestor
					else 
					{
						ancestor->setRightChildNode(tmp->getLeftChildNode());
						tmp->setLeftChildNode(ancestor->getRightChildNode()->getRightChildNode());
						ancestor->getRightChildNode()->setRightChildNode(tmp);
					}
					return;
				}
				//LR
				else if ((insertPos->getData() < tmp->getData()) &&
						 (element > tmp->getLeftChildNode()->getData()))
				{
					int dl = recursiveGetDepth(tmp->getLeftChildNode()->getRightChildNode()->getLeftChildNode());
					int dr = recursiveGetDepth(tmp->getLeftChildNode()->getRightChildNode()->getRightChildNode());
					int cbf = dl - dr;
					tmp->getLeftChildNode()->getRightChildNode()->changeBf(cbf);

					if (tmp->getData() < ancestor->getData()) {
						ancestor->setLeftChildNode(tmp->getLeftChildNode()->getRightChildNode());
						tmp->getLeftChildNode()->setRightChildNode(ancestor->getLeftChildNode()->getLeftChildNode());
						ancestor->getLeftChildNode()->setLeftChildNode(tmp->getLeftChildNode());
						tmp->setLeftChildNode(ancestor->getLeftChildNode()->getRightChildNode());
						ancestor->getLeftChildNode()->setRightChildNode(tmp);

						if (cbf == 0) {
							ancestor->getLeftChildNode()->getLeftChildNode()->changeBf(0);
							ancestor->getLeftChildNode()->getRightChildNode()->changeBf(0);
						}
						else if (cbf == 1) {
							ancestor->getLeftChildNode()->getLeftChildNode()->changeBf(0);
							ancestor->getLeftChildNode()->getRightChildNode()->changeBf(-1);
						}
						else if (cbf == -1) {
							ancestor->getLeftChildNode()->getLeftChildNode()->changeBf(1);
							ancestor->getLeftChildNode()->getRightChildNode()->changeBf(0);
						}
					}
					else {
						ancestor->setRightChildNode(tmp->getLeftChildNode()->getRightChildNode());
						tmp->getLeftChildNode()->setRightChildNode(ancestor->getRightChildNode()->getLeftChildNode());
						ancestor->getRightChildNode()->setLeftChildNode(tmp->getLeftChildNode());
						tmp->setLeftChildNode(ancestor->getRightChildNode()->getRightChildNode());
						ancestor->getRightChildNode()->setRightChildNode(tmp);

						if (cbf == 0) {
							ancestor->getRightChildNode()->getLeftChildNode()->changeBf(0);
							ancestor->getRightChildNode()->getRightChildNode()->changeBf(0);
						}
						else if (cbf == 1) {
							ancestor->getRightChildNode()->getLeftChildNode()->changeBf(0);
							ancestor->getRightChildNode()->getRightChildNode()->changeBf(-1);
						}
						else if (cbf == -1) {
							ancestor->getRightChildNode()->getLeftChildNode()->changeBf(1);
							ancestor->getRightChildNode()->getRightChildNode()->changeBf(0);
						}
					}
					return;
				}
				//don't change the stability
				else if ((insertPos->getData() > tmp->getData())) {
					t = tmp;
					while (t) {
						if (element > t->getData()) {
							t->changeBf(t->getBf() - 1);
							t = t->getRightChildNode();
						}
						else if (element < t->getData()) {
							t->changeBf(t->getBf() + 1);
							t = t->getLeftChildNode();
						}
						else return;
					}
					return;

				}
			}
			//RL&RR
			else if (tmp->getBf() == -1) {

			}
		}

	}
}