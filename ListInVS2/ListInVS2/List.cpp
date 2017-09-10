#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

typedef int Rank;	//秩
//#define ListNodePosi(T) ListNode<T>*;	//列表结点位置,为了描述方便
//列表结点模板类，双向链表形式

template<class T>struct ListNode{
	T data;	ListNode<T>* pred;	ListNode<T>* succ;	//前驱与后继指针
	ListNode(){}
	ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL) : data(e), pred(p), succ(s) {}
	//操作接口
	ListNode<T>* insertAsPred(T const& e);	//当前节点前插入结点
	ListNode<T>* insertAsSucc(T const& e);	//当前节点后插入结点
};

//列表模板类
//头尾哨兵对外不可见，对外可见的第一个和最后一个是首节点first node，末节点last node
//哨兵结点的引入使得不用各种边界退化情况做专门处理，避免出错
template <class T>class List{
private:
	int _size; ListNode<T>* header; ListNode<T>* trailer;	//规模，头哨兵，尾哨兵
protected:
	void init();	//初始化列表
	int clear();	//清楚所有结点
	void copyNodes(ListNode<T>* p, int n);	//复制自位置p起的n项
	void merge(ListNode<T>*&, int, List<T>&, ListNode<T>*, int);	//归并
	void mergeSort(ListNode<T>*& p, int n);	//对自p开始的n个结点归并排序
	void selectionSort(ListNode<T>*, int);	//....选择排序
	void insertSort(ListNode<T>*, int);		//....插入排序
public:
	//构造函数
	List(){ init(); }
	List(List<T> const& L);		//整体复制构造，拷贝List L；
	List(List<T> const& L, Rank r, int n);	//复制L，自第r项起的n项
	List(ListNode<T>* p, int n);


	//复制列表自P位置起的n项
	~List();
	//只读访问接口
	Rank size()const{ return _size; }
	bool empty()const{ return _size <= 0; }
	//T& operator[](Rank r)const;
	ListNode<T>* &operator[](Rank r)const;
	ListNode<T>* first()const{ return header->succ; }	//返回首节点，不是头结点
	ListNode<T>* last()const{ return trailer->pred; }	//返回末节点，不是尾节点
	bool valid(ListNode<T>* p){
		return p && (p != trailer) && (p != header);	//判断位置p是否对外合法
	}
	int disordered()const;		//判断是否已经排序
	ListNode<T>* find(T const&e, int n, ListNode<T>* p)const;
	ListNode<T>* find(T const&e)const {
		return find(e, _size, trailer);
	}
	ListNode<T>* search(T const&e, int n, ListNode<T>*p)const;	//有序区间查找
	ListNode<T>* search(T const&e)const{		//有序列表查找
		return search(e, _size, trailer);
	}
	ListNode<T>* selectMax(ListNode<T>* p, int n);		//在在p及其n-1个后继中找最大者
	ListNode<T>* selectMax(){ return selectMax(header->succ, _size); }	//整体最大的
	void print(){
		ListNode<T>* p = first();
		while (p != trailer){
			cout << p->data << "\t";	p = p->succ;
		}
	}
	//可写访问的接口
	ListNode<T>* insertAsFrist(T const&e);	//将e作为首节点插入
	ListNode<T>* insertAsLast(T const&e);	//将e作为末节点插入
	ListNode<T>* insertA(ListNode<T>* p, T const& e);	//将e作为p的后继插入
	ListNode<T>* insertB(ListNode<T>* p, T const& e);	//将e作为p的前驱插入

	T remove(ListNode<T>* p);	//删除合法位置p处结点，返回删除的结点

	//void merge ( List<T>& L ) { merge ( first(), size, L, L.first(), L._size ); } //全列表归并
	void sort(ListNode<T>* p, int n);	//列表区间排序
	void sort(){ sort(first(), _size); }	//列表整体排序
	int deduplicate();		//无序去重
	int uniquify();		//有序去重
	void reverse();		//前后倒置
	//遍历
	template<class VST> void traverse(VST&); //遍历，依次visit操作（函数对象）
	void traverse(void(*)(T&));	//遍历，依次visit操作（函数指针）

};

template<class T>void List<T>::init(){
	header = new ListNode<T>; trailer = new ListNode<T>;	//创建头尾哨兵结点
	header->succ = trailer;		header->pred = NULL;
	trailer->pred = header;		trailer->succ = NULL;
	_size = 0;
}
template<class T> ListNode<T>*& List<T>::operator[](Rank r)const{
	ListNode<T>* p = first();		//从首节点开始
	while (0 < r--)		//后置--
		p = p->succ;
	return p;       //返回指针
}

template <class T> ListNode<T>* List<T>::insertAsFrist(T const &e) {
	_size++;
	return header->insertAsSucc(e);     //首节点
}
template  <class T> ListNode<T>* List<T>::insertAsLast(T const &e) {
	_size++;
	return trailer->insertAsPred(e);    //末节点
}
template <class T>ListNode<T>* List<T>::insertA(ListNode<T> *p, T const &e) {
	_size++; return p->insertAsSucc(e);
	//e作为p的后继插入
}
template <class T>ListNode<T>* List<T>::insertB(ListNode<T> *p, T const &e) {
	_size++;
	return p->insertAsPred(e);  //e作为p的前驱插入
}

//将e插入当前节点前
template <class T>ListNode<T>* ListNode<T>::insertAsPred(T const &e) {
	ListNode<T>* x = new ListNode(e, pred, this);
	pred->succ = x; pred = x;   //设置正向连接， 注意理解？？？？？？？？？？？？？？
	return x;       //返回新节点的位置
}
//将e插入当前节点之后
template <class T>ListNode<T>* ListNode<T>::insertAsSucc(T const &e) {
	ListNode<T>* x = new ListNode(e, this, succ);
	succ->pred = x;   succ = x;
	return x;
}

//基于复制的构造
//复制列表自p起的n项
template <class T>void List<T>::copyNodes(ListNode<T> *p, int n) {
	init();
	while (n--){
		insertAsLast(p->data);  p = p->succ;      //将p及之后项作为末节点插入
	}
}
template <class T>List<T>::List(ListNode<T> *p, int n) {
	copyNodes(p, n);
}
template <class T>List<T>::List(List<T> const &L, int r, int n) {
	//ListNode<T>* l=L->operator[](r);
	copyNodes(L[r], n);      //原先出错因为重载【】时，返回的不是引用
	//有问题？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
}
template <class T>List<T>::List(List<T> const &L) {
	copyNodes(L.first(), L._size);
}

//删除节点p，返回数值
template <class T>T List<T>::remove(ListNode<T> *p) {
	T e = p->data;
	p->pred->succ = p->succ; p->succ->pred = p->pred;       //后继，前驱  注意理解！！！！！
	delete p;   _size--;
	return e;
}
//析构
template <class T>List<T>::~List() {
	clear(); delete header; delete trailer;
}
template <class T>int List<T>::clear() {
	int oldSize = _size;      //清空链表。
	while (0<_size)
		remove(header->succ);
	return oldSize;
}

//唯一化
template <class T>int List<T>::deduplicate() {
	if (_size<2)return 0;
	int oldSize = _size;
	ListNode<T>* p = header;  Rank r = 0;   //p从首节点开始
	while (trailer != (p = p->succ)){       //依次直达末节点
		ListNode<T>* q = find(p->data, r, p);//p的r个前驱中查找雷同者
		q ? remove(q) : r++;                 //若存在，则删除
	}
	return oldSize - _size;
}
//遍历
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

//唯一化
template <class T>int List<T>::uniquify() {
	if (_size<2) return 0;
	int oldSize = _size;
	ListNode<T>* p = first(); ListNode<T>* q;     //
	while (trailer != (q = p->succ))    //q为p后继
	if (p->data != q->data) p = q;  //若互不相等，转向下一lun
	else remove(q);     //删除
	return oldSize - _size;
}

template <class T>ListNode<T>* List<T>::search(T const &e, int n, ListNode<T> *p) const {
	//在p的n个前驱中找到不大于e的最后者
	while (0<n--){      //自右到左
		if (((p = p->pred)->data) <= e) break;
	}
	return p;
}

//排序器
template <class T>void List<T>::sort(ListNode<T> *p, int n) {
	//列表区间排序
	//srand((int)time(0));???????????????????????????????????????????????????????????????
	//int i=std::rank();
	//srand(2);
	switch (rand() % 3){
	//case 0:selectionSort(p, n); break;
	
	case 3:selectionSort(p, n);
		cout << "选择排序\n";	break;
	case 2:mergeSort(p, n);
		cout << "归并排序\n";	break;
	case 1:insertSort(p, n);
		cout << "插入排序\n";
	}
}
//起始于p的n个元素
template <class T>void List<T>::insertSort(ListNode<T> *p, int n) {
	for (int r = 0; r<n+1; r++){
		//书上是r<n; 发现出错，
		insertA(search(p->data, r, p), p->data);
		p = p->succ; remove(p->pred);     //转向下一个
	}
}

template <class T> void List<T>::selectionSort(ListNode<T> *p, int n) {
	ListNode<T>* head = p->pred; ListNode<T>* tail = p;
	for (int i = 0; i<n; i++)
		tail = tail->succ;    //待排序区间（head，tail）
	while (1<n){
		//在至少还剩两个节点前
		ListNode<T>* max = selectMax(head->succ, n);
		insertB(tail, remove(max));  //将其移到无序区间末尾，（作为有序区间首元素）
		tail = tail->pred; n--;
	}
}

template <class T>static bool lt(T&a, T&b){ return a<b; }
template <class T>ListNode<T>* List<T>::selectMax(ListNode<T> *p, int n) {
	ListNode<T>* max = p; //暂定为p
	for (ListNode<T>* cur = p; 1<n; n--){
		if (!lt((cur = cur->succ)->data, max->data))
			max = cur;
	}
	return max;
}

template <class T>void List<T>::merge(ListNode<T> *&p, int n, List<T> &L, ListNode<T> *q, int m) {
	//当前列表自p起n个元素，与L列表自q起m个元素归并
	ListNode<T>* pp = p->pred;
	while (0<m){    //q尚未移除区间
		if ((0<n) && (p->data <= q->data)){  //若p仍在区间，且V(p)<=V(q)
			if (q == (p = p->succ)) break; n--;//p归入合并列表，并替换为其直接后继
		}
		else{ //若p已超出右界，或V(q)<V(p)
			insertB(p, L.remove((q = q->succ)->pred)); m--;    //将q转移至p之前
		}
	}
	p = pp->succ;      //确定归并后的新起点
}

template <class T> void List<T>::mergeSort(ListNode<T> *&p, int n) {
	if (n<2)return;
	int m = n >> 1; //以中点为界
	ListNode<T>* q = p; for (int i = 0; i<m; i++)q = q->succ;   //均分列表
	mergeSort(p, m); mergeSort(q, n - m);       //对前后分别进行排序
	merge(p, m, *this, q, n - m);     //归并
}//注意，排序后，p依然指向归并后区间新起点

template <class T> int List<T>::disordered() const {
	int n = 0; ListNode<T>* p = first();
	for (int i = 0; i<_size - 1; p = p->succ, i++){
		if (p->data>p->succ->data) n++;
	}
	return n;   //返回逆序对数
}

template <class T>
ListNode<T> *List<T>::find(const T &e, int n, ListNode<T> *p) const {	//无序区间查找
	//在p的n个前驱中找到等于e的最后者
	while (0<n--)		//自右到左
	if (e == (p = p->pred)->data) return p;
	return NULL;
}

template <class T> void List<T>::reverse() {
	if (_size < 2) return; //平凡情况
	for (ListNode<T>* p = header; p; p = p->pred) //自前向后，依次
		swap(p->pred, p->succ); //交换各节点的前驱、后继指针
	swap(header, trailer); //头、尾节点互换
}
int main(){
	List<float> fList;
	//List.insertAsFrist(11);
	fList.print();
	srand(111);
	for (int i = 0; i < 10; i++){
		fList.insertAsLast(rand() % 10);
	}
	cout << "通过插入创造链表: ";
	fList.print();
	List<float> fList1(fList, 1, 3);
	cout << "\n复制构造，自r=1起的三项： ";
	fList1.print();
	ListNode<float>* p = fList.first();
	cout << "\n测试first() " << (p->data) << "\n";
	int d = fList.disordered();
	cout << "\n是否已排序，逆序对数： " << d << ends;
	fList1.reverse();
	cout << "fList1前后倒置: ";
	fList1.print();
	fList1.deduplicate();
	cout << "fList1无序去重 ";
	fList1.print();
	fList.remove(p);
	cout << "\nflist删除p\n";
	fList.print();
	fList.sort();
	cout << "插入排序有问题！!!!!!!!!!!!!!!!!!!!!!!!!已解决，见插入排序代码";
	cout << "fList排序： ";
	fList.print();
	fList.uniquify();
	cout << "\n有序去重\n";
	fList.print();
	incerase(fList);
	cout << "\n遍历加一 \n";
	fList.print();
}







