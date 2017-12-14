//顺序Queue
//环形队列，用tag表示队列空与不空，此时可用front==rear作为队满标志

#include<iostream>
using namespace std;

#ifndef QUEUE
#define QUEUE

template<class T>class Queue{
private:
	int maxSize;	//数组最大值
	int front;	//队头位置下标
	int rear;	//队尾位置下标
	int tag;	//区别队列空与不空
	T *queue;	//存放T类型数据的数组
public:
	Queue(int size = 5){
		maxSize = size ;	
		queue = new T[maxSize];
		front = rear = 0;
		tag = 0;	//表示队列空
	}
	~Queue(){
		delete[] queue;
	}
	void Clear(){
		front = rear;	//清空队列，不是真的清空
		tag = 0;
	}
	bool EnQueue(T item);	//入队，队尾加入新元素
	bool DeQueue(T& item);	//出队，取出第一个元素，并删除（不是真删除）
	bool GetFront(T& item);	//读取队头，不删除
};

#endif

template<class T>bool Queue<T>::EnQueue(T item){
	if (front == rear&&tag==1){
		cout << "队列已满\n";	return false;
	}
	tag = 1;
	queue[rear] = item;
	rear = (rear + 1) % maxSize;
	return true;
	//if ((rear + 1) % maxSize == front){
	//	//队列也可以永远不满，与压栈类似
	//	/*T *newQueue = new T[maxSize * 2];
	//	for (int i = 0; i < maxSize - 1; i++){
	//	newQueue[i] = queue[i];
	//	}
	//	maxSize *= 2;
	//	delete[] queue;
	//	queue = newQueue;*/

	//	cout << "队列已满" << endl;
	//	return false;
	//}
	//queue[rear] = item;		//说明rear秩处本来是没有元素的
	//rear = (rear + 1) % maxSize;
	//return true;
}

//出队后检测队列是否为空,更改标记tag
template<class T>bool Queue<T>::DeQueue(T& item){
	if (tag==0){
		cout << "队列为空\n";	return false;
	}
	item = queue[front];
	front = (front + 1) % maxSize;
	if (front == rear)
		tag = 0;	//出队后front还等于rear,说明队列已空
	return true;
}
template<class T>bool Queue<T>::GetFront(T& item){
	if (tag==0){
		cout << "队列为空\n";	return false;
	}
	item = queue[front];	return true;
}