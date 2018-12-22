#pragma once

#ifndef STRING_H
#define STRING_H
#include <string>
using std::string;
#endif // !STRING_H

#ifndef STLQUEUE
#define STLQUEUE
#include <queue>
using std::queue;
#endif // !STLQUEUE

namespace dataStructure {

	template <class T>
	class binaryTreeNode {
	private:
		T data;
		binaryTreeNode<T>* leftChildNode;
		binaryTreeNode<T>* rightChildNode;
	public:
		binaryTreeNode(const T& dat);
		binaryTreeNode(const T& dat, binaryTreeNode<T>* l, binaryTreeNode<T>* r);
		void setLeft(binaryTreeNode<T>* node) { leftChildNode = node; };
		void setRight(binaryTreeNode<T>* node) { rightChildNode = node; };
		void setData(const T& dat) { data = dat; };
		binaryTreeNode<T>* getLeft() { return leftChildNode; };
		binaryTreeNode<T>* getRight() { return rightChildNode; };
		T& getData() { return data; };
	};

	template <class T>
	class binaryTree {
	private:
		binaryTreeNode<T>* root;
		binaryTreeNode<T>* recursiveMakeTree(T* inOrder, T* preOrder, size_t length, size_t inLeft, size_t preLeft);
		size_t recursiveGetDepth(binaryTreeNode<T>* t);
	protected:
		binaryTreeNode<T>* getRoot() { return root; };
		void setNullRoot(binaryTreeNode<T>* node) {
			if (root) throw badInput();
			root = node;
		}
		const char* badInput();
	public:
		binaryTree() { root = NULL; };
		bool empty() { return (root == NULL); };
		void makeTree(T* inOrder, T* preOrder, size_t length);
		//void preOrder();
		//void inOrder();
		//void postOrder();
		//void levelOrder();
		size_t depth();
	};

	template <class T>
	dataStructure::binaryTreeNode<T>::binaryTreeNode(const T& dat) {
		data = dat;
		leftChildNode = NULL;
		rightChildNode = NULL;
	}

	template <class T>
	dataStructure::binaryTreeNode<T>::binaryTreeNode(const T& dat, binaryTreeNode<T>* l, binaryTreeNode<T>* r) {
		leftChildNode = l;
		rightChildNode = r;
		data = dat;
	}


	//binaryTree implement
	template <class T>
	binaryTreeNode<T>* binaryTree<T>::recursiveMakeTree(T* inOrder, T* preOrder, size_t length, size_t inLeft, size_t preLeft) {
		//if (inOrder.size() != preOrder.size()) throw badInput();
		//size_t nodeNum = inOrder.size();
		size_t nodeNum = length;
		//	size_t root_index = inOrder.find(preOrder.at(0));
		size_t root_index = inLeft;
		for (size_t i = inLeft; i < length; i++) {
			if (inOrder[i] == preOrder[preLeft]) {
				root_index = i;
				break;
			}
		}
		//	if (root_index == string::npos) throw badInput();

		binaryTreeNode<T>* root = new binaryTreeNode<T>(preOrder[preLeft]);
		//	if (root_index > 0) root->setLeftChildNode(recursiveMakeTree(inOrder.substr(0, root_index), preOrder.substr(1, root_index)));
		if (root_index > inLeft) root->setLeft(recursiveMakeTree(inOrder, preOrder, root_index - inLeft, inLeft, preLeft + 1));
		//	if (root_index + 1 < nodeNum) root->setRightChildNode(recursiveMakeTree(inOrder.substr(root_index + 1, nodeNum - root_index), preOrder.substr(root_index + 1, nodeNum - root_index - 1)));
		if (root_index + 1 < nodeNum) root->setRight(recursiveMakeTree(inOrder, preOrder, nodeNum - root_index + inLeft - 1, root_index + 1, preLeft + root_index + 1));
		return root;
	}

	template <class T>
	const char* binaryTree<T>::badInput() {
		char s[] = "Wrong Input!";
		std::cout << s;
		return s;
	}

	template <class T>
	void binaryTree<T>::makeTree(T* inOrder, T* preOrder, size_t length) {
		root = recursiveMakeTree(inOrder, preOrder, length, 0, 0);
	}

	template <class T>
	size_t binaryTree<T>::recursiveGetDepth(binaryTreeNode<T>* t) {
		if (t == NULL) return 0;
		size_t dl = recursiveGetDepth(t->getLeft());
		size_t dr = recursiveGetDepth(t->getRight());
		if (dl > dr) return ++dl;
		else return ++dr;
	}

	template <class T>
	size_t binaryTree<T>::depth() {
		return recursiveGetDepth(root);
	}
}