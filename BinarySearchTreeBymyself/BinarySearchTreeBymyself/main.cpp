#include"BinTree.h"

int main() {
	BinaryTree<int>* btree = new BinaryTree<int>;
	int num = 0;
	cout << "������: ";
	cin >> num;
	int *arr = new int[num];
	cout << "�������ν�㣺\n";
	for (int i = 0; i < num; i++)
		cin >> arr[i];
	for (int i = 0; i < num; i++)
		btree->insertNode(arr[i]);
	cout << "������ȱ���\n";
	btree->levelOrder(btree->root);
	cout << "������ҵĽ��ֵ: ";
	int v; cin >> v;
	BinaryTreeNode<int>* pv = btree->searchNode(v);
	cout << pv->data << "\n";
	cout << "����ɾ���Ľ��: ";
	cin >> v;
	bool b = btree->deleteNode(v);
	if (b) {
		cout << "������ȱ���\n";
		btree->levelOrder(btree->root);
	}
	else
		cout << "ɾ��ʧ�ܣ�������ֵ\n";
	return 0;
}