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
	class binarySearchTree;
}

using dataStructure::binarySearchTree;

template <class T>
class dataStructure::binarySearchTree : public binaryTree<T> {
public:
	binarySearchTree() :binaryTree<T>::binaryTree() { };
//	void makeTree(string& inOrder, string& preOrder);
//	binaryTreeNode<T>* search(T& theKey);
//	void insert(T& theKey);
//	void deleteNode(T& theKey);
//	void ascent();
};