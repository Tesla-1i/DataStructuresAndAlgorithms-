#include<iostream>
using namespace std;
#define stature(p) ((p)?(p)->height:-1)//���߶ȣ������h=-1��Ӧ��
typedef enum{RB_RED,RB_BLACK}RBColor;//�����ɫ���������
//ע�� ifndef ��߲���1�������Լ����õ�
#ifndef BINNODE
#define BINNODE
template<class T>class BinNode{
public:
	T data;
	BinNode<T>* parent; BinNode<T>* lc;	BinNode<T>* rc;	//���ڵ㡣���Һ��ӽ���ָ��
	int height;	//��α���ͬ
	int npl;	//��ʽ��
	RBColor color;	//��ɫ�������
	BinNode() :parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNode<T>* p = NULL, BinNode<T>* lc = NULL, BinNode<T>* rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) {
		data = e;	parent = p;	this->lc = lc; this->rc = rc; height = h; npl = l; this->color = c;
	}
	//�����ӿ�
	int size();	//��ǰ�ڵ�������
	BinNode<T>* insertAsLc(T &);	//��Ϊ��ǰ�ڵ����Ӳ����½ڵ�
	BinNode<T>* insertAsRc(T &);
	BinNode<T>* succ();	//ȡ��ǰ�ڵ��ֱ�Ӻ��
	template<class VST>void travLevel(VST&);//������α���
	template<class VST>void travPre(VST&);//�����������
	template<class VST>void travIn(VST&);//�����������
	template<class VST>void travPost(VST&);//�����������
										   //�Ƚ������е���
	bool operator<(BinNode &bn) { return data < bn.data; }
	bool operator==(BinNode &bn) { return data == bn.data; }
};

template<class T>BinNode<T>* BinNode<T>::insertAsLc(T &e) {
	return lc = new BinNode(e, this);
}
template<class T>BinNode<T>* BinNode<T>::insertAsRc(T &e) {
	return rc = new BinNode(e, this);
}
template<class T>template<class VST>void BinNode<T>::travIn(VST& visit) {
	travIn_I1(this, visit);
}


#endif // !1

