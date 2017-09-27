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
private:
	int _size; ListNode<T>* header; ListNode<T>* trailer;
public:
	void init();	//��ʼ��
	List(){ init(); }
	ListNode<T>* insert(T const& e);	//��Ϊĩ�ڵ����
	int getSize(){ return _size; }
	void setSize(int num){ _size = num; }
	ListNode<T>* getHeader(){ return header; }
	void print();	//��ӡ
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
	return trailer;		//���ص�����βָ��
}

//�������ֵ���ݹ鷽��
template<class T>T getMax(ListNode<T>* a){
	T max = -1000;
	if (a == NULL) return max;	//���ڵ�ĺ��ʱ
	T value = getMax(a->succ);
	if (a->data > value)
		return a->data;
	else
		return value;
}
//���ҽ����Ŀ���ݹ鷽��
template<class T>int getNodeNum(ListNode<T>* a){
	if (a == NULL)	return 0;
	return 1 + getNodeNum(a->succ);
}
//���������ݵ�ƽ��ֵ���ݹ鷽��
template<class T>double getAvg(ListNode<T>* a, int n){//n�ǽ�����
	if (a == NULL) return 0;	//���ڵ�ĺ��
	return a->data / (double)n + getAvg(a->succ, n);
}

int main(){
	List<int>* fList = new List<int>;
	cout << "�������ǣ� ";
	int num; cin >> num;
	fList->setSize(num);
	ListNode<int>* trailer;
	int data;
	cout << "����ÿһ���ڵ�: ";
	for (int i = 0; i < num; i++){
		cin >> data;
		trailer = fList->insert(data);
	}
	cout << "�����ǣ� ";
	fList->print();
	cout << "_size = " << (fList->getSize()) << "\n";
	ListNode<int>* l = fList->getHeader()->succ;	//��Ϊ����ͷ���
	int max = getMax<int>(l);	//ģ�庯��ʹ�÷���
	cout << "max = " << max << "\n";
	int nodeNum = getNodeNum<int>(l);
	cout << "nodeNum = " << nodeNum << "\n";
	double avg = getAvg<int>(l, nodeNum);
	cout << "avg = " << avg << "\n";
}
