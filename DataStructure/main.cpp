#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class binaryTreeNode {
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



class binaryTree {
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


binaryTreeNode* binaryTree::recursiveMakeTree(string inOrder, string preOrder) {
	if (inOrder.size() != preOrder.size()) throw badInput();
	size_t nodeNum = inOrder.size();

	size_t root_index = inOrder.find(preOrder.at(0));
	if (root_index == string::npos) throw badInput();

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

int main() {
	binaryTree tree;
	string a, b;
	cin >> a >> b;
	tree.makeTree(b, a);
	cout << tree.depth();
	system("pause");
	return 0;
}