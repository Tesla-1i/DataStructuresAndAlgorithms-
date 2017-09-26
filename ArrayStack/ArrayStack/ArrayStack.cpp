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
	if (topRank == -1)	//不是赋值
	{
		cout << "栈为空\n";
		return false;
	}
	else{
		item = st[topRank--];		//取栈顶，删除栈顶，返回原来的栈顶元素，不是现在栈顶的元素
		return true;
	}
}

template<class T>bool ArrayStack<T>::top(T& item){
	if (topRank == -1){
		cout << "栈为空\n";
		return false;
	}else{
		item = st[topRank];			//取栈顶，不删除
		return true;
	}
}

int main(){
	ArrayStack<float> *arrayStack = new ArrayStack<float>(10);
	cout << "输入五个数\n";
	float num;
	for (int i = 0; i < 5; i++){
		cin >> num;
		arrayStack->push(num);
	}
	cout << "栈顶元素是 ";
	float item;
	arrayStack->top(item);
	cout << item << "\n";
	cout << "删除栈顶元素, ";
	float item1;
	arrayStack->pop(item1);
	cout << item1 << "\n";
	arrayStack->top(item);
	cout << "新栈顶 ";
	cout << item << "\n";
}