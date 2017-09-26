//˳��ջ��ʵ�� �Ժ����ۺ�ջ������ΪStack
//����const��satic֮��Ķ���
#include<iostream>
using namespace std;

#ifndef STACK
#define STACK

template<class T>class Stack{
public:
	int maxSize; //ջ���ֵ
	int top;	//ջ��λ�ã���
	T* st;		//���ջԪ�صĶ�̬����
	//Stack(){ top = -1; }
	Stack(int size=20){	//����һ���������ȵ�˳��ջ,Ĭ��Ϊ20
		maxSize = size; top = -1; st = new T[maxSize];
	}
	~Stack(){
		delete[] st;
	}
	void Clear(){
		top = -1;	//���ջ�����轫top=-1���ɣ�����ҪĨ��st�����е�Ԫ��
					//֮����ѹջʱ���ὫԪ�ظ����µ�ֵ
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
	if (top == maxSize - 1){	//�ɵ�ջ����
		T *newSt = new T[maxSize * 2];
		for (int i = 0; i < maxSize; i++){
			newSt[i] = st[i];	//����T�����Ѿ�������[]
		}
		delete[] st;
		st = newSt;
		maxSize *= 2;	//����maxSize
	}
	st[++top] = item;	//++top ǰ��++
	return true;
}
template<class T>bool Stack<T>::Pop(T &item){
	if (top == -1){
		cout << "Stack is empty\n";	return false;
	}
	item = st[top--];	//itemֵ��ԭ�ȵ�ջ��,����--
	return true;
}
template<class T>bool Stack<T>::Top(T &item){
	if (top == -1){
		cout << "Stack is empty\n";	return false;
	}
	item = st[top];	return true;
}

#endif