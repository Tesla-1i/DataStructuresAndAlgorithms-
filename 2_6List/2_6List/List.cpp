//��ͷ���ĵ�����
#include<iostream>
using namespace std;
template<class T>class ListNode{
public:
	T data; ListNode<T>* succ;	//�����ָ��
	ListNode(){ }
	ListNode(T e, ListNode<T>* s = NULL) :data(e), succ(s){}
};
template<class T>class List{
public:
	int _size; ListNode<T>* header; ListNode<T>* trailer;
public:
	void init();	//��ʼ��
	List(){ init(); }
	ListNode<T>* insert(T const& e);	//��Ϊĩ�ڵ����
	int getSize(){ return _size; }
	void setSize(int num){ _size = num; }
	ListNode<T>* getHeader(){ return header; }
	void print();	//��ӡ
	void merge(List<T>* List1);		//�鲢����
};
///////////////////////////////////
template<class T>void List<T>::init(){
	header = new ListNode<T>;	//header����Ϊ�գ��벻��ͷ�������������
	header->succ = NULL; trailer = header;
	header->data = _size;
}
template<class T>void List<T>::print(){
	ListNode<T>* p = header->succ;	//����ָ��,����ӡheader������
	while (p != NULL){
		cout << (p->data) << "  ";
		p = p->succ;
	}cout << "\n";
}
template<class T>ListNode<T>* List<T>::insert(T const&e){
	ListNode<T>* p = new ListNode<T>(e);
	trailer->succ = p;
	trailer = p;
	return trailer;		//���ص�����βָ��(�ٵ�βָ�룬���ĩָ��)
}

///////////////////////////////////////////////
//�ϲ�����ĺ���
template<class T>void List<T>::merge(List<T>* List1){
	ListNode<T> *head, *p, *q, *p1, *q1, *temp;	//head����ʱ��ָ��(first)����������ʱ��ͷ��
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
	if (p == NULL){	//q����һ�Σ��ӵ���������
		temp->succ = q; temp = q;
	}
	if (q == NULL){
		temp->succ = p; temp = p;
	}
	header->succ = head;	//header���Ǵ�ͷ��������ͷ��㣬headָ���׽��
	while (temp->succ != NULL){
		temp = temp->succ;
	}
	trailer = temp;
}

int main(){
	List<int>* fList1 = new List<int>;
	cout << "�������ǣ� ";
	int num; cin >> num;
	fList1->setSize(num);
	ListNode<int>* trailer1;
	int data;
	cout << "����ÿһ���ڵ�: ";
	for (int i = 0; i < num; i++){
		cin >> data;
		trailer1 = fList1->insert(data);
	}
	cout << "�����ǣ� ";
	fList1->print();
	//////////////////////////////
	List<int>* fList2 = new List<int>;
	cout << "�������ǣ� ";
	int num2; cin >> num2;
	fList2->setSize(num2);
	ListNode<int>* trailer2;
	int data2;
	cout << "����ÿһ���ڵ�: ";
	for (int i = 0; i < num2; i++){
		cin >> data2;
		trailer2 = fList2->insert(data2);
	}
	cout << "�����ǣ� ";
	fList2->print();
	fList1->merge(fList2);
	cout << "�������ǣ� \n";
	fList1->print();
}