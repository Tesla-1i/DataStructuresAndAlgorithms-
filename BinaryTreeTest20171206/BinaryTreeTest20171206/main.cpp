#include"BinTree.h"

int main() {
	BinaryTree<int>* btree = new BinaryTree<int>;
	int num = 0;
	cout << "整型结点个数: ";
	cin >> num;
	int *arr = new int[num];
	cout << "输入整型结点：\n";
	for (int i = 0; i < num; i++)
		cin >> arr[i];
	for (int i = 0; i < num; i++)
		btree->insertNode(arr[i]);
	cout << "广度优先遍历\n";
	btree->levelOrder(btree->root);
	int numOfLeaf = btree->leaf(btree->root);
	cout << "叶子节点个数是 " << numOfLeaf << "\n";
	cout << "输入K值,输出大于k的关键码 ";
	int k; cin >> k;
	btree->searchBiggerNode(btree->root, k);
	//bool b = btree->judgeTree(btree->root);
	//if (b)
	//	cout << "是二叉搜索树\n";
	//else
	//	cout << "不是二叉搜索树\n";
	//cout << "输入查找的结点值: ";
	//int v; cin >> v;
	//BinaryTreeNode<int>* pv = btree->searchNode(v);
	//cout << pv->data << "\n";
	//cout << "输入删除的结点: ";
	//cin >> v;
	//bool b = btree->deleteNode(v);
	//if (b) {
	//	//cout << "广度优先遍历\n";
	//	//btree->levelOrder(btree->root);
	//	//btree->preOrder(btree->root);
	//}
	//else {
	//	cout << "删除失败，不存在值\n";
	//	btree->levelOrder(btree->root);
	//}
	//return 0;
}