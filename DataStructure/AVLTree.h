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
		AVLTreeNode(const T& dat) {
			bf = 0;
			leftChildNode = rightChildNode = NULL;
			data = dat;
		}
		AVLTreeNode<T>* getRightChildNode() { return rightChildNode; };
		AVLTreeNode<T>* getLeftChildNode() { return leftChildNode; };
		void setRightChildNode(AVLTreeNode<T>* node) { rightChildNode = node; };
		void setLeftChildNode(AVLTreeNode<T>* node) { leftChildNode = node; };
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
		void recursivePreOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*));
		void recursiveInOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*));
		void recursivePostOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*));
		//		void recursiveLevelOrder(AVLTree<T>* node, void(*visit)(AVLTreeNode<T>*));
	public:
		AVLTree();
		void insert(const T& element);
		void preOrder(void(*visit)(AVLTreeNode<T>*) = NULL);
		void inOrder(void(*visit)(AVLTreeNode<T>*) = NULL);
		void postOrder(void(*visit)(AVLTreeNode<T>*) = NULL);
		void levelOrder(void(*visit)(AVLTreeNode<T>*) = NULL);
		//		bool isComplete();

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

	template<class T>
	void AVLTree<T>::recursivePreOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*)) {
		if (visit == NULL) {
			if (node) {
				cout << node->getData();
				recursivePreOrder(node->getLeftChildNode(), visit);
				recursivePreOrder(node->getRightChildNode(), visit);
			}
		}
		else {
			if (node) {
				visit(node);
				recursivePreOrder(node->getLeftChildNode(), visit);
				recursivePreOrder(node->getRightChildNode(), visit);
			}
		}
	}

	template <class T>
	void AVLTree<T>::recursiveInOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*)) {
		if (visit == NULL) {
			if (node) {
				recursiveInOrder(node->getLeftChildNode(), visit);
				cout << node->getData();
				recursiveInOrder(node->getRightChildNode(), visit);
			}
		}
		else {
			if (node) {
				recursiveInOrder(node->getLeftChildNode(), visit);
				visit(node);
				recursiveInOrder(node->getRightChildNode(), visit);
			}
		}
	}

	template <class T>
	void AVLTree<T>::recursivePostOrder(AVLTreeNode<T>* node, void(*visit)(AVLTreeNode<T>*)) {
		if (visit == NULL) {
			if (node) {
				recursivePostOrder(node->getLeftChildNode(), visit);
				recursivePostOrder(node->getRightChildNode(), visit);
				cout << node->getData();
			}
		}
		else {
			if (node) {
				recursivePostOrder(node->getLeftChildNode(), visit);
				recursivePostOrder(node->getRightChildNode(), visit);
				visit(node);
			}
		}
	}

	template <class T>
	void AVLTree<T>::levelOrder(void(*visit)(AVLTreeNode<T>*)) {
		if (root == NULL) return;
		queue<AVLTreeNode<T>*> prelist;
		prelist.push(root);
		while (prelist.size() != 0) {
			AVLTreeNode<T>* front = prelist.front();
			if (visit == NULL) cout << front->getData();
			else visit(front);
			prelist.pop();
			if (front->getLeftChildNode() != NULL) prelist.push(front->getLeftChildNode());
			if (front->getRightChildNode() != NULL) prelist.push(front->getRightChildNode());
		}
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
			else if (element < t->getData()) t = t->getLeftChildNode();
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
			if (element < insertPos->getData()) insertPos->setLeftChildNode(newNode);
			else if (element > insertPos->getData()) insertPos->setRightChildNode(newNode);

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
				if ((insertPos->getData() < tmp->getData()) && (element < tmp->getLeftChildNode()->getData())) {
					if (ancestor == NULL) {
						root = tmp->getLeftChildNode();
//						root->setLeftChildNode(tmp->getLeftChildNode()->getRightChildNode());
						tmp->setLeftChildNode(NULL);
						root->setRightChildNode(tmp);
						root->getRightChildNode()->changeBf(0);
						return;
					}
					//tmp is at the left side of it's ancestor
					else if (tmp->getData() < ancestor->getData())
					{
						ancestor->setLeftChildNode(tmp->getLeftChildNode());
						tmp->setLeftChildNode(ancestor->getLeftChildNode()->getRightChildNode());
						ancestor->getLeftChildNode()->setRightChildNode(tmp);
						tmp->changeBf(0);
						ancestor->getLeftChildNode()->changeBf(0);
					}
					//tmp is at the right side of it's ancestor
					else
					{
						ancestor->setRightChildNode(tmp->getLeftChildNode());
						tmp->setLeftChildNode(ancestor->getRightChildNode()->getRightChildNode());
						ancestor->getRightChildNode()->setRightChildNode(tmp);
						tmp->changeBf(0);
						ancestor->getLeftChildNode()->changeBf(0);
					}
					return;
				}
				//LR
				else if ((insertPos->getData() < tmp->getData()) && (element > tmp->getLeftChildNode()->getData())) {
					int dl = recursiveGetDepth(tmp->getLeftChildNode()->getRightChildNode()->getLeftChildNode());
					int dr = recursiveGetDepth(tmp->getLeftChildNode()->getRightChildNode()->getRightChildNode());
					int cbf = dl - dr;
					tmp->getLeftChildNode()->getRightChildNode()->changeBf(cbf);

					if (ancestor == NULL) {
						root = tmp->getLeftChildNode()->getRightChildNode();
						tmp->getLeftChildNode()->setRightChildNode(NULL);
						root->setLeftChildNode(tmp->getLeftChildNode());
						tmp->setLeftChildNode(NULL);
						root->setRightChildNode(tmp);
						root->getRightChildNode()->changeBf(0);
						return;
					}
					else if (tmp->getData() < ancestor->getData()) {
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
				//RR
				if ((insertPos->getData() > tmp->getData()) &&
					(element > tmp->getRightChildNode()->getData())) {
					if (ancestor == NULL) {
						root = tmp->getRightChildNode();
						tmp->setRightChildNode(NULL);
						root->setLeftChildNode(tmp);
						root->getLeftChildNode()->changeBf(0);
						return;
					}
					else if (tmp->getData() < ancestor->getData()) {
						ancestor->setLeftChildNode(tmp->getRightChildNode());
						tmp->setRightChildNode(ancestor->getLeftChildNode()->getLeftChildNode());
						ancestor->getLeftChildNode()->setLeftChildNode(tmp);
						tmp->changeBf(0);
						ancestor->getLeftChildNode()->changeBf(0);
					}
					else if (tmp->getData() > ancestor->getData()) {
						ancestor->setRightChildNode(tmp->getRightChildNode());
						tmp->setRightChildNode(ancestor->getRightChildNode()->getLeftChildNode());
						ancestor->getRightChildNode()->setLeftChildNode(tmp);
						tmp->changeBf(0);
						ancestor->getRightChildNode()->changeBf(0);
					}
				}
				//RL
				else if ((insertPos->getData() > tmp->getData()) && (element < tmp->getRightChildNode()->getData())) {
					int dl = recursiveGetDepth(tmp->getRightChildNode()->getLeftChildNode()->getLeftChildNode());
					int dr = recursiveGetDepth(tmp->getRightChildNode()->getLeftChildNode()->getRightChildNode());
					int cbf = dl - dr;
					if (ancestor == NULL) {
						root = tmp->getRightChildNode()->getLeftChildNode();
						tmp->getRightChildNode()->setLeftChildNode(NULL);
						root->setRightChildNode(tmp->getRightChildNode());
						tmp->setRightChildNode(NULL);
						root->setLeftChildNode(tmp);
						root->getLeftChildNode()->changeBf(0);
						return;
					}
					else if (tmp->getData() < ancestor->getData()) {
						ancestor->setLeftChildNode(tmp->getRightChildNode()->getLeftChildNode());
						tmp->getRightChildNode()->setLeftChildNode(ancestor->getLeftChildNode()->getRightChildNode());
						ancestor->getLeftChildNode()->setRightChildNode(tmp->getRightChildNode());
						tmp->setRightChildNode(ancestor->getLeftChildNode()->getLeftChildNode());
						ancestor->getLeftChildNode()->setLeftChildNode(tmp);

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
					else if (tmp->getData() > ancestor->getData()) {
						ancestor->setRightChildNode(tmp->getRightChildNode()->getLeftChildNode());
						tmp->getRightChildNode()->setLeftChildNode(ancestor->getRightChildNode()->getRightChildNode());
						ancestor->getRightChildNode()->setRightChildNode(tmp->getRightChildNode());
						tmp->setRightChildNode(ancestor->getRightChildNode()->getLeftChildNode());
						ancestor->getRightChildNode()->setLeftChildNode(tmp);

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
				}
				else {
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
		}

	}
}