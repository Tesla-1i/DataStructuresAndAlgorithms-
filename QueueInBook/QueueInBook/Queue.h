//˳��Queue
//���ζ��У�ȡģ���㣬n��n+1�ռ�洢

#include<iostream>
using namespace std;

#ifndef QUEUE
#define QUEUE

template<class T>class Queue{
private:
	int maxSize;	//�������ֵ
	int front;	//��ͷλ���±�
	int rear;	//��βλ���±�
	T *queue;	//���T�������ݵ�����
public:
	Queue(int size = 20){
		maxSize = size + 1;	//���һ���ռ䣬���ֿ�����
		queue = new T[maxSize];
		front = rear = 0;
	}
	~Queue(){
		delete[] queue;
	}
	void Clear(){
		front = rear;	//��ն��У�����������
	}
	bool EnQueue(T item);	//��ӣ���β������Ԫ��
	bool DeQueue(T& item);	//���ӣ�ȡ����һ��Ԫ�أ���ɾ����������ɾ����
	bool GetFront(T& item);	//��ȡ��ͷ����ɾ��
	bool IsEmpty(){
		if (front == rear)	return true;
		else	return false;
	}
	bool IsFull(){
		if ((rear + 1) % (maxSize) == front)	return true;
		else	return false;
	}
	int GetSize(){
		return ((rear - front + maxSize) % maxSize);	//���ض�����Ԫ�ظ���
	}
};

#endif

template<class T>bool Queue<T>::EnQueue(T item){
	if ((rear + 1) % maxSize == front){
		//����Ҳ������Զ��������ѹջ����
		/*T *newQueue = new T[maxSize * 2];
		for (int i = 0; i < maxSize - 1; i++){
			newQueue[i] = queue[i];
		}
		maxSize *= 2;
		delete[] queue;
		queue = newQueue;*/

		cout << "��������" << endl;
		return false;
	}
	queue[rear] = item;		//˵��rear�ȴ�������û��Ԫ�ص�
	rear = (rear + 1) % maxSize;
	return true;
}
template<class T>bool Queue<T>::DeQueue(T& item){
	if (front == rear){
		cout << "����Ϊ��\n";	return false;
	}
	item = queue[front];
	front = (front + 1) % maxSize;
	return true;
}
template<class T>bool Queue<T>::GetFront(T& item){
	if (front == rear){
		cout << "����Ϊ��\n";	return false;
	}
	item = queue[front];	return true;
}
