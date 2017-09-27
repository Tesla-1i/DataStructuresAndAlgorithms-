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
private:
	int _size; ListNode<T>* header; ListNode<T>* trailer;
public:
	void init();	//初始化
	List(){ init(); }
	ListNode<T>* insert(T const& e);	//作为末节点插入
	int getSize(){ return _size; }
	void setSize(int num){ _size = num; }
	ListNode<T>* getHeader(){ return header; }
	void print();	//打印
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
	return trailer;		//返回单链表尾指针
}

//查找最大值，递归方法
template<class T>T getMax(ListNode<T>* a){
	T max = -1000;
	if (a == NULL) return max;	//最后节点的后边时
	T value = getMax(a->succ);
	if (a->data > value)
		return a->data;
	else
		return value;
}
//查找结点数目，递归方法
template<class T>int getNodeNum(ListNode<T>* a){
	if (a == NULL)	return 0;
	return 1 + getNodeNum(a->succ);
}
//计算结点数据的平均值，递归方法
template<class T>double getAvg(ListNode<T>* a, int n){//n是结点个数
	if (a == NULL) return 0;	//最后节点的后边
	return a->data / (double)n + getAvg(a->succ, n);
}

int main(){
	List<int>* fList = new List<int>;
	cout << "结点个数是： ";
	int num; cin >> num;
	fList->setSize(num);
	ListNode<int>* trailer;
	int data;
	cout << "输入每一个节点: ";
	for (int i = 0; i < num; i++){
		cin >> data;
		trailer = fList->insert(data);
	}
	cout << "链表是： ";
	fList->print();
	cout << "_size = " << (fList->getSize()) << "\n";
	ListNode<int>* l = fList->getHeader()->succ;	//因为带有头结点
	int max = getMax<int>(l);	//模板函数使用方法
	cout << "max = " << max << "\n";
	int nodeNum = getNodeNum<int>(l);
	cout << "nodeNum = " << nodeNum << "\n";
	double avg = getAvg<int>(l, nodeNum);
	cout << "avg = " << avg << "\n";
}
