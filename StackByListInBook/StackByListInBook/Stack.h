//��ʽջ,������λ����Ϊջ��
#include<iostream>
using namespace std;

#ifndef STACK
#define STACK

template<class T>class ListNode{
public:
	T data;
	ListNode<T>* succ;
	ListNode(T& v, ListNode<T>* p = NULL){
		data = v; succ = p;
	}
};

template<class T>class Stack{
private:
	ListNode<T>* top;	//ջ��ָ��
	int size;	//ջԪ�ظ���
public:
	Stack(int s = 0){
		top = NULL;	size = 0;
	}
	~Stack(){
		Clear();
	}
	void Clear(){//���ջ����Ҫ�ͷ�ÿһ���ڵ㣬��˳��ջ��һ����˳��ջ�Ƕ�̬���飬�������
		while (top != NULL){
			ListNode<T>* tmp = top;
			top = top->succ;
			delete tmp;
		}
		size = 0;
	}
	bool Push(T item);
	bool Pop(T& item);
	bool Top(T& item);
};

template<class T>bool Stack<T>::Push(T item){
	ListNode<T> *tmp = new ListNode<T>(item, top);
	top = tmp;
	size++;
	return true;
}
template<class T>bool Stack<T>::Pop(T &item){
	ListNode<T>* tmp;
	if (size == 0){
		cout << "ջΪ��\n"; return false;
	}
	item = top->data;
	tmp = top->succ;
	delete top;
	top = tmp;
	size--;
	return true;
}
template<class T>bool Stack<T>::Top(T& item){
	if (size == 0){
		cout << "ջΪ��\n"; return false;
	}
	item = top->data;
	return true;
}

#endif