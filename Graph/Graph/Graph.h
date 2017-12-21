//利用邻接矩阵构造图
//有向图
//只需改setEdge和delEdge
#include<iostream>
#include<queue>
#include"MinHeap.h"
#include"UFsets.h"
using namespace std;

#ifndef GRAPH
#define GRAPH

template<class T>class Edge {
public:
	int start;
	int end;
	T weight;	//权重,起始和终止结点
	Edge(){}
	Edge(int st, int en, int w) {
		start = st; end = en; weight = w;
	}
	//重载运算符,比较权重
	bool operator >(Edge oneEdge) {
		if (weight > oneEdge.weight) return true;
		else return false;
	}
	bool operator <(Edge oneEdge) {
		if (weight < oneEdge.weight)return true;
		else return false;
	}
	void printEdge() {
		cout << "边 <" << start << " , " << end << "> 权重: " << weight << "\n";
	}
};

template<class T>class Graph {
public:
	int vertexNum;
	int edgeNum;
	int *Mark;	//标志顶点vertex是否被访问过的数组
	int **matrix;	//指向邻接矩阵的指针
	Graph(int verticesNum) {
		vertexNum = verticesNum;	//初始化顶点个数
		edgeNum = 0;
		////////////
		Mark = new int[vertexNum];
		for (int i = 0; i < vertexNum; i++)
			Mark[i] = 0;	//标志位初始化为未被访问,0,入度初始化为0
		////////////
		int i, j;
		matrix = (int **)new int*[vertexNum];	//申请行数等于vertexNum的数组,每一个元素是一个指针
		for (i = 0; i < vertexNum; i++)
			matrix[i] = new int[vertexNum];	//申请矩阵matrix中每一行的空间
		for (i = 0; i < vertexNum; i++)
			for (j = 0; j < vertexNum; j++)
				matrix[i][j] = 0;	//初始化邻接矩阵值为0,表示没有边,有的代码认为存个大的数作为没有边
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	~Graph() {
		for (int i = 0; i < vertexNum; i++)
			delete[] matrix[i];	//释放每一行
		delete[] matrix;
		delete[] Mark;
	}
	Edge<T> firstEdge(int oneVertix);	//返回顶点的第一条边
	Edge<T> nextEdge(Edge<T> oneEdge);	//返回与边有相同始点的下一条边
	int startVertex(Edge<T> oneEdge) {
		return oneEdge.start;	//返回边的始点
	}
	int endVertex(Edge<T> oneEdge) {
		return oneEdge.end;
	}
	void setEdge(int start, int end, T weight) {//设置无向图的边和权重,start,end从0计数
		if (matrix[start][end] == 0) edgeNum++;	//本来两节点没有边,新增边
		matrix[start][end] = weight;
		//matrix[start][end] = weight;
		//matrix[end][start] = weight;
	}
	void delEdge(int start, int end) {
		if (matrix[start][end] != 0) edgeNum--;	//本来有边
		matrix[start][end] = 0;	//本来没边时,实话,没用
		//matrix[end][start] = 0;
		//存为0,表示没有边
	}

	bool isEdge(Edge<T> oneEdge) {//////////可能有点问题////////
		//if (oneEdge.weight > 0 && (oneEdge.start >= 0 && oneEdge < vertexNum) && (oneEdge.end >= 0 && oneEdge < vertexNum))
		//	return true;
		//else return false;
		if (oneEdge.weight > 0 &&oneEdge.weight<1000 )
			return true;
		else return false;
	}
	void visit(int v) {
		cout << "已访问顶点 " << v << "\n";
	}
	void DFS(int v);	//从顶点v开始的深度优先遍历
	void DFSTraverse();	//图的深度优先搜索
	void BFS(int v);	//从顶点开始的广度优先搜索
	void BFSTraverse();	//图的广度优先搜索
	Edge<T>* Prim(int s);	//最小生成树Prim算法,s为起点
	void PrimOne(int s);
	void Kruskal();
	void Dijkstra(int s, T *D, int *Path);	//单源最短路径 s是源点,D最短路径长度数组,Path[i]是i的前驱编号
	void Floyd(Graph<T>& G, T **Adj, int **Path);	//顶点对间的最短路径
	bool TopologySort(int* SortArray);	//拓扑排序
	void TologySortDisplay();
	void Poquan();	//破圈法求无向连通图最小生成树
	bool Liantong();	//判断是否联通
	void DFS1(int v);
};

#endif // !GRAPH
//返回顶点的第一条边
template<class T>Edge<T> Graph<T>::firstEdge(int oneVertix) {	//返回顶点的第一条边
	//if (oneVertix < 0 || oneVertix >= vertexNum) {
	//	cout << "不存在的顶点,返回Edge(0,0,0)\n";
	//	Edge<T> e(0, 0, 0);
	//	return e;
	//}
	Edge<T> tmpEdge;
	tmpEdge.start = oneVertix;	//返回边的起点就是oneVertex
	for (int i = 0; i < vertexNum; i++) {
		if (matrix[oneVertix][i] != 0) {
			tmpEdge.end = i;
			tmpEdge.weight = matrix[oneVertix][i];
			break;
		}
	}
	return tmpEdge;
}
//返回与边有相同始点的下一条边,不是前一条边,
template<class T>Edge<T> Graph<T>::nextEdge(Edge<T> oneEdge){
	Edge<T> tmpEdge;
	tmpEdge.start = oneEdge.start;
	for (int i = oneEdge.end + 1; i < vertexNum; i++) {	//起始列很重要
		if (matrix[oneEdge.start][i] != 0) {
			tmpEdge.end = i;
			tmpEdge.weight = matrix[oneEdge.start][i];
			break;
		}
	}
	return tmpEdge;
}
//从顶点v开始的深度优先遍历
template<class T>void Graph<T>::DFS(int v){
	Mark[v] = 1;	//标记结点已访问
	visit(v);
	//由该节点所关联的边进行深度优先搜索
	for (Edge<T> ee = firstEdge(v); isEdge(ee); ee = nextEdge(ee)) {	//isEdge可能有问题
		//访问v邻接的未被访问的顶点
		if (Mark[ee.end] == 0) 
			DFS(ee.end);
	}
}
//图的深度优先搜索
template<class T>void Graph<T>::DFSTraverse(){
	for (int i = 0; i < vertexNum; i++)
		Mark[i] = 0;	//初始化为未访问
	for (int i = 0; i < vertexNum; i++) {
		//检查图是否有没有访问的结点
		if (Mark[i] == 0)
			DFS(i);
	}
}

//可能有点问题
template<class T>void Graph<T>::BFS(int v){
	queue<int> Q;
	Mark[v] = 1;
	visit(v);
	Q.push(v);
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		for (Edge<T> e = firstEdge(v); isEdge(e); e = nextEdge(e)) {
			int u = Mark[e.end];
			int m = e.end;
			if (u == 0) {
				visit(m);
				Mark[m] = 1;
				Q.push(m);
			}
		}
	}
}

template<class T>void Graph<T>::BFSTraverse(){
	int v;
	for (v = 0; v < vertexNum; v++)
		Mark[v] = 0;
	for (v = 0; v < vertexNum; v++) {
		if (Mark[v] == 0)
			BFS(v);
	}
}

template<class T>
Edge<T>* Graph<T>::Prim(int s)
{
	int i, j;
	Edge<T> *MST;	//存放最小生成树的边
	T *nearest;	//nearest[i]表示生成树中点到i点的最小边权值
	int *neighbor;	//neighbor[i]表示生成树中与i最近的点的编号
	int n = vertexNum;	//顶点个数
	nearest = new T[n];
	neighbor = new int[n];
	MST = new Edge<T>[n - 1];
	//MST = new T[n - 1];
	for (i = 0; i < n; i++) {
		neighbor[i] = s;
		
		nearest[i] = 1000;	//最小边权值初始化为1000,
	}
	//与s邻接的顶点的边权值作为这些点距离生成树集合的最短边长
	for (Edge<T> e = firstEdge(s); isEdge(e); e = nextEdge(e)) {
		nearest[e.end] = e.weight;
		//nearest[i] = e.weight;
		//i++;
	}
	neighbor[s] = -1;	//将以加入生成树的点的最近邻设置为-1
	for (i = 0; i < n; i++) {
		//i标记已加入到生成树的点的个数
		T min = 1000;
		int v = -1;
		for (j = 0; j < n; j++) {
			//确定一个顶点在生成树集合一个定点不在生成树集合且权值最小的边所关联的顶点
			if (nearest[j]<min&&neighbor[j]>-1) {
				min = nearest[j];
				v = j;
			}
		}
		if (v >= 0) {
			//将v加入到生成树集合,更新到生成树外的各点最小权值的边信息
			//neighbor[v] = -1;
			Edge<T> tempEdge(neighbor[v], v, nearest[v]);
			neighbor[v] = -1;	//将以加入生成树的点的最近邻设置为-1,课本上语句顺序有问题
			MST[i] = tempEdge;
			for (Edge<T> e = firstEdge(v); isEdge(e); e = nextEdge(e)) {
				int u = e.end;
				if (neighbor[u] != -1 && nearest[u] > e.weight) {
					//用与v关联的边更新生成树之外顶点到生成树集合的最小权值边
					neighbor[u] = v;
					nearest[u] = e.weight;
				}
			}
		}
	}
	//delete[] neighbor;
	//delete[] nearest;
	cout << "Prim算法的输出结果(图4-15)\n";
	for (i = 0; i < n - 1; i++)
		cout << "<" << MST[i].start << " , " << MST[i].end << "> " << MST[i].weight << "\t";
	return MST;
}

template<class T>
void Graph<T>::PrimOne(int s)//应用Prim算法从s顶点出发得到的最小生成树
{
	int i, j;
	int n = vertexNum;
	Edge<T> * MST = new Edge<T>[n - 1];
	T * nearest = new T[n];
	int * neighbor = new int[n];
	for (i = 0; i<n; i++)
	{
		neighbor[i] = s;//表示生成树中与i点最近的点的编号
		nearest[i] = 100;//生成树中到i点的最小边权值
	}
	for (Edge<T> e = firstEdge(s); isEdge(e); e = nextEdge(e))
	{
		nearest[e.end] = e.weight;
	}
	neighbor[s] = -1;
	for (i = 0; i<n; i++)//i标记已经加入树中的点的个数
	{
		T min = 100;
		int v = -1;
		for (j = 0; j<n; j++)
		{
			if (nearest[j]<min&&neighbor[j]>-1)
			{
				min = nearest[j];
				v = j;
			}
		}
		if (v >= 0)
		{
			Edge<T> tempEdge(neighbor[v], v, nearest[v]);
			neighbor[v] = -1;
			MST[i] = tempEdge;
			for (Edge<T> e = firstEdge(v); isEdge(e); e = nextEdge(e))
			{
				int u = e.end;
				if (neighbor[u] != -1 && nearest[u]>e.weight)
				{
					neighbor[u] = v;
					nearest[u] = e.weight;
				}
			}
		}
	}
	cout << "\nPrim算法输出边的结果\n";
	for (i = 0; i<n - 1; i++)
		cout << MST[i].start<<" " << MST[i].end << "\t";
	cout << endl;
}
template<class T>void Graph<T>::Kruskal() {

	//int n = vertexNum;
	//UFSets set(n);
	//Edge<T> * MS = new Edge<T>[n - 1];
	//minheap<Edge<T>> H(edgeNum);
	//Edge<T> edge;
	//for (int i = 0; i<vertexNum; i++)
	//{
	//	for (edge = firstEdge(i); isEdge(edge); edge = nextEdge(edge))
	//	{
	//		if (startVertex(edge)<endVertex(edge))
	//			H.insert(edge);
	//	}
	//}
	//int edgenu = 0;
	//while (edgenu<n - 1)
	//{
	//	if (!H.isempty())
	//	{
	//		edge = H.removemin();
	//		int v = edge.start;
	//		int u = edge.end;
	//		if (set.Find(v) != set.Find(u))
	//		{
	//			set.Union(v, u);
	//			MS[edgenu++] = edge;
	//		}
	//	}
	//}
	//for (int m = 0; m<edgenu; m++)
	//	cout << MS[m].start << MS[m].end << MS[m].weight << ' ';
	//cout << endl;

	//求含有n个结点e条边的最小生成树
	int n = vertexNum;
	UFSets set(n);	//n个结点的等价类
	Edge<T>* MST = new Edge<T>[n - 1];	//记录最小生成树的边
	minheap<Edge<T>> H(edgeNum);	//定义e个元素的最小堆
	Edge<T> edge;
	for (int i = 0; i < vertexNum; i++) {
		for (edge = firstEdge(i); isEdge(edge); edge = nextEdge(edge)) {
			if (startVertex(edge) < endVertex(edge)) {//避免无向图的边被重复考察
				H.insert(edge);
			}
		}
	}
	int edgeNum = 0;	//生成树的边的个数
	while (edgeNum < n - 1) {
		//n个结点的连通图生成树有n-1个边
		if (!H.isempty()) {
			edge = H.removemin();	//找到权重最小的未处理的边
			int v = edge.start;
			int u = edge.end;
			if (set.Find(v) != set.Find(u)) {
				//判断该边关联的顶点是否在一个联通分量
				set.Union(v, u);	//不在,合并两个顶点所在的等价类
				//将符合条件的边添加到生成树的边集合
				MST[edgeNum++] = edge;
			}
		}
	}
	cout << "\nKruskal算法的输出结果(图4-17)\n";
	for (int i = 0; i < edgeNum; i++) {
		cout << "<" << MST[i].start << " , " << MST[i].end << "> " << MST[i].weight << "\t";
	}
}

template<class T>void Graph<T>::Dijkstra(int s, T *D, int *Path) {
	int n = vertexNum;
	//D = new T[n];
	//Path = new int[n];
	int i, j;
	for (i = 0; i < n; i++) {
		Mark[i] = 0;	//未访问
		D[i] = 1000;	//路径无穷长
		Path[i] = -1;	//标记此时不存在s到i的路径,则无前驱顶点
	}
	Mark[s] = 1;	//已访问
	D[s] = 0;
	Path[s] = s;
	for (i = 0; i < n; i++) {
		//找到一条最短路径
		T min = 1000;
		int k = 0;
		for (j = 1; j < n; j++) {
			if (Mark[j] == 0 && min > D[j]) {
				min = D[j];
				k = j;
			}
		}
		//已经确定s到k的最短路径
		Mark[k] = 1;
		//利用k更新到其余未访问顶点的最短特殊路径
		for (Edge<T> e = firstEdge(k); isEdge(e); e = nextEdge(e)) {
			int endVertex = e.end;
			if (Mark[endVertex] == 0 && D[endVertex] > (D[k] + e.weight)) {
				//更新到endVertex的最短特殊路径
				D[endVertex] = D[k] + e.weight;
				Path[endVertex] = k;
			}
		}
	}
	cout << "\nDjikstra算法(图4-18)";
	cout << "\n最短路径长度\n";
	for (i = 0; i < n; i++)
		cout << D[i] << "\t";
	cout << "\n前驱结点\n";
	for (i = 0; i < n; i++)
		cout << Path[i] << "\t";
	cout << "\n";
	//PrintPath(Path);
}



void PrintPath(int* Path) {
	if (*Path>0) {
		int i = 0;
		int num = *Path;
		while (Path[i] != NULL) {
			if (Path[i] == num)break;
		}
		PrintPath(&Path[i]);
		cout << (*Path) << "\t";
	}
	else {
		
		cout << (*Path);
	}
}
template<class T>void Graph<T>::Floyd(Graph<T>& G, T ** Adj, int ** Path){
	int i, j, v;	//v是记录相应顶点
	int n = G.vertexNum;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {	//初始化Adj数组和Path数组
			if (i == j) {
				Adj[i][j] = 0;
				Path[i][j] = i;
			}
			else {
				Adj[i][j] = 1000;
				Path[i][j] = -1;
			}
		}
	}
	for (v = 0; v < n; v++) {	//检查个条边,将e.weight的值作为Adj[v][e.end],v作为Path[v][e.end]的值
		for (Edge<T> e = G.firstEdge(v); G.isEdge(e); e = G.nextEdge(e)) {
			Adj[v][e.end] = e.weight;
			Path[v][e.end] = v;
		}
	}
	//如果两个顶点ij间最短经过v的路径,且adj[i][j]>(adj[i][v]+adj[v][j]),
	//则更新adj[i][j]和path[i][j]
	//三层循环
	for (v = 0; v < n; v++) {	//允许经过的中转顶点v(v自0到n-1变大)
		for (i = 0; i < n; i++) {	//矩阵的i行
			for (j = 0; j < n; j++) {	//矩阵的j列
				if (Adj[i][j] > (Adj[i][v] + Adj[v][j])) {
					Adj[i][j] = Adj[i][v] + Adj[v][j];	//更新最短路径
					Path[i][j] = v;		//更新前驱(中转站)
				}
			}
		}
	}
}
template<class T>bool Graph<T>::TopologySort(int* SortArray) {
	//拓扑排序序列存在SortArray
	int n = vertexNum;
	int *indegree = new int[n];	//各个顶点的入度值
	int i, v;
	Edge<T> e;
	for (v = 0; v < n; v++) {
		//入度初始化为0,状态标记为未访问
		indegree[v] = 0;
		Mark[v] = 0;
	}
	for (v = 0; v < n; v++) {
		//统计各个顶点的入度信息
		for (e = firstEdge(v); isEdge(e); e = nextEdge(e)) {
			indegree[e.end]++;
		}
	}
	for (i = 0; i < n; i++) {
		//确定拓扑序列SortArray
		//找到入度为0且未被访问的顶点
		for (v = 0; v < n; v++) {
			if (indegree[v] == 0 && Mark[v] == 0) {
				break;
			}
		}
		if (v == n) {
			return false;	//找不到入度为0的顶点,有回路,返回false
		}
		Mark[v] = 1;
		SortArray[i] = v;
		for (e = firstEdge(v); isEdge(e); e = nextEdge(e)) {
			//修改v指向的顶点的入度
			indegree[e.end]--;
		}
	}
	return true;
}
template<class T>void Graph<T>::TologySortDisplay() {
	int n = vertexNum;
	int *sortArray =new int[n];
	if (TopologySort(sortArray)) {
		cout << "没有回路,拓扑序列是(图4-18)\n";
		for (int i = 0; i < n; i++) {
			cout << sortArray[i] << "\t";
		}
		cout << "\n";
	}
	else {
		Edge<T> e;
		cout << "有回路存在,一个回路是(图4-18)\n";
		for (int i = 0; i < n; i++) {
			for (e = firstEdge(i); isEdge(e); e = nextEdge(e)) {
				if (Mark[e.end] == 0)
					break;	//找到没有被访问的一个结点,此节点一定在自圈中
			}
		}
		cout << e.end << "\t";
		Mark[e.end] = 1;
		for(e=firstEdge(e.end);isEdge(e)&&Mark[e.end]==0;e=firstEdge(e.end)){
			cout << e.end << "\t";
			Mark[e.end] = 1;
		}
		cout << "\n";
	}
}

template<class T>void Graph<T>::DFS1(int v) {
	Mark[v] = 1;	//标记结点已访问
	//由该节点所关联的边进行深度优先搜索
	for (Edge<T> ee = firstEdge(v); isEdge(ee); ee = nextEdge(ee)) {	//isEdge可能有问题
																		//访问v邻接的未被访问的顶点
		if (Mark[ee.end] == 0)
			DFS1(ee.end);
	}
}
template<class T>bool Graph<T>::Liantong() {
	int count = 0;
	int n = vertexNum;
	for (int i = 0; i < n; ++i)
		Mark[i] = 0;	//初始化为未访问
	for (int i = 0; i < n; ++i) {
		if (!Mark[i]) {
			DFS1(i);	//深度优先搜索,将访问到的顶点标记为Mark[i]=1
			count++;
		}
	}
	//如果只调用一次DFS(i),就将所有顶点标记为已访问,说明是联通图
	if (count == 1) {
		return true;
	}
	else {
		return false;
	}
}
template<class T>void Graph<T>::Poquan() {
	int n = vertexNum;
	int v;
	Edge<T> e;
	maxheap<Edge<T>> H(edgeNum);
	for (v = 0; v < n; v++) {
		for (e = firstEdge(v); isEdge(e); e = nextEdge(e)) {
			if (e.start < e.end) {
				//无向图的要求
				H.insert(e);
			}
		}
	}
	while (!H.isempty()) {
		e = H.removemax();
		int weight1 = matrix[e.start][e.end];
		int weight2 = matrix[e.end][e.start];
		matrix[e.start][e.end] = 0;
		matrix[e.end][e.start] = 0;
		//matrix[e.start][e.end] = matrix[e.end][e.start] = 1000;
		//先删除最大边,置为0,表示没有边
		if (!Liantong()) {
			//删除最大边后原图不再联通了,则恢复最大边
			//因为我们求得是最小生成树,每个点均连通
			//此时说明这个最大边是桥不是圈上的最大边
			//否则,删除的边正是圈上的最大边
			matrix[e.start][e.end] = weight1;
			matrix[e.end][e.start] = weight2;
		}
		//或者判断从一个结点开始遍历，如果遍历过程中还会回到已经访问过的结点，则证明存在环，然后去除环中最大边
	}
	cout << "破圈法求得的最小生成树(图4-15)\n";
	for (v = 0; v < vertexNum; v++) {
		for (e = firstEdge(v); isEdge(e); e = nextEdge(e)) {
			if (e.start < e.end) {
				//无向图的要求
				cout << "<" << e.start << "," << e.end << "> " << e.weight << "\t \t";
			}
		}
	}
}