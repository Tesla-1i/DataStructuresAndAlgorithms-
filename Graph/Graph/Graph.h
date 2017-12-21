//�����ڽӾ�����ͼ
//����ͼ
//ֻ���setEdge��delEdge
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
	T weight;	//Ȩ��,��ʼ����ֹ���
	Edge(){}
	Edge(int st, int en, int w) {
		start = st; end = en; weight = w;
	}
	//���������,�Ƚ�Ȩ��
	bool operator >(Edge oneEdge) {
		if (weight > oneEdge.weight) return true;
		else return false;
	}
	bool operator <(Edge oneEdge) {
		if (weight < oneEdge.weight)return true;
		else return false;
	}
	void printEdge() {
		cout << "�� <" << start << " , " << end << "> Ȩ��: " << weight << "\n";
	}
};

template<class T>class Graph {
public:
	int vertexNum;
	int edgeNum;
	int *Mark;	//��־����vertex�Ƿ񱻷��ʹ�������
	int **matrix;	//ָ���ڽӾ����ָ��
	Graph(int verticesNum) {
		vertexNum = verticesNum;	//��ʼ���������
		edgeNum = 0;
		////////////
		Mark = new int[vertexNum];
		for (int i = 0; i < vertexNum; i++)
			Mark[i] = 0;	//��־λ��ʼ��Ϊδ������,0,��ȳ�ʼ��Ϊ0
		////////////
		int i, j;
		matrix = (int **)new int*[vertexNum];	//������������vertexNum������,ÿһ��Ԫ����һ��ָ��
		for (i = 0; i < vertexNum; i++)
			matrix[i] = new int[vertexNum];	//�������matrix��ÿһ�еĿռ�
		for (i = 0; i < vertexNum; i++)
			for (j = 0; j < vertexNum; j++)
				matrix[i][j] = 0;	//��ʼ���ڽӾ���ֵΪ0,��ʾû�б�,�еĴ�����Ϊ����������Ϊû�б�
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	~Graph() {
		for (int i = 0; i < vertexNum; i++)
			delete[] matrix[i];	//�ͷ�ÿһ��
		delete[] matrix;
		delete[] Mark;
	}
	Edge<T> firstEdge(int oneVertix);	//���ض���ĵ�һ����
	Edge<T> nextEdge(Edge<T> oneEdge);	//�����������ͬʼ�����һ����
	int startVertex(Edge<T> oneEdge) {
		return oneEdge.start;	//���رߵ�ʼ��
	}
	int endVertex(Edge<T> oneEdge) {
		return oneEdge.end;
	}
	void setEdge(int start, int end, T weight) {//��������ͼ�ıߺ�Ȩ��,start,end��0����
		if (matrix[start][end] == 0) edgeNum++;	//�������ڵ�û�б�,������
		matrix[start][end] = weight;
		//matrix[start][end] = weight;
		//matrix[end][start] = weight;
	}
	void delEdge(int start, int end) {
		if (matrix[start][end] != 0) edgeNum--;	//�����б�
		matrix[start][end] = 0;	//����û��ʱ,ʵ��,û��
		//matrix[end][start] = 0;
		//��Ϊ0,��ʾû�б�
	}

	bool isEdge(Edge<T> oneEdge) {//////////�����е�����////////
		//if (oneEdge.weight > 0 && (oneEdge.start >= 0 && oneEdge < vertexNum) && (oneEdge.end >= 0 && oneEdge < vertexNum))
		//	return true;
		//else return false;
		if (oneEdge.weight > 0 &&oneEdge.weight<1000 )
			return true;
		else return false;
	}
	void visit(int v) {
		cout << "�ѷ��ʶ��� " << v << "\n";
	}
	void DFS(int v);	//�Ӷ���v��ʼ��������ȱ���
	void DFSTraverse();	//ͼ�������������
	void BFS(int v);	//�Ӷ��㿪ʼ�Ĺ����������
	void BFSTraverse();	//ͼ�Ĺ����������
	Edge<T>* Prim(int s);	//��С������Prim�㷨,sΪ���
	void PrimOne(int s);
	void Kruskal();
	void Dijkstra(int s, T *D, int *Path);	//��Դ���·�� s��Դ��,D���·����������,Path[i]��i��ǰ�����
	void Floyd(Graph<T>& G, T **Adj, int **Path);	//����Լ�����·��
	bool TopologySort(int* SortArray);	//��������
	void TologySortDisplay();
	void Poquan();	//��Ȧ����������ͨͼ��С������
	bool Liantong();	//�ж��Ƿ���ͨ
	void DFS1(int v);
};

#endif // !GRAPH
//���ض���ĵ�һ����
template<class T>Edge<T> Graph<T>::firstEdge(int oneVertix) {	//���ض���ĵ�һ����
	//if (oneVertix < 0 || oneVertix >= vertexNum) {
	//	cout << "�����ڵĶ���,����Edge(0,0,0)\n";
	//	Edge<T> e(0, 0, 0);
	//	return e;
	//}
	Edge<T> tmpEdge;
	tmpEdge.start = oneVertix;	//���رߵ�������oneVertex
	for (int i = 0; i < vertexNum; i++) {
		if (matrix[oneVertix][i] != 0) {
			tmpEdge.end = i;
			tmpEdge.weight = matrix[oneVertix][i];
			break;
		}
	}
	return tmpEdge;
}
//�����������ͬʼ�����һ����,����ǰһ����,
template<class T>Edge<T> Graph<T>::nextEdge(Edge<T> oneEdge){
	Edge<T> tmpEdge;
	tmpEdge.start = oneEdge.start;
	for (int i = oneEdge.end + 1; i < vertexNum; i++) {	//��ʼ�к���Ҫ
		if (matrix[oneEdge.start][i] != 0) {
			tmpEdge.end = i;
			tmpEdge.weight = matrix[oneEdge.start][i];
			break;
		}
	}
	return tmpEdge;
}
//�Ӷ���v��ʼ��������ȱ���
template<class T>void Graph<T>::DFS(int v){
	Mark[v] = 1;	//��ǽ���ѷ���
	visit(v);
	//�ɸýڵ��������ı߽��������������
	for (Edge<T> ee = firstEdge(v); isEdge(ee); ee = nextEdge(ee)) {	//isEdge����������
		//����v�ڽӵ�δ�����ʵĶ���
		if (Mark[ee.end] == 0) 
			DFS(ee.end);
	}
}
//ͼ�������������
template<class T>void Graph<T>::DFSTraverse(){
	for (int i = 0; i < vertexNum; i++)
		Mark[i] = 0;	//��ʼ��Ϊδ����
	for (int i = 0; i < vertexNum; i++) {
		//���ͼ�Ƿ���û�з��ʵĽ��
		if (Mark[i] == 0)
			DFS(i);
	}
}

//�����е�����
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
	Edge<T> *MST;	//�����С�������ı�
	T *nearest;	//nearest[i]��ʾ�������е㵽i�����С��Ȩֵ
	int *neighbor;	//neighbor[i]��ʾ����������i����ĵ�ı��
	int n = vertexNum;	//�������
	nearest = new T[n];
	neighbor = new int[n];
	MST = new Edge<T>[n - 1];
	//MST = new T[n - 1];
	for (i = 0; i < n; i++) {
		neighbor[i] = s;
		
		nearest[i] = 1000;	//��С��Ȩֵ��ʼ��Ϊ1000,
	}
	//��s�ڽӵĶ���ı�Ȩֵ��Ϊ��Щ��������������ϵ���̱߳�
	for (Edge<T> e = firstEdge(s); isEdge(e); e = nextEdge(e)) {
		nearest[e.end] = e.weight;
		//nearest[i] = e.weight;
		//i++;
	}
	neighbor[s] = -1;	//���Լ����������ĵ�����������Ϊ-1
	for (i = 0; i < n; i++) {
		//i����Ѽ��뵽�������ĵ�ĸ���
		T min = 1000;
		int v = -1;
		for (j = 0; j < n; j++) {
			//ȷ��һ������������������һ�����㲻��������������Ȩֵ��С�ı��������Ķ���
			if (nearest[j]<min&&neighbor[j]>-1) {
				min = nearest[j];
				v = j;
			}
		}
		if (v >= 0) {
			//��v���뵽����������,���µ���������ĸ�����СȨֵ�ı���Ϣ
			//neighbor[v] = -1;
			Edge<T> tempEdge(neighbor[v], v, nearest[v]);
			neighbor[v] = -1;	//���Լ����������ĵ�����������Ϊ-1,�α������˳��������
			MST[i] = tempEdge;
			for (Edge<T> e = firstEdge(v); isEdge(e); e = nextEdge(e)) {
				int u = e.end;
				if (neighbor[u] != -1 && nearest[u] > e.weight) {
					//����v�����ı߸���������֮�ⶥ�㵽���������ϵ���СȨֵ��
					neighbor[u] = v;
					nearest[u] = e.weight;
				}
			}
		}
	}
	//delete[] neighbor;
	//delete[] nearest;
	cout << "Prim�㷨��������(ͼ4-15)\n";
	for (i = 0; i < n - 1; i++)
		cout << "<" << MST[i].start << " , " << MST[i].end << "> " << MST[i].weight << "\t";
	return MST;
}

template<class T>
void Graph<T>::PrimOne(int s)//Ӧ��Prim�㷨��s��������õ�����С������
{
	int i, j;
	int n = vertexNum;
	Edge<T> * MST = new Edge<T>[n - 1];
	T * nearest = new T[n];
	int * neighbor = new int[n];
	for (i = 0; i<n; i++)
	{
		neighbor[i] = s;//��ʾ����������i������ĵ�ı��
		nearest[i] = 100;//�������е�i�����С��Ȩֵ
	}
	for (Edge<T> e = firstEdge(s); isEdge(e); e = nextEdge(e))
	{
		nearest[e.end] = e.weight;
	}
	neighbor[s] = -1;
	for (i = 0; i<n; i++)//i����Ѿ��������еĵ�ĸ���
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
	cout << "\nPrim�㷨����ߵĽ��\n";
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

	//����n�����e���ߵ���С������
	int n = vertexNum;
	UFSets set(n);	//n�����ĵȼ���
	Edge<T>* MST = new Edge<T>[n - 1];	//��¼��С�������ı�
	minheap<Edge<T>> H(edgeNum);	//����e��Ԫ�ص���С��
	Edge<T> edge;
	for (int i = 0; i < vertexNum; i++) {
		for (edge = firstEdge(i); isEdge(edge); edge = nextEdge(edge)) {
			if (startVertex(edge) < endVertex(edge)) {//��������ͼ�ı߱��ظ�����
				H.insert(edge);
			}
		}
	}
	int edgeNum = 0;	//�������ıߵĸ���
	while (edgeNum < n - 1) {
		//n��������ͨͼ��������n-1����
		if (!H.isempty()) {
			edge = H.removemin();	//�ҵ�Ȩ����С��δ����ı�
			int v = edge.start;
			int u = edge.end;
			if (set.Find(v) != set.Find(u)) {
				//�жϸñ߹����Ķ����Ƿ���һ����ͨ����
				set.Union(v, u);	//����,�ϲ������������ڵĵȼ���
				//�����������ı���ӵ��������ı߼���
				MST[edgeNum++] = edge;
			}
		}
	}
	cout << "\nKruskal�㷨��������(ͼ4-17)\n";
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
		Mark[i] = 0;	//δ����
		D[i] = 1000;	//·�����
		Path[i] = -1;	//��Ǵ�ʱ������s��i��·��,����ǰ������
	}
	Mark[s] = 1;	//�ѷ���
	D[s] = 0;
	Path[s] = s;
	for (i = 0; i < n; i++) {
		//�ҵ�һ�����·��
		T min = 1000;
		int k = 0;
		for (j = 1; j < n; j++) {
			if (Mark[j] == 0 && min > D[j]) {
				min = D[j];
				k = j;
			}
		}
		//�Ѿ�ȷ��s��k�����·��
		Mark[k] = 1;
		//����k���µ�����δ���ʶ�����������·��
		for (Edge<T> e = firstEdge(k); isEdge(e); e = nextEdge(e)) {
			int endVertex = e.end;
			if (Mark[endVertex] == 0 && D[endVertex] > (D[k] + e.weight)) {
				//���µ�endVertex���������·��
				D[endVertex] = D[k] + e.weight;
				Path[endVertex] = k;
			}
		}
	}
	cout << "\nDjikstra�㷨(ͼ4-18)";
	cout << "\n���·������\n";
	for (i = 0; i < n; i++)
		cout << D[i] << "\t";
	cout << "\nǰ�����\n";
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
	int i, j, v;	//v�Ǽ�¼��Ӧ����
	int n = G.vertexNum;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {	//��ʼ��Adj�����Path����
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
	for (v = 0; v < n; v++) {	//��������,��e.weight��ֵ��ΪAdj[v][e.end],v��ΪPath[v][e.end]��ֵ
		for (Edge<T> e = G.firstEdge(v); G.isEdge(e); e = G.nextEdge(e)) {
			Adj[v][e.end] = e.weight;
			Path[v][e.end] = v;
		}
	}
	//�����������ij����̾���v��·��,��adj[i][j]>(adj[i][v]+adj[v][j]),
	//�����adj[i][j]��path[i][j]
	//����ѭ��
	for (v = 0; v < n; v++) {	//����������ת����v(v��0��n-1���)
		for (i = 0; i < n; i++) {	//�����i��
			for (j = 0; j < n; j++) {	//�����j��
				if (Adj[i][j] > (Adj[i][v] + Adj[v][j])) {
					Adj[i][j] = Adj[i][v] + Adj[v][j];	//�������·��
					Path[i][j] = v;		//����ǰ��(��תվ)
				}
			}
		}
	}
}
template<class T>bool Graph<T>::TopologySort(int* SortArray) {
	//�����������д���SortArray
	int n = vertexNum;
	int *indegree = new int[n];	//������������ֵ
	int i, v;
	Edge<T> e;
	for (v = 0; v < n; v++) {
		//��ȳ�ʼ��Ϊ0,״̬���Ϊδ����
		indegree[v] = 0;
		Mark[v] = 0;
	}
	for (v = 0; v < n; v++) {
		//ͳ�Ƹ�������������Ϣ
		for (e = firstEdge(v); isEdge(e); e = nextEdge(e)) {
			indegree[e.end]++;
		}
	}
	for (i = 0; i < n; i++) {
		//ȷ����������SortArray
		//�ҵ����Ϊ0��δ�����ʵĶ���
		for (v = 0; v < n; v++) {
			if (indegree[v] == 0 && Mark[v] == 0) {
				break;
			}
		}
		if (v == n) {
			return false;	//�Ҳ������Ϊ0�Ķ���,�л�·,����false
		}
		Mark[v] = 1;
		SortArray[i] = v;
		for (e = firstEdge(v); isEdge(e); e = nextEdge(e)) {
			//�޸�vָ��Ķ�������
			indegree[e.end]--;
		}
	}
	return true;
}
template<class T>void Graph<T>::TologySortDisplay() {
	int n = vertexNum;
	int *sortArray =new int[n];
	if (TopologySort(sortArray)) {
		cout << "û�л�·,����������(ͼ4-18)\n";
		for (int i = 0; i < n; i++) {
			cout << sortArray[i] << "\t";
		}
		cout << "\n";
	}
	else {
		Edge<T> e;
		cout << "�л�·����,һ����·��(ͼ4-18)\n";
		for (int i = 0; i < n; i++) {
			for (e = firstEdge(i); isEdge(e); e = nextEdge(e)) {
				if (Mark[e.end] == 0)
					break;	//�ҵ�û�б����ʵ�һ�����,�˽ڵ�һ������Ȧ��
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
	Mark[v] = 1;	//��ǽ���ѷ���
	//�ɸýڵ��������ı߽��������������
	for (Edge<T> ee = firstEdge(v); isEdge(ee); ee = nextEdge(ee)) {	//isEdge����������
																		//����v�ڽӵ�δ�����ʵĶ���
		if (Mark[ee.end] == 0)
			DFS1(ee.end);
	}
}
template<class T>bool Graph<T>::Liantong() {
	int count = 0;
	int n = vertexNum;
	for (int i = 0; i < n; ++i)
		Mark[i] = 0;	//��ʼ��Ϊδ����
	for (int i = 0; i < n; ++i) {
		if (!Mark[i]) {
			DFS1(i);	//�����������,�����ʵ��Ķ�����ΪMark[i]=1
			count++;
		}
	}
	//���ֻ����һ��DFS(i),�ͽ����ж�����Ϊ�ѷ���,˵������ͨͼ
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
				//����ͼ��Ҫ��
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
		//��ɾ������,��Ϊ0,��ʾû�б�
		if (!Liantong()) {
			//ɾ�����ߺ�ԭͼ������ͨ��,��ָ�����
			//��Ϊ�����������С������,ÿ�������ͨ
			//��ʱ˵������������Ų���Ȧ�ϵ�����
			//����,ɾ���ı�����Ȧ�ϵ�����
			matrix[e.start][e.end] = weight1;
			matrix[e.end][e.start] = weight2;
		}
		//�����жϴ�һ����㿪ʼ������������������л���ص��Ѿ����ʹ��Ľ�㣬��֤�����ڻ���Ȼ��ȥ����������
	}
	cout << "��Ȧ����õ���С������(ͼ4-15)\n";
	for (v = 0; v < vertexNum; v++) {
		for (e = firstEdge(v); isEdge(e); e = nextEdge(e)) {
			if (e.start < e.end) {
				//����ͼ��Ҫ��
				cout << "<" << e.start << "," << e.end << "> " << e.weight << "\t \t";
			}
		}
	}
}