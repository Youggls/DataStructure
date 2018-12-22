#pragma once

#ifndef STRING_H
#define STRING_H
#include <string>
using std::string;
#endif // !STRING_H
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "binaryTree.h"
using dataStructure::binaryTree;
using dataStructure::binaryTreeNode;
#endif // !BINARYTREE_H

namespace dataStructure {
	template <class T>
	class binarySearchTree : public binaryTree<T> {
	public:
		binarySearchTree() :binaryTree<T>::binaryTree() { };
		//	void makeTree(string& inOrder, string& preOrder);
		binaryTreeNode<T>* search(const T& theKey);
		void insert(const T& theKey);
		void deleteNode(const T& theKey);
		//	void ascent();
	};

	template <class T>
	binaryTreeNode<T>* binarySearchTree<T>::search(const T& thekey) {
		binaryTreeNode<T>* temp = binaryTree<T>::getRoot();
		while (true) {
			if (temp == NULL) return NULL;
			else if (thekey == temp->getData()) return temp;
			else if (thekey < temp->getData()) temp = temp->getLeft();
			else if (thekey > temp->getData()) temp = temp->getRight();
		}
	}

	template <class T>
	void binarySearchTree<T>::insert(const T& theKey) {
		binaryTreeNode<T>* tmp = binaryTree<T>::getRoot();
		binaryTreeNode<T>* target = NULL;
		while (tmp) {
			target = tmp;
			if (theKey < tmp->getData()) tmp = tmp->getLeft();
			else if (theKey > tmp->getData()) tmp = tmp->getRight();
			else throw binaryTree<T>::badInput();
		}

		binaryTreeNode<T>* newNode = new binaryTreeNode<T>(theKey);
		if (binaryTree<T>::getRoot()) {
			if (theKey < target->getData()) target->setLeft(newNode);
			else target->setRight(newNode);
		}
		else binaryTree<T>::setNullRoot(newNode);
		return;
	}

	template <class T>
	void binarySearchTree<T>::deleteNode(const T& theKey) {
		binaryTreeNode<T>* root = binaryTree<T>::getRoot();
		if (root == NULL) return;
		if (root->getLeft() == NULL && root->getRight() == NULL && root->getData() == theKey) {
			delete root;
			root = NULL;
			return;
		}
		binaryTreeNode<T>* t = root;
		binaryTreeNode<T>* ancestor = NULL;
		while (t) {
			if (t->getData() == theKey) {
				break;
			}
			ancestor = t;
			if (t->getData() < theKey) {
				t = t->getRight();
			}
			else {
				t = t->getLeft();
			}
		}
		if (t == NULL) return;


		if (ancestor == NULL) ancestor = root;
		if (t->getLeft() == NULL && t->getRight() == NULL) {
			if (ancestor->getData() > t->getData()) {
				delete t;
				ancestor->setLeft(NULL);
				return;
			}
			else {
				delete t;
				ancestor->setRight(NULL);
				return;
			}
		}
		else if (t->getRight() == NULL && t->getLeft() != NULL) {
			if (ancestor->getData() > t->getData()) {
				ancestor->setLeft(t->getLeft());
				delete t;
				return;
			}
			else {
				ancestor->setRight(t->getLeft());
				delete t;
				return;
			}
		}
		else if (t->getRight() != NULL && t->getLeft() == NULL) {
			if (ancestor->getData() > t->getData()) {
				ancestor->setLeft(t->getRight());
				delete t;
				return;
			}
			else {
				ancestor->setRight(t->getRight());
				delete t;
				return;
			}
		}
		else {
			binaryTreeNode<T>* maxOfLeft = t->getLeft();
			binaryTreeNode<T>* p = t;
			while (maxOfLeft->getRight() != NULL) {
				p = maxOfLeft;
				maxOfLeft = maxOfLeft->getRight();
			}
			t->setData(maxOfLeft->getData());
			delete maxOfLeft;
			p->setLeft(NULL);
			return;
		}
	}
}