#include"BInTree.h"

int main() {
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
	//////////////////////////
	int one = bt1->one(bt1->root);
	cout << "度为1结点个数 " << one << "\n";
	int two = bt1->two(bt1->root);
	cout << "度为2结点个数 " << two << "\n";
	int leaf = bt1->leaf(bt1->root);
	cout << "度为0结点个数 " << leaf << "\n";
	int height = bt1->getHeight(bt1->root);
	cout << "二叉树高度是 " << height << "\n";
	int *wid = new int[height];
	for (int i = 0; i < height; i++)
		wid[i] = 0;
	bt1->getWidth(bt1->root, 0, wid);
	int width = wid[0];
	for (int i = 0; i < height; i++) {
		if (width < wid[i])
			width = wid[i];
		cout << wid[i] << "\t";
	}
	cout << "\n二叉树宽度 " << width << "\n";
	cout << "结点最大值 " << (bt1->getMax(bt1->root)) << "\n";
	bt1->change(bt1->root);
	cout << "交换左右孩子之后层次遍历\n";
	bt1->levelOrder(bt1->root);
	cout << "\n" << "删除叶子节点后层次遍历\n";
	bt1->deleteLeaf(bt1->root);
	bt1->levelOrder(bt1->root);
	bool bl = bt1->isCompleteTree();
	cout << "现在是否完全二叉树 " << ((bl == true) ? "true" : "false") << "\n";
}