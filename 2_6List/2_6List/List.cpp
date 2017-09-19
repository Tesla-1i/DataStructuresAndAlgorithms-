//带头结点的单链表
#include<iostream>
using namespace std;
template<class T>class ListNode{
public:
	T data; ListNode<T>* succ;	//结点后继指针
	ListNode(){ }
	ListNode(T e, ListNode<T>* s = NULL) :data(e), succ(s){}
};
template<class T>class List{
public:
	int _size; ListNode<T>* header; ListNode<T>* trailer;
public:
	void init();	//初始化
	List(){ init(); }
	ListNode<T>* insert(T const& e);	//作为末节点插入
	int getSize(){ return _size; }
	void setSize(int num){ _size = num; }
	ListNode<T>* getHeader(){ return header; }
	void print();	//打印
	void merge(List<T>* List1);		//归并操作
};
///////////////////////////////////
template<class T>void List<T>::init(){
	header = new ListNode<T>;	//header本身不为空；与不带头结点的链表的区别
	header->succ = NULL; trailer = header;
	header->data = _size;
}
template<class T>void List<T>::print(){
	ListNode<T>* p = header->succ;	//遍历指针,不打印header数据域
	while (p != NULL){
		cout << (p->data) << "  ";
		p = p->succ;
	}cout << "\n";
}
template<class T>ListNode<T>* List<T>::insert(T const&e){
	ListNode<T>* p = new ListNode<T>(e);
	trailer->succ = p;
	trailer = p;
	return trailer;		//返回单链表尾指针(假的尾指针，真的末指针)
}

///////////////////////////////////////////////
//合并链表的函数
template<class T>void List<T>::merge(List<T>* List1){
	ListNode<T> *head, *p, *q, *p1, *q1, *temp;	//head是临时首指针(first)（新链表暂时无头）
	p = header->succ; q = List1->header->succ;
	if (header->succ->data <= List1->header->succ->data){
		head = header->succ;  p = p->succ;
	}
	else{
		head = List1->header->succ; q = q->succ;
	}
	temp = head;
	while (p&&q){
		if (p->data <= q->data){
			p1 = p->succ;
			temp->succ = p;
			temp = p;
			p = p1;
		}
		else{
			q1 = q->succ;
			temp->succ = q;
			temp = q;
			q = q1;
		}
	}
	if (p == NULL){	//q还有一段，接到新链表上
		temp->succ = q; temp = q;
	}
	if (q == NULL){
		temp->succ = p; temp = p;
	}
	header->succ = head;	//header还是带头结点链表的头结点，head指向首结点
	while (temp->succ != NULL){
		temp = temp->succ;
	}
	trailer = temp;
}

int main(){
	List<int>* fList1 = new List<int>;
	cout << "结点个数是： ";
	int num; cin >> num;
	fList1->setSize(num);
	ListNode<int>* trailer1;
	int data;
	cout << "输入每一个节点: ";
	for (int i = 0; i < num; i++){
		cin >> data;
		trailer1 = fList1->insert(data);
	}
	cout << "链表是： ";
	fList1->print();
	//////////////////////////////
	List<int>* fList2 = new List<int>;
	cout << "结点个数是： ";
	int num2; cin >> num2;
	fList2->setSize(num2);
	ListNode<int>* trailer2;
	int data2;
	cout << "输入每一个节点: ";
	for (int i = 0; i < num2; i++){
		cin >> data2;
		trailer2 = fList2->insert(data2);
	}
	cout << "链表是： ";
	fList2->print();
	fList1->merge(fList2);
	cout << "新链表是： \n";
	fList1->print();
}