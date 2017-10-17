#include"BinNode.h"
#ifndef BINTREE
#define BINTREE
template<class T>class BinTree {
protected:
	int _size; BinNode<T>* _root;	//��ģ�͸��ڵ�
	virtual int updateHeight(BinNode<T>* x);	//���½ڵ�ĸ߶�
	void updateHeightAbove(BinNode<T>* x);	//���½ڵ�����ȵĸ߶�
public:
	BinTree():_size(0),_root(NULL){ }
	~BinTree() {
		if (0 < _size) remove(_root);
	}
	int size() { return _size; }
	bool empty() { return !_root; }
	BinNode<T>* root() { return _root; }
	BinNode<T>* insertAsRoot(T &e);	//������ڵ�
	BinNode<T>* insertAsLC(BinNode<T>* x, T &e);	//������Ϊx������
	BinNode<T>* insertAsRC(BinNode<T>* x, T &e);
	BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* &T);	//T��Ϊx������������
	BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>* &T);
	int remove(BinTree<T>* x);	//ɾ������������������ģ
	BinTree<T>* secede(BinTree<T>* x);	//ժ����������Ϊ�µ���
	template<class VST>void travLevel(VST& visit) {
		if (_root) {
			_root->travLevel(visit);
		}
	}
	template<class VST>void travPre(VST& visit) {
		if (_root) {
			_root->travPre(visit);
		}
	}
	template<class VST>void travIn(VST& visit) {
		if (_root) {
			_root->travIn(visit);
		}
	}
	template<class VST>void travPost(VST& visit) {
		if (_root) {
			_root->travPost(visit);
		}
	}
	bool operator<(BinTree<T>& t) {
		return _root&&t._root&&lt(_root, t._root);
	}
	bool operator==(BinTree<T>& t) {
		return _root&&t._root && (_root == t._root);
	}
};

#endif 
template<class T>int BinTree<T>::updateHeight(BinNode<T>* x) {
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}
template<class T>void BinTree<T>::updateHeightAbove(BinNode<T>* x) {
	while (x)
	{
		updateHeight(x); x = x->parent;
	}
}
template<class T>BinNode<T>* BinTree<T>::insertAsRoot(T &e) {
	_size = 1; return _root = new BinNode<T>(e);
}
template<class T>BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, T &e) {
	_size++; x->insertAsLc(e); updateHeightAbove(x); return x->lc;
}
template<class T>BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, T &e) {
	_size++; x->insertAsRc(e); updateHeightAbove(x); return x->rc;
}
template<class T>BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>* &S) {
	if (x->lc=S->_root)
	{
		x->lc->parent = x;
	}
	_size += S->_size; updateHeightAbove(x);
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x;
}
template<class T>BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree<T>* &S) {
	if (x->rc = S->_root)
	{
		x->rc->parent = x;
	}
	_size += S->_size; updateHeightAbove(x);
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x;
}


