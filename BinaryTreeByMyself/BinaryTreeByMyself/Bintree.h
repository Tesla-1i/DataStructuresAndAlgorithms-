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
	void inOrder(BinaryTreeNode<T>* root);	//�������
	void postOrder(BinaryTreeNode<T>* root);	//�������
};

#endif // !BINTRE

template<class T>void BinaryTree<T>::levelOrder(BinaryTreeNode<T>* root) {
	queue<BinaryTreeNode<T>*> nodeQueue;
	BinaryTreeNode<T>* pointer = root;
	if (pointer == NULL) {
		cout << "����\n"; return;
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
	cout << "����\n";
}

template<class T>void BinaryTree<T>::preOrder(BinaryTreeNode<T>* root) {
	stack<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* pointer = root;
	while (!nodeStack.empty()||pointer)
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
	while (!nodeStack.empty()||pointer)
	{
		if (pointer) {
			nodeStack.push(pointer);
			pointer = pointer->leftChild;	//����ɨ��
		}
		else
		{
			pointer = nodeStack.top();	//���������ܽ�����ɾ��
			visit(pointer);
			pointer = pointer->rightChild;
			nodeStack.pop();
		}
	}
}

template<class T>void BinaryTree<T>::postOrder(BinaryTreeNode<T>* root) {
	stack<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* pointer = root;	//��ǰ�ڵ�
	BinaryTreeNode<T>* pre = root;	//�ոձ����ʵĽڵ�
	while (pointer)
	{
		//����������ѹ�뵱ǰ�ڵ�
		for (; pointer->leftChild != NULL; pointer = pointer->leftChild)
			nodeStack.push(pointer);	
		//pointer->rightchildΪ�ջ���rightChild�Ѿ������ʣ��ſ��Է��ʵ�ǰ�ڵ�pointer
		while (pointer != NULL && (pointer->rightChild == NULL || pointer->rightChild == pre)) {
			visit(pointer);
			pre = pointer;	//���ʺ󣬾ͱ����ǰ�Ľ����
			if (nodeStack.empty())
				return;
			pointer = nodeStack.top();	//ȡջ��
			nodeStack.pop();
		}
		nodeStack.push(pointer);	//���������õ�
		pointer = pointer->rightChild;	//����������
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


