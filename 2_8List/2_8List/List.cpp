//循环不带头双链表
#include<iostream>
using namespace std;
template<class T>class ListNode{
public:
	T data; ListNode<T>* pred; ListNode<T>* succ;
	ListNode(){}
	ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL){
		data = e;	pred = p; succ = s;
	}
	//ListNode<T>* insertAsSucc(T const& e);
};

template<class T>class List{
private:
	int _size; ListNode<T>* header; ListNode<T>* trailer;
public:
	void init();	//初始化
	List(){ init(); }
	ListNode<T>* insert(T const&e);	//从后插入
	void xunHuan();	//实现循环
	T remove(T x);	//删除第一个data=x的结点，返回删除的数值
	void List<T>::print(){
		ListNode<T>* p = header;	//遍历指针
		while (p->succ != header){
			cout << (p->data) << "  ";
			p = p->succ;
		}
		cout << (p->data);
		cout << "\n";
	}
};
////////////////////////////////////////////////////////
template<class T>void List<T>::init(){
	header = NULL; trailer = NULL;
	_size = 0;
}
template<class T>ListNode<T>* List<T>::insert(T const&e){
	ListNode<T>* p = new ListNode<T>(e);
	if (header == NULL){
		header = p; trailer = p;
		_size++; return trailer;
	}
	p->pred = trailer;
	trailer->succ = p;
	trailer = p;
	_size++;
	return trailer;
}
template<class T>void List<T>::xunHuan(){
	trailer->succ = header;
	header->pred = trailer;
}
template<class T>T List<T>::remove(T x){
	ListNode<T> *p;
	p = header;
	if (trailer->data == x){
		trailer->pred->succ = header;
		header->pred = trailer->pred;
		trailer = trailer->pred;
		//trailer->pred = NULL; trailer->succ = NULL; delete trailer;
		return x;
	}
	while (p->succ != header){
		if (p->data == x){
			p->pred->succ = p->succ;	//先处理p的前驱和后继
			p->succ->pred = p->pred;	
			p->pred = NULL; p->succ = NULL; delete p;	//再处理p自身
			return x;
		}
		p = p->succ;
	}
	return 10000;
}

////////////////////////
int main(){
	List<float>* fList = new List<float>;
	cout << "结点个数是： ";
	int num; cin >> num;
	ListNode<float>* trailer;
	float data;
	cout << "输入每一个节点: ";
	for (int i = 0; i < num; i++){
		cin >> data;
		trailer = fList->insert(data);
	}
	fList->xunHuan();
	cout << "链表是： ";
	fList->print();
	cout << "x = ";
	float x; cin >> x;
	float n=fList->remove(x);
	if (n == 10000)
		cout << "不存在";
	fList->print();
}