#include"BinTree.h"

int main() {
	BinaryTree<int>* btree = new BinaryTree<int>;
	int num = 0;
	cout << "���ͽ�����: ";
	cin >> num;
	int *arr = new int[num];
	cout << "�������ͽ�㣺\n";
	for (int i = 0; i < num; i++)
		cin >> arr[i];
	for (int i = 0; i < num; i++)
		btree->insertNode(arr[i]);
	cout << "������ȱ���\n";
	btree->levelOrder(btree->root);
	int numOfLeaf = btree->leaf(btree->root);
	cout << "Ҷ�ӽڵ������ " << numOfLeaf << "\n";
	cout << "����Kֵ,�������k�Ĺؼ��� ";
	int k; cin >> k;
	btree->searchBiggerNode(btree->root, k);
	//bool b = btree->judgeTree(btree->root);
	//if (b)
	//	cout << "�Ƕ���������\n";
	//else
	//	cout << "���Ƕ���������\n";
	//cout << "������ҵĽ��ֵ: ";
	//int v; cin >> v;
	//BinaryTreeNode<int>* pv = btree->searchNode(v);
	//cout << pv->data << "\n";
	//cout << "����ɾ���Ľ��: ";
	//cin >> v;
	//bool b = btree->deleteNode(v);
	//if (b) {
	//	//cout << "������ȱ���\n";
	//	//btree->levelOrder(btree->root);
	//	//btree->preOrder(btree->root);
	//}
	//else {
	//	cout << "ɾ��ʧ�ܣ�������ֵ\n";
	//	btree->levelOrder(btree->root);
	//}
	//return 0;
}