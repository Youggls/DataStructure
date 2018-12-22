namespace dataStructure {
	template <class T>
	class abstractBinaryTreeNode {
	public:
		virtual abstractBinaryTreeNode<T>* getLeft() = 0;
		virtual abstractBinaryTreeNode<T>* getRight() = 0;
		virtual abstractBinaryTreeNode<T>* getAncestor() = 0;
		virtual void setLeft(abstractBinaryTreeNode<T>* left) = 0;
		virtual void setRight(abstractBinaryTreeNode<T>* right) = 0;
		virtual void setAncestor(abstractBinaryTreeNode<T>* ancestor) = 0;
		virtual T& getData() = 0;
	};

	template <class T>
	class abstractBinaryTree {
	public:
		virtual void insert(const T& element) = 0;
		virtual void deleteNode(const T& theKey) = 0;
		virtual size_t depth() = 0;
		virtual size_t size() = 0;
		virtual bool empty() = 0;
		virtual void preOrder(void(*visit)(const T&)) = 0;
		virtual void inOrder(void(*visit)(const T&)) = 0;
		virtual void postOrder(void(*visit)(const T&)) = 0;
		virtual void levelOrder(void(*visit)(const T&)) = 0;
		virtual ~abstractBinaryTree() {};
	};
}