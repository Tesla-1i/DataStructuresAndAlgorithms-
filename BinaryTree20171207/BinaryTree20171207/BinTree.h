//�ж�һ�ö������Ƿ���������,�����ɺ��ж�
//��ͷ�ļ��������ֱ���,���ɶ�����

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
	int currentSize;	//��ǰ�����Ŀ,�ڵ���createTreeByTwoOrderʱֵ����
	BinaryTree() {
		root = NULL; currentSize = 0;
	}
	void createTree(BinaryTreeNode<T>* r) { root = r; }
	void visit(BinaryTreeNode<T>* pointer) { cout << (pointer->data) << endl; }

	void levelOrder(BinaryTreeNode<T>* root);
	void preOrder(BinaryTreeNode<T>* root);
	void inOrder(BinaryTreeNode<T>* root);	//�������
	void postOrder(BinaryTreeNode<T>* root);	//�������
												//�Ѿ�֪��ǰ���������У�Ψһȷ��������
	BinaryTreeNode<T>* createTreeByPreInOrder(T* a, int start1, int end1, T* b, int start2, int end2);
	//��֪����������У�Ψһȷ��������
	BinaryTreeNode<T>* createTreeByPostInOrder(T* a, int start1, int end1, T* b, int start2, int end2);
	//�ж�����������ȫ������
	bool isCompleteTree();

	//�ж϶������ǲ���������
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

template<class T>bool BinaryTree<T>::isCompleteTree() {
	queue<BinaryTreeNode<T>*> nodeQueue;
	BinaryTreeNode<T>* pointer = root;
	if (pointer == NULL) {
		cout << "����\n"; return false;
	}
	//
	nodeQueue.push(root);
	pointer = nodeQueue.front();
	//���ղ�������İ취��ӣ�ֱ��������һ��NULLֹͣ
	while (pointer) {
		nodeQueue.push(pointer->leftChild);
		nodeQueue.push(pointer->rightChild);
		nodeQueue.pop();
		pointer = nodeQueue.front();
	}
	//��ʱ������������в�ΪBULL�ģ�������ȫ������
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

//�Ѿ�֪��ǰ���������У�Ψһȷ��������,a[]ǰ���������飬b[]������������
template<class T>BinaryTreeNode<T>* BinaryTree<T>::createTreeByPreInOrder(T* a, int start1, int end1, T* b, int start2, int end2) {
	BinaryTreeNode<T>* root = new BinaryTreeNode<T>;	//���ֵĸ��ڵ�
	root->data = a[start1];
	currentSize++;	//һ������Լ�һ
					//�ҵ����������У������ȵ�b[j]
	int j = 0;
	for (j = start2; j <= end2; j++) {
		if (b[j] == a[start1])
			break;
	}
	//������
	int L = j - start2;	//���������ȣ�����j-start2+1
	if (L > 0) {	//��������,�ݹ���������
		root->leftChild = createTreeByPreInOrder(a, start1 + 1, start1 + L, b, start2, j - 1);
	}
	//������,�ݹ���������
	if (end2 >= j + 1) {
		root->rightChild = createTreeByPreInOrder(a, start1 + L + 1, end1, b, j + 1, end2);
	}
	return root;
}

//��֪����������У�Ψһȷ��������,a[]�����������飬 b[]������������
template<class T>BinaryTreeNode<T>* BinaryTree<T>::createTreeByPostInOrder(T* a, int start1, int end1, T* b, int start2, int end2) {
	BinaryTreeNode<T>* root = new BinaryTreeNode<T>;
	root->data = a[end1];	//a[end1]���ܵĸ��ڵ�
	currentSize++;
	int j = 0;
	for (j = start2; j <= end2; j++) {
		if (b[j] == a[end1])
			break;
	}
	//������
	int L = j - start2;		//���������Ȳ���j-start2+1
	if (L > 0) {	//����������
		root->leftChild = createTreeByPostInOrder(a, start1, start1 + L - 1, b, start2, j - 1);
	}
	//������
	if (end2 >= j + 1) {
		root->rightChild = createTreeByPostInOrder(a, start1 + L, end1 - 1, b, j + 1, end2);
	}
	return root;
}

template<class T>bool BinaryTree<T>::judgeTree(BinaryTreeNode<T>* root) {
	if (root == NULL)
		return true;
	//������������ֵ���ڸ��ڵ�,����false
	if (root->leftChild != NULL&&maxValue(root->leftChild) > root->data)
		return false;
	//�����������СֵС�ڸ��ڵ�,����false
	if (root->rightChild != NULL&&minValue(root->rightChild) < root->data)
		return false;
	//�ݹ��ж�
	if (judgeTree(root->leftChild) && judgeTree(root->rightChild))
		return true;
	return false;

	//BinaryTreeNode<T>* current = root;
	//while (current) {
	//	cout << "����\n";
	//	if (current->leftChild&&current->rightChild) {
	//		if (current->data > current->leftChild->data&&current->data < current->rightChild->data) {
	//			judgeTree(current->leftChild);
	//			judgeTree(current->rightChild);
	//		}
	//		else {
	//			cout << "���Ƕ���������\n";
	//			exit(0);
	//		}
	//	}
	//	if (current->leftChild && (!current->rightChild)) {
	//		if (current->data > current->leftChild->data) {
	//			judgeTree(current->leftChild);
	//		}
	//		else {
	//			cout << "���Ƕ���������\n";
	//			exit(0);
	//		}
	//	}
	//	if ((!current->leftChild) && current->rightChild) {
	//		if (current->data < current->rightChild->data) {
	//			judgeTree(current->rightChild);
	//		}
	//		else {
	//			cout << "���Ƕ���������\n";
	//			exit(0);
	//		}
	//	}
	//}
	//cout << "�Ƕ���������\n";
}


