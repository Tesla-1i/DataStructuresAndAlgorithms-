#include"MaxHeap.h"

int main() {
	int *array = new int[20];
	cout << "����������� ";
	int cnum;	cin >> cnum;
	cout << "������\n";
	for (int i = 0; i < cnum; i++)
		cin >> array[i];
	MaxHeap<int>* maxheap = new MaxHeap<int>(array, cnum, 20);
	maxheap->buildHeap();
	for (int i = 0; i < maxheap->currentSize; i++)
		cout << (maxheap->heapArray[i]) << "\t";
	cout << "\n";
	int max;
	maxheap->removeMax(max);
	cout << "ɾ�����ֵ\n";
	cout << "max = " << max << "\n";
	for (int i = 0; i < maxheap->currentSize; i++)
		cout << (maxheap->heapArray[i]) << "\t";
	cout << "\n��������Ԫ��ֵ: ";
	int value;	cin >> value;
	maxheap->insert(value);
	for (int i = 0; i < maxheap->currentSize; i++)
		cout << (maxheap->heapArray[i]) << "\t";
}