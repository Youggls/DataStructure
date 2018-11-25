#pragma once

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "binaryTree.h"
using dataStructure::binaryTreeNode;
#endif // !BINARYTREE_H


namespace dataStructure {
	template <class T>
	class AVLTreeNode:public binaryTreeNode<T> {
	private:
		int bf;
	public:
		AVLTreeNode(const T& dat) :binaryTreeNode<T>::binaryTreeNode(dat) {
			bf = 0;
		}
	};
	template <class T>
	class AVLTree {
	private:
		AVLTreeNode<T>* root;
		size_t num;
	public:
		AVLTree();
		AVLTree();
		void insert(const T& element);
	};

	template <class T>
	AVLTree<T>::AVLTree() {
		root = NULL;
		num = 0;
	}

	template <class T>
	void AVLTree<T>::insert(const T& element) {
		AVLTreeNode<T>* newNode = new AVLTreeNode<T>(element);
		if (root == NULL) {
			root = newNode;
			return;
		}

	}
}