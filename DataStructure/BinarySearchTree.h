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
		//	void deleteNode(T& theKey);
		//	void ascent();
	};

	template <class T>
	binaryTreeNode<T>* binarySearchTree<T>::search(const T& thekey) {
		binaryTreeNode<T>* temp = binaryTree<T>::getRoot();
		while (true) {
			if (temp == NULL) return NULL;
			else if (thekey == temp->getData()) return temp;
			else if (thekey < temp->getData()) temp = temp->getLeftChildNode();
			else if (thekey > temp->getData()) temp = temp->getRightChildNode();
		}
	}

	template <class T>
	void binarySearchTree<T>::insert(const T& theKey) {
		binaryTreeNode<T>* tmp = binaryTree<T>::getRoot();
		binaryTreeNode<T>* target = NULL;
		while (tmp) {
			target = tmp;
			if (theKey < tmp->getData()) tmp = tmp->getLeftChildNode();
			else if (theKey > tmp->getData()) tmp = tmp->getRightChildNode();
			else throw binaryTree<T>::badInput();
		}

		binaryTreeNode<T>* newNode = new binaryTreeNode<T>(theKey);
		if (binaryTree<T>::getRoot()) {
			if (theKey < target->getData()) target->setLeftChildNode(newNode);
			else target->setRightChildNode(newNode);
		}
		else binaryTree<T>::setNullRoot(newNode);
		return;
	}
}