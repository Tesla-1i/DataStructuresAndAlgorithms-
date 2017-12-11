//判断一棵二叉树是否是搜索树,先生成后判断
//本头文件包含三种遍历,生成二叉树

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
	int currentSize;	//当前结点数目,在调用createTreeByTwoOrder时值增加
	BinaryTree() {
		root = NULL; currentSize = 0;
	}
	void createTree(BinaryTreeNode<T>* r) { root = r; }
	void visit(BinaryTreeNode<T>* pointer) { cout << (pointer->data) << endl; }

	void levelOrder(BinaryTreeNode<T>* root);
	void preOrder(BinaryTreeNode<T>* root);
	void inOrder(BinaryTreeNode<T>* root);	//中序遍历
	void postOrder(BinaryTreeNode<T>* root);	//后序遍历
												//已经知道前序中序序列，唯一确定二叉树
	BinaryTreeNode<T>* createTreeByPreInOrder(T* a, int start1, int end1, T* b, int start2, int end2);
	//已知中序后序序列，唯一确定二叉树
	BinaryTreeNode<T>* createTreeByPostInOrder(T* a, int start1, int end1, T* b, int start2, int end2);
	//判读二叉树是完全二叉树
	bool isCompleteTree();

	//判断二叉树是不是搜索树
	bool judgeTree(BinaryTreeNode<T>* root);
	T maxValue(BinaryTreeNode<T>* root) {
		while (root->rightChild)
			root = root->rightChild;
		return root->data;
	}
	T minValue(BinaryTreeNode<T>* root) {
		while (root->leftChild)
			root = root->leftChild;
		return root->data;
	}
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

template<class T>bool BinaryTree<T>::isCompleteTree() {
	queue<BinaryTreeNode<T>*> nodeQueue;
	BinaryTreeNode<T>* pointer = root;
	if (pointer == NULL) {
		cout << "空树\n"; return false;
	}
	//
	nodeQueue.push(root);
	pointer = nodeQueue.front();
	//按照层序遍历的办法入队，直至遇到第一个NULL停止
	while (pointer) {
		nodeQueue.push(pointer->leftChild);
		nodeQueue.push(pointer->rightChild);
		nodeQueue.pop();
		pointer = nodeQueue.front();
	}
	//此时，如果队列中有不为BULL的，则不是完全二叉树
	while (!nodeQueue.empty()) {
		if (nodeQueue.front())
			return false;
		nodeQueue.pop();
	}
	return true;
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
										/*while (!nodeStack.empty()&&(pointer=nodeStack.top())) {
										if (pointer->rightChild != NULL&&pointer->rightChild != pre) {
										BinaryTreeNode<T>* temp = pointer->rightChild;
										nodeStack.pop();
										pointer = temp;
										visit(pointer);
										}
										else
										{
										visit(pointer);
										nodeStack.pop();
										}
										}*/

	}
}

//已经知道前序中序序列，唯一确定二叉树,a[]前序序列数组，b[]中序序列数组
template<class T>BinaryTreeNode<T>* BinaryTree<T>::createTreeByPreInOrder(T* a, int start1, int end1, T* b, int start2, int end2) {
	BinaryTreeNode<T>* root = new BinaryTreeNode<T>;	//部分的根节点
	root->data = a[start1];
	currentSize++;	//一个结点自加一
					//找到中序序列中，与根相等的b[j]
	int j = 0;
	for (j = start2; j <= end2; j++) {
		if (b[j] == a[start1])
			break;
	}
	//左子树
	int L = j - start2;	//左子树长度，不是j-start2+1
	if (L > 0) {	//有左子树,递归求左子树
		root->leftChild = createTreeByPreInOrder(a, start1 + 1, start1 + L, b, start2, j - 1);
	}
	//右子树,递归求右子树
	if (end2 >= j + 1) {
		root->rightChild = createTreeByPreInOrder(a, start1 + L + 1, end1, b, j + 1, end2);
	}
	return root;
}

//已知中序后序序列，唯一确定二叉树,a[]后续序列数组， b[]中序序列数组
template<class T>BinaryTreeNode<T>* BinaryTree<T>::createTreeByPostInOrder(T* a, int start1, int end1, T* b, int start2, int end2) {
	BinaryTreeNode<T>* root = new BinaryTreeNode<T>;
	root->data = a[end1];	//a[end1]是总的根节点
	currentSize++;
	int j = 0;
	for (j = start2; j <= end2; j++) {
		if (b[j] == a[end1])
			break;
	}
	//左子树
	int L = j - start2;		//左子树长度不是j-start2+1
	if (L > 0) {	//存在左子树
		root->leftChild = createTreeByPostInOrder(a, start1, start1 + L - 1, b, start2, j - 1);
	}
	//右子树
	if (end2 >= j + 1) {
		root->rightChild = createTreeByPostInOrder(a, start1 + L, end1 - 1, b, j + 1, end2);
	}
	return root;
}

template<class T>bool BinaryTree<T>::judgeTree(BinaryTreeNode<T>* root) {
	if (root == NULL)
		return true;
	//如果左子树最大值大于根节点,返回false
	if (root->leftChild != NULL&&maxValue(root->leftChild) > root->data)
		return false;
	//如果右子树最小值小于根节点,返回false
	if (root->rightChild != NULL&&minValue(root->rightChild) < root->data)
		return false;
	//递归判断
	if (judgeTree(root->leftChild) && judgeTree(root->rightChild))
		return true;
	return false;

	//BinaryTreeNode<T>* current = root;
	//while (current) {
	//	cout << "测试\n";
	//	if (current->leftChild&&current->rightChild) {
	//		if (current->data > current->leftChild->data&&current->data < current->rightChild->data) {
	//			judgeTree(current->leftChild);
	//			judgeTree(current->rightChild);
	//		}
	//		else {
	//			cout << "不是二叉搜索树\n";
	//			exit(0);
	//		}
	//	}
	//	if (current->leftChild && (!current->rightChild)) {
	//		if (current->data > current->leftChild->data) {
	//			judgeTree(current->leftChild);
	//		}
	//		else {
	//			cout << "不是二叉搜索树\n";
	//			exit(0);
	//		}
	//	}
	//	if ((!current->leftChild) && current->rightChild) {
	//		if (current->data < current->rightChild->data) {
	//			judgeTree(current->rightChild);
	//		}
	//		else {
	//			cout << "不是二叉搜索树\n";
	//			exit(0);
	//		}
	//	}
	//}
	//cout << "是二叉搜索树\n";
}


