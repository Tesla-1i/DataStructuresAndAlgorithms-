#ifndef STACK
#define STACK

template<class T>class Stack{
public:
	bool push(T item);	//ѹջ
	bool pop(T& item);	//��ջ
	bool top(T& item);	//ȡ��ջ��Ԫ��
	bool isEmpty();
	bool isFull();
	void clear();	//���
};

#endif