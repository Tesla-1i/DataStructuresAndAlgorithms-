#include"BInTree.h"

int main() {
	cout << "�������ַ�ǰ�����г���: ";
	int l; cin >> l;
	cout << "��������������ַ�\n";
	char *a1 = new char[l];
	for (int i = 0; i < l; i++)
		cin >> (a1[i]);
	cout << "�����������ַ�������������\n";
	char *b1 = new char[l];
	for (int i = 0; i < l; i++)
		cin >> (b1[i]);
	BinaryTree<char>* bt1 = new BinaryTree<char>;
	bt1->createTree(bt1->createTreeByPreInOrder(a1, 0, l - 1, b1, 0, l - 1));
	cout << "��������\n";
	bt1->postOrder(bt1->root);
	//////////////////////////
	int one = bt1->one(bt1->root);
	cout << "��Ϊ1������ " << one << "\n";
	int two = bt1->two(bt1->root);
	cout << "��Ϊ2������ " << two << "\n";
	int leaf = bt1->leaf(bt1->root);
	cout << "��Ϊ0������ " << leaf << "\n";
	int height = bt1->getHeight(bt1->root);
	cout << "�������߶��� " << height << "\n";
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
	cout << "\n��������� " << width << "\n";
	cout << "������ֵ " << (bt1->getMax(bt1->root)) << "\n";
	bt1->change(bt1->root);
	cout << "�������Һ���֮���α���\n";
	bt1->levelOrder(bt1->root);
	cout << "\n" << "ɾ��Ҷ�ӽڵ���α���\n";
	bt1->deleteLeaf(bt1->root);
	bt1->levelOrder(bt1->root);
	bool bl = bt1->isCompleteTree();
	cout << "�����Ƿ���ȫ������ " << ((bl == true) ? "true" : "false") << "\n";
}