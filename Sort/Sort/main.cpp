#include"Sort.h"

int main() {
	Sort<int> *sort = new Sort<int>;
	cout << "����Ԫ�ظ���: ";
	int n;
	cin >> n;
	int *Array1 = new int[n];
	int *Array2 = new int[n];
	int *Array3 = new int[n];
	int *Array4 = new int[n];
	int *Array5 = new int[n]; 
	int *Array6 = new int[n];
	int *Array7 = new int[n];
	cout << "��������Ԫ��\n";
	for (int i = 0; i < n; i++)
		cin >> Array1[i];
	for (int i = 0; i < n; i++) {
		Array2[i] = Array3[i] = Array4[i] = Array5[i] = Array6[i] = Array7[i] = Array1[i];
	}
	cout << "ֱ�Ӳ�������\n";
	sort->InsertSort(Array1, n);
	sort->Print(Array1, n);
	cout << "�۰��������\n";
	sort->BinaryInsertSort(Array2, n);
	sort->Print(Array2,n);
	cout << "ð������\n";
	sort->BubbleSort(Array3, n);
	sort->Print(Array3, n);
	cout << "��������\n";
	sort->QuickSort(Array4, 0,n-1);
	sort->Print(Array4, n);
	cout << "ֱ��ѡ������\n";
	sort->SelectSort(Array5, n);
	sort->Print(Array5, n);
	cout << "�鲢����\n";
	sort->MergeSort(Array6, 0, n-1 );
	sort->Print(Array6, n);
}