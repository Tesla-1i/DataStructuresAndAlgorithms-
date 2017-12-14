//���ѣ�ʵ������ȫ������

#include<iostream>
using namespace std;

#ifndef MAXHEAP
#define MAXHEAP

template<class T>class MaxHeap {
public:
	T* heapArray;	//��Ŷ����ݵ�����
	int currentSize;	//��ǰԪ�ظ���
	int maxSize;	//���Ԫ����Ŀ
	MaxHeap(T* array, int num, int max) { heapArray = array; currentSize = num; maxSize = max; }
	void buildHeap();	//�����
	void siftDown(int left);	//ɸѡ����left��ʾ��ʼ����������±�
	void siftUp(int position);	//��position���Ͽ�ʼ������ʹ���гɶ�
	void removeMax(T& max);		//�ӶѶ�ɾ�����ֵ,------���ȶ��еĳ��Ӳ���
	bool insert(T& value);	//�����½ڵ�
	void removeByIndex(T& in);	//ɾ��������,ͨ������
	void removeByValue(T& va);	//ɾ��������,ͨ��ֵ
};

#endif // !MAXHEAP

template<class T>void MaxHeap<T>::buildHeap() {
	for (int i = currentSize / 2 - 1; i >= 0; i--)
		siftDown(i);
}
template<class T>void MaxHeap<T>::siftDown(int left) {
	int i = left;	//��ʶ���ڵ�
	int j = 2 * i + 1;	//��ʶ���ӽڵ�
	T temp = heapArray[i];	//���游�ڵ�Ĺؼ���
	while (j < currentSize) {	//������
		if ((j < currentSize - 1) && (heapArray[j] < heapArray[j + 1])) {
			j++;
		//�ýڵ����Һ������Һ��ӵĹؼ���������ӵĹؼ���ʱ��jָ�����ӽڵ�
		}
		if (temp < heapArray[j]) {	//heapArray[j]���ڲ�һ����������
			//�ýڵ�Ĺؼ���С�����Һ����бȽϴ���Ǹ�ʱ
			swap(heapArray[i], heapArray[j]);	//����
			i = j;
			j = 2 * j + 1;
		}
		else
			break;
	}
	heapArray[i] = temp;
}
//�ö�ʵ�����ȶ��еĳ��Ӳ���
template<class T>void MaxHeap<T>::removeMax(T& max) {	//ʵ����ɾ���Ѷ�Ԫ��
	if (currentSize <= 0) {
		cout << "����Ϊ��\n";
		exit(1);
	}
	else {
		T temp = heapArray[0];		//ȡ�Ѷ�Ԫ��
		heapArray[0] = heapArray[currentSize - 1];	//����βԪ���������Ѷ�
		currentSize--;
		if (currentSize > 1)	//�ӶѶ���ʼɸѡ
			siftDown(0);
		//return temp;	//���У�����Ǻ
		max = temp;
	}
}

template<class T>void MaxHeap<T>::removeByIndex(T& in) {
	if (in < 0 || in >= currentSize) {
		cout << "�������,�˳�����\n";	exit(1);
	}
	if (in == currentSize - 1) {
		currentSize--;	//ɾ�����һ��
		return;
	}
	heapArray[in] = heapArray[currentSize - 1];	//�滻
	currentSize--;
	if (currentSize > 1) {
		siftDown(in);
		siftUp(in);
	}
}

template<class T>void MaxHeap<T>::removeByValue(T& va) {
	int i = 0;
	for (i = 0; i < currentSize; i++) {
		if (heapArray[i] == va) break;
	}
	if (i >= currentSize) {
		cout << "û��ƥ���ֵ\n";	return;
	}
	removeByIndex(i);
}

template<class T>bool MaxHeap<T>::insert(T& value) {
	if (currentSize >= maxSize) {
		cout << "������������\n";	return false;
	}
	heapArray[currentSize] = value;	//value���������ž���currentsize
	siftUp(currentSize);
	currentSize++;	//��ǰ������һ
	return true;
}
template<class T>void MaxHeap<T>::siftUp(int position) {
	int me = position;
	int parent = (position - 1) / 2;	//���ڵ�λ��
	while (me!=0) {	//ֱ���½ڵ��Ϊ���ڵ㣬����ѭ��
		if (heapArray[me] > heapArray[parent]) {
			swap(heapArray[me], heapArray[parent]);
			me = parent;
			parent = (me - 1) / 2;
		}
		else {	//�½ڵ�ֵ�����ڸ��ڵ�ֵ������
			break;
		}
	}
}

