//ttp://blog.csdn.net/qq_30490125/article/details/53135274
//ttp://blog.csdn.net/qq_30091945/article/details/77816368
//1.�����������Ҷ�ӽڵ����,2.��������������д���k�����н��(Ŀǰ������),3.�ж�һ�Ŷ������Ƿ���������(����һ����Ŀ����)
//���������������,�ɵõ�����С����˳�����еĹؼ�������
//����ڶ�������,ֻ��ʹ��һ����������

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

	//ͳ��Ҷ�ӽڵ����
	int leaf(BinaryTreeNode<T>* root);
	//�����������������K������ֵ
	T BinaryTree<T>::maxValue(BinaryTreeNode<T>* root);
	void searchBiggerNode(BinaryTreeNode<T>* root,T& k);
	//�ж϶������Ƿ��Ƕ���������
	//bool judgeTree(BinaryTreeNode<T>* root);
	//T maxValue(BinaryTreeNode<T>* root) {
	//	while (root->rightChild)
	//		root = root->rightChild;
	//	return root->data;
	//}
	//T minValue(BinaryTreeNode<T>* root) {
	//	while (root->leftChild)
	//		root = root->leftChild;
	//	return root->data;
	//}
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

template<class T>int BinaryTree<T>::leaf(BinaryTreeNode<T>* root) {
	if (root) {
		if (root->leftChild == NULL&&root->rightChild == NULL)
			return 1;
		if (root->leftChild == NULL&&root->rightChild != NULL)
			return leaf(root->rightChild);
		if (root->leftChild != NULL&&root->rightChild == NULL)
			return leaf(root->leftChild);
		if (root->leftChild != NULL&&root->rightChild != NULL)
			return leaf(root->leftChild) + leaf(root->rightChild);
	}
}

template<class T>T BinaryTree<T>::maxValue(BinaryTreeNode<T>* root) {
	//������������������ֵ
	T maxValue = (T)(0);
	stack<BinaryTreeNode<T>*> nodeStack;
	BinaryTreeNode<T>* pointer = root;
	while (!nodeStack.empty() || pointer) {
		if (pointer) {
			nodeStack.push(pointer);
			pointer = pointer->leftChild;
		}
		else {
			pointer = nodeStack.top();
			if (maxValue < pointer->data)
				maxValue = pointer->data;
			pointer = pointer->rightChild;
			nodeStack.pop();
		}
	}
	return maxValue;
}
//������������õ��������Ĺؼ�������,���������k�Ĺؼ���
template<class T>void BinaryTree<T>::searchBiggerNode(BinaryTreeNode<T>* root,T & k) {

	//T maxOfLeft = maxValue(root->leftChild);
	//if(maxOfLeft)

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
			if(pointer->data>k)	//�����Ķ�
				visit(pointer);
			pointer = pointer->rightChild;
			nodeStack.pop();
		}
	}

	//BinaryTreeNode<T>* current = root;
	//while (current) {
	//	if ((current->data) <= k) {
	//		current = current->rightChild;
	//	}
	//	else {
	//		break;
	//	}
	//}
	//levelOrder(current);
}

//template<class T>bool BinaryTree<T>::judgeTree(BinaryTreeNode<T>* root) {
//	if (root == NULL)
//		return true;
//	//������������ֵ���ڸ��ڵ�,����false
//	if (root->leftChild != NULL&&maxValue(root->leftChild) > root->data)
//		return false;
//	//�����������СֵС�ڸ��ڵ�,����false
//	if (root->rightChild != NULL&&minValue(root->rightChild) < root->data)
//		return false;
//	//�ݹ��ж�
//	if (judgeTree(root->leftChild) && judgeTree(root->rightChild))
//		return true;
//	return false;
//
//	//BinaryTreeNode<T>* current = root;
//	//while (current) {
//	//	cout << "����\n";
//	//	if (current->leftChild&&current->rightChild) {
//	//		if (current->data > current->leftChild->data&&current->data < current->rightChild->data) {
//	//			judgeTree(current->leftChild);
//	//			judgeTree(current->rightChild);
//	//		}
//	//		else {
//	//			cout << "���Ƕ���������\n";
//	//			exit(0);
//	//		}
//	//	}
//	//	if (current->leftChild && (!current->rightChild)) {
//	//		if (current->data > current->leftChild->data) {
//	//			judgeTree(current->leftChild);
//	//		}
//	//		else {
//	//			cout << "���Ƕ���������\n";
//	//			exit(0);
//	//		}
//	//	}
//	//	if ((!current->leftChild) && current->rightChild) {
//	//		if (current->data < current->rightChild->data) {
//	//			judgeTree(current->rightChild);
//	//		}
//	//		else {
//	//			cout << "���Ƕ���������\n";
//	//			exit(0);
//	//		}
//	//	}
//	//}
//	//cout << "�Ƕ���������\n";
//}
//
