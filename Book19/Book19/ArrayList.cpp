#include<iostream>
using namespace std;

class ArrayList{
private:
	int *arrayList;
	int maxSize;
	int curLen;
	int position;
public:
	ArrayList(const int size = 0){
		maxSize = size;
		arrayList = new int[size];
		curLen = 0;	//?Ϊ��ħ��0
		position = 0;
	}
	~ArrayList(){
		delete[] arrayList;
		cout << "ɾ��˳���\n";
	}
	//pλ�ò���value
	bool Insert(const int p, const int value){
		if (curLen >= maxSize){
			cout << "˳������\n";
			return false;
		}
		if (p<0||p>maxSize){
			cout << "����λ�÷Ƿ�\n";
			return false;
		}
		for (int i = curLen; i > p; i--){
			arrayList[i] = arrayList[i - 1];
		}
		arrayList[p] = value;
		curLen++;
		return true;
	}
	void Show(){
		for (int i = 0; i < curLen; i++){
			cout << arrayList[i] << " ";
		}
	}
};

int main(){
	int size;
	cout << "����˳����С\n";
	cin >> size;
	ArrayList arrayList(size);
	while (1){
		cout << "�������λ�ú�ֵ,����qֹͣ���룬��������Q\n";
		int p, value;
		char q;
		cin >> p >> value >> q;
		if (arrayList.Insert(p, value))
			cout << "����ɹ�\n";
		else{
			cout << "����ʧ��\n";
			return 0;
		}
		cout << "����qֹͣ����\n";
		if (q == 'q')
			break;
	}
	arrayList.Show();
	return 0;
}