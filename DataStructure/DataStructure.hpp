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
	template <class T>
	class maxHeap;
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

template <class T>
binaryTreeNode<T>::binaryTreeNode(const char& dat) {
	data = dat;
	leftChildNode = NULL;
	rightChildNode = NULL;
}

template <class T>
binaryTreeNode<T>::binaryTreeNode(const char& dat, binaryTreeNode<T>* l, binaryTreeNode<T>* r) {
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

template <class T>
class dataStructure::maxHeap {
private:
	T* arr;
	size_t size;
	size_t capacity;
	void shiftUp(size_t index);
//	void shiftDowm(size_t index);
public:
	maxHeap();
//	maxHeap(T* arr, size_t size);
	maxHeap(size_t capacity);
	bool insert(T& element);
	void printWayToRoot(size_t index);
};

template <class T>
maxHeap<T>::maxHeap() {
	arr = NULL;
	size = capacity = 0;
}

template <class T>
maxHeap<T>::maxHeap(size_t cap) {
	capacity = cap;
	arr = new T[capacity + 1];
	size = 0;
}

template <class T>
void maxHeap<T>::shiftUp(size_t index) {
	if (index == 1) return;
	else if (arr[index] > arr[index / 2]) {
		T temp = arr[index / 2];
		arr[index / 2] = arr[index];
		arr[index] = temp;
		shiftUp(index / 2);
	}
	else return;
}

template <class T>
bool maxHeap<T>::insert(T& element) {
	size++;
	arr[size] = element;
	shiftUp(size);
	return true;
}

template <class T>
void maxHeap<T>::printWayToRoot(size_t index) {
	while (index >= 1)
	{
		std::cout << arr[index];
		if (index != 1) std::cout << ' ';
		index /= 2;
	}
	std::cout << std::endl;
}