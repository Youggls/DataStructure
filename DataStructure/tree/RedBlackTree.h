#define BLACK 1
#define RED 0
#include <iostream>

using namespace std;

namespace dataStructure {
	class RBTree {
	private:

		struct RBTreeNode {
			int value;
			bool color;
			RBTreeNode *leftTree, *rightTree, *parent;

			RBTreeNode() : value(0), color(RED), leftTree(NULL), rightTree(NULL), parent(NULL) { }

			RBTreeNode* grandparent() {
				if (parent == NULL) {
					return NULL;
				}
				return parent->parent;
			}

			RBTreeNode* uncle() {
				if (grandparent() == NULL) {
					return NULL;
				}
				if (parent == grandparent()->rightTree)
					return grandparent()->leftTree;
				else
					return grandparent()->rightTree;
			}

			RBTreeNode* sibling() {
				if (parent->leftTree == this)
					return parent->rightTree;
				else
					return parent->leftTree;
			}
		};

		void rotate_right(RBTreeNode *p) {
			RBTreeNode *gp = p->grandparent();
			RBTreeNode *fa = p->parent;
			RBTreeNode *y = p->rightTree;

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

		void rotate_left(RBTreeNode *p) {
			if (p->parent == NULL) {
				root = p;
				return;
			}
			RBTreeNode *gp = p->grandparent();
			RBTreeNode *fa = p->parent;
			RBTreeNode *y = p->leftTree;

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

		void inorder(RBTreeNode *p) {
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

		RBTreeNode* getSmallestChild(RBTreeNode *p) {
			if (p->leftTree == NIL)
				return p;
			return getSmallestChild(p->leftTree);
		}

		bool delete_child(RBTreeNode *p, int data) {
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
				RBTreeNode *smallest = getSmallestChild(p->rightTree);
				swap(p->value, smallest->value);
				delete_one_child(smallest);

				return true;
			}
			else {
				return false;
			}
		}

		void delete_one_child(RBTreeNode *p) {
			RBTreeNode *child = p->leftTree == NIL ? p->rightTree : p->leftTree;
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

		void delete_case(RBTreeNode *p) {
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

		void insert(RBTreeNode *p, int data) {
			if (p->value >= data) {
				if (p->leftTree != NIL)
					insert(p->leftTree, data);
				else {
					RBTreeNode *tmp = new RBTreeNode();
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
					RBTreeNode *tmp = new RBTreeNode();
					tmp->value = data;
					tmp->leftTree = tmp->rightTree = NIL;
					tmp->parent = p;
					p->rightTree = tmp;
					insert_case(tmp);
				}
			}
		}

		void insert_case(RBTreeNode *p) {
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

		void DeleteTree(RBTreeNode *p) {
			if (!p || p == NIL) {
				return;
			}
			DeleteTree(p->leftTree);
			DeleteTree(p->rightTree);
			delete p;
		}
	public:

		RBTree() {
			NIL = new RBTreeNode();
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

		void insert(int x) {
			if (root == NULL) {
				root = new RBTreeNode();
				root->color = BLACK;
				root->leftTree = root->rightTree = NIL;
				root->value = x;
			}
			else {
				insert(root, x);
			}
		}

		bool delete_value(int data) {
			return delete_child(root, data);
		}

		bool isEmpty() { return (root == NULL); }

		int getMax() {
			if (root == NULL) return -1;
			RBTreeNode* t = root;
			while (t->rightTree != NIL) {
				t = t->rightTree;
			}
			return t->value;
		}

		int getMin() {
			return getSmallestChild(root)->value;
		}
	private:
		RBTreeNode *root, *NIL;
	};
}