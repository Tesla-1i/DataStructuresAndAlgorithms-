//顺序Queue
//环形队列，取模运算，n用n+1空间存储

#include<iostream>
using namespace std;

#ifndef QUEUE
#define QUEUE

template<class T>class Queue{
private:
	int maxSize;	//数组最大值
	int front;	//队头位置下标
	int rear;	//队尾位置下标
	T *queue;	//存放T类型数据的数组
public:
	Queue(int size = 20){
		maxSize = size + 1;	//多出一个空间，区分空与满
		queue = new T[maxSize];
		front = rear = 0;
	}
	~Queue(){
		delete[] queue;
	}
	void Clear(){
		front = rear;	//清空队列，不是真的清空
	}
	bool EnQueue(T item);	//入队，队尾加入新元素
	bool DeQueue(T& item);	//出队，取出第一个元素，并删除（不是真删除）
	bool GetFront(T& item);	//读取队头，不删除
	bool IsEmpty(){
		if (front == rear)	return true;
		else	return false;
	}
	bool IsFull(){
		if ((rear + 1) % (maxSize) == front)	return true;
		else	return false;
	}
	int GetSize(){
		return ((rear - front + maxSize) % maxSize);	//返回队列中元素个数
	}
};

#endif

template<class T>bool Queue<T>::EnQueue(T item){
	if ((rear + 1) % maxSize == front){
		//队列也可以永远不满，与压栈类似
		/*T *newQueue = new T[maxSize * 2];
		for (int i = 0; i < maxSize - 1; i++){
			newQueue[i] = queue[i];
		}
		maxSize *= 2;
		delete[] queue;
		queue = newQueue;*/

		cout << "队列已满" << endl;
		return false;
	}
	queue[rear] = item;		//说明rear秩处本来是没有元素的
	rear = (rear + 1) % maxSize;
	return true;
}
template<class T>bool Queue<T>::DeQueue(T& item){
	if (front == rear){
		cout << "队列为空\n";	return false;
	}
	item = queue[front];
	front = (front + 1) % maxSize;
	return true;
}
template<class T>bool Queue<T>::GetFront(T& item){
	if (front == rear){
		cout << "队列为空\n";	return false;
	}
	item = queue[front];	return true;
}
