#include "DataStructure.h"

//binaryTreeNode inplement
binaryTreeNode::binaryTreeNode(const char& dat) {
	data = dat;
	leftChildNode = NULL;
	rightChildNode = NULL;
}

binaryTreeNode::binaryTreeNode(const char& dat, binaryTreeNode* l, binaryTreeNode* r) {
	leftChildNode = l;
	rightChildNode = r;
	data = dat;
}


//binaryTree implement
binaryTreeNode* binaryTree::recursiveMakeTree(string inOrder, string preOrder) {
	if (inOrder.size() != preOrder.size()) throw badInput();
	size_t nodeNum = inOrder.size();

	size_t root_index = inOrder.find(preOrder.at(0));
//	if (root_index == string::npos) throw badInput();

	binaryTreeNode* root = new binaryTreeNode(preOrder.at(0));
	if (root_index > 0) root->setLeftChildNode(recursiveMakeTree(inOrder.substr(0, root_index), preOrder.substr(1, root_index)));
	if (root_index + 1 < nodeNum) root->setRightChildNode(recursiveMakeTree(inOrder.substr(root_index + 1, nodeNum - root_index), preOrder.substr(root_index + 1, nodeNum - root_index - 1)));
	return root;
}

const char* binaryTree::badInput() {
	char s[] = "Wrong Input!";
	std::cout << s;
	return s;
}

void binaryTree::makeTree(string& inOrder, string& preOrder) {
	root = recursiveMakeTree(inOrder, preOrder);
}

size_t binaryTree::recursiveGetDepth(binaryTreeNode* t) {
	if (t == NULL) return 0;
	size_t dl = recursiveGetDepth(t->getLeftChildNode());
	size_t dr = recursiveGetDepth(t->getRightChildNode());
	if (dl > dr) return ++dl;
	else return ++dr;
}

size_t binaryTree::depth() {
	return recursiveGetDepth(root);
}