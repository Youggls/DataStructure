#include <windows.h>  
#include "DataStructure.hpp"
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using dataStructure::binarySearchTree;
using dataStructure::AVLTree;
using dataStructure::BTree;
using dataStructure::RBTree;
using dataStructure::generateArray;

int main() {
	fstream bstData;
	fstream avlData;
	fstream btData;
	fstream rbtData;
	bstData.open("D:/Project/C++poj/DataStructure/bstData.txt", ios::app);
	avlData.open("D:/Project/C++poj/DataStructure/avlData.txt", ios::app);
	btData.open("D:/Project/C++poj/DataStructure/btData.txt", ios::app);
	rbtData.open("D:/Project/C++poj/DataStructure/rbtData.txt", ios::app);
	int max = 10000;
	//Order insert and delete
	bstData << "sitiuation1, size from 1000 to 100000" << endl;
	avlData << "sitiuation1, size from 1000 to 100000" << endl;
	btData << "sitiuation1, size from 1000 to 100000" << endl;
	rbtData << "sitiuation1, size from 1000 to 100000" << endl;
	cout << "sitiuation1, size from 1000 to 100000" << endl;
	for (int size = 1000; size <= 100000; size += 1000) {
		cout << "sitiuation1, size : " << size << endl;
		int* arr = generateArray(size, 1, 0);
		binarySearchTree<int> bst;
		AVLTree<int> avl;
		BTree<int> bt(4);
		RBTree<int> rbt;
		LARGE_INTEGER t1, t2, tc;
		//bst insert and delete
		bstData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) 
			bst.insert(arr[i]);
		QueryPerformanceCounter(&t2);
		bstData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) bst.erase(arr[i]);
		QueryPerformanceCounter(&t2);
		bstData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		//avl
		avlData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) avl.insert(arr[i]);
		QueryPerformanceCounter(&t2);
		avlData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) avl.erase(arr[i]);
		QueryPerformanceCounter(&t2);
		avlData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		//btree
		btData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) bt.insert(arr[i]);
		QueryPerformanceCounter(&t2);
		btData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) bt.erase(arr[i]);
		QueryPerformanceCounter(&t2);
		btData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		//rbt
		rbtData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) rbt.insert(arr[i]);
		QueryPerformanceCounter(&t2);
		rbtData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) rbt.erase(arr[i]);
		QueryPerformanceCounter(&t2);
		rbtData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		delete arr;
	}
	//Order insert and reverse order delete
	bstData << "sitiuation2, size from 1000 to 100000" << endl;
	avlData << "sitiuation2, size from 1000 to 100000" << endl;
	btData << "sitiuation2, size from 1000 to 100000" << endl;
	rbtData << "sitiuation2, size from 1000 to 100000" << endl;
	cout << "sitiuation2, size from 1000 to 100000" << endl;
	for (int size = 1000; size <= 100000; size += 1000) {
		cout << "sitiuation2, size : " << size << endl;
		int* arr = generateArray(size, 1, 0);
		binarySearchTree<int> bst;
		AVLTree<int> avl;
		BTree<int> bt(4);
		RBTree<int> rbt;
		LARGE_INTEGER t1, t2, tc;
		//bst insert and delete
		bstData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) bst.insert(arr[i]);
		QueryPerformanceCounter(&t2);
		bstData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = size - 1; i >= 0; i--) bst.erase(arr[i]);
		QueryPerformanceCounter(&t2);
		bstData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		//avl
		avlData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) avl.insert(arr[i]);
		QueryPerformanceCounter(&t2);
		avlData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = size - 1; i >= 0; i--) avl.erase(arr[i]);
		QueryPerformanceCounter(&t2);
		avlData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		//btree
		btData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) bt.insert(arr[i]);
		QueryPerformanceCounter(&t2);
		btData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = size - 1; i >= 0; i--) bt.erase(arr[i]);
		QueryPerformanceCounter(&t2);
		btData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		//rbt
		rbtData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) rbt.insert(arr[i]);
		QueryPerformanceCounter(&t2);
		rbtData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = size - 1; i >= 0; i--) rbt.erase(arr[i]);
		QueryPerformanceCounter(&t2);
		rbtData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		delete arr;
	}
	//Ramdom insert and delete
	bstData << "sitiuation3, size from 1000 to 100000" << endl;
	avlData << "sitiuation3, size from 1000 to 100000" << endl;
	btData << "sitiuation3, size from 1000 to 100000" << endl;
	rbtData << "sitiuation3, size from 1000 to 100000" << endl;
	cout << "sitiuation2, size from 1000 to 100000" << endl;
	for (int size = 1000; size <= 100000; size += 1000) {
		cout << "sitiuation3, size : " << size << endl;
		int* insertArr = generateArray(size, 1);
		int* eraseArr = generateArray(size, 1);
		binarySearchTree<int> bst;
		AVLTree<int> avl;
		BTree<int> bt(4);
		RBTree<int> rbt;
		LARGE_INTEGER t1, t2, tc;
		//bst insert and delete
		bstData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) bst.insert(insertArr[i]);
		QueryPerformanceCounter(&t2);
		bstData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) bst.erase(eraseArr[i]);
		QueryPerformanceCounter(&t2);
		bstData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		//avl
		avlData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) avl.insert(insertArr[i]);
		QueryPerformanceCounter(&t2);
		avlData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) avl.erase(eraseArr[i]);
		QueryPerformanceCounter(&t2);
		avlData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		//btree
		btData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) bt.insert(insertArr[i]);
		QueryPerformanceCounter(&t2);
		btData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) bt.erase(eraseArr[i]);
		QueryPerformanceCounter(&t2);
		btData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		//rbt
		rbtData << size << ' ';
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) rbt.insert(insertArr[i]);
		QueryPerformanceCounter(&t2);
		rbtData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << ' ';

		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);
		for (int i = 0; i < size; i++) rbt.erase(eraseArr[i]);
		QueryPerformanceCounter(&t2);
		rbtData << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
		delete insertArr;
		delete eraseArr;
	}
	system("pause");
	return 0;
}
