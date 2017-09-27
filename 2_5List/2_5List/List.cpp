//����ͷ���ĵ�����
#include<iostream>
#include<stack>
using namespace std;
template<class T>class ListNode{
public:
	T data; ListNode<T>* succ;	//�����򣬺��ָ��
	ListNode(){}
	ListNode(T e, ListNode<T>* s = NULL) :data(e), succ(s){ }
};
template<class T>class List{
private:
	int _size; ListNode<T>* header; ListNode<T>* trailer;
public:
	void init();	//��ʼ��
	List(){ init(); }
	ListNode<T>* insert(T const& e);	//��Ϊĩ�ڵ����List,����βָ��trailer��
	void reverse();		//����
	void merge(List<T>* List1);		//�鲢����
	//ֻ������
	void print();	//��ӡ
	int getSize(){ return _size; }
};
/////////////////////////////////////
template<class T>void List<T>::init(){
	header = NULL; trailer = NULL;
	_size = 0;
}
template<class T>ListNode<T>* List<T>::insert(T const& e){
	ListNode<T>* p;	//��ʱָ��p
	if (header == NULL){	//��������׽ڵ�
		p = new ListNode<T>(e);
		header = p; trailer = p;		//ͷָ��ָ���׽ڵ�
		_size++;
		return trailer;
	}
	p = new ListNode<T>(e);
	trailer->succ = p;
	trailer = p;	//header���ڱ���,			���д�� == ��������������������
	_size++;
	return trailer;
}
template<class T>void List<T>::print(){
	ListNode<T>* p = header;	//����ָ��
	while (p != NULL){
		cout << (p->data) << "  ";
		p = p->succ;
	}cout << "\n";
}

//�ȵ��ú�鲢�������ռ�Ϊ������
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

	//�����汾	��ͼ���
	ListNode<T>* prev = NULL;	//���浱ǰ��ͷ���
	ListNode<T>* tmp = NULL;	//���浱ǰ����succ
	while (header != NULL){		
		tmp = header->succ;		//���浱ǰ���next
		header->succ = prev;	//����ǰ�����뵽ͷ���֮ǰ
		prev = header;			//����󽫵�ǰ�ڵ���Ϊͷ���
		header = tmp;			//�´ε����ĵ�ǰ���
	}
	header = prev;				//prev�ǵ��ú��ͷ���
}

template<class T>void List<T>::merge(List<T>* List1){
	//�������е��ã�ֱ�ӹ鲢ʱ�����Խ���ͷ���룬С��Ϊͷ����Ĳ���ͷǰ�棬ͷ��ǰ��
	ListNode<T>* head, *p, *q,*p1,*q1;	//headΪ�µ�ͷָ��
	p = header; q = List1->header;
	if ((header->data) < (List1->header->data)){
		head = header;	p = header->succ;
	}
	else{
		head = List1->header;	q = q->succ;
	}
	trailer = head;		//����ĵ�һ����㽫�����һ��
	trailer->succ = NULL;	//��Ȼ��β�ڵ㣬��Ħ�����NULL�������ӡʱû����ֹ
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
	if (p == NULL){		//q����ʣ�࣬һ����ͷ�嵽headǰ��
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
	header = head;	//head��ͷָ��

	//���õ�����ĵ���
	//ListNode<T>* head, *p, *q, *p1, *q1, *temp;	//��ʱͷ���
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
	//header = head;	//header����ͷ���
	//while (temp->succ != NULL){
	//	temp = temp->succ;
	//}
	//trailer = temp;	//βָ��Ҳ������
}

int main(){
	List<float>* fList = new List<float>;
	cout << "�������ǣ� ";
	int num; cin >> num;
	ListNode<float>* trailer;
	float data;
	cout << "����ÿһ���ڵ�: ";
	for (int i = 0; i < num; i++){
		cin >> data;
		trailer = fList->insert(data);
	}
	cout << "�����ǣ� ";
	fList->print();
	////////////////////
	List<float>* fList1 = new List<float>;
	cout << "�������ǣ� ";
	int num1; cin >> num1;
	ListNode<float>* trailer1;
	float data1;
	cout << "����ÿһ���ڵ�: ";
	for (int i = 0; i < num1; i++){
		cin >> data1;
		trailer1 = fList1->insert(data1);
	}
	cout << "�����ǣ� ";
	fList1->print();
	//////////////////////
	//fList->reverse();
	//fList1->reverse();
	fList->merge(fList1);
	fList->print();
}
