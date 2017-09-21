//带头双链表

//#include<iostream>
//using namespace std;
//template<class T>
//class DLLNode
//{
//public:
//	T data;
//	DLLNode<T>* prev, *next;
//	DLLNode(T info=0)
//	{
//		data = info;
//		prev = NULL;
//		next = NULL;
//	}
//};
//template<class T>
//class LinkList
//{
//public:
//
//	DLLNode<T>* prevPtr, *currPtr;
//	DLLNode<T>* head, *tail;
//	int position;
//	LinkList(T value)
//	{
//		DLLNode<T>*p;
//		p = new DLLNode<T>(value);
//		head = p;
//		tail = p;
//		position = 0;
//	}
//	void insertTail(T item)//插入节点函数
//	{
//		DLLNode<T> *p;
//		p = new DLLNode<T>(item);
//		tail->next = p;
//		p->prev = tail;
//		tail = p;
//		position++;
//	}
//	void change()
//	{
//		
//		DLLNode<T> *p;
//		p = head;
//		while ((p->next) && (p->next->next))
//		{
//			p->next = p->next->next;
//			p = p->next;
//			//cout << (p->data) << " ";
//		}
//		cout << "\n";
//		//奇数个时，p跑到了最后边了
//		if (!(p->next))//奇数个节点时
//		{
//			p->next = p->prev;
//			p = p->next;
//			while (p->prev->prev)
//			{
//				p->next = p->prev->prev;
//				p = p->next;
//			}
//			p->next = NULL;
//			tail = p;
//		}
//		else//偶数个节点时
//		{
//			p = p->next;
//			while (p->prev->prev)
//			{
//				p->next = p->prev->prev;
//				p = p->next;
//				//cout << (p->data) << " ";
//			}
//			p->next = NULL;
//			tail = p;
//			//cout << (p->data);
//		}
//		/*DLLNode<T>* p = head->next;
//		DLLNode<T>* q ;
//		DLLNode<T>* p1,  *q1;
//		q = new DLLNode<T>;
//		有问题
//		if (position % 2 == 0)
//		q = tail->prev;
//		q = tail->prev;
//		while ((p->next != NULL)&&(p->next->next != NULL)){
//		p1 = p->next->next;
//		p->next = p1;
//		p1->prev = p;
//		cout << (p->data) << " ";
//		p = p1;
//		}
//		cout << (p->data) << " ";
//		cout << (tail->data) << "\n";
//
//		cout << "\n" << (q->data) << "\n";
//		q->prev = p;
//		while (q->prev != head){
//		q1 = q->prev->prev;
//		q->next = q->prev->prev;
//		q->prev->prev->prev = q;
//		cout << (q->data) << " ";
//		q = q1;
//		}*/
//	}
//};
//int main()
//{
//	LinkList<int> L(0);
//	for (int i = 1; i<10; i++)
//	{
//		L.insertTail(i);
//	}
//	DLLNode<int>* ps;
//	ps = (L.head)->next;
//	while (ps)
//	{
//		cout << (ps->data) << "\t";
//		ps = ps->next;
//	}
//	L.change();
//	ps = (L.head)->next;
//	cout << "\n";
//	while (ps)
//	{
//		cout << (ps->data) << "\t";
//		ps = ps->next;
//	}
//}

#include<iostream>
#include<cstdlib>
using namespace std;

class LinkedList;

class DLLNode
{
public:
	int data;
	DLLNode *next, *prev;	//后继，前驱
	friend class LinkedList;
	DLLNode(int x, DLLNode *n, DLLNode *p) :data(x), next(n), prev(p){};
	~DLLNode(){ if (next)delete next; }
};

class LinkList
{
public:
	DLLNode *head, *tail;	//头尾指针
	LinkList(int data)
	{
		head = new DLLNode(data, NULL, NULL);
		tail = new DLLNode(data, NULL, head);
		head->next = tail;
	}
	~LinkList()
	{
		delete head;
	}
	void insert(int data)	//插入
	{
		DLLNode *nTail = new DLLNode(data, tail, tail->prev);
		tail->prev->next = nTail;
		tail->prev = nTail;
	}
	//转换函数
	void transform(void)
	{
		int temp = 0;
		DLLNode *tmpTail = tail->prev, *save;
		for (DLLNode *x = head->next; x != tmpTail; x = save, temp++)
		{
			save = x->next;
			if (temp & 1)
			{
				x->prev->next = x->next;
				x->next->prev = x->prev;
				x->next = tmpTail->next;
				x->prev = tmpTail;
				tmpTail->next = x;
				tmpTail->next->prev = x;
			}
		}
	}
	void show()
	{
		for (DLLNode *temp = head->next; temp->next != NULL; temp = temp->next)
		{
			cout << temp->data << "  ";
		}
		cout << "\n";
	}
};


int main()
{
	LinkList A(0);
	cout << "输入9个整数";
	for (int i = 0; i <= 8; i++)
	{
		int a; cin >> a;
		A.insert(a);
	}
	A.transform();
	A.show();
}

//#include<iostream>
//using namespace std;
//template<class T>class ListNode{
//public:
//	T data; ListNode<T>* pred; ListNode<T>* succ;
//	ListNode(){}
//	ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL){
//		data = e;	pred = p; succ = s;
//	}
//	//ListNode<T>* insertAsSucc(T const& e);
//};
//
//template<class T>class List{
//private:
//	int _size; ListNode<T>* header; ListNode<T>* trailer;
//public:
//	void init();	//初始化
//	List(){ init(); }
//	ListNode<T>* insert(T const&e);	//从后插入
//	//void xunHuan();	//实现循环
//	//T remove(T x);	//删除第一个data=x的结点，返回删除的数值
//	void List<T>::print(){
//		ListNode<T>* p = header;	//遍历指针
//		while (p!=NULL){
//			cout << (p->data) << "  ";
//			p = p->succ;
//		}
//		cout << "\n";
//	}
//	void sort();
//};
//////////////////////////////////////////////////////////
//template<class T>void List<T>::init(){
//	header = NULL; trailer = NULL;
//	_size = 0;
//}
//template<class T>ListNode<T>* List<T>::insert(T const&e){
//	ListNode<T>* p = new ListNode<T>(e);
//	if (header == NULL){
//		header = p; trailer = p;
//		_size++; return trailer;
//	}
//	p->pred = trailer;
//	trailer->succ = p;
//	trailer = p;
//	_size++;
//	return trailer;
//}
//
//template<class T>void List<T>::sort(){
//	ListNode<T> *p, *q, *p1, *q1, *q2;
//	if (_size / 2 == (_size - 1) / 2){	//奇数
//		p = header;	q = trailer->pred; q2 = trailer->pred;
//		while (p->succ!=NULL){
//			p1 = p->succ->succ;
//			p->succ = p1;
//			p1->pred = p;
//			p = p1;
//		}
//		while (q->pred!=header){
//			q1 = q->pred->pred;
//			q->pred = q1;
//			q1->succ = q;
//			q = q1;
//		}
//		p->succ = q2;
//		q2->pred = p;
//	}
//	else
//	{
//		p = header; q = trailer; q2 = trailer;
//		while (p->succ->succ != NULL){
//			p1 = p->succ->succ;
//			p->succ = p1;
//			p1->pred = p;
//			p = p1;
//		}
//		while (q->pred != header){
//			q1 = q->pred->pred;
//			q->pred = q1;
//			q1->succ = q;
//			q = q1;
//		}
//		p->succ = q2;
//		q2->pred = p;
//	}
//}
//
//////////////////////////
//int main(){
//	List<float>* fList = new List<float>;
//	cout << "结点个数是： ";
//	int num; cin >> num;
//	ListNode<float>* trailer;
//	float data;
//	cout << "输入每一个节点: ";
//	for (int i = 0; i < num; i++){
//		cin >> data;
//		trailer = fList->insert(data);
//	}
//	cout << "链表是： ";
//	fList->print();
//	fList->sort();
//	fList->print();
//}