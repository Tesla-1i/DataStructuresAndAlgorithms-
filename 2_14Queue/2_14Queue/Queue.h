#include<iostream>
using namespace std;

//链式实现队列

#ifndef QUEUE
#define QUEUE

template<class T>class ListNode{
public:
	T data;
	ListNode<T>* succ;
	ListNode(T d, ListNode<T>* s){
		data = d;
		succ = s;
	}
};

template<class T>class Queue{
public:
	int size;	//队列元素个数
	ListNode<T>* front;
	ListNode<T>* rear;
public:
	Queue(int size = 0){
		size = 0;
		front = rear = NULL;
	}
	~Queue(){
		Clear();
	}
	void Clear();
	bool EnQueue(T item);
	bool DeQueue(T& item);
	bool GetFront(T& item);
};

#endif

template<class T>void Queue<T>::Clear(){
	while (front != NULL){
		rear = front;
		front = front->succ;
		delete rear;
	}
	rear = NULL;
	size = 0;
}
template<class T>bool Queue<T>::EnQueue(T item){
	if (rear == NULL){
		front = rear = new ListNode<T>(item, NULL);	//模板，不是类
	}
	else{
		rear->succ = new ListNode<T>(item, NULL);
		rear = rear->succ;
	}
	size++;
	return true;
}
template<class T>bool Queue<T>::DeQueue(T& item){
	ListNode<T>* temp;
	if (size == 0){
		cout << "队列为空\n"; return false;
	}
	item = front->data;
	temp = front;
	front = front->succ;
	delete temp;
	if (front == NULL){	//front==NULL，说明最后一个也出队了，此时rear必须也变成NULL
		rear = NULL;
	}
	size--;
	return true;
}

template<class T>bool Queue<T>::GetFront(T& item){
	if (size == 0){
		cout << "队列为空\n";	return false;
	}
	item = front->data;
	return true;
}


