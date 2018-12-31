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
	class binarySearchTree {
	private:
		binaryTreeNode<T>* root;
	public:
		binarySearchTree(){ 
			root = NULL;
		};
		binaryTreeNode<T>* search(const T& theKey);
		inline void insert(const T& theKey);
		inline void erase(const T& theKey);
	};

	template <class T>
	binaryTreeNode<T>* binarySearchTree<T>::search(const T& thekey) {
		binaryTreeNode<T>* temp = root;
		while (true) {
			if (temp == NULL) return NULL;
			else if (thekey == temp->getData()) return temp;
			else if (thekey < temp->getData()) temp = temp->getLeft();
			else if (thekey > temp->getData()) temp = temp->getRight();
		}
	}

	template <class T>
	void binarySearchTree<T>::insert(const T& theKey) {
		binaryTreeNode<T>* tmp = root;
		binaryTreeNode<T>* target = NULL;
		while (tmp) {
			target = tmp;
			if (theKey < tmp->getData()) tmp = tmp->getLeft();
			else if (theKey > tmp->getData()) tmp = tmp->getRight();
			else return;
		}

		binaryTreeNode<T>* newNode = new binaryTreeNode<T>(theKey);
		if (root) {
			if (theKey < target->getData()) target->setLeft(newNode);
			else target->setRight(newNode);
		}
		else root = newNode;
		return;
	}

	template <class T>
	void binarySearchTree<T>::erase(const T& theKey) {
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
			else if(t->getData() > theKey){
				t = t->getLeft();
			}
		}
		if (t == NULL) return;

		if (t->getLeft() && t->getRight()) {
			binaryTreeNode<T>* s = t->getLeft();
			binaryTreeNode<T>* ps = t;

			while (s->getRight()) {
				ps = s;
				s = s->getRight();
			}

			binaryTreeNode<T>* q = new binaryTreeNode<T>(s->getData());
			q->setLeft(t->getLeft());
			q->setRight(t->getRight());

			if (ancestor == NULL) {
				root = q;
			}
			else if (ancestor->getLeft() && t->getData() == ancestor->getLeft()->getData()) {
				ancestor->setLeft(q);
			}
			else {
				ancestor->setRight(q);
			}

			if (ps->getData() == t->getData()) ancestor = q;
			else ancestor = ps;

			delete t;
			t = s;
		}

		binaryTreeNode<T>* c = NULL;
		if (t->getLeft()) c = t->getLeft();
		else c = t->getRight();

		if (t->getData() == root->getData()) root = c;
		else {
			if (t == ancestor->getLeft()) {
				ancestor->setLeft(c);
			}
			else ancestor->setRight(c);
		}
		delete t;
	}
}