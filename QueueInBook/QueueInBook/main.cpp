#include"Queue.h"

int main(){
	Queue<float> queue;
	float f;
	while (1){
		cout << "���\n";
		cin >> f;
		bool b = queue.EnQueue(f);
		if (b == false)
			break;
	}
	cout << "����\n";
	while (1){
		cout << "����\n";
		float item;
		bool b = queue.DeQueue(item);
		if (b == false)
			break;
		cout << item << endl;
	}
	cout << "����\n";
}