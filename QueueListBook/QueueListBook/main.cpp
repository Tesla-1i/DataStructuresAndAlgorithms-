#include"Queue.h"

int main(){
	Queue<float> queue;
	int i = 4;
	float f;
	while (i){
		cout << "���\n";
		cin >> f;
		queue.EnQueue(f);
		i--;
	}
	i = 4;
	while (i){
		cout << "����\n";
		queue.DeQueue(f);
		cout << f << endl;
		i--;
	}
	cout << "����\n";
}