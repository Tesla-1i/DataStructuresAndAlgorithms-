#include<iostream>
using namespace std;

template<class T>class ArrayList{
private:
	T* _elem; int _size; int _capacity;	//ʵ�ʹ�ģ��������
public:
	void expand(); //����
	ArrayList(T* e,int s = 10, int c = 10){
		_elem = new T[_capacity = c]; 
		_size = s;
		for (int i = 0; i < _size; i++)  _elem[i] =e[i];
	}
	~ArrayList(){ delete[] _elem; }
	//ֻ���ӿ�
	int size()const{ return _size; }		//����ʵ�ʹ�ģ
	bool empty()const{ return !_size; }	//�Ƿ�Ϊ��
	int min()const;	//������СԪ�أ������ȣ�
	void print()const{ for (int i = 0; i < _size; i++) cout << _elem[i] << "  "; cout << "\n"; }	//��ӡ����
	T getValue(int r){ return _elem[r]; }	//��r��ֵ
	//��д�ӿ�
	T& operator[](int r)const;	//����С�꣬Ѱ�ȷ���
	int insert(int r, T const&e);	//����r����Ԫ��e,���ز���λ�õ��ȡ�r�ڡ�0��_size]
	int insert(T const&e){return insert(_size, e); }	//ĩβ����,�൱��׷��append����
	T remove(int r);	//ɾ����=r��Ԫ�أ�����ɾ����Ԫ��
	int remove(int lo, int hi);	//ɾ����lo��hi��Ԫ�أ�����ɾ������
	/////////////////////////////////////////////////////////
	void deleteAllX( T x);
	void deleteStoT( T s, T t);
	
};
template<class T>void ArrayList<T>::expand(){
	if (_size < _capacity) return;	//����Ҫ����
	T* oldElem = _elem; _elem = new T[_capacity <<= 1];		//�����ģΪ2��,λ����
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}
template<class T>T& ArrayList<T>::operator[](int r)const{
	return _elem[r];	//���������е������е�ĳ��Ԫ��
}
template<class T>int ArrayList<T>::insert(int r, T const&e){
	expand();	//����������capacity
	if (r<0 || r>_size){
		cout << "����λ�ô���\n";	return -1; //����-1����Ϊ���
	}
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;		//��Ҫ���ǣ�������������������
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
template<class T>int ArrayList<T>::remove(int lo, int hi){	//ɾ����lo��hi��
	if (lo == hi) return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];	//�ȸ��ƣ����Լ�
	_size = lo;		//lo������ǰ��lo��		��ܹؼ�����������������������������������������
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
			//remove(i, i + 1);	//ɾ��arraylist[i]�ע��remove����˵��
			////listsize = arraylist->size();	//����listsize
			//listsize--;		//�����Ϳ���
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
			//remove(i, i + 1);	//ɾ��arraylist��i����һ��Ԫ��
			//listsize--;		//���¹�ģ
			_size--;
			i--;
		}
	}
}


int main(){
	cout << "˳���ǰ��ģ����������� ";
	int s, c; cin >> s >> c;
	cout << "����" << s << "��Ԫ��";
	float* e = new float[s];
	for (int i = 0; i < s; i++)
		cin >> e[i];
	ArrayList<float> *arrayList = new ArrayList<float>(e, s, c);
	cout << "˳����ǣ� \n";
	arrayList->print();
	deleteMin(arrayList);
	cout << "ɾ����Сֵ��βԪ�ز��ȥ\n";
	arrayList->print();
	cout << "����ɾ��Ԫ�ص�ֵ ";
	float v; cin >> v;
	arrayList->deleteAllX(v);
	arrayList->print();
	cout << "����ɾ��Ԫ�صı߽�ֵs,t ";
	float ss, tt; cin >> ss >> tt;
	arrayList->deleteStoT(ss, tt);
	arrayList->print();
	//cout << (arrayList->size()) << "\n";
	/*cout << "ɾ������ \n";
	int zhi; cin >> zhi;
	arrayList->remove(zhi);
	arrayList->print();*/
	/*cout << "����ɾ��Ԫ�ص�ֵ ";
	float v; cin >> v;
	arrayList->remove(v, 'f');
	arrayList->print();*/
	/*cout << "����ɾ��Ԫ�صı߽�ֵ ";
	float ss, tt; cin >> ss >> tt;
	arrayList->remove(ss, tt, 'f');
	arrayList->print();*/
}