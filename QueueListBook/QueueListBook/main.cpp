#include"Queue.h"

int main(){
	Queue<float> queue;
	int i = 4;
	float f;
	while (i){
		cout << "入队\n";
		cin >> f;
		queue.EnQueue(f);
		i--;
	}
	i = 4;
	while (i){
		cout << "出队\n";
		queue.DeQueue(f);
		cout << f << endl;
		i--;
	}
	cout << "结束\n";
}