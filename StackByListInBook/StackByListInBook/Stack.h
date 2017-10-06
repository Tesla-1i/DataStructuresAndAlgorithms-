//链式栈,链表首位置作为栈顶
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
	ListNode<T>* top;	//栈顶指针
	int size;	//栈元素个数
public:
	Stack(int s = 0){
		top = NULL;	size = 0;
	}
	~Stack(){
		Clear();
	}
	void Clear(){//清空栈必须要释放每一个节点，与顺序栈不一样，顺序栈是动态数组，不需清空
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
		cout << "栈为空\n"; return false;
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
		cout << "栈为空\n"; return false;
	}
	item = top->data;
	return true;
}

#endif