#include<iostream>  
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;
template<class T>
class stack  
{
private:
	int top;
	T *atr;
	int maxize;
public:
	stack(int size = 0);
	~stack();
	bool IsFull();
	bool IsEmpty();
	void pop(T &item);
	void push(T &item);
	void clear();
	void GetTop(T &item);
};
class calculator  
{
private:
	int number;
	int iN;
	string thz;
	char* min;
	int **p;
	string st1;
public:
	calculator();
	~calculator();
	void TheMin();
	void show();
};
template<class T>
stack<T>::stack(int size = 0)
{
	maxize  = size;
	atr  = new T[maxize];
	top  = -1;
}
template<class T>
stack<T>::~stack()
{
	delete[]atr;
}
template<class T>
bool stack<T>::IsFull()
{
	return top  == maxize  - 1;
}
template<class T>
bool stack<T>::IsEmpty()
{
	return top == -1;
}
template<class T>
void stack<T>::clear()
{
	top  == -1;
}
template<class T>
void stack<T>::pop(T &item)
{
	item  = atr[top--];
}
template<class T>
void stack<T>::push(T &item)
{
	atr[++top] = item;
}
template<class T>
void stack<T>::GetTop(T &item)
{
	item  = atr[top];
}
calculator::calculator()
{
	char p[100], c  = '\0', a = '\0';
	stack <char> s(10);
	int i  = 0;
	number  = 0;
	cout  << "输入*表示合取，+表示析取，！表示非，记得输入大写字母的命题变员" << endl;
	while (1)
	{
		c  = getchar();
		if (c  == '\n')
			break;
		p[i++] = c;
	}

	for (int j  = 0; j < i; j++)
	{
		if (p[j] >= 'A'&&p[j] <= 'Z')
		{
			thz  += p[j];
			int k  = 0;
			for (; st1[k]; k++)
			{
				if (p[j] == st1[k])
					break;
			}
			if (!st1[k])
			{
				st1  += p[j];
				number++;
			}
		}
		else if (p[j] == '+' || p[j] == '*' || p[j] == '!' || p[j] == '(')
		{
			s.GetTop(c);
			if (s.IsEmpty() || p[j] == '!' || p[j] == '(')
			{
				s.push(p[j]);
			}
			else if (p[j] == '*' && (c == '*' || c == '!'))
			{
				s.pop(a);
				thz  += a;
				s.push(p[j]);
			}
			else if (p[j] == '+'&&!s.IsEmpty() && c  != '(')
			{
				s.pop(a);
				thz  += a;
				s.push(p[j]);
			}
			else if (c  == '(')
				s.push(p[j]);
		}
		else if (p[j] == ')')
		{
			if (!s.IsEmpty())
			{
				while (!s.IsEmpty())
				{
					s.pop(a);
					if (a  == '(')
						break;
					thz  += a;
				}
				if (a  != '(')
				{
					cout  << "能不能输入正确呀!" << endl;
					return ;
				}
			}
			else  
			{
				cout  << "哈哈哈，你又错了!" << endl;
				return;
			}
		}
	}
	while (!s.IsEmpty())
	{
		s.pop(a);
		thz  += a;

	}
}
calculator::~calculator()
{

	for (int i  = 0; i < iN; i++)
	{
		delete[]p[i];
	}
	delete []p;
}
void calculator::TheMin()
{
	stack<int> s1(20);
	min  = new char[100];
	int a, b, c = 0, d = 1, t = 0;
	iN  = pow(2, number);
	int count  = number;
	p  = new int*[iN];
	for (int i  = 0; i < iN; i++)
	{
		p[i] = new int[number];

	}
	for (int i  = 0; i < iN; i++)
	{
		for (int j  = count  - 1, k  = i; j  >= 0; j--)
		{

			p[i][j] = k  % 2;
			k  = k  / 2;
		}
	}
	int k  = 0;
	for (; k<iN; k++)
	{
		for (int j  = 0; thz[j]; j++)
		{
			if (thz[j] >= 'A'&&thz[j] <= 'Z')
			{
				int e  = 0;
				for (; st1[e]; e++)
				{
					if (thz[j] == st1[e])
						break;
				}
				s1.push(p[k][e]);
			}
			else if (thz[j] == '!')
			{
				s1.pop(a);
				if (a  == 1)
					s1.push(c);
				else  
					s1.push(d);
			}
			else if (thz[j] == '*')
			{
				s1.pop(a);
				s1.pop(b);
				if (a  == 1 && b  == 1)
					s1.push(d);
				else  
					s1.push(c);
			}
			else  
			{
				s1.pop(a);
				s1.pop(b);
				if (a  == 0 && b  == 0)
					s1.push(c);
				else  
					s1.push(d);
			}
		}
		s1.pop(a);
		if (a  == 1)
		{
			for (int f  = 0; f < number; f++)
			{
				if (p[k][f] == 0)
				{
					min[t++] = '!';
					min[t++] = st1[f];
				}
				if (p[k][f] == 1)
					min[t++] = st1[f];
				if (f  != number  - 1)
					min [t++] = '*';
			}
			min[t++] = '+';
		}
	}
	min[t] = '\0';
	for (int i  = 0; i<t - 1; i++)
	{
		cout  << min[i];
	}
}
int main()
{
	calculator c;
	c.TheMin();
}

