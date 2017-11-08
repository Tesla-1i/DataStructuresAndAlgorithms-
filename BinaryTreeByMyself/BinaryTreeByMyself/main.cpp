#include"Bintree.h"

int main() {
	cout << "节点个数: ";
	int num; cin >> num;
	BinaryTreeNode<float>* bt = new BinaryTreeNode<float>[num];
	cout << "输入节点数据\n";
	for (int i = 0; i < num; i++) {
		float nu;
		cin >> nu;
		bt[i].setData(nu);
	}
	bt[0].setLeftChild(&bt[1]);
	bt[0].setRightChild(&bt[2]);
	bt[1].setLeftChild(&bt[3]);
	bt[1].setRightChild(&bt[4]);
	
	BinaryTree<float> btTree;
	btTree.createTree(&bt[0]);
	cout << "层次遍历\n";
	btTree.levelOrder(btTree.root);
	cout << "前序遍历\n";
	btTree.preOrder(btTree.root);
}