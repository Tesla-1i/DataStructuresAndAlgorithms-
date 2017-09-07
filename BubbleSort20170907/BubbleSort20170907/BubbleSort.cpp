#include<iostream>
using namespace std;

template<class T>
void bubbleSort(T Data[], int n){
	int flag = 0;	//��־
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
			return;		//���ĳһ��û�з�������������Ҫ��ɨ��һ��
	}
}

int main(){
	cout << "����Ԫ�ظ���";
	int n; cin >> n;
	cout << "����Ԫ�أ�";
	float *Data = new float[n];	//����float Data[n]��������Ҫ��ջ�п�
	for (int i = 0; i < n; i++)
		cin >> Data[i];
	bubbleSort(Data, n);
	for (int i = 0; i < n; i++)
		cout << " " << Data[i];
	delete[] Data;
	return 0;
}