#include<iostream>
using namespace std;
#ifndef SORT
#define SORT

template<class T>class Sort {
public:
	void Print(T* Array, int n);
	void InsertSort(T *Array, int n) {
		//Array[]�Ǵ�������,n�ǳ���
		T TempRecord;	//��ʱ����
		for (int i = 1; i < n; i++) {
			TempRecord = Array[i];
			//��i��ʼ��ǰѰ�Ҽ�¼i����ȷλ��
			int j = i - 1;
			//�����ڵ��ڼ�¼i�ļ�¼����
			while ((j >= 0) && (TempRecord < Array[j])) {
				Array[j + 1] = Array[j];
				j = j - 1;
			}
			//��ʱj������Ǽ�¼i����ȷλ��,
			Array[j + 1] = TempRecord;
		}
	}
	void BinaryInsertSort(T *R, int n);
	void BubbleSort(T *Array, int n);
	int Partition1(T *Array, int first, int last);
	int Partition2(T *Array, int low, int high);
	void QuickSort(T *Array, int low, int high);
	void SelectSort(T* Array, int n);
	void MergeSort(T* Data, int start, int end);
	void Merge(T* Data, int start, int mid, int end);
};

#endif // !SORT
template<class T>void Sort<T>::Print(T* Array, int n) {
	for (int i = 0; i < n; i++) {
		cout << Array[i] << "\t";
	}
	cout << "\n";
}
template<class T>void Sort<T>::BinaryInsertSort(T *R, int n) {
	//������n-1�β���
	for (int i = 1; i < n; i++) {
		int left = 0, right = i - 1;
		T temp = R[i];
		while (left <= right) {
			int middle = (left + right) / 2;//ȡ�е�
			if (temp < R[middle])
				right = middle - 1;	//ȡ������
			else
				left = middle + 1;	//ȡ������
		}
		for (int j = i - 1; j >= left; j--)
			R[j + 1] = R[j];	//Ԫ�غ���
		R[left] = temp;
	}
}
template<class T>void Sort<T>::BubbleSort(T *Array, int n) {
	bool NoSwap;	//��־
	int i, j;
	for (i = 0; i < n - 1; i++) {
		NoSwap = true;	//��Ϊtrue
		for (j = n - 1; j > i; j--) {
			if (Array[j] < Array[j - 1]) {
				T temp = Array[j];
				Array[j] = Array[j - 1];
				Array[j - 1] = temp;
				NoSwap = false;	//��������
			}
		}
		if (NoSwap)
			return;	//һ������û�н���,����Ҫ������
	}
}

//���ݶ���(�׼�¼) �C ȡ����ָ��low��high����ʼֵ�������еĵڶ���Ԫ \
//�ؼ����һ��Ԫ�ص��±꣬low <= high �C �ƶ�����ָ�� ?��high��ָ��λ������������
//�ҵ���һ��С���� ��Ԫ�� ?��low��ʼ���ң��ҵ���һ���������Ԫ�� �C �ظ��������̣�
//ֱ��low>high�� �C �������high��ָ��λ��
//
//��ǰѰ�Ҵ������¼�ļ�¼���Ӻ�Ѱ��С�����¼�ļ�¼ ��
//i j
//������ֵ��¼��Сֵ��¼ �� �ظ���������������ֱ�� i  �� j ��
//ji j i
//�������¼�ͱ�ʶ j ָʾ�ļ�¼
template<class T>int Sort<T>::Partition1(T *Array, int first, int last) {
	int low = first + 1, high = last;
	T pivot = Array[first];	//��
	while (low <= high) {
		while (low <= high&&Array[low] < pivot)
			low++;
		while (low <= high&&Array[high] > pivot)
			high--;
		if (low < high)
			swap(Array[high--], Array[low++]);
		else
			low++;
	}
	swap(Array[first], Array[high]);
	return high;
}

//�������¼ ? ȡ����ָ��low��high����ʼֵ�������е����� �±꣬
//��֤low <= high ? �ƶ�����ָ�� �C ��high�����ҵ���һ��С�����Ԫ��, 
//����low ��λ�� �C ��low�����ҵ���һ���������Ԫ�أ�����high ��λ�� ?
//�ظ���ֱ��low = high�� ? �������low��ָ��λ��
template<class T>
int Sort<T>::Partition2(T * Array, int low, int high)
{
	T pivot = Array[low];
	while (low < high) {
		while (low < high&&Array[high] >= pivot)
			high--;
		Array[low] = Array[high];
		while (low < high&&Array[low] <= pivot)
			low++;
		Array[high] = Array[low];
	}
	Array[low] = pivot;
	return low;
}

template<class T>
void Sort<T>::QuickSort(T * Array, int low, int high)	//low��high������
{
	int PivotLocation;	//��
	if (low < high) {
		PivotLocation = Partition2(Array, low, high);
		QuickSort(Array, low, PivotLocation - 1);
		QuickSort(Array, PivotLocation + 1, high);
	}
}
template<class T>void Sort<T>::SelectSort(T* Array, int n) {	//n�Ǹ���
	//����ѡ����iС�ļ�¼,����ʣ���¼����С���Ǹ�
	for (int i = 0; i < n - 1; i++) {
		//�����¼i��С
		int Smallest = i;
		for (int j = i + 1; j < n; j++) {
			//������ָ�С��,��¼λ��
			if (Array[j] < Array[Smallest])
				Smallest = j;
		}
		//����iС�ķ��������i��λ��
		swap(Array[i], Array[Smallest]);
	}
}
template<class T>void Sort<T>::MergeSort(T* Data, int start, int end) {	//start��end��������
	if (start < end) {
		int mid = (start + end) / 2;
		//�ݹ����,�����������зֱ�鲢����
		MergeSort(Data, start, mid);
		MergeSort(Data, mid + 1, end);
		//�鲢��������
		Merge(Data, start, mid, end);
	}
}
template<class T>void Sort<T>::Merge(T* Data, int start, int mid, int end) {
	int len1 = mid - start + 1;
	int len2 = end - (mid + 1) + 1;	//�����鲢����ĳ���[start,mid];[mid+1,end]
	int i, j, k;
	T* left = new T[len1];
	T* right = new T[len2];	//��ʱ����
	for (i = 0; i < len1; i++)
		left[i] = Data[i + start];
	for (i = 0; i < len2; i++)
		right[i] = Data[i + mid + 1];
	i = 0;
	j = 0;
	//ִ�й鲢
	for (k = start; k < end; k++) {
		if (i == len1 || j == len2)
			break;
		if (left[i] <= right[j])
			Data[k] = left[i++];	//����++
		else
			Data[k] = right[j++];	//����++
	}
	while (i < len1)	//��Data[start,mid]��������,�ŵ�Data����
		Data[k++] = left[i++];	//����++
	while (j < len2)	//Data[mid+1,end]���д��鲢����,����Data����
		Data[k++] = right[j++];	//����++
	delete[] left;
	delete[] right;
}