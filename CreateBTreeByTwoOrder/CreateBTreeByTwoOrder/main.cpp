#include"BinTree.h"

int main() {
	char a[] = { 'a','b','d','f','g','c','e','h' };
	char b[] = { 'b','f','d','g','a','c','e','h' };
	BinaryTree<char>* bt = new BinaryTree<char>;
	bt->createTree(bt->createTreeByPreInOrder(a, 0, 7, b, 0, 7));
	bt->postOrder(bt->root);
	char c[] = { 'f','g','d','b','h','e','c','a' };
	bt->createTree(bt->createTreeByPostInOrder(c, 0, 7, b, 0, 7));
	cout << "-------------------------------\n";
	bt->preOrder(bt->root);
	cout << "-------------------------------\n";
	cout << "请输入字符前序序列长度: ";
	int l; cin >> l;
	cout << "请依次输入各个字符\n";
	char *a1 = new char[l];
	for (int i = 0; i < l; i++)
		cin >> (a1[i]);
	cout << "请依次输入字符，按中序序列\n";
	char *b1 = new char[l];
	for (int i = 0; i < l; i++)
		cin >> (b1[i]);
	BinaryTree<char>* bt1 = new BinaryTree<char>;
	bt1->createTree(bt1->createTreeByPreInOrder(a1, 0, l - 1, b1, 0, l - 1));
	cout << "后序序列\n";
	bt1->postOrder(bt1->root);
}