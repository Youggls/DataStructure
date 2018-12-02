namespace dataStructure {
	template <class T>
	class abstractBinaryTreeNode {
	private:
		T data;
		abstractBinaryTreeNode<T>* leftChildNode;
		abstractBinaryTreeNode<T>* rightChildNode;
	public:
		virtual void getLeft() = 0;
		virtual void getRight() = 0;
		virtual abstractBinaryTreeNode<T>* setLeft() = 0;
		virtual abstractBinaryTreeNode<T>* setRight() = 0;
		virtual T& getData() = 0;
	};
	template <class T>
	class abstractBinaryTree {
	private:
		abstractBinaryTreeNode<T>* root;
		size_t nodeSize;
	public:
		virtual void insert(const T& element) = 0;
		virtual void deleteNode(const T& theKey) = 0;
		virtual size_t depth() = 0;
		virtual size_t size() = 0;
		s
	};
}