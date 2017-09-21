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
	//ListNode<T>* insertAsPred(ListNode<T>* Node,ListNode<T>* nowNode);	//��Node����nowNodeǰ�棻
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
	
	//�����汾
	//ͷ���뷽��
	ListNode<T>* prev = NULL;	//���浱ǰ��ͷ���
	ListNode<T>* tmp = NULL;	//���浱ǰ����succ
	while (header != NULL){		
		tmp = header->succ;		//���浱ǰ���next
		header->succ = prev;	//����ǰ�����뵽ͷ���֮ǰ
		prev = header;			//����󽫵�ǰ�ڵ���Ϊͷ���
		header = tmp;			//�´ε����ĵ�ǰ���
	}
	header = prev;				//prev�ǵ��ú��ͷ���
	
	//����β���
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
	//����������
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
	cout << "_size = " << (fList->getSize()) << "\n";
	fList->reverse();
	fList->print();
}

