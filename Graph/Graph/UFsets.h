//Kruskal求最小生成树算法用到的等价类
#include<iostream>
using namespace std;
#ifndef UFSETS
#define UFSETS

class UFSets {
public:
	int n;	//等价元素的个数
	int* root;	//root[i]表示元素i所在的等价类的代表元素的编号
	int *next;	//next[i]表示在等价类中,i后面的元素的编号
	int *length;	//length[i]表示i所在的等价类的元素个数
	UFSets(int size) {
		n = size;
		root = new int[n];
		next = new int[n];
		length = new int[n];
		for (int i = 0; i < n; i++) {
			root[i] = next[i] = i;	//各个元素独自成为一个等价类
			length[i] = 1;
		}
	}
	int Find(int v) {
		return root[v];	//查找v的代表元素
	}
	void Union(int v, int u);
};

#endif // !UFSETS

void UFSets::Union(int v, int u) {
	int rt, j;
	if (root[u] == root[v])return;	//如果v和u在一个等价类中则返回.
	else if (length[root[v]] < length[root[u]]) {
		//将v所在的等价类合并到u所在的等价类中
		//将u所在的等价类的代表元素作为合并后的等价类的代表元素
		rt = root[v];
		length[root[u]] += length[rt];
		root[rt] = root[u];	//修改v所在的等价类的各个代表元素信息
		for (j = next[rt]; j != rt; j = next[j])
			root[j] = root[u];
		swap(next[rt], next[root[u]]);
		//将两个等价类的元素连接起来
	}
	else {
		int rt = root[u];
		length[root[v]] += length[rt];
		root[rt] = root[v];	//修改v所在的等价类的各个代表元素信息
		for (j = next[rt]; j != rt; j = next[j])
			root[j] = root[v];
		swap(next[rt], next[root[v]]);
	}
}
