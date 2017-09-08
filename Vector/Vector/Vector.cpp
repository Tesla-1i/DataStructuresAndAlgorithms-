#include<iostream>
#include<ctime>
using namespace std;
typedef int Rank;	//秩
#define DEFALT_CAPACITY 3	//默认的初始容量

template <class T>class Vector{
protected:
	Rank _size; int _capacity; T* _elem;	//规模，容量，数据区
	void copyFrom(T const*A, Rank lo, Rank hi);		//复制数组区间【lo，hi）
	void expand();		//扩展数组容量
	void shrink();		//填装因子过小时缩小容量
	bool bubble(Rank lo, Rank hi);	//扫描交换
	void bubbleSort(Rank lo, Rank hi);		//气泡排序
	//Rank max(Rank lo, Rank hi);		//选取最大元素
	Rank selectionSort(Rank lo, Rank hi);		//选择排序
	void merge(Rank lo, Rank mi, Rank hi);		//归并算法
	void mergSort(Rank lo, Rank hi);		//归并排序
	//Rank partition(Rank lo, Rank hi);		//轴点构造
	//void quickSort(Rank lo, Rank hi);		//快速排序
	//void heapSort(Rank lo, Rank hi);		//堆排序
public:
	//构造函数
	Vector(int c = DEFALT_CAPACITY, int s = 0, T v = 0){
		//容量为c，规模为s，所有元素初始化为v
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);		//s<=c; 代码简练
	}
	Vector(T const*A, Rank lo, Rank hi){
		copyFrom(A, lo, hi);		//数组区间复制
	}
	Vector(T const* A, Rank n){
		copyFrom(A, 0, n);		//数组整体复制
	}
	Vector(Vector<T> const&V, Rank lo, Rank hi){
		copyFrom(V._elem, lo, hi);		//向量区间复制
	}
	Vector(Vector<T> const&V){
		copyFrom(V._elem, 0, V._size);		//向量整体复制
	}
	//析构函数
	~Vector(){
		delete[] _elem;
	}
	//只读接口
	void print()const;
	Rank size()const{ return _size; }		//规模
	bool empty()const{ return !_size; }		//判空
	int disordered()const;		//判断是否已排序
	Rank find(T const&e)const{ return find(e, 0, (Rank)_size); }	//无序向量整体查找
	Rank find(T const&e, Rank lo, Rank hi)const;	//无序向量区间查找
	Rank binSearch(T*A, T const& e, Rank lo, Rank hi)const;
	Rank search(T const&e)const{ return (0 >= _size) ? -1 : search(e, (Rank)0, (Rank)_size); }	//有序向量整体查找
	Rank search(T const&e, Rank lo, Rank hi)const;		//有序向量区间查找
	//可访问的接口
	T& operator[](Rank r)const;		//重载下标运算符
	Vector<T>& operator=(Vector<T>const&);	//重载赋值运算符，便于克隆
	T remove(Rank r);		//删除秩为r的元素
	int remove(Rank lo, Rank hi);		//删除秩在【lo，hi）间的元素
										//返回？
	Rank insert(Rank r, T const& e);		//插入元素
	Rank insert(T const& e){ return insert(_size, e); }		//默认插在最后
															//?
	void sort(Rank lo, Rank hi);		//对【lo，hi）排序
	void sort(){ sort(0, _size); }		//整体排序
	void unsort(Rank lo, Rank hi);		//【lo，hi）置乱
	void unsort(){ unsort(0, _size); }	//整体置乱
	int deduplicate();		//无序去重
	int uniquify();		//有序去重
	//遍历
	void traverse(void(*)(T&));		//遍历（使用函数指针,只读或局部修改）
	template<class VST> void traverse(VST&);		//遍历（使用函数对象？ 可全局修改）
	
};

template <class T>
void Vector<T>::copyFrom(T const*A, Rank lo, Rank hi){
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];		//代码简练
}

template<class T>Vector<T>& Vector<T>::operator=(Vector<T> const&V){
	if (_elem)
		delete[] _elem;
	copyFrom(V._elem, 0, V.size());
	return *this;		//返回当前对象的引用，便于链式赋值
}

template<class T> void Vector<T>::expand(){
	if (_size < _capacity) return;		//不需要扩容
	if (_capacity < DEFALT_CAPACITY)	_capacity = DEFALT_CAPACITY;	//不低于最小容量
	T *oldElem = _elem;
	_elem = new T[_capacity <<= 1];		//容量加倍，位操作
	for (int i = 0; i < _size; i++){
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

template<class T> void Vector<T>::shrink(){
	if (_capacity < DEFALT_CAPACITY << 1) return;
	if (_size << 2 >_capacity)return;	//以25%为界
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];		//容量减半
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}
template<class T>T& Vector<T>::operator[](Rank r)const{
	return _elem[r];
}
template<class T>void Vector<T>::unsort(Rank lo, Rank hi){
	T* e = _elem + lo;		//将子向量elem[lo,hi)视作另一向量e[0,hi-lo)
	for (Rank i = hi - lo; i>0; i--){
		swap(e[i - 1], e[rand() % i]);	//将e[i-1]和e[0,i)中某一元素随机交换，swap()是stl中的
						//随机生成
	}
}

template<class T> Rank Vector<T>::find(T const&e, Rank lo, Rank hi)const{
	while ((lo < hi--) && (e != _elem[hi]));	//自后往前查找,查找成功时返回最后一个e
	return hi;	//hi是成功时命中的秩，失败时也返回hi
}
template<class T> Rank Vector<T>::insert(Rank r, T const& e){
	//将e插入r位置
	expand();		//如有必要扩容
	for (int i = _size; i>r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;		//_size++
	return r;	//返回插入位置
}

//删除区间【lo，hi】
template<class T>int Vector<T>::remove(Rank lo, Rank hi){
	if (lo == hi)	return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];		//前移hi-lo，注意理解后置++
	_size = lo;		//更新—size
	shrink();		//如有必要，缩小容量
	return hi - lo;		//返回删除个数
}

//删除单个元素调用区间删除算法
template<class T>T Vector<T>::remove(Rank r){
	T e = _elem[r];		//备份
	remove(r, r + 1);
	return e;		//返回删除的元素
}

//删除无序向量中的重复元素
template<class T> int Vector<T>::deduplicate(){
	int oldSize = _size;		//记录原先规模
	Rank i = 1;		//从1开始
	while (i < _size){
		//在他前缀中寻找，若无相同则i++，否则删除重复元素
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);	//i为重复元素的秩
	}
	return oldSize - _size;		//返回删除元素的总数
}

//遍历 ？？??????????????????????????????????????????????????????????????????????????
template<class T> void Vector<T>::traverse(void(*visit)(T&)){	//利用函数指针实现的遍历,注意visit仅仅是一个名
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

template<class T> 
template<class VST>	//元素类型，操作器
void Vector<T>::traverse(VST&visit){		//利用函数对象机制的遍历。注意visit仅仅是一个名
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}
//测试遍历
template<class T> struct Increase{		//函数对象，递增一个T类对象
	virtual void operator()(T& e){		//重载括号，用于Increase(_elem[i]);
		e++;		//假设T可直接递增，或重载了++
	}
};
template<class T>void increase(Vector<T> &V){
	V.traverse(Increase<T>());
}
//????????????????????????????????????????????????????????????????????????????????


//有序向量甄别
template<class T> int Vector<T>::disordered()const{
	int n = 0;
	for (int i = 1; i < _size; i++){
		if (_elem[i - 1]>_elem[i]) n++;
	}
	return n;	//返回逆序相邻元素对的总数
}

//有序向量删除重复元素
template<class T> int Vector<T>::uniquify(){
	Rank i = 0, j = 0;
	while (++j < _size){	//先++
		if (_elem[i] != _elem[j])	//跳过重复，将不重复元素前移覆盖重复的
			_elem[++i] = _elem[j];	//先++
	}
	_size = ++i;
	shrink();
	return j - i;	//返回删除元素总数
}

//在【lo，hi）查找e
template<class T> Rank Vector<T>::binSearch(T*A, T const& e, Rank lo, Rank hi)const{
	while (lo < hi){
		Rank mi = (lo + hi) >> 1;		//以中轴为中点
		(e < A[mi]) ? hi = mi : lo = mi + 1;	//分界
	}	//不能提前终止
	return --lo;
	//循环结束，lo是大于e的最小秩，lo-1是不大于e的最大秩
	//有多个元素命中，返回秩最大的，查找失败，返回失败位置
	//????????????????????????????????????????????
}

template<class T> Rank Vector<T>::search(T const&e, Rank lo, Rank hi)const{
	Rank retu= binSearch(_elem, e, lo, hi);
	return retu;
}

template<class T>void Vector<T>::sort(Rank lo, Rank hi){
	switch (rand() % 2){
	case 0: bubbleSort(lo, hi); 
		cout << "冒泡排序";	break;
	case 1: mergSort(lo, hi);
		cout << "归并排序";	break;
	}

}

template<class T> void Vector<T>::bubbleSort(Rank lo, Rank hi){
	while (!bubble(lo, hi--));	//逐一做扫描交换
}
template<class T>bool Vector<T>::bubble(Rank lo, Rank hi){
	bool sorted = true;		//整体有序标志
	while (++lo < hi){		//前置++，
		if (_elem[lo - 1]>_elem[lo]){
			sorted = false;		//设置为无序
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

template<class T> void Vector<T>::mergSort(Rank lo, Rank hi){
	if (hi - lo < 2) return;		//单元素
	int mi = (lo + hi) >> 1;		//中点
	mergSort(lo, mi); mergSort(mi, hi);	//递归
	merge(lo, mi, hi);		//归并
}

template<class T>void Vector<T>::merge(Rank lo, Rank mi, Rank hi){
	//以mi为界，各自有序的子向量【lo，mi），【mi，hi）
	T* A = _elem + lo;		//合并后的向量A[0,hi-lo)=_elem[lo,hi)
	int lb = mi - lo; T* B = new T[lb];		//前子向量B[0,lb)=_elem[lo,mi)
	for (Rank i = 0; i < lb; B[i] = A[i++]);		//复制前子向量
	int lc = hi - mi; T* C = _elem + mi;		//后子向量C[0,lc)=_elem[mi,hi)
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);){
		//将B[j]和C[k]中小的接到A末尾
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
			A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] < B[j])))
			A[i++] = C[k++];
	}
	delete[] B;
}//归并后得到完整有序向量【lo，hi）

template<class T>void Vector<T>::print()const{
	for (int i = 0; i < _size; i++)
		cout << _elem[i] << "\t";
}

int main(){
	int *array = new int[10];
	for (int i = 0; i < 10; i++)
		array[i] = 10 - i;
	Vector<int> vectorByArray(array, 1, 8);
	vectorByArray.print();
	int size = vectorByArray.size();
	cout << "规模是： " << size<<"\n";
	int order = vectorByArray.disordered();
	cout << "是否已排序： " << order<<"\n";
	int search = vectorByArray.search(11);
	cout << "是否有11： " << search<<"\n";
	Vector<int> vectorByCopy = vectorByArray;
	cout << "拷贝得到的： ";
	vectorByCopy.print();
	vectorByArray.remove(2, 4);
	cout << "\n删除【2,4）元素后";
	vectorByArray.print();
	vectorByArray.insert(0, 1);
	cout << "首位插入1 ";
	vectorByArray.print();
	vectorByArray.unsort();
	cout << "\n整体置乱:";
	vectorByArray.print();
	cout << "\n无序去重： ";
	vectorByArray.print();
	cout << "\n整体排序:";
	vectorByArray.sort();
	vectorByArray.print();
	increase(vectorByArray);
	cout << "\n测试遍历加一： ";
	vectorByArray.print();
	return 0;
}