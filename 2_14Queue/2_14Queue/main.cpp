//利用链式队列实现
#include"Queue.h"

int main(){
	Queue<int>* queue = new Queue<int>[10];	//队列数组
	int n, num;
	cout << "输入数据个数是 "; cin >> n;
	for (int i = 0; i < n; i++){
		cout << "一次输入一个数据[0,9]\n";
		cin >> num;
		queue[num].EnQueue(num);	//输入的num入队第num个队
	}
	ListNode<int>* Front = NULL;
	ListNode<int>* Rear = NULL;
	for (int i = 0; i < 10; i++){
		if (queue[i].front != NULL){	//某个队列不为空
			if (Front == NULL){	//总的头结点
				Front = (queue[i].front);
				Rear = (queue[i].rear);
			}
			else{
				Rear->succ = queue[i].front;
				Rear = queue[i].rear;
			}
		}
	}
	cout << "拼接完毕\n";
	ListNode<int>* Temp = Front;
	while (Temp != NULL){
		cout << (Temp->data) << " ";
		Temp = Temp->succ;
	}
	cout << "输出结束\n";
}