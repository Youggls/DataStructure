#pragma once

#ifndef STRING_H
#define STRING_H
#include <string>
using std::string;
#endif // !STRING_H

namespace dataStructure {
	template <class T>
	class binaryTreeNode;
	template <class T>
	class binaryTree;
}
using dataStructure::binaryTree;
using dataStructure::binaryTreeNode;

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

template <class T>
dataStructure::binaryTreeNode<T>::binaryTreeNode(const char& dat) {
	data = dat;
	leftChildNode = NULL;
	rightChildNode = NULL;
}

template <class T>
dataStructure::binaryTreeNode<T>::binaryTreeNode(const char& dat, binaryTreeNode<T>* l, binaryTreeNode<T>* r) {
	leftChildNode = l;
	rightChildNode = r;
	data = dat;
}


//binaryTree implement
template <class T>
binaryTreeNode<T>* binaryTree<T>::recursiveMakeTree(string inOrder, string preOrder) {
	if (inOrder.size() != preOrder.size()) throw badInput();
	size_t nodeNum = inOrder.size();

	size_t root_index = inOrder.find(preOrder.at(0));
	//	if (root_index == string::npos) throw badInput();

	binaryTreeNode<T>* root = new binaryTreeNode<T>(preOrder.at(0));
	if (root_index > 0) root->setLeftChildNode(recursiveMakeTree(inOrder.substr(0, root_index), preOrder.substr(1, root_index)));
	if (root_index + 1 < nodeNum) root->setRightChildNode(recursiveMakeTree(inOrder.substr(root_index + 1, nodeNum - root_index), preOrder.substr(root_index + 1, nodeNum - root_index - 1)));
	return root;
}

template <class T>
const char* binaryTree<T>::badInput() {
	char s[] = "Wrong Input!";
	std::cout << s;
	return s;
}

template <class T>
void binaryTree<T>::makeTree(string& inOrder, string& preOrder) {
	root = recursiveMakeTree(inOrder, preOrder);
}

template <class T>
size_t binaryTree<T>::recursiveGetDepth(binaryTreeNode<T>* t) {
	if (t == NULL) return 0;
	size_t dl = recursiveGetDepth(t->getLeftChildNode());
	size_t dr = recursiveGetDepth(t->getRightChildNode());
	if (dl > dr) return ++dl;
	else return ++dr;
}

template <class T>
size_t binaryTree<T>::depth() {
	return recursiveGetDepth(root);
}