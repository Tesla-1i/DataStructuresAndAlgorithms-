//#include<iostream>
//using namespace std;

typedef int Rank;	//��
//#define ListNodePosi(T) ListNode<T>*;	//�б���λ��,Ϊ����������
//�б���ģ���࣬˫��������ʽ
#ifndef L
#define L
template<class T>struct ListNode{
	T data;	ListNode<T>* pred;	ListNodePosi(T) succ;	//ǰ������ָ��
	ListNode(){}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) :data(e), pred(p), succ(s){}
	//�����ӿ�
	ListNodePosi(T) insertAsPred(T const& e);	//��ǰ�ڵ�ǰ������
	ListNodePosi(T) insertAsSucc(T const& e);	//��ǰ�ڵ�������
};
#endif
//�б�ģ����
//ͷβ�ڱ����ⲻ�ɼ�������ɼ��ĵ�һ�������һ�����׽ڵ�first node��ĩ�ڵ�last node
//�ڱ���������ʹ�ò��ø��ֱ߽��˻������ר�Ŵ����������
template <class T>class List{
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;	//��ģ��ͷ�ڱ���β�ڱ�
protected:
	void init();	//��ʼ���б�
	int clear();	//������н��
	void copyNodes(ListNodePosi(T) p, int n);	//������λ��p���n��
	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);	//�鲢
	void mergeSort(ListNodePosi(T)& p, int n);	//����p��ʼ��n�����鲢����
	void selectionSort(ListNodePosi(T), int);	//....ѡ������
	void insertSort(ListNodePosi(T), int);		//....��������
public:
	//���캯��
	List(){ init(); }
	List(List<T> const& L);		//���帴�ƹ��죬����List L��
	List(List<T> const& L, Rank r, int n);	//����L���Ե�r�����n��
	List(ListNodePosi(T) p, int n);		//�����б���Pλ�����n��
	~List();
	//ֻ�����ʽӿ�
	Rank size()const{ return _size; }
	bool empty()const{ return _size <= 0; }
	T& operator[](Rank r)const;
	ListNodePosi(T) first()const{ return header->succ; }	//�����׽ڵ㣬����ͷ���
	ListNodePosi(T) last()const{ return trailer->pred; }	//����ĩ�ڵ㣬����β�ڵ�
	bool valid(ListNodePosi(T) p){
		return p && (p != trailer) && (p != header);	//�ж�λ��p�Ƿ����Ϸ�
	}
	int disordered()const;		//�ж��Ƿ��Ѿ�����
	ListNodePosi(T) find(T const&e, int n, ListNode<T>* p)const{	//�����������
		//��p��n��ǰ�����ҵ�����e�������
		while (0<n--)		//���ҵ���
			if (e == (p = p->pred)->data) return p;
		return NULL;
	}
	ListNodePosi(T) find(T const&e)const{		//�����б����
		return find(e, _size, trailer);
	}
	ListNodePosi(T) search(T const&e, int n, ListNodePosi(T)p)const;	//�����������
	ListNodePosi(T) search(T const&e)const{		//�����б����
		return search(e, _size, trailer);
	}
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);		//����p����n-1��������������
	ListNodePosi(T) selectMax(){ return selectMax(header->succ, _size); }	//��������
	//��д���ʵĽӿ�
	ListNode<T>* insertAsFrist(T const&e);	//��e��Ϊ�׽ڵ����
	ListNodePosi(T) insertAsLast(T const&e);	//��e��Ϊĩ�ڵ����
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);	//��e��Ϊp�ĺ�̲���
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);	//��e��Ϊp��ǰ������
	
	T remove(ListNodePosi(T) p);	//ɾ���Ϸ�λ��p����㣬����ɾ���Ľ��

	void merge(List<T>& L){			//ȫ�б�鲢�� �о��е����⣿��������������������������
		merge(first(), size, L, L.first(), L.size());
	}
	void sort(ListNodePosi(T) p, int n);	//�б���������
	void sort(){ sort(first(), _size); }	//�б���������
	int deduplicate();		//����ȥ��
	int uniquify();		//����ȥ��
	void reverse();		//ǰ����
	//����
	void traverse(void(*)(T&));	//����������visit����������ָ�룩
	template<class VST> void traverse(VST&); //����������visit��������������
};

template<class T>void List<T>::init(){
	header = new ListNode<T>; trailer = new ListNode<T>;	//����ͷβ�ڱ����
	header->succ = trailer;		header->pred = NULL;
	trailer->pred = header;		trailer->succ = NULL;
	_size = 0;
}
template<class T> T& List<T>::operator[](Rank r)const{
	ListNodePosi(T) p = first();		//���׽ڵ㿪ʼ
	while (0 < r--)		//����--
		p = p->succ;	
	return p->data;
}

template<class T>	
ListNode<T>* List<T>::insertAsFirst(T const&e){

}
	

