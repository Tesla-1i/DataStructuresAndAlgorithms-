//�����������Ĳ��ң����루���ɶ���������ɾ��������ɾ���������������ҽ�㣩
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
	//�����������Ĳ��ң����룬ɾ��
	BinaryTreeNode<T>* searchNode(T& x);
	void insertNode(T& x);
	bool deleteNode(T& x);
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
	cout << "û���ҵ�������root\n";
	return root;
}

template<class T>void BinaryTree<T>::insertNode(T& x) {
	BinaryTreeNode<T>* pre = NULL;	//pre��p�ĸ��ڵ�
	BinaryTreeNode<T>* p = root;
	while (p) {
		pre = p;	
		if (p->data > x)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	//����p��NULL��pre��Ҷ�ӽڵ㣬�������root=NULL
	p = new BinaryTreeNode<T>;
	p->data = x;
	if (root == NULL)
		root = p;
	else if (pre->data > x)
		pre->leftChild = p;
	else
		pre->rightChild = p;
}

//����ɾ��
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
	//�ҵ����
	BinaryTreeNode<T>* pre = NULL;	//p�ĸ��ڵ���pre
	BinaryTreeNode<T>* p = new BinaryTreeNode<T>;
	p = root;
	while (p) {
		pre = p;
		if (p->data > x)
			p = p->leftChild;
		else if (p->data < x)
			p = p->rightChild;
		else
			break;	//�ҵ���������ע���������������Ǹ�����ͬ��
	}
	if (p == NULL)
		return false;	//û�ҵ�
	//p��Ҷ�ӽڵ�
	if ((p->leftChild == NULL) && (p->rightChild == NULL)) {
		if (pre->data < p->data)
			pre->rightChild = NULL;
		else
			pre->leftChild = NULL;
		delete p;
		cout << "ɾ��Ҷ�ӽڵ�ɹ�\n";
	}
	else if ((p->leftChild == NULL) || (p->rightChild == NULL)) {
		//ֻ��һ������
		BinaryTreeNode<T>* child;
		//BinaryTreeNode<T>* child;	//p�ĺ���
		if (p->leftChild)
			child = p->leftChild;
		else
			child = p->rightChild;
		if (pre->data < p->data)
			pre->rightChild = child;
		else
			pre->leftChild = child;
		delete p;
		cout << "ɾ��ֻ��һ�����ӵĽ��ɹ�\n";
	}
	else {	//���������ӣ����������һ�������滻
		BinaryTreeNode<T>* q = p->leftChild;
		BinaryTreeNode<T>* preq = p;
		while (q->rightChild) {
			preq = q;
			q = q->rightChild;
		}
		//�����q�����������е����Ҷ˽�㣨���������ֵ��
		p->data = q->data;	//�滻
		//ɾ��q
		//��ʱqҪô��Ҷ�ӣ�Ҫôֻ�����ӣ����������Һ���
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
		cout << "ɾ�����������ӵĽ��ɹ�\n";
	}
	return true;
}


