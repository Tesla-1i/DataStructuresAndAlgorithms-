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
	void deleteLeaf(BinaryTreeNode<T>* root);	//ɾ��Ҷ�ӽڵ�
	void change(BinaryTreeNode<T>* root);	//�������Һ���
	T getMax(BinaryTreeNode<T>* root);	//���ڵ�ֵ
	void getWidth(BinaryTreeNode<T>* root, int i, int* width);//ͳ�ƶ��������
	int getHeight(BinaryTreeNode<T>* root);//ͳ�ƶ������ĸ߶�
	int two(BinaryTreeNode<T>* root);//ͳ�ƶ�Ϊ2 �Ľڵ���
	int one(BinaryTreeNode<T>* root);//ͳ�ƶ�Ϊ1 �Ľڵ���
	int leaf(BinaryTreeNode<T>* root);//ͳ�ƶ�Ϊ0 Ҷ�ӽڵ���Ŀ
	
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

template<class T>void BinaryTree<T>::deleteLeaf(BinaryTreeNode<T>* root) {
	if (root->leftChild) {
		if (root->leftChild->leftChild == NULL&&root->leftChild->rightChild == NULL) {
			delete root->leftChild; root->leftChild = NULL;
		}
		else {
			deleteLeaf(root->leftChild);
		}
	}
	if (root->rightChild) {
		if (root->rightChild->leftChild == NULL&&root->rightChild->rightChild == NULL) {
			delete root->rightChild; root->rightChild = NULL;
		}
		else {
			deleteLeaf(root->rightChild);
		}
	}
}

template<class T>void BinaryTree<T>::change(BinaryTreeNode<T>* root) {
	if (root != NULL) {
		BinaryTreeNode<T>* tmp = root->leftChild;
		root->leftChild = root->rightChild;
		root->rightChild = tmp;
		if (root->leftChild)
			change(root->leftChild);
		if (root->rightChild)
			change(root->rightChild);
	}
}

template<class T>T BinaryTree<T>::getMax(BinaryTreeNode<T>* root) {
	if (root != NULL) {
		if (root->leftChild == NULL&&root->rightChild == NULL)
			return root->data;
		if (root->leftChild != NULL&&root->rightChild != NULL) {
			T maxNode;
			maxNode = (getMax(root->leftChild) > getMax(root->rightChild) )? getMax(root->leftChild) : getMax(root->rightChild);
			return (maxNode > root->data) ? maxNode : root->data;
		}
		if (root->leftChild == NULL&&root->rightChild != NULL)
			return (root->data > getMax(root->rightChild)) ? root->data : getMax(root->rightChild);
		if (root->leftChild != NULL&&root->rightChild == NULL)
			return (root->data > getMax(root->leftChild)) ? root->data : getMax(root->leftChild);
	}
}

template<class T>void BinaryTree<T>::getWidth(BinaryTreeNode<T>* root, int i, int *width) {
	BinaryTreeNode<T>* p = root;
	if (p != NULL)
		width[i]++;
	if (p->leftChild != NULL)
		getWidth(p->leftChild, i + 1, width);
	if (p->rightChild != NULL)
		getWidth(p->rightChild, i + 1, width);
}

template<class T>int BinaryTree<T>::getHeight(BinaryTreeNode<T>* root) {
	BinaryTreeNode<T>* p = root;
	if (p->leftChild == NULL&&p->rightChild == NULL)
		return 1;
	if (p->leftChild == NULL&&p->rightChild != NULL)
		return 1 + getHeight(p->rightChild);
	if (p->leftChild != NULL&&p->rightChild == NULL)
		return 1 + getHeight(p->leftChild);
	if (p->leftChild != NULL&&p->rightChild != NULL) {
		int x = 1 + getHeight(p->leftChild);
		int y = 1 + getHeight(p->rightChild);
		return (x > y) ? x : y;
	}
}

template<class T>int BinaryTree<T>::two(BinaryTreeNode<T>* root) {
	if (root != NULL) {
		if (root->leftChild == NULL&&root->rightChild != NULL)
			return two(root->rightChild);
		if (root->leftChild != NULL&&root->rightChild == NULL) {
			return two(root->leftChild);
		}
		if (root->leftChild == NULL&&root->rightChild == NULL)
			return 0;
		if (root->leftChild != NULL&&root->rightChild != NULL)
			return 1 + two(root->leftChild) + two(root->rightChild);
	}
}

template<class T>int BinaryTree<T>::one(BinaryTreeNode<T>* root) {
	if (root != NULL) {
		if (root->leftChild == NULL&&root->rightChild != NULL)
			return 1+one(root->rightChild);
		if (root->leftChild != NULL&&root->rightChild == NULL) {
			return 1+one(root->leftChild);
		}
		if (root->leftChild == NULL&&root->rightChild == NULL)
			return 0;
		if (root->leftChild != NULL&&root->rightChild != NULL)
			return one(root->leftChild) + one(root->rightChild);
	}
}

template<class T>int BinaryTree<T>::leaf(BinaryTreeNode<T>* root) {
	if (root != NULL) {
		if (root->leftChild == NULL&&root->rightChild != NULL)
			return leaf(root->rightChild);
		if (root->leftChild != NULL&&root->rightChild == NULL) {
			return leaf(root->leftChild);
		}
		if (root->leftChild == NULL&&root->rightChild == NULL)
			return 1;
		if (root->leftChild != NULL&&root->rightChild != NULL)
			return leaf(root->leftChild) + leaf(root->rightChild);
	}
}

