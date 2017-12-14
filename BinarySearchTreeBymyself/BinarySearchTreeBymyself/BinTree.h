//二叉搜索树的查找，插入（生成二叉树），删除（复制删除，用左子树最右结点）
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

#ifndef BINTREE
#define BINTREE

template<class T>class BinaryTreeNode {
public:
	T data;
	BinaryTreeNode<T>* leftChild;
	BinaryTreeNode<T>* rightChild;
	BinaryTreeNode() {
		leftChild = rightChild = NULL;
	}
	void setData(T d) { data = d; }
	void setLeftChild(BinaryTreeNode<T>* l) { leftChild = l; }
	void setRightChild(BinaryTreeNode<T>* r) { rightChild = r; }
	BinaryTreeNode<T>* getLeftChild() { return leftChild; }
	BinaryTreeNode<T>* getRightChild() { return rightChild; }
};

template<class T>class BinaryTree {
public:
	BinaryTreeNode<T>* root;
	BinaryTree() { root = NULL; }
	void createTree(BinaryTreeNode<T>* r) { root = r; }
	void visit(BinaryTreeNode<T>* pointer) { cout << (pointer->data) << endl; }

	void levelOrder(BinaryTreeNode<T>* root);
	void preOrder(BinaryTreeNode<T>* root);
	void inOrder(BinaryTreeNode<T>* root);	//中序遍历
	void postOrder(BinaryTreeNode<T>* root);	//后序遍历
	//二叉搜索树的查找，插入，删除
	BinaryTreeNode<T>* searchNode(T& x);
	void insertNode(T& x);
	bool deleteNode(T& x);
};

#endif // !BINTRE

template<class T>void BinaryTree<T>::levelOrder(BinaryTreeNode<T>* root) {
	queue<BinaryTreeNode<T>*> nodeQueue;
	BinaryTreeNode<T>* pointer = root;
	if (pointer == NULL) {
		cout << "空树\n"; return;
	}
	nodeQueue.push(pointer);
	while (!nodeQueue.empty())
	{
		pointer = nodeQueue.front();
		visit(pointer);
		nodeQueue.pop();
		if (pointer->leftChild)
			nodeQueue.push(pointer->leftChild);
		if (pointer->rightChild)
			nodeQueue.push(pointer->rightChild);
	}
	cout << "结束\n";
}

template<class T>void BinaryTree<T>::preOrder(BinaryTreeNode<T>* root) {
	stack<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* pointer = root;
	while (!nodeStack.empty() || pointer)
	{
		if (pointer) {
			visit(pointer);
			nodeStack.push(pointer);
			pointer = pointer->leftChild;
		}
		else {
			pointer = nodeStack.top();
			nodeStack.pop();
			pointer = pointer->rightChild;
		}
	}
}

template<class T>void BinaryTree<T>::inOrder(BinaryTreeNode<T>* root) {
	stack<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* pointer = root;
	while (!nodeStack.empty() || pointer)
	{
		if (pointer) {
			nodeStack.push(pointer);
			pointer = pointer->leftChild;	//向左扫描
		}
		else
		{
			pointer = nodeStack.top();	//弹出，不能紧接着删除
			visit(pointer);
			pointer = pointer->rightChild;
			nodeStack.pop();
		}
	}
}

template<class T>void BinaryTree<T>::postOrder(BinaryTreeNode<T>* root) {
	stack<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* pointer = root;	//当前节点
	BinaryTreeNode<T>* pre = root;	//刚刚被访问的节点
	while (pointer)
	{
		//向左搜索，压入当前节点
		for (; pointer->leftChild != NULL; pointer = pointer->leftChild)
			nodeStack.push(pointer);
		//pointer->rightchild为空或者rightChild已经被访问，才可以访问当前节点pointer
		while (pointer != NULL && (pointer->rightChild == NULL || pointer->rightChild == pre)) {
			visit(pointer);
			pre = pointer;	//访问后，就变成先前的结点了
			if (nodeStack.empty())
				return;
			pointer = nodeStack.top();	//取栈顶
			nodeStack.pop();
		}
		nodeStack.push(pointer);	//将来回来用到
		pointer = pointer->rightChild;	//深入右子树
	}
}

template<class T>BinaryTreeNode<T>* BinaryTree<T>::searchNode(T& x) {
	BinaryTreeNode<T>* p = root;
	while (p) {
		if (p->data > x)
			p = p->leftChild;
		else if (p->data < x)
			p = p->rightChild;
		else
			return p;
	}
	cout << "没有找到，返回root\n";
	return root;
}

template<class T>void BinaryTree<T>::insertNode(T& x) {
	BinaryTreeNode<T>* pre = NULL;	//pre是p的父节点
	BinaryTreeNode<T>* p = root;
	while (p) {
		pre = p;	
		if (p->data > x)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	//现在p是NULL，pre是叶子节点，特殊情况root=NULL
	p = new BinaryTreeNode<T>;
	p->data = x;
	if (root == NULL)
		root = p;
	else if (pre->data > x)
		pre->leftChild = p;
	else
		pre->rightChild = p;
}

//复制删除
template<class T>bool BinaryTree<T>::deleteNode(T& x) {
	
	//BinaryTreeNode<T>* node = new BinaryTreeNode<T>;
	//node->data = x;
	//BinaryTreeNode<T>* previous, *tmp = node;
	//if (node->rightChild == NULL)
	//	node = node->leftChild;
	//else if (node->leftChild == NULL)
	//	node = node->rightChild;
	//else {
	//	tmp = node->leftChild;
	//	previous = node;
	//	while (tmp->rightChild) {
	//		previous = tmp;
	//		tmp = tmp->rightChild;
	//	}
	//	node->data = tmp->data;
	//	if (previous == node)
	//		previous->leftChild = tmp->leftChild;
	//	else
	//		previous->rightChild = tmp->leftChild;
	//}
	//delete tmp;
	//return true;
	//找到结点
	BinaryTreeNode<T>* pre = NULL;	//p的父节点是pre
	BinaryTreeNode<T>* p = new BinaryTreeNode<T>;
	p = root;
	while (p) {
		pre = p;
		if (p->data > x)
			p = p->leftChild;
		else if (p->data < x)
			p = p->rightChild;
		else
			break;	//找到后，跳出，注意二叉搜索树标号是各不相同的
	}
	if (p == NULL)
		return false;	//没找到
	//p是叶子节点
	if ((p->leftChild == NULL) && (p->rightChild == NULL)) {
		if (pre->data < p->data)
			pre->rightChild = NULL;
		else
			pre->leftChild = NULL;
		delete p;
		cout << "删除叶子节点成功\n";
	}
	else if ((p->leftChild == NULL) || (p->rightChild == NULL)) {
		//只有一个孩子
		BinaryTreeNode<T>* child;
		//BinaryTreeNode<T>* child;	//p的孩子
		if (p->leftChild)
			child = p->leftChild;
		else
			child = p->rightChild;
		if (pre->data < p->data)
			pre->rightChild = child;
		else
			pre->leftChild = child;
		delete p;
		cout << "删除只有一个孩子的结点成功\n";
	}
	else {	//有两个孩子，找左边最大的一个，来替换
		BinaryTreeNode<T>* q = p->leftChild;
		BinaryTreeNode<T>* preq = p;
		while (q->rightChild) {
			preq = q;
			q = q->rightChild;
		}
		//到这里，q就是左子树中的最右端结点（左子树最大值）
		p->data = q->data;	//替换
		//删除q
		//此时q要么是叶子，要么只有左孩子，不可能有右孩子
		if (q->leftChild == NULL&&q->rightChild == NULL) {
			if (pre->data < q->data)
				pre->rightChild = NULL;
			else
				pre->leftChild = NULL;
			delete q;
		}
		else {
			if (pre->data < q->data)
				pre->rightChild = q->leftChild;
			else
				pre->leftChild = q->leftChild;
			delete q;
		}
		cout << "删除有两个孩子的结点成功\n";
	}
	return true;
}


