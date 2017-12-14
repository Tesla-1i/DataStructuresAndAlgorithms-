#include"MaxHeap.h"

int main() {
	cout << "输入结点个数： ";
	int cnum;	cin >> cnum;
	int *array = new int[cnum];
	cout << "输入结点\n";
	for (int i = 0; i < cnum; i++)
		cin >> array[i];
	MaxHeap<int>* maxheap = new MaxHeap<int>(array, cnum, 20);
	maxheap->buildHeap();
	for (int i = 0; i < maxheap->currentSize; i++)
		cout << (maxheap->heapArray[i]) << "\t";
	cout << "\n";
	int max;
	maxheap->removeMax(max);
	cout << "删除最大值\n";
	cout << "max = " << max << "\n";
	for (int i = 0; i < maxheap->currentSize; i++)
		cout << (maxheap->heapArray[i]) << "\t";
	cout << "\n输入插入的元素值: ";
	int value;	cin >> value;
	maxheap->insert(value);
	for (int i = 0; i < maxheap->currentSize; i++)
		cout << (maxheap->heapArray[i]) << "\t";
	cout << "输入删除的索引: ";
	int in;	cin >> in;
	maxheap->removeByIndex(in);
	for (int i = 0; i < maxheap->currentSize; i++)
		cout << (maxheap->heapArray[i]) << "\t";
	cout << "输入删除的值: ";
	int va; cin >> va;
	maxheap->removeByValue(va);
	for (int i = 0; i < maxheap->currentSize; i++)
		cout << (maxheap->heapArray[i]) << "\t";
}