#pragma once
#include <iostream>
using std::string;

namespace dataStructure {
	template <class T>
	class binaryTree;
	template <class T>
	class binaryTreeNode;
//	class hashTable;
	template <class T>
	class linkedList;
	template <class T>
	class linkedQueue;
	template <class T>
	class linkedStack;
	template <class T>
	class arrayList;
	template <class T>
	class arrayQueue;
	template <class T>
	class arrayStack;
}

using namespace dataStructure;

template <class T>
class dataStructure::binaryTreeNode {
private:
	T data;
	binaryTreeNode<T>* leftChildNode;
	binaryTreeNode<T>* rightChildNode;
public:
	binaryTreeNode(const char& dat);
	binaryTreeNode(const char& dat, binaryTreeNode<T>* l, binaryTreeNode<T>* r);
	void setLeftChildNode(binaryTreeNode<T>* node) { leftChildNode = node; };
	void setRightChildNode(binaryTreeNode<T>* node) { rightChildNode = node; };
	binaryTreeNode<T>* getLeftChildNode() { return leftChildNode; };
	binaryTreeNode<T>* getRightChildNode() { return rightChildNode; };
	const T getData() { return data; };
};


template <class T>
class dataStructure::binaryTree {
private:
	binaryTreeNode<T>* root;
	binaryTreeNode<T>* recursiveMakeTree(string inOrder, string preOrder);
	size_t recursiveGetDepth(binaryTreeNode<T>* t);
	const char* badInput();
public:
	binaryTree() { root = NULL; };
	bool isEmpty() { return (root == NULL); };
	void makeTree(string& inOrder, string& preOrder);
	size_t depth();
};