//判断二叉树是否为完全二叉树
//ttp://blog.csdn.net/ONEDAY_789/article/details/54928613
#include"BinTree.h"

int main() {
	cout << "请输入字符前序序列长度: ";
	int l; cin >> l;
	cout << "请依次输入各个字符,按前序序列\n";
	char *a1 = new char[l];
	for (int i = 0; i < l; i++)
		cin >> (a1[i]);
	cout << "请依次输入字符，按中序序列\n";
	char *b1 = new char[l];
	for (int i = 0; i < l; i++)
		cin >> (b1[i]);
	BinaryTree<char>* bt1 = new BinaryTree<char>;
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

