//判断二叉树是否为完全二叉树
//ttp://blog.csdn.net/ONEDAY_789/article/details/54928613
#include"BinTree.h"

int main() {
	cout << "请输入数字前序序列长度: ";
	int l; cin >> l;
	cout << "请依次输入各个数字,按前序序列\n";
	int *a1 = new int[l];
	for (int i = 0; i < l; i++)
		cin >> (a1[i]);
	cout << "请依次输入数字，按中序序列\n";
	int *b1 = new int[l];
	for (int i = 0; i < l; i++)
		cin >> (b1[i]);
	BinaryTree<int>* bt1 = new BinaryTree<int>;
	bt1->createTree(bt1->createTreeByPreInOrder(a1, 0, l - 1, b1, 0, l - 1));
	bool isSearchTree = bt1->judgeTree(bt1->root);
	if (isSearchTree)
		cout << "是二叉搜索树\n";
	else
		cout << "不是二叉搜索树\n";
	//cout << "后序序列\n";
	//bt1->postOrder(bt1->root);
	//bool bl = bt1->isCompleteTree();
	//cout << ((bl == true) ? "true" : "false") << "\n";
}

