#include<iostream>
using namespace std;

template<class T>
void bubbleSort(T Data[], int n){
	int flag = 0;	//标志
	for (int i = 0; i < n; i++){
		flag = 0;
		for (int j = 0; j < n - (i + 1); j++){
			if (Data[j]>Data[j + 1]){
				flag = 1;
				T temp = Data[j];
				Data[j] = Data[j + 1];
				Data[j + 1] = temp;
			}
		}
		if (flag == 0)
			return;		//如果某一趟没有发生交换，则不需要再扫描一趟
	}
}

int main(){
	cout << "数组元素个数";
	int n; cin >> n;
	cout << "输入元素：";
	float *Data = new float[n];	//避免float Data[n]不允许，不要在栈中开
	for (int i = 0; i < n; i++)
		cin >> Data[i];
	bubbleSort(Data, n);
	for (int i = 0; i < n; i++)
		cout << " " << Data[i];
	delete[] Data;
	return 0;
}