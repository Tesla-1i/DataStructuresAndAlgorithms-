#include"Queue.h"

int main(){
	Queue<float> queue;
	float f;
	bool b;
	while (1){
		cout << "���\n";
		cin >> f;
		b = queue.EnQueue(f);
		if (b == false)
			break;
	}
	cout << "����\n";
	while (1){
		cout << "����\n";
		b = queue.DeQueue(f);
		if (b == false)
			break;
		cout << f << endl;
	}
}