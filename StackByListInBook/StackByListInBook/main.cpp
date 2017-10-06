#include"Stack.h"

int main(){
	Stack<float> S;
	cout << "ÊäÈëÔªËØ\n";
	float f;
	for (int i = 0; i < 5; i++){
		cin >> f;
		S.Push(f);
	}
	float item;
	S.Top(item);
	cout << "Õ»¶¥ " << item << "\n";
	S.Pop(item);
	S.Top(item);
	cout << "Õ»¶¥ " << item << endl;
}