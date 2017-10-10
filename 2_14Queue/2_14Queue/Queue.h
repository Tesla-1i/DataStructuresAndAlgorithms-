#include<iostream>
using namespace std;

//��ʽʵ�ֶ���

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
	int size;	//����Ԫ�ظ���
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
		front = rear = new ListNode<T>(item, NULL);	//ģ�壬������
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
		cout << "����Ϊ��\n"; return false;
	}
	item = front->data;
	temp = front;
	front = front->succ;
	delete temp;
	if (front == NULL){	//front==NULL��˵�����һ��Ҳ�����ˣ���ʱrear����Ҳ���NULL
		rear = NULL;
	}
	size--;
	return true;
}

template<class T>bool Queue<T>::GetFront(T& item){
	if (size == 0){
		cout << "����Ϊ��\n";	return false;
	}
	item = front->data;
	return true;
}


