#include"Graph.h"
int main() {
	//Graph<int> *graph1 = new Graph<int>(8);	//要求无向图
	//graph1->setEdge(0, 1, 1);
	//graph1->setEdge(1, 3, 1);
	//graph1->setEdge(1, 4, 1);
	//graph1->setEdge(3, 7, 1);
	//graph1->setEdge(4, 7, 1);
	//graph1->setEdge(0, 2, 1);
	//graph1->setEdge(2, 5, 1);
	//graph1->setEdge(2, 6, 1);
	//graph1->setEdge(5, 6, 1);
	//cout << "深度优先搜索树\n";
	//graph1->DFSTraverse();
	//cout << "广度优先搜索树\n";
	//graph1->BFSTraverse();

	//cout << "输入要加边的两个顶点的索引\n";
	//int f1, f2;
	//cin >> f1 >> f2;
	//if (f1 < 0 || f1 >= 8 || f2 < 0 || f2 >= 8) {
	//	cout << "索引越界,重新输入两个顶点\n";
	//	cin >> f1 >> f2;
	//}
	//graph1->setEdge(f1, f2, 1);
	//cout << "深度优先搜索树\n";
	//graph1->DFSTraverse();
	//cout << "输入要删边的两个顶点的索引\n";
	//cin >> f1 >> f2;
	//if (f1 < 0 || f1 >= 8 || f2 < 0 || f2 >= 8) {
	//	cout << "索引越界,重新输入两个顶点\n";
	//	cin >> f1 >> f2;
	//}
	//graph1->delEdge(f1, f2);
	//cout << "深度优先搜索树\n";
	//graph1->DFSTraverse();

	Graph<int>* graph2 = new Graph<int>(6);
	graph2->setEdge(0, 1, 6);
	graph2->setEdge(0, 2, 1);
	graph2->setEdge(0, 3, 5);
	graph2->setEdge(1, 4, 3);
	graph2->setEdge(1, 2, 5);
	graph2->setEdge(2, 3, 5);
	graph2->setEdge(2, 4, 6);
	graph2->setEdge(2, 5, 4);
	graph2->setEdge(3, 5, 2);
	graph2->setEdge(4, 5, 6);
	//设为无向图
	graph2->setEdge(1, 0, 6);
	graph2->setEdge(2, 0, 1);
	graph2->setEdge(3, 0, 5);
	graph2->setEdge(4, 1, 3);
	graph2->setEdge(2, 1, 5);
	graph2->setEdge(3, 2, 5);
	graph2->setEdge(4, 2, 6);
	graph2->setEdge(5, 2, 4);
	graph2->setEdge(5, 3, 2);
	graph2->setEdge(5, 4, 6);
	//graph2->Poquan();
	Edge<int>* edgeArrayOfMST = graph2->Prim(0);
	////edgeArrayOfMST[0].printEdge();
	////graph2->PrimOne(0);
	graph2->Kruskal();
	//最短路径需要有向图
	Graph<int> *graph3 = new Graph<int>(6);
	graph3->setEdge(0, 1, 12);
	graph3->setEdge(0, 2, 10);
	graph3->setEdge(0, 4, 30);
	graph3->setEdge(0, 5, 100);
	graph3->setEdge(1, 2, 5);
	graph3->setEdge(2, 3, 50);
	graph3->setEdge(3, 5, 10);
	graph3->setEdge(4, 3, 20);
	graph3->setEdge(4, 5, 60);
	int *D = new int[graph3->vertexNum];
	int *Path = new int[graph3->vertexNum];
	graph3->Dijkstra(0, D, Path);
	Graph<int>* graph4 = new Graph<int>(3);
	graph4->setEdge(0, 1, 10);
	graph4->setEdge(0, 2, 5);
	graph4->setEdge(1, 0, 9);
	graph4->setEdge(1, 2, 6);
	graph4->setEdge(2, 0, 2);
	graph4->setEdge(2, 1, 13);
	//int *Adj = new int[3];
	//Adj[0] = new int[3];
	int n = 3;
	int **adj = new int*[n];	//二维数组的定义方式
	for (int i = 0; i < n; i++)
		adj[i] = new int[n];
	int **path = new int*[n];
	for (int i = 0; i < n; i++)
		path[i] = new int[n];
	graph4->Floyd(*graph4, adj, path);
	cout << "Floyd算法(图4-20)";
	cout << "Adj数组\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << adj[i][j] << "\t";
		cout << "\n";
	}
	cout << "Path数组\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << path[i][j] << "\t";
		cout << "\n";
	}
	graph3->TologySortDisplay();
	cout << "////////////////\n";
	//graph2->Poquan();
	Graph <int> tu2(6);
	tu2.setEdge(0, 1, 6);
	tu2.setEdge(0, 2, 1);
	tu2.setEdge(0, 3, 5);
	tu2.setEdge(1, 0, 6);
	tu2.setEdge(1, 2, 5);
	tu2.setEdge(1, 4, 3);
	tu2.setEdge(2, 0, 1);
	tu2.setEdge(2, 1, 5);
	tu2.setEdge(2, 3, 5);
	tu2.setEdge(2, 4, 6);
	tu2.setEdge(2, 5, 4);
	tu2.setEdge(3, 0, 5);
	tu2.setEdge(3, 2, 5);
	tu2.setEdge(3, 5, 2);
	tu2.setEdge(4, 1, 3);
	tu2.setEdge(4, 2, 6);
	tu2.setEdge(4, 5, 6);
	tu2.setEdge(5, 2, 4);
	tu2.setEdge(5, 3, 2);
	tu2.setEdge(5, 4, 6);
	tu2.Poquan();
}
