//�ж϶������Ƿ�Ϊ��ȫ������
//ttp://blog.csdn.net/ONEDAY_789/article/details/54928613
#include"BinTree.h"

int main() {
	cout << "�������ַ�ǰ�����г���: ";
	int l; cin >> l;
	cout << "��������������ַ�,��ǰ������\n";
	char *a1 = new char[l];
	for (int i = 0; i < l; i++)
		cin >> (a1[i]);
	cout << "�����������ַ�������������\n";
	char *b1 = new char[l];
	for (int i = 0; i < l; i++)
		cin >> (b1[i]);
	BinaryTree<char>* bt1 = new BinaryTree<char>;
	bt1->createTree(bt1->createTreeByPreInOrder(a1, 0, l - 1, b1, 0, l - 1));
	bool isSearchTree = bt1->judgeTree(bt1->root);
	if (isSearchTree)
		cout << "�Ƕ���������\n";
	else
		cout << "���Ƕ���������\n";
	//cout << "��������\n";
	//bt1->postOrder(bt1->root);
	//bool bl = bt1->isCompleteTree();
	//cout << ((bl == true) ? "true" : "false") << "\n";
}

