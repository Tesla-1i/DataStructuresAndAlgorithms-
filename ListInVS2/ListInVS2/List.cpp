#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

typedef int Rank;	//��
//#define ListNodePosi(T) ListNode<T>*;	//�б���λ��,Ϊ����������
//�б���ģ���࣬˫��������ʽ

template<class T>struct ListNode{
	T data;	ListNode<T>* pred;	ListNode<T>* succ;	//ǰ������ָ��
	ListNode(){}
	ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL) : data(e), pred(p), succ(s) {}
	//�����ӿ�
	ListNode<T>* insertAsPred(T const& e);	//��ǰ�ڵ�ǰ������
	ListNode<T>* insertAsSucc(T const& e);	//��ǰ�ڵ�������
};

//�б�ģ����
//ͷβ�ڱ����ⲻ�ɼ�������ɼ��ĵ�һ�������һ�����׽ڵ�first node��ĩ�ڵ�last node
//�ڱ���������ʹ�ò��ø��ֱ߽��˻������ר�Ŵ����������
template <class T>class List{
private:
	int _size; ListNode<T>* header; ListNode<T>* trailer;	//��ģ��ͷ�ڱ���β�ڱ�
protected:
	void init();	//��ʼ���б�
	int clear();	//������н��
	void copyNodes(ListNode<T>* p, int n);	//������λ��p���n��
	void merge(ListNode<T>*&, int, List<T>&, ListNode<T>*, int);	//�鲢
	void mergeSort(ListNode<T>*& p, int n);	//����p��ʼ��n�����鲢����
	void selectionSort(ListNode<T>*, int);	//....ѡ������
	void insertSort(ListNode<T>*, int);		//....��������
public:
	//���캯��
	List(){ init(); }
	List(List<T> const& L);		//���帴�ƹ��죬����List L��
	List(List<T> const& L, Rank r, int n);	//����L���Ե�r�����n��
	List(ListNode<T>* p, int n);


	//�����б���Pλ�����n��
	~List();
	//ֻ�����ʽӿ�
	Rank size()const{ return _size; }
	bool empty()const{ return _size <= 0; }
	//T& operator[](Rank r)const;
	ListNode<T>* &operator[](Rank r)const;
	ListNode<T>* first()const{ return header->succ; }	//�����׽ڵ㣬����ͷ���
	ListNode<T>* last()const{ return trailer->pred; }	//����ĩ�ڵ㣬����β�ڵ�
	bool valid(ListNode<T>* p){
		return p && (p != trailer) && (p != header);	//�ж�λ��p�Ƿ����Ϸ�
	}
	int disordered()const;		//�ж��Ƿ��Ѿ�����
	ListNode<T>* find(T const&e, int n, ListNode<T>* p)const;
	ListNode<T>* find(T const&e)const {
		return find(e, _size, trailer);
	}
	ListNode<T>* search(T const&e, int n, ListNode<T>*p)const;	//�����������
	ListNode<T>* search(T const&e)const{		//�����б����
		return search(e, _size, trailer);
	}
	ListNode<T>* selectMax(ListNode<T>* p, int n);		//����p����n-1��������������
	ListNode<T>* selectMax(){ return selectMax(header->succ, _size); }	//��������
	void print(){
		ListNode<T>* p = first();
		while (p != trailer){
			cout << p->data << "\t";	p = p->succ;
		}
	}
	//��д���ʵĽӿ�
	ListNode<T>* insertAsFrist(T const&e);	//��e��Ϊ�׽ڵ����
	ListNode<T>* insertAsLast(T const&e);	//��e��Ϊĩ�ڵ����
	ListNode<T>* insertA(ListNode<T>* p, T const& e);	//��e��Ϊp�ĺ�̲���
	ListNode<T>* insertB(ListNode<T>* p, T const& e);	//��e��Ϊp��ǰ������

	T remove(ListNode<T>* p);	//ɾ���Ϸ�λ��p����㣬����ɾ���Ľ��

	//void merge ( List<T>& L ) { merge ( first(), size, L, L.first(), L._size ); } //ȫ�б�鲢
	void sort(ListNode<T>* p, int n);	//�б���������
	void sort(){ sort(first(), _size); }	//�б���������
	int deduplicate();		//����ȥ��
	int uniquify();		//����ȥ��
	void reverse();		//ǰ����
	//����
	template<class VST> void traverse(VST&); //����������visit��������������
	void traverse(void(*)(T&));	//����������visit����������ָ�룩

};

template<class T>void List<T>::init(){
	header = new ListNode<T>; trailer = new ListNode<T>;	//����ͷβ�ڱ����
	header->succ = trailer;		header->pred = NULL;
	trailer->pred = header;		trailer->succ = NULL;
	_size = 0;
}
template<class T> ListNode<T>*& List<T>::operator[](Rank r)const{
	ListNode<T>* p = first();		//���׽ڵ㿪ʼ
	while (0 < r--)		//����--
		p = p->succ;
	return p;       //����ָ��
}

template <class T> ListNode<T>* List<T>::insertAsFrist(T const &e) {
	_size++;
	return header->insertAsSucc(e);     //�׽ڵ�
}
template  <class T> ListNode<T>* List<T>::insertAsLast(T const &e) {
	_size++;
	return trailer->insertAsPred(e);    //ĩ�ڵ�
}
template <class T>ListNode<T>* List<T>::insertA(ListNode<T> *p, T const &e) {
	_size++; return p->insertAsSucc(e);
	//e��Ϊp�ĺ�̲���
}
template <class T>ListNode<T>* List<T>::insertB(ListNode<T> *p, T const &e) {
	_size++;
	return p->insertAsPred(e);  //e��Ϊp��ǰ������
}

//��e���뵱ǰ�ڵ�ǰ
template <class T>ListNode<T>* ListNode<T>::insertAsPred(T const &e) {
	ListNode<T>* x = new ListNode(e, pred, this);
	pred->succ = x; pred = x;   //�����������ӣ� ע����⣿��������������������������
	return x;       //�����½ڵ��λ��
}
//��e���뵱ǰ�ڵ�֮��
template <class T>ListNode<T>* ListNode<T>::insertAsSucc(T const &e) {
	ListNode<T>* x = new ListNode(e, this, succ);
	succ->pred = x;   succ = x;
	return x;
}

//���ڸ��ƵĹ���
//�����б���p���n��
template <class T>void List<T>::copyNodes(ListNode<T> *p, int n) {
	init();
	while (n--){
		insertAsLast(p->data);  p = p->succ;      //��p��֮������Ϊĩ�ڵ����
	}
}
template <class T>List<T>::List(ListNode<T> *p, int n) {
	copyNodes(p, n);
}
template <class T>List<T>::List(List<T> const &L, int r, int n) {
	//ListNode<T>* l=L->operator[](r);
	copyNodes(L[r], n);      //ԭ�ȳ�����Ϊ���ء���ʱ�����صĲ�������
	//�����⣿����������������������������������������������������������������������
}
template <class T>List<T>::List(List<T> const &L) {
	copyNodes(L.first(), L._size);
}

//ɾ���ڵ�p��������ֵ
template <class T>T List<T>::remove(ListNode<T> *p) {
	T e = p->data;
	p->pred->succ = p->succ; p->succ->pred = p->pred;       //��̣�ǰ��  ע����⣡��������
	delete p;   _size--;
	return e;
}
//����
template <class T>List<T>::~List() {
	clear(); delete header; delete trailer;
}
template <class T>int List<T>::clear() {
	int oldSize = _size;      //�������
	while (0<_size)
		remove(header->succ);
	return oldSize;
}

//Ψһ��
template <class T>int List<T>::deduplicate() {
	if (_size<2)return 0;
	int oldSize = _size;
	ListNode<T>* p = header;  Rank r = 0;   //p���׽ڵ㿪ʼ
	while (trailer != (p = p->succ)){       //����ֱ��ĩ�ڵ�
		ListNode<T>* q = find(p->data, r, p);//p��r��ǰ���в�����ͬ��
		q ? remove(q) : r++;                 //�����ڣ���ɾ��
	}
	return oldSize - _size;
}
//����
template <class T>void List<T>::traverse(void(*visit)(T&)) {
	for (ListNode<T>* p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}

template <class T>template <class VST> void List<T>::traverse(VST& visit) {
	for (ListNode<T>*p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}

template <class T>struct Increase{
	virtual void operator()(T& e){ e++; }
};
template <class T>void incerase(List<T>& L){
	L.traverse(Increase<T>());
}

//Ψһ��
template <class T>int List<T>::uniquify() {
	if (_size<2) return 0;
	int oldSize = _size;
	ListNode<T>* p = first(); ListNode<T>* q;     //
	while (trailer != (q = p->succ))    //qΪp���
	if (p->data != q->data) p = q;  //��������ȣ�ת����һlun
	else remove(q);     //ɾ��
	return oldSize - _size;
}

template <class T>ListNode<T>* List<T>::search(T const &e, int n, ListNode<T> *p) const {
	//��p��n��ǰ�����ҵ�������e�������
	while (0<n--){      //���ҵ���
		if (((p = p->pred)->data) <= e) break;
	}
	return p;
}

//������
template <class T>void List<T>::sort(ListNode<T> *p, int n) {
	//�б���������
	//srand((int)time(0));???????????????????????????????????????????????????????????????
	//int i=std::rank();
	//srand(2);
	switch (rand() % 3){
	//case 0:selectionSort(p, n); break;
	
	case 3:selectionSort(p, n);
		cout << "ѡ������\n";	break;
	case 2:mergeSort(p, n);
		cout << "�鲢����\n";	break;
	case 1:insertSort(p, n);
		cout << "��������\n";
	}
}
//��ʼ��p��n��Ԫ��
template <class T>void List<T>::insertSort(ListNode<T> *p, int n) {
	for (int r = 0; r<n+1; r++){
		//������r<n; ���ֳ���
		insertA(search(p->data, r, p), p->data);
		p = p->succ; remove(p->pred);     //ת����һ��
	}
}

template <class T> void List<T>::selectionSort(ListNode<T> *p, int n) {
	ListNode<T>* head = p->pred; ListNode<T>* tail = p;
	for (int i = 0; i<n; i++)
		tail = tail->succ;    //���������䣨head��tail��
	while (1<n){
		//�����ٻ�ʣ�����ڵ�ǰ
		ListNode<T>* max = selectMax(head->succ, n);
		insertB(tail, remove(max));  //�����Ƶ���������ĩβ������Ϊ����������Ԫ�أ�
		tail = tail->pred; n--;
	}
}

template <class T>static bool lt(T&a, T&b){ return a<b; }
template <class T>ListNode<T>* List<T>::selectMax(ListNode<T> *p, int n) {
	ListNode<T>* max = p; //�ݶ�Ϊp
	for (ListNode<T>* cur = p; 1<n; n--){
		if (!lt((cur = cur->succ)->data, max->data))
			max = cur;
	}
	return max;
}

template <class T>void List<T>::merge(ListNode<T> *&p, int n, List<T> &L, ListNode<T> *q, int m) {
	//��ǰ�б���p��n��Ԫ�أ���L�б���q��m��Ԫ�ع鲢
	ListNode<T>* pp = p->pred;
	while (0<m){    //q��δ�Ƴ�����
		if ((0<n) && (p->data <= q->data)){  //��p�������䣬��V(p)<=V(q)
			if (q == (p = p->succ)) break; n--;//p����ϲ��б����滻Ϊ��ֱ�Ӻ��
		}
		else{ //��p�ѳ����ҽ磬��V(q)<V(p)
			insertB(p, L.remove((q = q->succ)->pred)); m--;    //��qת����p֮ǰ
		}
	}
	p = pp->succ;      //ȷ���鲢��������
}

template <class T> void List<T>::mergeSort(ListNode<T> *&p, int n) {
	if (n<2)return;
	int m = n >> 1; //���е�Ϊ��
	ListNode<T>* q = p; for (int i = 0; i<m; i++)q = q->succ;   //�����б�
	mergeSort(p, m); mergeSort(q, n - m);       //��ǰ��ֱ��������
	merge(p, m, *this, q, n - m);     //�鲢
}//ע�⣬�����p��Ȼָ��鲢�����������

template <class T> int List<T>::disordered() const {
	int n = 0; ListNode<T>* p = first();
	for (int i = 0; i<_size - 1; p = p->succ, i++){
		if (p->data>p->succ->data) n++;
	}
	return n;   //�����������
}

template <class T>
ListNode<T> *List<T>::find(const T &e, int n, ListNode<T> *p) const {	//�����������
	//��p��n��ǰ�����ҵ�����e�������
	while (0<n--)		//���ҵ���
	if (e == (p = p->pred)->data) return p;
	return NULL;
}

template <class T> void List<T>::reverse() {
	if (_size < 2) return; //ƽ�����
	for (ListNode<T>* p = header; p; p = p->pred) //��ǰ�������
		swap(p->pred, p->succ); //�������ڵ��ǰ�������ָ��
	swap(header, trailer); //ͷ��β�ڵ㻥��
}
int main(){
	List<float> fList;
	//List.insertAsFrist(11);
	fList.print();
	srand(111);
	for (int i = 0; i < 10; i++){
		fList.insertAsLast(rand() % 10);
	}
	cout << "ͨ�����봴������: ";
	fList.print();
	List<float> fList1(fList, 1, 3);
	cout << "\n���ƹ��죬��r=1������ ";
	fList1.print();
	ListNode<float>* p = fList.first();
	cout << "\n����first() " << (p->data) << "\n";
	int d = fList.disordered();
	cout << "\n�Ƿ���������������� " << d << ends;
	fList1.reverse();
	cout << "fList1ǰ����: ";
	fList1.print();
	fList1.deduplicate();
	cout << "fList1����ȥ�� ";
	fList1.print();
	fList.remove(p);
	cout << "\nflistɾ��p\n";
	fList.print();
	fList.sort();
	cout << "�������������⣡!!!!!!!!!!!!!!!!!!!!!!!!�ѽ�����������������";
	cout << "fList���� ";
	fList.print();
	fList.uniquify();
	cout << "\n����ȥ��\n";
	fList.print();
	incerase(fList);
	cout << "\n������һ \n";
	fList.print();
}







