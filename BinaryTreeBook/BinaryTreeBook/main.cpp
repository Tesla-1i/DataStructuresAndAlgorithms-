#include"BinaryTreeBook.h"

int main() {
	BinaryTree<int> bt;
	BinaryTreeNode<int>* p = new BinaryTreeNode<int>[5];
	for (int i = 1; i < 6; i++)
		p[i-1].element = i;
	p[0].setLeftChild(&p[1]);
	p[0].setRightChild(&p[2]);
	p[1].setLeftChild(&p[3]);
	p[1].setRightChild(&p[4]);
	bt.creatTree(&p[0]);
	bt.preOrderBinTree();
	cout << "��α���\n";
	bt.levelOrder(bt.root);
	//int i;
	//srand((int)time(NULL));     //ÿ��ִ�����Ӳ�ͬ�����ɲ�ͬ�������
	//for (i = 0; i<10; i++)
	//{
	//	printf("%d\n", rand()%2);  //��Ϊִ��̫�죬����һ���ӣ�10�����������ͨ�ģ�����ÿ��ִ���ǲ�ͬ�� 
	//}
}