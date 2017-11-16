#include<iostream>
#include<stack>
#include<queue>
#include<stdlib.h>
#include<time.h>
using namespace std;
//�������Ļ���ʵ�֣����ֱ���
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
	BinaryTreeNode() { leftChild = rightChild = NULL;  }	//��ʱ����
	BinaryTreeNode(T& ele) { element = ele; leftChild = rightChild = NULL; }
	BinaryTreeNode(T& ele, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) { element = ele; leftChild = l; rightChild = r; }	//�������Һ��ӽ��
	BinaryTreeNode<T>* getLeftChild() { return leftChild; }	//��������
	BinaryTreeNode<T>* getRightChild() { return rightChild; }
	BinaryTreeNode<T>* getParent() { return parent };
	void setLeftChild(BinaryTreeNode<T>* l) { leftChild = l; }	//��������
	void setRightChild(BinaryTreeNode<T>* r) { rightChild = r; }
	void setParent(BinaryTreeNode<T>* p) { parent = p; }	//���ø���
	T getValue() { return element; }	//�õ�����ֵ
	void setValue(T& val) { element = val; }
	bool isLeaf() {
		if (leftChild == NULL&&rightChild == NULL) return true;
		else return false;
	}
};

template<class T>class BinaryTree {
public:
	BinaryTreeNode<T>* root;	//���ڵ�
public:
	BinaryTree() { root = new BinaryTreeNode<T>();  }
	//~BinaryTree(){ }
	bool isEmpty() { return (root == NULL); }
	BinaryTreeNode<T>* getRoot() { return root; }
	BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* current) { return current->parent; }
	//BinaryTreeNode<T>* getLeftSibling(BinaryTreeNode<T>* current);	//����current���ֵ�
	//BinaryTreeNode<T>* getRightSibling(BinaryTreeNode<T>* current)
	void levelOrder(BinaryTreeNode<T>* root);	//�������
	//ǰ������ӿ�
	void preOrderBinTree() {
		srand((int)time(NULL));
		switch (rand()%2)
		{
		case 0:cout << "�ǵݹ�ǰ�����\n"; preOrder(root); break;
		case 1:cout << "�ݹ�ǰ�����\n"; preOrderWithRecusion(root); break;
		default:
			break;
		}
	}
	void preOrder(BinaryTreeNode<T>* root);	//ǰ�����
	void preOrderWithRecusion(BinaryTreeNode<T>* root);	//�ݹ�ǰ�����
	void inOrder(BinaryTreeNode<T>* root);		//�������
	void postOrder(BinaryTreeNode<T>* root);	//�������
	//void deleteBinaryTree(BinaryTreeNode<T>* root);	//ɾ����rootΪ��������
	void visit(BinaryTreeNode<T>* current) { cout << current->element << "\n"; }
	void creatTree(BinaryTreeNode<T>* p) { root = p; }	//�������Ľӿ�
	void creatTreeByPreOrder(queue<T> q);	//�����������
};

#endif // !BINARYTREE

////////////////////////////////////////////////////////////////////////////////////

template<class T>void BinaryTree<T>::levelOrder(BinaryTreeNode<T>* root) {
	using std::queue;
	queue<BinaryTreeNode<T>*> nodeQueue;	//�ö��д�Ž�Ҫ���ʵĽ��
	BinaryTreeNode<T>* pointer = root;
	if (pointer)
		nodeQueue.push(pointer);	//���ڵ�ǿգ����
	while (!nodeQueue.empty()) {
		pointer = nodeQueue.front();	//������
		visit(pointer);
		nodeQueue.pop();
		//�����ʹ��Ľ������Һ������
		if (pointer->leftChild)
			nodeQueue.push(pointer->leftChild);
		if (pointer->rightChild)
			nodeQueue.push(pointer->rightChild);	
	}
}

//�ȷ��ʸýڵ㣬���ýڵ�ķǿ��������ĸ��ڵ�ѹ��ջ�У�
//Ȼ��������������ظ��ù���ֱ����ǰ���ʵĽ��û��������ʱֹͣ
//Ȼ���ջ�����������ʵĽ�㣬����������ֱ��ջ��.
template<class T>void BinaryTree<T>::preOrder(BinaryTreeNode<T>* root) {
	using std::stack;
	stack<BinaryTreeNode<T>*> nodeStack;	//��Ŵ����ʵĽ��
	BinaryTreeNode<T>* pointer = root;	//������ڵ�
	//while (!nodeStack.empty() || pointer) {
	//	if (pointer) {
	//		visit(pointer);
	//		if (pointer->rightChild != NULL)
	//			nodeStack.push(pointer->rightChild);	//��ǰ���ʽ����������ĸ��ڵ���ջ
	//		pointer = pointer->leftChild;	//����������
	//	}
	//	else
	//	{
	//		pointer = nodeStack.top();	//��ȡջ�������ʵĽ��
	//		nodeStack.pop();
	//	}
	//}
	//��һ��ʵ�ַ���
	while (!nodeStack.empty() || pointer) {
		if (pointer) {
			visit(pointer);
			nodeStack.push(pointer);	//��ǰ���ʽ����ջ
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

//�Ӹ��ڵ㿪ʼ����������,ѹջ��Ȼ��ȥ������������������󣬵���ջ������������Ȼ�����������
template<class T>void BinaryTree<T>::inOrder(BinaryTreeNode<T>* root) {
	using std::stack;
	stack<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* pointer = root;
	while (!nodeStack.empty()||pointer)
	{
		if (pointer) {
			nodeStack.push(pointer);
			pointer = pointer->leftChild;	//ת������
			}
		else {
			pointer = nodeStack.top;	
			visit(pointer);
			pointer = pointer->rightChild;	//ת���Һ���
			nodeStack.pop();
		}
	}
}

//�Ӹ��ڵ㿪ʼ����������,ѹջ��ֱ��ѹ��Ľ�㲻����������
//��ȡջ�����,���������������û�з��ʣ��������������
//�����������������.
template<class T>void BinaryTree<T>::postOrder(BinaryTreeNode<T>* root) {
	using std::stack;
	stack<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* pointer = root;
	BinaryTreeNode<T>* pre = root;	//������һ�������ʵ��Ľ��
	while (pointer) {
		for (; pointer->leftChild != NULL; pointer = pointer->leftChild)
			nodeStack.push(pointer);	//��������
		while (pointer != NULL && (pointer->rightChild == NULL || pointer->rightChild == pre)) {
			//��ǰ�ڵ�û���Һ���||�Һ����Ѿ����ʣ�����ʸýڵ�
			visit(pointer);
			pre = pointer;
			if (nodeStack.empty())
				return;
			pointer = nodeStack.top();
			nodeStack.pop();
		}
		nodeStack.push(pointer);
		pointer = pointer->rightChild;	//ת��������
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

