//#include <bits/stdc++.h>
//#include <windows.h>  
//
//using std::cin;
//using std::cout;
//using std::endl;
//using std::string;
//using std::vector;
//
//
//template <class T>
//class binaryTreeNode {
//private:
//	T data;
//	binaryTreeNode<T>* leftChildNode;
//	binaryTreeNode<T>* rightChildNode;
//public:
//	binaryTreeNode(T dat);
//	binaryTreeNode(T dat, binaryTreeNode<T>* l, binaryTreeNode<T>* r);
//	void setLeft(binaryTreeNode<T>* node) { leftChildNode = node; };
//	void setRight(binaryTreeNode<T>* node) { rightChildNode = node; };
//	void setData(T dat) { data = dat; };
//	binaryTreeNode<T>* getLeft() { return leftChildNode; };
//	binaryTreeNode<T>* getRight() { return rightChildNode; };
//	T& getData() { return data; };
//};
//
//template <class T>
//binaryTreeNode<T>::binaryTreeNode(T dat) {
//	data = dat;
//	leftChildNode = NULL;
//	rightChildNode = NULL;
//}
//
//template <class T>
//binaryTreeNode<T>::binaryTreeNode(T dat, binaryTreeNode<T>* l, binaryTreeNode<T>* r) {
//	leftChildNode = l;
//	rightChildNode = r;
//	data = dat;
//}
//
//template <class T>
//class binarySearchTree {
//private:
//	binaryTreeNode<T>* root;
//public:
//	binarySearchTree() {
//		root = NULL;
//	};
//	binaryTreeNode<T>* search(const T& theKey);
//	inline void insert(const T& theKey);
//	inline void erase(const T& theKey);
//};
//
//template <class T>
//binaryTreeNode<T>* binarySearchTree<T>::search(const T& thekey) {
//	binaryTreeNode<T>* temp = root;
//	while (true) {
//		if (temp == NULL) return NULL;
//		else if (thekey == temp->getData()) return temp;
//		else if (thekey < temp->getData()) temp = temp->getLeft();
//		else if (thekey > temp->getData()) temp = temp->getRight();
//	}
//}
//
//template <class T>
//void binarySearchTree<T>::insert(const T& theKey) {
//	binaryTreeNode<T>* tmp = root;
//	binaryTreeNode<T>* target = NULL;
//	while (tmp) {
//		target = tmp;
//		if (theKey < tmp->getData()) tmp = tmp->getLeft();
//		else if (theKey > tmp->getData()) tmp = tmp->getRight();
//		else return;
//	}
//
//	binaryTreeNode<T>* newNode = new binaryTreeNode<T>(theKey);
//	if (root) {
//		if (theKey < target->getData()) target->setLeft(newNode);
//		else target->setRight(newNode);
//	}
//	else root = newNode;
//	return;
//}
//
//template <class T>
//void binarySearchTree<T>::erase(const T& theKey) {
//	if (root == NULL) return;
//	if (root->getLeft() == NULL && root->getRight() == NULL && root->getData() == theKey) {
//		delete root;
//		root = NULL;
//		return;
//	}
//	binaryTreeNode<T>* t = root;
//	binaryTreeNode<T>* ancestor = NULL;
//	while (t) {
//		if (t->getData() == theKey) {
//			break;
//		}
//		ancestor = t;
//		if (t->getData() < theKey) {
//			t = t->getRight();
//		}
//		else if (t->getData() > theKey) {
//			t = t->getLeft();
//		}
//	}
//	if (t == NULL) return;
//
//	if (t->getLeft() && t->getRight()) {
//		binaryTreeNode<T>* s = t->getLeft();
//		binaryTreeNode<T>* ps = t;
//
//		while (s->getRight()) {
//			ps = s;
//			s = s->getRight();
//		}
//
//		binaryTreeNode<T>* q = new binaryTreeNode<T>(s->getData());
//		q->setLeft(t->getLeft());
//		q->setRight(t->getRight());
//
//		if (ancestor == NULL) {
//			root = q;
//		}
//		else if (ancestor->getLeft() && t->getData() == ancestor->getLeft()->getData()) {
//			ancestor->setLeft(q);
//		}
//		else {
//			ancestor->setRight(q);
//		}
//
//		if (ps->getData() == t->getData()) ancestor = q;
//		else ancestor = ps;
//
//		delete t;
//		t = s;
//	}
//
//	binaryTreeNode<T>* c = NULL;
//	if (t->getLeft()) c = t->getLeft();
//	else c = t->getRight();
//
//	if (t->getData() == root->getData()) root = c;
//	else {
//		if (t == ancestor->getLeft()) {
//			ancestor->setLeft(c);
//		}
//		else ancestor->setRight(c);
//	}
//	delete t;
//}
//
//int* generateArray(int size, int order, int swaptimes = -1) {
//	int* n = new int[size];
//	if (swaptimes == -1) swaptimes = size / 2;
//	if (order == 1) {
//		for (int i = 0; i < size; i++) {
//			n[i] = i + 1;
//		}
//	}
//	else if (order == -1) {
//		for (int i = 0; i < size; i++) {
//			n[i] = size - i;
//		}
//	}
//
//	srand(time(NULL));
//	for (int i = 0; i < swaptimes; i++) {
//		int x = rand() % size;
//		int y = rand() % size;
//		std::swap(n[x], n[y]);
//	}
//
//	return n;
//}
//
//int main() {
//	int n;
//	cin >> n;
//	int* arr = generateArray(n, 1, 0);
//	//int arr[] = { 7, 2, 5, 9, 1, 8, 10, 6, 4, 3 };
////	for (int i = 0; i < n; i++) cout << arr[i] << ' ';
//	cout << endl;
//	binarySearchTree<int> avl;
//	LARGE_INTEGER t1, t2, tc;
//	QueryPerformanceFrequency(&tc);
//	QueryPerformanceCounter(&t1);
//	for (int i = 0; i < n; i++) {
//		avl.insert(arr[i]);
//	}
//	QueryPerformanceCounter(&t2);
//	cout << "AVLTree insert n = " << n << " time " << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
//	QueryPerformanceFrequency(&tc);
//	QueryPerformanceCounter(&t1);
//	for (int i = 0; i < n; i++) {
//		avl.erase(arr[i]);
//	}
//	QueryPerformanceCounter(&t2);
//	cout << "AVLTree delete n = " << n << " time " << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
//	system("pause");
//	return 0;
//}