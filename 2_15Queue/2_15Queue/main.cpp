#include"Queue.h"

int main(){
	Queue<float> queue;
	float f;
	bool b;
	while (1){
		cout << "入队\n";
		cin >> f;
		b = queue.EnQueue(f);
		if (b == false)
			break;
	}
	cout << "结束\n";
	while (1){
		cout << "出队\n";
		b = queue.DeQueue(f);
		if (b == false)
			break;
		cout << f << endl;
	}
}