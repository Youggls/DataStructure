#pragma once
#include <iostream>
using std::string;

namespace dataStructure {
	class binaryTree;
	class binaryTreeNode;
	class hashTable;
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

class dataStructure::binaryTreeNode {
private:
	char data;
	binaryTreeNode* leftChildNode;
	binaryTreeNode* rightChildNode;
public:
	binaryTreeNode(const char& dat);
	binaryTreeNode(const char& dat, binaryTreeNode* l, binaryTreeNode* r);
	void setLeftChildNode(binaryTreeNode* node) { leftChildNode = node; };
	void setRightChildNode(binaryTreeNode* node) { rightChildNode = node; };
	binaryTreeNode* getLeftChildNode() { return leftChildNode; };
	binaryTreeNode* getRightChildNode() { return rightChildNode; };
	const char getData() { return data; };
};



class dataStructure::binaryTree {
private:
	binaryTreeNode* root;
	binaryTreeNode* recursiveMakeTree(string inOrder, string preOrder);
	size_t recursiveGetDepth(binaryTreeNode* t);
	const char* badInput();
public:
	binaryTree() { root = NULL; };
	bool isEmpty() { return (root == NULL); };
	void makeTree(string& inOrder, string& preOrder);
	size_t depth();
};