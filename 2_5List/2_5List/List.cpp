//不带头结点的单链表
#include<iostream>
#include<stack>
using namespace std;
template<class T>class ListNode{
public:
	T data; ListNode<T>* succ;	//数据域，后继指针
	ListNode(){}
	ListNode(T e, ListNode<T>* s = NULL) :data(e), succ(s){ }
};
template<class T>class List{
private:
	int _size; ListNode<T>* header; ListNode<T>* trailer;
public:
	void init();	//初始化
	List(){ init(); }
	ListNode<T>* insert(T const& e);	//作为末节点插入List,返回尾指针trailer。
	void reverse();		//倒置
	void merge(List<T>* List1);		//归并链表
	//只读函数
	void print();	//打印
	int getSize(){ return _size; }
};
/////////////////////////////////////
template<class T>void List<T>::init(){
	header = NULL; trailer = NULL;
	_size = 0;
}
template<class T>ListNode<T>* List<T>::insert(T const& e){
	ListNode<T>* p;	//临时指针p
	if (header == NULL){	//插入的是首节点
		p = new ListNode<T>(e);
		header = p; trailer = p;		//头指针指向首节点
		_size++;
		return trailer;
	}
	p = new ListNode<T>(e);
	trailer->succ = p;
	trailer = p;	//header不在变了,			差点写成 == ！！！！！！！！！！
	_size++;
	return trailer;
}
template<class T>void List<T>::print(){
	ListNode<T>* p = header;	//遍历指针
	while (p != NULL){
		cout << (p->data) << "  ";
		p = p->succ;
	}cout << "\n";
}

//先倒置后归并，辅助空间为常数级
template<class T>void List<T>::reverse(){
	/*stack<T>* temp = new stack<T>;
	ListNode<T>* p = header;
	while (p != NULL){
		temp->push(p->data);
		p = p->succ;
	}
	p = header;
	while (p != NULL){
		p->data = temp->top();
		p = p->succ;
		temp->pop();
	}*/

	//迭代版本	画图理解
	ListNode<T>* prev = NULL;	//保存当前的头结点
	ListNode<T>* tmp = NULL;	//保存当前结点的succ
	while (header != NULL){		
		tmp = header->succ;		//保存当前结点next
		header->succ = prev;	//将当前结点插入到头结点之前
		prev = header;			//插入后将当前节点设为头结点
		header = tmp;			//下次迭代的当前结点
	}
	header = prev;				//prev是倒置后的头结点
}

template<class T>void List<T>::merge(List<T>* List1){
	//当不进行倒置，直接归并时，可以进行头插入，小的为头，大的插在头前面，头再前移
	ListNode<T>* head, *p, *q,*p1,*q1;	//head为新的头指针
	p = header; q = List1->header;
	if ((header->data) < (List1->header->data)){
		head = header;	p = header->succ;
	}
	else{
		head = List1->header;	q = q->succ;
	}
	trailer = head;		//插入的第一个结点将是最后一个
	trailer->succ = NULL;	//既然是尾节点，那摩后继是NULL，否则打印时没有终止
	while (p&&q){
		if (p->data < q->data){
			p1 = p->succ;
			p->succ = head;
			head = p;
			p = p1;
		}
		else{
			q1 = q->succ;
			q->succ = head;
			head = q;
			q = q1;
		}
	}
	if (p == NULL){		//q还有剩余，一个个头插到head前面
		while (q){
			q1 = q->succ;
			q->succ = head;
			head = q;
			q = q1;
		}
	}
	else{
		while (p){
			p1 = p->succ;
			p->succ = head;
			head = p;
			p = p1;
		}
	}
	header = head;	//head是头指针

	//利用第三题的倒置
	//ListNode<T>* head, *p, *q, *p1, *q1, *temp;	//临时头结点
	//p = header; q = List1->header;
	//if (header->data >= List1->header->data){
	//	head = header; p = p->succ;
	//}
	//else{
	//	head = List1->header; q = q->succ;
	//}
	//temp = head;
	//while (p&&q){
	//	if (p->data >= q->data){
	//		p1 = p->succ;
	//		temp->succ = p;
	//		temp = p;
	//		p = p1;
	//	}
	//	else{
	//		q1 = q->succ;
	//		temp->succ = q;
	//		temp = q;
	//		q = q1;
	//	}
	//}
	//if (p == NULL){
	//	temp->succ = q;	temp = q;
	//}
	//if (q == NULL){
	//	temp->succ = p;	temp = p;
	//}
	//header = head;	//header仍是头结点
	//while (temp->succ != NULL){
	//	temp = temp->succ;
	//}
	//trailer = temp;	//尾指针也正常了
}

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
	cout << "链表是： ";
	fList->print();
	////////////////////
	List<float>* fList1 = new List<float>;
	cout << "结点个数是： ";
	int num1; cin >> num1;
	ListNode<float>* trailer1;
	float data1;
	cout << "输入每一个节点: ";
	for (int i = 0; i < num1; i++){
		cin >> data1;
		trailer1 = fList1->insert(data1);
	}
	cout << "链表是： ";
	fList1->print();
	//////////////////////
	//fList->reverse();
	//fList1->reverse();
	fList->merge(fList1);
	fList->print();
}
