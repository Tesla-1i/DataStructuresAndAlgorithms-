#include<iostream>
using namespace std;

template<class T>class ArrayList{
private:
	T* _elem; int _size; int _capacity;	//实际规模，总容量
public:
	void expand(); //扩容
	ArrayList(T* e,int s = 10, int c = 10){
		_elem = new T[_capacity = c]; 
		_size = s;
		for (int i = 0; i < _size; i++)  _elem[i] =e[i];
	}
	~ArrayList(){ delete[] _elem; }
	//只读接口
	int size()const{ return _size; }		//返回实际规模
	bool empty()const{ return !_size; }	//是否为空
	int min()const;	//查找最小元素，返回秩；
	void print()const{ for (int i = 0; i < _size; i++) cout << _elem[i] << "  "; cout << "\n"; }	//打印数据
	T getValue(int r){ return _elem[r]; }	//秩r的值
	//可写接口
	T& operator[](int r)const;	//重载小标，寻秩访问
	int insert(int r, T const&e);	//在秩r插入元素e,返回插入位置的秩。r在【0，_size]
	int insert(T const&e){return insert(_size, e); }	//末尾插入,相当于追加append（）
	T remove(int r);	//删除秩=r处元素，返回删除的元素
	int remove(int lo, int hi);	//删除【lo，hi）元素，返回删除个数
	/////////////////////////////////////////////////////////
	void deleteAllX( T x);
	void deleteStoT( T s, T t);
	
};
template<class T>void ArrayList<T>::expand(){
	if (_size < _capacity) return;	//不需要扩容
	T* oldElem = _elem; _elem = new T[_capacity <<= 1];		//扩大规模为2倍,位操作
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}
template<class T>T& ArrayList<T>::operator[](int r)const{
	return _elem[r];	//返回向量中的数组中的某个元素
}
template<class T>int ArrayList<T>::insert(int r, T const&e){
	expand();	//检查最大容量capacity
	if (r<0 || r>_size){
		cout << "插入位置错误\n";	return -1; //返回-1，作为检查
	}
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;		//不要忘记！！！！！！！！！！
	return r;
}
template<class T>int ArrayList<T>::min()const{
	int rr = 0; T min = _elem[0];
	for (int i = 1; i < _size; i++){
		if (min>_elem[i]){
			min = _elem[i]; rr = i;
		}
	}
	return rr;
}
template<class T>T ArrayList<T>::remove(int r){
	T e = _elem[r];
	remove(r, r + 1);
	print();
	return e;
}
template<class T>int ArrayList<T>::remove(int lo, int hi){	//删除【lo，hi）
	if (lo == hi) return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];	//先复制，后自加
	_size = lo;		//lo不是先前的lo了		这很关键！！！！！！！！！！！！！！！！！！！！
	return hi - lo;
}


template<class T>T deleteMin(ArrayList<T>* arrayList){
	int rank = arrayList->min();
	T value = arrayList->remove(rank);
	int size = arrayList->size();
	T valueOfLast = arrayList->getValue(size - 1);
	arrayList->insert(rank, valueOfLast);
	arrayList->remove(size);
	return value;
}

template<class T>void ArrayList<T>::deleteAllX(T x){
	//int listsize = _size;
	int i, j;
	for ( i = 0; i < _size; i++){
		if (x == _elem[i]){
			for (j = i; j < _size - 1; j++)
				_elem[j] = _elem[j + 1];
			//remove(i, i + 1);	//删除arraylist[i]项，注意remove参数说明
			////listsize = arraylist->size();	//更新listsize
			//listsize--;		//这样就可以
			_size--;
			i--;
		}
	}
}

template<class T>void ArrayList<T>::deleteStoT(T s, T t){
	if (s >= t){ cout << "s>=t"; return; }
	//int listsize = _size;
	int i,j;
	for ( i = 0; i < _size; i++){
		if ((_elem[i])>s && (_elem[i]) < t){
			for (j = i; j < _size - 1; j++)
				_elem[j] = _elem[j + 1];
			//remove(i, i + 1);	//删除arraylist【i】这一个元素
			//listsize--;		//更新规模
			_size--;
			i--;
		}
	}
}


int main(){
	cout << "顺序表当前规模，最大容量： ";
	int s, c; cin >> s >> c;
	cout << "输入" << s << "个元素";
	float* e = new float[s];
	for (int i = 0; i < s; i++)
		cin >> e[i];
	ArrayList<float> *arrayList = new ArrayList<float>(e, s, c);
	cout << "顺序表是： \n";
	arrayList->print();
	deleteMin(arrayList);
	cout << "删除最小值后，尾元素插过去\n";
	arrayList->print();
	cout << "输入删除元素的值 ";
	float v; cin >> v;
	arrayList->deleteAllX(v);
	arrayList->print();
	cout << "输入删除元素的边界值s,t ";
	float ss, tt; cin >> ss >> tt;
	arrayList->deleteStoT(ss, tt);
	arrayList->print();
	//cout << (arrayList->size()) << "\n";
	/*cout << "删除的秩 \n";
	int zhi; cin >> zhi;
	arrayList->remove(zhi);
	arrayList->print();*/
	/*cout << "输入删除元素的值 ";
	float v; cin >> v;
	arrayList->remove(v, 'f');
	arrayList->print();*/
	/*cout << "输入删除元素的边界值 ";
	float ss, tt; cin >> ss >> tt;
	arrayList->remove(ss, tt, 'f');
	arrayList->print();*/
}