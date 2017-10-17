#include<iostream>
using namespace std;
#define stature(p) ((p)?(p)->height:-1)//结点高度（与空树h=-1对应）
typedef enum{RB_RED,RB_BLACK}RBColor;//结点颜色（红黑树）
//注： ifndef 后边不是1，而是自己设置的
#ifndef BINNODE
#define BINNODE
template<class T>class BinNode{
public:
	T data;
	BinNode<T>* parent; BinNode<T>* lc;	BinNode<T>* rc;	//父节点。左右孩子结点的指针
	int height;	//与课本不同
	int npl;	//左式堆
	RBColor color;	//颜色，红黑树
	BinNode() :parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNode<T>* p = NULL, BinNode<T>* lc = NULL, BinNode<T>* rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED) {
		data = e;	parent = p;	this->lc = lc; this->rc = rc; height = h; npl = l; this->color = c;
	}
	//操作接口
	int size();	//当前节点后代总数
	BinNode<T>* insertAsLc(T &);	//作为当前节点左孩子插入新节点
	BinNode<T>* insertAsRc(T &);
	BinNode<T>* succ();	//取当前节点的直接后继
	template<class VST>void travLevel(VST&);//子树层次遍历
	template<class VST>void travPre(VST&);//子树先序遍历
	template<class VST>void travIn(VST&);//子树中序遍历
	template<class VST>void travPost(VST&);//子树后序遍历
										   //比较器，判等器
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

