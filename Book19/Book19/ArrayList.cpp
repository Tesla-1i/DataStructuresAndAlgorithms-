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
		curLen = 0;	//?为神魔是0
		position = 0;
	}
	~ArrayList(){
		delete[] arrayList;
		cout << "删除顺序表\n";
	}
	//p位置插入value
	bool Insert(const int p, const int value){
		if (curLen >= maxSize){
			cout << "顺序表溢出\n";
			return false;
		}
		if (p<0||p>maxSize){
			cout << "插入位置非法\n";
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
	cout << "输入顺序表大小\n";
	cin >> size;
	ArrayList arrayList(size);
	while (1){
		cout << "输入插入位置和值,输入q停止插入，否则输入Q\n";
		int p, value;
		char q;
		cin >> p >> value >> q;
		if (arrayList.Insert(p, value))
			cout << "插入成功\n";
		else{
			cout << "插入失败\n";
			return 0;
		}
		cout << "输入q停止插入\n";
		if (q == 'q')
			break;
	}
	arrayList.Show();
	return 0;
}