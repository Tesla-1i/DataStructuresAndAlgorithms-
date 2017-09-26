#include<iostream>
#include"Stack.h"
#include"ArrayStack.h"
using namespace std;
template<class T>bool ArrayStack<T>::push(T item){
	if (topRank == maxSize - 1){
		T *newSt = new T[maxSize << 1];
		for (int i = 0; i <= topRank; i++){
			newSt[i] = st[i];
		}
		delete[] st;
		st = newSt;
		maxSize *= 2;
	}
	st[++topRank] = item;
	return true;
}

template<class T>bool ArrayStack<T>::pop(T& item){
	if (topRank == -1)	//���Ǹ�ֵ
	{
		cout << "ջΪ��\n";
		return false;
	}
	else{
		item = st[topRank--];		//ȡջ����ɾ��ջ��������ԭ����ջ��Ԫ�أ���������ջ����Ԫ��
		return true;
	}
}

template<class T>bool ArrayStack<T>::top(T& item){
	if (topRank == -1){
		cout << "ջΪ��\n";
		return false;
	}else{
		item = st[topRank];			//ȡջ������ɾ��
		return true;
	}
}

int main(){
	ArrayStack<float> *arrayStack = new ArrayStack<float>(10);
	cout << "���������\n";
	float num;
	for (int i = 0; i < 5; i++){
		cin >> num;
		arrayStack->push(num);
	}
	cout << "ջ��Ԫ���� ";
	float item;
	arrayStack->top(item);
	cout << item << "\n";
	cout << "ɾ��ջ��Ԫ��, ";
	float item1;
	arrayStack->pop(item1);
	cout << item1 << "\n";
	arrayStack->top(item);
	cout << "��ջ�� ";
	cout << item << "\n";
}