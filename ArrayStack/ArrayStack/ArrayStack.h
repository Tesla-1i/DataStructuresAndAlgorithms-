#include<iostream>
#include"Stack.h"

#ifndef ARRAYSTACK
#define ARRAYATACK
//˳��ջ��ʵ��
template<class T>class ArrayStack :public Stack<T>{
private:
	int maxSize; //ջ�����������������
	int topRank;	//ջ����λ�ã��ȣ���ջtop=-1
	T* st;		//���ջԪ�ص�����
public:
	ArrayStack(){
		topRank = -1;	//��ջ
	}
	ArrayStack(int size){	//�������
		maxSize = size;
		topRank = -1;		//������Ȼ�ǿ�ջ
		st = new T[size];
	}
	~ArrayStack(){
		delete[] st;
	}
	void clear(){
		topRank = -1;	//��������
	}
	bool push(T item);
	bool pop(T &item);
	bool top(T &item);
};

#endif