//Kruskal����С�������㷨�õ��ĵȼ���
#include<iostream>
using namespace std;
#ifndef UFSETS
#define UFSETS

class UFSets {
public:
	int n;	//�ȼ�Ԫ�صĸ���
	int* root;	//root[i]��ʾԪ��i���ڵĵȼ���Ĵ���Ԫ�صı��
	int *next;	//next[i]��ʾ�ڵȼ�����,i�����Ԫ�صı��
	int *length;	//length[i]��ʾi���ڵĵȼ����Ԫ�ظ���
	UFSets(int size) {
		n = size;
		root = new int[n];
		next = new int[n];
		length = new int[n];
		for (int i = 0; i < n; i++) {
			root[i] = next[i] = i;	//����Ԫ�ض��Գ�Ϊһ���ȼ���
			length[i] = 1;
		}
	}
	int Find(int v) {
		return root[v];	//����v�Ĵ���Ԫ��
	}
	void Union(int v, int u);
};

#endif // !UFSETS

void UFSets::Union(int v, int u) {
	int rt, j;
	if (root[u] == root[v])return;	//���v��u��һ���ȼ������򷵻�.
	else if (length[root[v]] < length[root[u]]) {
		//��v���ڵĵȼ���ϲ���u���ڵĵȼ�����
		//��u���ڵĵȼ���Ĵ���Ԫ����Ϊ�ϲ���ĵȼ���Ĵ���Ԫ��
		rt = root[v];
		length[root[u]] += length[rt];
		root[rt] = root[u];	//�޸�v���ڵĵȼ���ĸ�������Ԫ����Ϣ
		for (j = next[rt]; j != rt; j = next[j])
			root[j] = root[u];
		swap(next[rt], next[root[u]]);
		//�������ȼ����Ԫ����������
	}
	else {
		int rt = root[u];
		length[root[v]] += length[rt];
		root[rt] = root[v];	//�޸�v���ڵĵȼ���ĸ�������Ԫ����Ϣ
		for (j = next[rt]; j != rt; j = next[j])
			root[j] = root[v];
		swap(next[rt], next[root[v]]);
	}
}
