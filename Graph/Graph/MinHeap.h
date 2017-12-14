//��С�Ѻ����ѵĶ���
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

#ifndef MINHEAP
#define MINHEAP

template <class T>
class minheap // ��С���ඨ��    ��ʼ�������룬ɾ���Ѷ�Ԫ��
{
private:
	T * heaparray;
	int currentsize;
	int maxsize;
public:
	minheap(int n)
	{
		if (n <= 0)
			return;
		currentsize = 0;
		maxsize = n;
		heaparray = new T[maxsize];
		buildheap();
	}
	~minheap()
	{
		delete[] heaparray;
	}
	void buildheap()
	{
		for (int i = currentsize / 2 - 1; i >= 0; i--)
			siftdown(i);//��������ɸѡ����
	}
	void siftdown(int left)//ɸѡ������������left��ʾ��ʼ����������±�
	{
		int i = left;
		int j = 2 * i + 1;
		T temp = heaparray[i];
		while (j<currentsize)
		{
			if ((j<currentsize - 1) && (heaparray[j]>heaparray[j + 1]))
				j++;
			if (temp>heaparray[j])
			{
				heaparray[i] = heaparray[j];
				i = j;
				j = 2 * j + 1;
			}
			else break;
		}
		heaparray[i] = temp;
	}
	void siftup(int pos)//��pos���Ͽ�ʼ����
	{
		int temppos = pos;
		T temp = heaparray[temppos];
		while ((temppos>0) && (heaparray[(temppos - 1) / 2]>temp))
		{
			heaparray[temppos] = heaparray[(temppos - 1) / 2];
			temppos = (temppos - 1) / 2;
		}
		heaparray[temppos] = temp;
	}
	void insert(const T & newnode)//����в�����Ԫ��newnode
	{
		heaparray[currentsize] = newnode;
		siftup(currentsize);
		currentsize++;

	}
	T & removemin()//�ӶѶ�ɾ����Сֵ
	{
		T temp;
		if (currentsize == 0)
		{
			cout << "can't delete";
			exit(1);
		}
		else
		{
			temp = heaparray[0];
			heaparray[0] = heaparray[currentsize - 1];
			heaparray[currentsize - 1] = temp;
			currentsize--;
			if (currentsize>0)
				siftdown(0);
			return heaparray[currentsize];
		}
	}
	bool isempty()
	{
		if (currentsize == 0)
			return true;
		else
			return false;
	}
};
template <class T>
class maxheap // �����ඨ��    ��ʼ�������룬ɾ���Ѷ�Ԫ��
{
private:
	T * heaparray;
	int currentsize;
	int maxsize;
public:
	maxheap(int n)
	{
		if (n <= 0)
			return;
		currentsize = 0;
		maxsize = n;
		heaparray = new T[maxsize];
		buildheap();
	}
	~maxheap()
	{
		delete[] heaparray;
	}
	void buildheap()
	{
		for (int i = currentsize / 2 - 1; i >= 0; i--)
			siftdown(i);//��������ɸѡ����
	}
	void siftdown(int left)//ɸѡ������������left��ʾ��ʼ����������±�
	{
		int i = left;
		int j = 2 * i + 1;
		T temp = heaparray[i];
		while (j<currentsize)
		{
			if ((j<currentsize - 1) && (heaparray[j]<heaparray[j + 1]))
				j++;
			if (temp<heaparray[j])
			{
				heaparray[i] = heaparray[j];
				i = j;
				//heaparray[i]=temp;
				j = 2 * j + 1;
			}
			else break;
		}
		heaparray[i] = temp;
	}
	void siftup(int pos)//��pos���Ͽ�ʼ����
	{
		int temppos = pos;
		T temp = heaparray[temppos];
		while ((temppos>0) && (heaparray[(temppos - 1) / 2]<temp))
		{
			heaparray[temppos] = heaparray[(temppos - 1) / 2];
			temppos = (temppos - 1) / 2;
		}
		heaparray[temppos] = temp;
	}
	void insert(const T & newnode)//����в�����Ԫ��newnode
	{
		heaparray[currentsize] = newnode;
		siftup(currentsize);
		currentsize++;

	}
	T & removemax()//�ӶѶ�ɾ�����ֵ
	{
		T temp;
		if (currentsize == 0)
		{
			cout << "can't delete";
			exit(1);
		}
		else
		{
			temp = heaparray[0];
			heaparray[0] = heaparray[currentsize - 1];
			heaparray[currentsize - 1] = temp;
			currentsize--;
			if (currentsize>0)
				siftdown(0);
			return heaparray[currentsize];
		}
	}
	void display()//�������Ԫ��
	{
		for (int i = 0; i<currentsize; i++)
			cout << heaparray[i] << " ";
		cout << endl;
	}
	bool isempty()
	{
		if (currentsize == 0)
			return true;
		else
			return false;
	}
};

#endif // !MINHEAP


