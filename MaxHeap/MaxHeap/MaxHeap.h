//最大堆，实质是完全二叉树

#include<iostream>
using namespace std;

#ifndef MAXHEAP
#define MAXHEAP

template<class T>class MaxHeap {
public:
	T* heapArray;	//存放堆数据的数组
	int currentSize;	//当前元素个数
	int maxSize;	//最大元素数目
	MaxHeap(T* array, int num, int max) { heapArray = array; currentSize = num; maxSize = max; }
	void buildHeap();	//构造堆
	void siftDown(int left);	//筛选法，left表示开始处理的数组下标
	void siftUp(int position);	//从position向上开始调整，使序列成堆
	void removeMax(T& max);		//从堆顶删除最大值,------优先队列的出队操作
	bool insert(T& value);	//插入新节点
	void removeByIndex(T& in);	//删除任意结点,通过索引
	void removeByValue(T& va);	//删除任意结点,通过值
};

#endif // !MAXHEAP

template<class T>void MaxHeap<T>::buildHeap() {
	for (int i = currentSize / 2 - 1; i >= 0; i--)
		siftDown(i);
}
template<class T>void MaxHeap<T>::siftDown(int left) {
	int i = left;	//标识父节点
	int j = 2 * i + 1;	//标识左子节点
	T temp = heapArray[i];	//保存父节点的关键码
	while (j < currentSize) {	//有左孩子
		if ((j < currentSize - 1) && (heapArray[j] < heapArray[j + 1])) {
			j++;
		//该节点有右孩子且右孩子的关键码大于左孩子的关键码时，j指向右子节点
		}
		if (temp < heapArray[j]) {	//heapArray[j]现在不一定是左是右
			//该节点的关键码小于左右孩子中比较大的那个时
			swap(heapArray[i], heapArray[j]);	//交换
			i = j;
			j = 2 * j + 1;
		}
		else
			break;
	}
	heapArray[i] = temp;
}
//用堆实现优先队列的出队操作
template<class T>void MaxHeap<T>::removeMax(T& max) {	//实质是删除堆顶元素
	if (currentSize <= 0) {
		cout << "堆已为空\n";
		exit(1);
	}
	else {
		T temp = heapArray[0];		//取堆顶元素
		heapArray[0] = heapArray[currentSize - 1];	//将堆尾元素上升至堆顶
		currentSize--;
		if (currentSize > 1)	//从堆顶开始筛选
			siftDown(0);
		//return temp;	//能行？，够呛
		max = temp;
	}
}

template<class T>void MaxHeap<T>::removeByIndex(T& in) {
	if (in < 0 || in >= currentSize) {
		cout << "索引溢出,退出程序\n";	exit(1);
	}
	if (in == currentSize - 1) {
		currentSize--;	//删除最后一个
		return;
	}
	heapArray[in] = heapArray[currentSize - 1];	//替换
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
		cout << "没有匹配的值\n";	return;
	}
	removeByIndex(i);
}

template<class T>bool MaxHeap<T>::insert(T& value) {
	if (currentSize >= maxSize) {
		cout << "最大堆容量已满\n";	return false;
	}
	heapArray[currentSize] = value;	//value在数组的序号就是currentsize
	siftUp(currentSize);
	currentSize++;	//当前数量加一
	return true;
}
template<class T>void MaxHeap<T>::siftUp(int position) {
	int me = position;
	int parent = (position - 1) / 2;	//父节点位置
	while (me!=0) {	//直到新节点成为根节点，不再循环
		if (heapArray[me] > heapArray[parent]) {
			swap(heapArray[me], heapArray[parent]);
			me = parent;
			parent = (me - 1) / 2;
		}
		else {	//新节点值不大于父节点值，跳出
			break;
		}
	}
}

