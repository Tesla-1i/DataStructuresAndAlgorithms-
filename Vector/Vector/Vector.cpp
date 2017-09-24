#include<iostream>
#include<ctime>
using namespace std;
typedef int Rank;	//��
#define DEFALT_CAPACITY 3	//Ĭ�ϵĳ�ʼ����

template <class T>class Vector{
protected:
	Rank _size; int _capacity; T* _elem;	//��ģ��������������
	void copyFrom(T const*A, Rank lo, Rank hi);		//�����������䡾lo��hi��
	void expand();		//��չ��������
	void shrink();		//��װ���ӹ�Сʱ��С����
	bool bubble(Rank lo, Rank hi);	//ɨ�轻��
	void bubbleSort(Rank lo, Rank hi);		//��������
	//Rank max(Rank lo, Rank hi);		//ѡȡ���Ԫ��
	Rank selectionSort(Rank lo, Rank hi);		//ѡ������
	void merge(Rank lo, Rank mi, Rank hi);		//�鲢�㷨
	void mergSort(Rank lo, Rank hi);		//�鲢����
	//Rank partition(Rank lo, Rank hi);		//��㹹��
	//void quickSort(Rank lo, Rank hi);		//��������
	//void heapSort(Rank lo, Rank hi);		//������
public:
	//���캯��
	Vector(int c = DEFALT_CAPACITY, int s = 0, T v = 0){
		//����Ϊc����ģΪs������Ԫ�س�ʼ��Ϊv
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);		//s<=c; �������
	}
	Vector(T const*A, Rank lo, Rank hi){
		copyFrom(A, lo, hi);		//�������临��
	}
	Vector(T const* A, Rank n){
		copyFrom(A, 0, n);		//�������帴��
	}
	Vector(Vector<T> const&V, Rank lo, Rank hi){
		copyFrom(V._elem, lo, hi);		//�������临��
	}
	Vector(Vector<T> const&V){
		copyFrom(V._elem, 0, V._size);		//�������帴��
	}
	//��������
	~Vector(){
		delete[] _elem;
	}
	//ֻ���ӿ�
	void print()const;
	Rank size()const{ return _size; }		//��ģ
	bool empty()const{ return !_size; }		//�п�
	int disordered()const;		//�ж��Ƿ�������
	Rank find(T const&e)const{ return find(e, 0, (Rank)_size); }	//���������������
	Rank find(T const&e, Rank lo, Rank hi)const;	//���������������
	Rank binSearch(T*A, T const& e, Rank lo, Rank hi)const;
	Rank search(T const&e)const{ return (0 >= _size) ? -1 : search(e, (Rank)0, (Rank)_size); }	//���������������
	Rank search(T const&e, Rank lo, Rank hi)const;		//���������������
	//�ɷ��ʵĽӿ�
	T& operator[](Rank r)const;		//�����±������
	Vector<T>& operator=(Vector<T>const&);	//���ظ�ֵ����������ڿ�¡
	T remove(Rank r);		//ɾ����Ϊr��Ԫ��
	int remove(Rank lo, Rank hi);		//ɾ�����ڡ�lo��hi�����Ԫ��
										//���أ�
	Rank insert(Rank r, T const& e);		//����Ԫ��
	Rank insert(T const& e){ return insert(_size, e); }		//Ĭ�ϲ������
															//?
	void sort(Rank lo, Rank hi);		//�ԡ�lo��hi������
	void sort(){ sort(0, _size); }		//��������
	void unsort(Rank lo, Rank hi);		//��lo��hi������
	void unsort(){ unsort(0, _size); }	//��������
	int deduplicate();		//����ȥ��
	int uniquify();		//����ȥ��
	//����
	void traverse(void(*)(T&));		//������ʹ�ú���ָ��,ֻ����ֲ��޸ģ�
	template<class VST> void traverse(VST&);		//������ʹ�ú������� ��ȫ���޸ģ�
	
};

template <class T>
void Vector<T>::copyFrom(T const*A, Rank lo, Rank hi){
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];		//�������
}

template<class T>Vector<T>& Vector<T>::operator=(Vector<T> const&V){
	if (_elem)
		delete[] _elem;
	copyFrom(V._elem, 0, V.size());
	return *this;		//���ص�ǰ��������ã�������ʽ��ֵ
}

template<class T> void Vector<T>::expand(){
	if (_size < _capacity) return;		//����Ҫ����
	if (_capacity < DEFALT_CAPACITY)	_capacity = DEFALT_CAPACITY;	//��������С����
	T *oldElem = _elem;
	_elem = new T[_capacity <<= 1];		//�����ӱ���λ����
	for (int i = 0; i < _size; i++){
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

template<class T> void Vector<T>::shrink(){
	if (_capacity < DEFALT_CAPACITY << 1) return;
	if (_size << 2 >_capacity)return;	//��25%Ϊ��
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];		//��������
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}
template<class T>T& Vector<T>::operator[](Rank r)const{
	return _elem[r];
}
template<class T>void Vector<T>::unsort(Rank lo, Rank hi){
	T* e = _elem + lo;		//��������elem[lo,hi)������һ����e[0,hi-lo)
	for (Rank i = hi - lo; i>0; i--){
		swap(e[i - 1], e[rand() % i]);	//��e[i-1]��e[0,i)��ĳһԪ�����������swap()��stl�е�
						//�������
	}
}

template<class T> Rank Vector<T>::find(T const&e, Rank lo, Rank hi)const{
	while ((lo < hi--) && (e != _elem[hi]));	//�Ժ���ǰ����,���ҳɹ�ʱ�������һ��e
	return hi;	//hi�ǳɹ�ʱ���е��ȣ�ʧ��ʱҲ����hi
}
template<class T> Rank Vector<T>::insert(Rank r, T const& e){
	//��e����rλ��
	expand();		//���б�Ҫ����
	for (int i = _size; i>r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;		//_size++
	return r;	//���ز���λ��
}

//ɾ�����䡾lo��hi��
template<class T>int Vector<T>::remove(Rank lo, Rank hi){
	if (lo == hi)	return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];		//ǰ��hi-lo��ע��������++
	_size = lo;		//����?size
	shrink();		//���б�Ҫ����С����
	return hi - lo;		//����ɾ������
}

//ɾ������Ԫ�ص�������ɾ���㷨
template<class T>T Vector<T>::remove(Rank r){
	T e = _elem[r];		//����
	remove(r, r + 1);
	return e;		//����ɾ����Ԫ��
}

//ɾ�����������е��ظ�Ԫ��
template<class T> int Vector<T>::deduplicate(){
	int oldSize = _size;		//��¼ԭ�ȹ�ģ
	Rank i = 1;		//��1��ʼ
	while (i < _size){
		//����ǰ׺��Ѱ�ң�������ͬ��i++������ɾ���ظ�Ԫ��
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);	//iΪ�ظ�Ԫ�ص���
	}
	return oldSize - _size;		//����ɾ��Ԫ�ص�����
}

//���� ����??????????????????????????????????????????????????????????????????????????
template<class T> void Vector<T>::traverse(void(*visit)(T&)){	//���ú���ָ��ʵ�ֵı���,ע��visit������һ����
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

template<class T> 
template<class VST>	//Ԫ�����ͣ�������
void Vector<T>::traverse(VST&visit){		//���ú���������Ƶı�����ע��visit������һ����
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}
//���Ա���
template<class T> struct Increase{		//�������󣬵���һ��T�����
	virtual void operator()(T& e){		//�������ţ�����Increase(_elem[i]);
		e++;		//����T��ֱ�ӵ�������������++
	}
};
template<class T>void increase(Vector<T> &V){
	V.traverse(Increase<T>());
}
//????????????????????????????????????????????????????????????????????????????????


//�����������
template<class T> int Vector<T>::disordered()const{
	int n = 0;
	for (int i = 1; i < _size; i++){
		if (_elem[i - 1]>_elem[i]) n++;
	}
	return n;	//������������Ԫ�ضԵ�����
}

//��������ɾ���ظ�Ԫ��
template<class T> int Vector<T>::uniquify(){
	Rank i = 0, j = 0;
	while (++j < _size){	//��++
		if (_elem[i] != _elem[j])	//�����ظ��������ظ�Ԫ��ǰ�Ƹ����ظ���
			_elem[++i] = _elem[j];	//��++
	}
	_size = ++i;
	shrink();
	return j - i;	//����ɾ��Ԫ������
}

//�ڡ�lo��hi������e
template<class T> Rank Vector<T>::binSearch(T*A, T const& e, Rank lo, Rank hi)const{
	while (lo < hi){
		Rank mi = (lo + hi) >> 1;		//������Ϊ�е�
		(e < A[mi]) ? hi = mi : lo = mi + 1;	//�ֽ�
	}	//������ǰ��ֹ
	return --lo;
	//ѭ��������lo�Ǵ���e����С�ȣ�lo-1�ǲ�����e�������
	//�ж��Ԫ�����У����������ģ�����ʧ�ܣ�����ʧ��λ��
	//????????????????????????????????????????????
}

template<class T> Rank Vector<T>::search(T const&e, Rank lo, Rank hi)const{
	Rank retu= binSearch(_elem, e, lo, hi);
	return retu;
}

template<class T>void Vector<T>::sort(Rank lo, Rank hi){
	switch (rand() % 2){
	case 0: bubbleSort(lo, hi); 
		cout << "ð������";	break;
	case 1: mergSort(lo, hi);
		cout << "�鲢����";	break;
	}

}

template<class T> void Vector<T>::bubbleSort(Rank lo, Rank hi){
	while (!bubble(lo, hi--));	//��һ��ɨ�轻��
}
template<class T>bool Vector<T>::bubble(Rank lo, Rank hi){
	bool sorted = true;		//���������־
	while (++lo < hi){		//ǰ��++��
		if (_elem[lo - 1]>_elem[lo]){
			sorted = false;		//����Ϊ����
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

template<class T> void Vector<T>::mergSort(Rank lo, Rank hi){
	if (hi - lo < 2) return;		//��Ԫ��
	int mi = (lo + hi) >> 1;		//�е�
	mergSort(lo, mi); mergSort(mi, hi);	//�ݹ�
	merge(lo, mi, hi);		//�鲢
}

template<class T>void Vector<T>::merge(Rank lo, Rank mi, Rank hi){
	//��miΪ�磬�����������������lo��mi������mi��hi��
	T* A = _elem + lo;		//�ϲ��������A[0,hi-lo)=_elem[lo,hi)
	int lb = mi - lo; T* B = new T[lb];		//ǰ������B[0,lb)=_elem[lo,mi)
	for (Rank i = 0; i < lb; B[i] = A[i++]);		//����ǰ������
	int lc = hi - mi; T* C = _elem + mi;		//��������C[0,lc)=_elem[mi,hi)
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);){
		//��B[j]��C[k]��С�Ľӵ�Aĩβ
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
			A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] < B[j])))
			A[i++] = C[k++];
	}
	delete[] B;
}//�鲢��õ���������������lo��hi��

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
	cout << "��ģ�ǣ� " << size<<"\n";
	int order = vectorByArray.disordered();
	cout << "�Ƿ������� " << order<<"\n";
	int search = vectorByArray.search(11);
	cout << "�Ƿ���11�� " << search<<"\n";
	Vector<int> vectorByCopy = vectorByArray;
	cout << "�����õ��ģ� ";
	vectorByCopy.print();
	vectorByArray.remove(2, 4);
	cout << "\nɾ����2,4��Ԫ�غ�";
	vectorByArray.print();
	vectorByArray.insert(0, 1);
	cout << "��λ����1 ";
	vectorByArray.print();
	vectorByArray.unsort();
	cout << "\n��������:";
	vectorByArray.print();
	cout << "\n����ȥ�أ� ";
	vectorByArray.print();
	cout << "\n��������:";
	vectorByArray.sort();
	vectorByArray.print();
	increase(vectorByArray);
	cout << "\n���Ա�����һ�� ";
	vectorByArray.print();
	return 0;
}