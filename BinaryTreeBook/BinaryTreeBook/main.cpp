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
	cout << "层次遍历\n";
	bt.levelOrder(bt.root);
	//int i;
	//srand((int)time(NULL));     //每次执行种子不同，生成不同的随机数
	//for (i = 0; i<10; i++)
	//{
	//	printf("%d\n", rand()%2);  //因为执行太快，不到一秒钟，10个随机数是相通的，但是每次执行是不同的 
	//}
}