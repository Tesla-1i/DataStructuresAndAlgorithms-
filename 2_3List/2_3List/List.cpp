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
	//ListNode<T>* insertAsPred(ListNode<T>* Node,ListNode<T>* nowNode);	//将Node插在nowNode前面；
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
	
	//迭代版本
	//头插入方法
	ListNode<T>* prev = NULL;	//保存当前的头结点
	ListNode<T>* tmp = NULL;	//保存当前结点的succ
	while (header != NULL){		
		tmp = header->succ;		//保存当前结点next
		header->succ = prev;	//将当前结点插入到头结点之前
		prev = header;			//插入后将当前节点设为头结点
		header = tmp;			//下次迭代的当前结点
	}
	header = prev;				//prev是倒置后的头结点
	
	//处理尾结点
	/*ListNode<T>* p, *tmp;
	p = header->succ;
	tmp = p->succ;
	p->succ = NULL;
	header->succ = p;
	p = tmp;
	while (p){
		tmp = p->succ;
		p->succ = header->succ;
		header->succ = p;
		p = tmp;
	}*/
	/*ListNode<T>** pointArray = new ListNode<T>[_size];
	ListNode<T>* p = header;
	for (int i = 0; i < _size; i++){
		ListNode<T>* q = pointArray[i];
		q = p;
		p = p->succ;
		if (p == NULL) break;
	}
*/
	//交换数据域
	/*ListNode<T>* p = header; ListNode<T>* q = trailer;
	for (int i = 0; i < (_size / 2 ); i++){
		swap(p->data, q->data);
		p = p->succ; q = q->succ;
	}
	ListNode<T>* temp = header;
	header = trailer; trailer = temp;*/
	//ttp://www.cnblogs.com/Ray1024/p/5687737.html
}
//////////////////////////////////////////
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
	cout << "_size = " << (fList->getSize()) << "\n";
	fList->reverse();
	fList->print();
}

