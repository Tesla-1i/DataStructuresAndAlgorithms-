#include<iostream>
#include<stack>
#include<queue>
#include<stdlib.h>
#include<time.h>
using namespace std;
//二叉树的基本实现，各种遍历
#ifndef BINARYTREE
#define BINARYTREE

template<class T>class BinaryTreeNode {
	//friend class BinaryTree<T>;
public:
	T element;
	BinaryTreeNode<T>* leftChild;
	BinaryTreeNode<T>* rightChild;
	BinaryTreeNode<T>* parent;
public:
	BinaryTreeNode() { leftChild = rightChild = NULL;  }	//暂时这样
	BinaryTreeNode(T& ele) { element = ele; leftChild = rightChild = NULL; }
	BinaryTreeNode(T& ele, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) { element = ele; leftChild = l; rightChild = r; }	//给定左右孩子结点
	BinaryTreeNode<T>* getLeftChild() { return leftChild; }	//返回左孩子
	BinaryTreeNode<T>* getRightChild() { return rightChild; }
	BinaryTreeNode<T>* getParent() { return parent };
	void setLeftChild(BinaryTreeNode<T>* l) { leftChild = l; }	//设置左孩子
	void setRightChild(BinaryTreeNode<T>* r) { rightChild = r; }
	void setParent(BinaryTreeNode<T>* p) { parent = p; }	//设置父亲
	T getValue() { return element; }	//得到数据值
	void setValue(T& val) { element = val; }
	bool isLeaf() {
		if (leftChild == NULL&&rightChild == NULL) return true;
		else return false;
	}
};

template<class T>class BinaryTree {
public:
	BinaryTreeNode<T>* root;	//根节点
public:
	BinaryTree() { root = new BinaryTreeNode<T>();  }
	//~BinaryTree(){ }
	bool isEmpty() { return (root == NULL); }
	BinaryTreeNode<T>* getRoot() { return root; }
	BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* current) { return current->parent; }
	//BinaryTreeNode<T>* getLeftSibling(BinaryTreeNode<T>* current);	//返回current左兄弟
	//BinaryTreeNode<T>* getRightSibling(BinaryTreeNode<T>* current)
	void levelOrder(BinaryTreeNode<T>* root);	//广序遍历
	//前序遍历接口
	void preOrderBinTree() {
		srand((int)time(NULL));
		switch (rand()%2)
		{
		case 0:cout << "非递归前序遍历\n"; preOrder(root); break;
		case 1:cout << "递归前序遍历\n"; preOrderWithRecusion(root); break;
		default:
			break;
		}
	}
	void preOrder(BinaryTreeNode<T>* root);	//前序遍历
	void preOrderWithRecusion(BinaryTreeNode<T>* root);	//递归前序遍历
	void inOrder(BinaryTreeNode<T>* root);		//中序遍历
	void postOrder(BinaryTreeNode<T>* root);	//后序遍历
	//void deleteBinaryTree(BinaryTreeNode<T>* root);	//删除以root为根的子树
	void visit(BinaryTreeNode<T>* current) { cout << current->element << "\n"; }
	void creatTree(BinaryTreeNode<T>* p) { root = p; }	//创造树的接口
	void creatTreeByPreOrder(queue<T> q);	//先序创造二叉树
};

#endif // !BINARYTREE

////////////////////////////////////////////////////////////////////////////////////

template<class T>void BinaryTree<T>::levelOrder(BinaryTreeNode<T>* root) {
	using std::queue;
	queue<BinaryTreeNode<T>*> nodeQueue;	//用队列存放将要访问的结点
	BinaryTreeNode<T>* pointer = root;
	if (pointer)
		nodeQueue.push(pointer);	//根节点非空，入队
	while (!nodeQueue.empty()) {
		pointer = nodeQueue.front();	//读队首
		visit(pointer);
		nodeQueue.pop();
		//将访问过的结点的左右孩子入队
		if (pointer->leftChild)
			nodeQueue.push(pointer->leftChild);
		if (pointer->rightChild)
			nodeQueue.push(pointer->rightChild);	
	}
}

//先访问该节点，将该节点的非空右子树的根节点压入栈中，
//然后遍历左子树，重复该过程直到当前访问的结点没有左子树时停止
//然后从栈顶弹出待访问的结点，继续遍历，直至栈空.
template<class T>void BinaryTree<T>::preOrder(BinaryTreeNode<T>* root) {
	using std::stack;
	stack<BinaryTreeNode<T>*> nodeStack;	//存放待访问的结点
	BinaryTreeNode<T>* pointer = root;	//保存根节点
	//while (!nodeStack.empty() || pointer) {
	//	if (pointer) {
	//		visit(pointer);
	//		if (pointer->rightChild != NULL)
	//			nodeStack.push(pointer->rightChild);	//当前访问结点的右子树的根节点入栈
	//		pointer = pointer->leftChild;	//访问左子树
	//	}
	//	else
	//	{
	//		pointer = nodeStack.top();	//读取栈顶待访问的结点
	//		nodeStack.pop();
	//	}
	//}
	//另一种实现方法
	while (!nodeStack.empty() || pointer) {
		if (pointer) {
			visit(pointer);
			nodeStack.push(pointer);	//当前访问结点入栈
			pointer = pointer->leftChild;
		}
		else {
			pointer = nodeStack.top();
			nodeStack.pop();
			pointer = pointer->rightChild;
		}
	}
}
template<class T>void BinaryTree<T>::preOrderWithRecusion(BinaryTreeNode<T>* root) {
	if (root != NULL) {
		visit(root);
		preOrderWithRecusion(root->leftChild);
		preOrderWithRecusion(root->rightChild);
	}
}

//从根节点开始，向左搜索,压栈。然后去遍历左子树，遍历完后，弹出栈顶并访问他，然后遍历右子树
template<class T>void BinaryTree<T>::inOrder(BinaryTreeNode<T>* root) {
	using std::stack;
	stack<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* pointer = root;
	while (!nodeStack.empty()||pointer)
	{
		if (pointer) {
			nodeStack.push(pointer);
			pointer = pointer->leftChild;	//转向左孩子
			}
		else {
			pointer = nodeStack.top;	
			visit(pointer);
			pointer = pointer->rightChild;	//转向右孩子
			nodeStack.pop();
		}
	}
}

//从根节点开始，向左搜索,压栈。直至压入的结点不再有左子树
//读取栈顶结点,如果他有右子树且没有访问，则访问右子树，
//否则访问他，并弹出.
template<class T>void BinaryTree<T>::postOrder(BinaryTreeNode<T>* root) {
	using std::stack;
	stack<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* pointer = root;
	BinaryTreeNode<T>* pre = root;	//保存上一个被访问到的结点
	while (pointer) {
		for (; pointer->leftChild != NULL; pointer = pointer->leftChild)
			nodeStack.push(pointer);	//向左搜索
		while (pointer != NULL && (pointer->rightChild == NULL || pointer->rightChild == pre)) {
			//当前节点没有右孩子||右孩子已经访问，则访问该节点
			visit(pointer);
			pre = pointer;
			if (nodeStack.empty())
				return;
			pointer = nodeStack.top();
			nodeStack.pop();
		}
		nodeStack.push(pointer);
		pointer = pointer->rightChild;	//转向右子树
	}
}

/////////////////////////////////////////////////////////////////////////////////
template<class T>void BinaryTree<T>::creatTreeByPreOrder(queue<T> q) {
	BinaryTreeNode<T>* tmp;
	while (1) {
		if (!q.empty()) {
			tmp->element = q.front();
			tmp
		}
	}
}

