#define BLACK 1
#define RED 0
#include <iostream>

using namespace std;

namespace dataStructure {
	template <class T>
	class RBTree {
	private:

		template <class T>
		class RBTreeNode {
		public:
			T value;
			bool color;
			RBTreeNode<T> *leftTree, *rightTree, *parent;

			RBTreeNode() : value(0), color(RED), leftTree(NULL), rightTree(NULL), parent(NULL) { 

			}

			RBTreeNode<T>* grandparent() {
				if (parent == NULL) {
					return NULL;
				}
				return parent->parent;
			}

			RBTreeNode<T>* uncle() {
				if (grandparent() == NULL) {
					return NULL;
				}
				if (parent == grandparent()->rightTree)
					return grandparent()->leftTree;
				else
					return grandparent()->rightTree;
			}

			RBTreeNode<T>* sibling() {
				if (parent->leftTree == this)
					return parent->rightTree;
				else
					return parent->leftTree;
			}
		};

		void rotate_right(RBTreeNode<T> *p) {
			RBTreeNode<T> *gp = p->grandparent();
			RBTreeNode<T> *fa = p->parent;
			RBTreeNode<T> *y = p->rightTree;

			fa->leftTree = y;

			if (y != NIL)
				y->parent = fa;
			p->rightTree = fa;
			fa->parent = p;

			if (root == fa)
				root = p;
			p->parent = gp;

			if (gp != NULL) {
				if (gp->leftTree == fa)
					gp->leftTree = p;
				else
					gp->rightTree = p;
			}

		}

		void rotate_left(RBTreeNode<T> *p) {
			if (p->parent == NULL) {
				root = p;
				return;
			}
			RBTreeNode<T> *gp = p->grandparent();
			RBTreeNode<T> *fa = p->parent;
			RBTreeNode<T> *y = p->leftTree;

			fa->rightTree = y;

			if (y != NIL)
				y->parent = fa;
			p->leftTree = fa;
			fa->parent = p;

			if (root == fa)
				root = p;
			p->parent = gp;

			if (gp != NULL) {
				if (gp->leftTree == fa)
					gp->leftTree = p;
				else
					gp->rightTree = p;
			}
		}

		void inorder(RBTreeNode<T> *p) {
			if (p == NIL)
				return;
			cout << p->value << '(';
			if (p->color == RED) cout << 'R';
			else cout << 'B';
			cout << ')';
			cout << ' ';

			if (p->leftTree)
				inorder(p->leftTree);


			if (p->rightTree)
				inorder(p->rightTree);
		}

		string outputColor(bool color) {
			return color ? "BLACK" : "RED";
		}

		RBTreeNode<T>* getSmallestChild(RBTreeNode<T> *p) {
			if (p->leftTree == NIL)
				return p;
			return getSmallestChild(p->leftTree);
		}

		bool delete_child(RBTreeNode<T> *p, T data) {
			if (p->value > data) {
				if (p->leftTree == NIL) {
					return false;
				}
				return delete_child(p->leftTree, data);
			}
			else if (p->value < data) {
				if (p->rightTree == NIL) {
					return false;
				}
				return delete_child(p->rightTree, data);
			}
			else if (p->value == data) {
				if (p->rightTree == NIL) {
					delete_one_child(p);
					return true;
				}
				RBTreeNode<T> *smallest = getSmallestChild(p->rightTree);
				swap(p->value, smallest->value);
				delete_one_child(smallest);

				return true;
			}
			else {
				return false;
			}
		}

		void delete_one_child(RBTreeNode<T> *p) {
			RBTreeNode<T> *child = p->leftTree == NIL ? p->rightTree : p->leftTree;
			if (p->parent == NULL && p->leftTree == NIL && p->rightTree == NIL) {
				p = NULL;
				root = p;
				return;
			}

			if (p->parent == NULL) {
				delete  p;
				child->parent = NULL;
				root = child;
				root->color = BLACK;
				return;
			}

			if (p->parent->leftTree == p) {
				p->parent->leftTree = child;
			}
			else {
				p->parent->rightTree = child;
			}
			child->parent = p->parent;

			if (p->color == BLACK) {
				if (child->color == RED) {
					child->color = BLACK;
				}
				else
					delete_case(child);
			}

			delete p;
		}

		void delete_case(RBTreeNode<T> *p) {
			if (p->parent == NULL) {
				p->color = BLACK;
				return;
			}
			if (p->sibling()->color == RED) {
				p->parent->color = RED;
				p->sibling()->color = BLACK;
				if (p == p->parent->leftTree)
					rotate_left(p->sibling());
				else
					rotate_right(p->sibling());
			}
			if (p->parent->color == BLACK && p->sibling()->color == BLACK
				&& p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
				p->sibling()->color = RED;
				delete_case(p->parent);
			}
			else if (p->parent->color == RED && p->sibling()->color == BLACK
				&& p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
				p->sibling()->color = RED;
				p->parent->color = BLACK;
			}
			else {
				if (p->sibling()->color == BLACK) {
					if (p == p->parent->leftTree && p->sibling()->leftTree->color == RED
						&& p->sibling()->rightTree->color == BLACK) {
						p->sibling()->color = RED;
						p->sibling()->leftTree->color = BLACK;
						rotate_right(p->sibling()->leftTree);
					}
					else if (p == p->parent->rightTree && p->sibling()->leftTree->color == BLACK
						&& p->sibling()->rightTree->color == RED) {
						p->sibling()->color = RED;
						p->sibling()->rightTree->color = BLACK;
						rotate_left(p->sibling()->rightTree);
					}
				}
				p->sibling()->color = p->parent->color;
				p->parent->color = BLACK;
				if (p == p->parent->leftTree) {
					p->sibling()->rightTree->color = BLACK;
					rotate_left(p->sibling());
				}
				else {
					p->sibling()->leftTree->color = BLACK;
					rotate_right(p->sibling());
				}
			}
		}

		void insert(RBTreeNode<T> *p, T data) {
			if (p->value >= data) {
				if (p->leftTree != NIL)
					insert(p->leftTree, data);
				else {
					RBTreeNode<T> *tmp = new RBTreeNode<T>();
					tmp->value = data;
					tmp->leftTree = tmp->rightTree = NIL;
					tmp->parent = p;
					p->leftTree = tmp;
					insert_case(tmp);
				}
			}
			else {
				if (p->rightTree != NIL)
					insert(p->rightTree, data);
				else {
					RBTreeNode<T> *tmp = new RBTreeNode<T>();
					tmp->value = data;
					tmp->leftTree = tmp->rightTree = NIL;
					tmp->parent = p;
					p->rightTree = tmp;
					insert_case(tmp);
				}
			}
		}

		void insert_case(RBTreeNode<T> *p) {
			if (p->parent == NULL) {
				root = p;
				p->color = BLACK;
				return;
			}
			if (p->parent->color == RED) {
				if (p->uncle()->color == RED) {
					p->parent->color = p->uncle()->color = BLACK;
					p->grandparent()->color = RED;
					insert_case(p->grandparent());
				}
				else {
					if (p->parent->rightTree == p && p->grandparent()->leftTree == p->parent) {
						rotate_left(p);
						rotate_right(p);
						p->color = BLACK;
						p->leftTree->color = p->rightTree->color = RED;
					}
					else if (p->parent->leftTree == p && p->grandparent()->rightTree == p->parent) {
						rotate_right(p);
						rotate_left(p);
						p->color = BLACK;
						p->leftTree->color = p->rightTree->color = RED;
					}
					else if (p->parent->leftTree == p && p->grandparent()->leftTree == p->parent) {
						p->parent->color = BLACK;
						p->grandparent()->color = RED;
						rotate_right(p->parent);
					}
					else if (p->parent->rightTree == p && p->grandparent()->rightTree == p->parent) {
						p->parent->color = BLACK;
						p->grandparent()->color = RED;
						rotate_left(p->parent);
					}
				}
			}
		}

		void DeleteTree(RBTreeNode<T> *p) {
			if (!p || p == NIL) {
				return;
			}
			DeleteTree(p->leftTree);
			DeleteTree(p->rightTree);
			delete p;
		}
	public:

		RBTree() {
			NIL = new RBTreeNode<T>();
			NIL->color = BLACK;
			root = NULL;
		}

		~RBTree() {
			if (root)
				DeleteTree(root);
			delete NIL;
		}

		void inorder() {
			if (root == NULL)
				return;
			inorder(root);
			cout << endl;
		}

		void insert(T x) {
			if (root == NULL) {
				root = new RBTreeNode<T>;
				root->color = BLACK;
				root->leftTree = root->rightTree = NIL;
				root->value = x;
			}
			else {
				insert(root, x);
			}
		}

		bool erase(T data) {
			return delete_child(root, data);
		}

		bool isEmpty() { return (root == NULL); }

		T getMax() {
			if (root == NULL) return -1;
			RBTreeNode* t = root;
			while (t->rightTree != NIL) {
				t = t->rightTree;
			}
			return t->value;
		}

		T getMin() {
			return getSmallestChild(root)->value;
		}
	private:
		RBTreeNode<T> *root, *NIL;
	};
}