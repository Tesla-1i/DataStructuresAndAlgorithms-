#include"Stack.h"

int main(){
	Stack<float> S;
	cout << "����Ԫ��\n";
	float f;
	for (int i = 0; i < 5; i++){
		cin >> f;
		S.Push(f);
	}
	float item;
	S.Top(item);
	cout << "ջ�� " << item << "\n";
	S.Pop(item);
	S.Top(item);
	cout << "ջ�� " << item << endl;
}