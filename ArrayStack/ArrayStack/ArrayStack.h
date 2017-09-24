#include<iostream>
#include"Stack.h"

#ifndef ARRAYSTACK
#define ARRAYATACK
//顺序栈的实现
template<class T>class ArrayStack :public Stack<T>{
private:
	int maxSize; //栈的最大容量，不是秩
	int topRank;	//栈顶的位置，秩，空栈top=-1
	T* st;		//存放栈元素的数组
public:
	ArrayStack(){
		topRank = -1;	//空栈
	}
	ArrayStack(int size){	//最大容量
		maxSize = size;
		topRank = -1;		//现在仍然是空栈
		st = new T[size];
	}
	~ArrayStack(){
		delete[] st;
	}
	void clear(){
		topRank = -1;	//不是析构
	}
	bool push(T item);
	bool pop(T &item);
	bool top(T &item);
};

#endif