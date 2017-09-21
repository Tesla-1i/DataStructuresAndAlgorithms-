//#include<iostream>
//using namespace std;

typedef int Rank;	//秩
//#define ListNodePosi(T) ListNode<T>*;	//列表结点位置,为了描述方便
//列表结点模板类，双向链表形式
#ifndef L
#define L
template<class T>struct ListNode{
	T data;	ListNode<T>* pred;	ListNodePosi(T) succ;	//前驱与后继指针
	ListNode(){}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) :data(e), pred(p), succ(s){}
	//操作接口
	ListNodePosi(T) insertAsPred(T const& e);	//当前节点前插入结点
	ListNodePosi(T) insertAsSucc(T const& e);	//当前节点后插入结点
};
#endif
//列表模板类
//头尾哨兵对外不可见，对外可见的第一个和最后一个是首节点first node，末节点last node
//哨兵结点的引入使得不用各种边界退化情况做专门处理，避免出错
template <class T>class List{
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;	//规模，头哨兵，尾哨兵
protected:
	void init();	//初始化列表
	int clear();	//清楚所有结点
	void copyNodes(ListNodePosi(T) p, int n);	//复制自位置p起的n项
	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);	//归并
	void mergeSort(ListNodePosi(T)& p, int n);	//对自p开始的n个结点归并排序
	void selectionSort(ListNodePosi(T), int);	//....选择排序
	void insertSort(ListNodePosi(T), int);		//....插入排序
public:
	//构造函数
	List(){ init(); }
	List(List<T> const& L);		//整体复制构造，拷贝List L；
	List(List<T> const& L, Rank r, int n);	//复制L，自第r项起的n项
	List(ListNodePosi(T) p, int n);		//复制列表自P位置起的n项
	~List();
	//只读访问接口
	Rank size()const{ return _size; }
	bool empty()const{ return _size <= 0; }
	T& operator[](Rank r)const;
	ListNodePosi(T) first()const{ return header->succ; }	//返回首节点，不是头结点
	ListNodePosi(T) last()const{ return trailer->pred; }	//返回末节点，不是尾节点
	bool valid(ListNodePosi(T) p){
		return p && (p != trailer) && (p != header);	//判断位置p是否对外合法
	}
	int disordered()const;		//判断是否已经排序
	ListNodePosi(T) find(T const&e, int n, ListNode<T>* p)const{	//无序区间查找
		//在p的n个前驱中找到等于e的最后者
		while (0<n--)		//自右到左
			if (e == (p = p->pred)->data) return p;
		return NULL;
	}
	ListNodePosi(T) find(T const&e)const{		//无序列表查找
		return find(e, _size, trailer);
	}
	ListNodePosi(T) search(T const&e, int n, ListNodePosi(T)p)const;	//有序区间查找
	ListNodePosi(T) search(T const&e)const{		//有序列表查找
		return search(e, _size, trailer);
	}
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);		//在在p及其n-1个后继中找最大者
	ListNodePosi(T) selectMax(){ return selectMax(header->succ, _size); }	//整体最大的
	//可写访问的接口
	ListNode<T>* insertAsFrist(T const&e);	//将e作为首节点插入
	ListNodePosi(T) insertAsLast(T const&e);	//将e作为末节点插入
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);	//将e作为p的后继插入
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);	//将e作为p的前驱插入
	
	T remove(ListNodePosi(T) p);	//删除合法位置p处结点，返回删除的结点

	void merge(List<T>& L){			//全列表归并， 感觉有点问题？？？？？？？？？？？？？？
		merge(first(), size, L, L.first(), L.size());
	}
	void sort(ListNodePosi(T) p, int n);	//列表区间排序
	void sort(){ sort(first(), _size); }	//列表整体排序
	int deduplicate();		//无序去重
	int uniquify();		//有序去重
	void reverse();		//前后倒置
	//遍历
	void traverse(void(*)(T&));	//遍历，依次visit操作（函数指针）
	template<class VST> void traverse(VST&); //遍历，依次visit操作（函数对象）
};

template<class T>void List<T>::init(){
	header = new ListNode<T>; trailer = new ListNode<T>;	//创建头尾哨兵结点
	header->succ = trailer;		header->pred = NULL;
	trailer->pred = header;		trailer->succ = NULL;
	_size = 0;
}
template<class T> T& List<T>::operator[](Rank r)const{
	ListNodePosi(T) p = first();		//从首节点开始
	while (0 < r--)		//后置--
		p = p->succ;	
	return p->data;
}

template<class T>	
ListNode<T>* List<T>::insertAsFirst(T const&e){

}
	

