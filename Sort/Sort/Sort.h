#include<iostream>
using namespace std;
#ifndef SORT
#define SORT

template<class T>class Sort {
public:
	void Print(T* Array, int n);
	void InsertSort(T *Array, int n) {
		//Array[]是待排数组,n是长度
		T TempRecord;	//临时变量
		for (int i = 1; i < n; i++) {
			TempRecord = Array[i];
			//从i开始往前寻找记录i的真确位置
			int j = i - 1;
			//将大于等于记录i的记录后移
			while ((j >= 0) && (TempRecord < Array[j])) {
				Array[j + 1] = Array[j];
				j = j - 1;
			}
			//此时j后面就是记录i的正确位置,
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
	//共进行n-1次插入
	for (int i = 1; i < n; i++) {
		int left = 0, right = i - 1;
		T temp = R[i];
		while (left <= right) {
			int middle = (left + right) / 2;//取中点
			if (temp < R[middle])
				right = middle - 1;	//取左区间
			else
				left = middle + 1;	//取右区间
		}
		for (int j = i - 1; j >= left; j--)
			R[j + 1] = R[j];	//元素后移
		R[left] = temp;
	}
}
template<class T>void Sort<T>::BubbleSort(T *Array, int n) {
	bool NoSwap;	//标志
	int i, j;
	for (i = 0; i < n - 1; i++) {
		NoSwap = true;	//设为true
		for (j = n - 1; j > i; j--) {
			if (Array[j] < Array[j - 1]) {
				T temp = Array[j];
				Array[j] = Array[j - 1];
				Array[j - 1] = temp;
				NoSwap = false;	//发生交换
			}
		}
		if (NoSwap)
			return;	//一趟下来没有交换,则不需要继续了
	}
}

//备份对轴(首记录) – 取两个指针low和high，初始值就是序列的第二个元 \
//素及最后一个元素的下标，low <= high – 移动两个指针 ?从high所指的位置向左搜索，
//找到第一个小于轴 的元素 ?从low开始向右，找到第一个大于轴的元素 – 重复上述过程，
//直到low>high， – 把轴放在high所指的位置
//
//从前寻找大于轴记录的记录，从后寻找小于轴记录的记录 ；
//i j
//交换大值记录与小值记录 ； 重复上述两步操作，直至 i  ＞ j ；
//ji j i
//交换轴记录和标识 j 指示的记录
template<class T>int Sort<T>::Partition1(T *Array, int first, int last) {
	int low = first + 1, high = last;
	T pivot = Array[first];	//轴
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

//备份轴记录 ? 取两个指针low和high，初始值就是序列的两端 下标，
//保证low <= high ? 移动两个指针 – 从high向左找到第一个小于轴的元素, 
//放在low 的位置 – 从low向右找到第一个大于轴的元素，放在high 的位置 ?
//重复，直到low = high， ? 把轴放在low所指的位置
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
void Sort<T>::QuickSort(T * Array, int low, int high)	//low和high是索引
{
	int PivotLocation;	//轴
	if (low < high) {
		PivotLocation = Partition2(Array, low, high);
		QuickSort(Array, low, PivotLocation - 1);
		QuickSort(Array, PivotLocation + 1, high);
	}
}
template<class T>void Sort<T>::SelectSort(T* Array, int n) {	//n是个数
	//依次选出第i小的记录,既是剩余记录中最小的那个
	for (int i = 0; i < n - 1; i++) {
		//假设记录i最小
		int Smallest = i;
		for (int j = i + 1; j < n; j++) {
			//如果发现更小的,记录位置
			if (Array[j] < Array[Smallest])
				Smallest = j;
		}
		//将第i小的放在数组第i个位置
		swap(Array[i], Array[Smallest]);
	}
}
template<class T>void Sort<T>::MergeSort(T* Data, int start, int end) {	//start和end都是索引
	if (start < end) {
		int mid = (start + end) / 2;
		//递归调用,对左右子序列分别归并排序
		MergeSort(Data, start, mid);
		MergeSort(Data, mid + 1, end);
		//归并左右两边
		Merge(Data, start, mid, end);
	}
}
template<class T>void Sort<T>::Merge(T* Data, int start, int mid, int end) {
	int len1 = mid - start + 1;
	int len2 = end - (mid + 1) + 1;	//两个归并区间的长度[start,mid];[mid+1,end]
	int i, j, k;
	T* left = new T[len1];
	T* right = new T[len2];	//临时数组
	for (i = 0; i < len1; i++)
		left[i] = Data[i + start];
	for (i = 0; i < len2; i++)
		right[i] = Data[i + mid + 1];
	i = 0;
	j = 0;
	//执行归并
	for (k = start; k < end; k++) {
		if (i == len1 || j == len2)
			break;
		if (left[i] <= right[j])
			Data[k] = left[i++];	//后置++
		else
			Data[k] = right[j++];	//后置++
	}
	while (i < len1)	//若Data[start,mid]还有数据,放到Data后面
		Data[k++] = left[i++];	//后置++
	while (j < len2)	//Data[mid+1,end]还有待归并数据,放在Data后面
		Data[k++] = right[j++];	//后置++
	delete[] left;
	delete[] right;
}