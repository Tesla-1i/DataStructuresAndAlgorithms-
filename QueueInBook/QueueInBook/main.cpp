#include"Queue.h"

int main(){
	Queue<float> queue;
	float f;
	while (1){
		cout << "入队\n";
		cin >> f;
		bool b = queue.EnQueue(f);
		if (b == false)
			break;
	}
	cout << "结束\n";
	while (1){
		cout << "出队\n";
		float item;
		bool b = queue.DeQueue(item);
		if (b == false)
			break;
		cout << item << endl;
	}
	cout << "结束\n";
}