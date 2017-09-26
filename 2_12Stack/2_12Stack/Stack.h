//顺序栈的实现 以后无论何栈均命名为Stack
//少用const，satic之类的东西
#include<iostream>
using namespace std;

#ifndef STACK
#define STACK

template<class T>class Stack{
public:
	int maxSize; //栈最大值
	int top;	//栈顶位置，秩
	T* st;		//存放栈元素的动态数组
	//Stack(){ top = -1; }
	Stack(int size=20){	//创造一个给定长度的顺序栈,默认为20
		maxSize = size; top = -1; st = new T[maxSize];
	}
	~Stack(){
		delete[] st;
	}
	void Clear(){
		top = -1;	//清空栈，仅需将top=-1即可，不需要抹掉st【】中的元素
					//之后，再压栈时，会将元素赋予新的值
	}
	bool IsEmpty(){
		return (top == -1);
	}
	bool IsFull(){
		return (top == maxSize - 1);
	}
	bool Push(T item);
	bool Pop(T& item);
	bool Top(T& item);
};

template<class T>bool Stack<T>::Push(T item){
	if (top == maxSize - 1){	//旧的栈已满
		T *newSt = new T[maxSize * 2];
		for (int i = 0; i < maxSize; i++){
			newSt[i] = st[i];	//假设T类型已经重载了[]
		}
		delete[] st;
		st = newSt;
		maxSize *= 2;	//更新maxSize
	}
	st[++top] = item;	//++top 前置++
	return true;
}
template<class T>bool Stack<T>::Pop(T &item){
	if (top == -1){
		cout << "Stack is empty\n";	return false;
	}
	item = st[top--];	//item值是原先的栈顶,后置--
	return true;
}
template<class T>bool Stack<T>::Top(T &item){
	if (top == -1){
		cout << "Stack is empty\n";	return false;
	}
	item = st[top];	return true;
}

#endif