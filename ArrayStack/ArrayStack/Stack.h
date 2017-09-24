#ifndef STACK
#define STACK

template<class T>class Stack{
public:
	bool push(T item);	//Ñ¹Õ»
	bool pop(T& item);	//µ¯Õ»
	bool top(T& item);	//È¡³öÕ»¶¥ÔªËØ
	bool isEmpty();
	bool isFull();
	void clear();	//Çå¿Õ
};

#endif