//������ʽ����ʵ��
#include"Queue.h"

int main(){
	Queue<int>* queue = new Queue<int>[10];	//��������
	int n, num;
	cout << "�������ݸ����� "; cin >> n;
	for (int i = 0; i < n; i++){
		cout << "һ������һ������[0,9]\n";
		cin >> num;
		queue[num].EnQueue(num);	//�����num��ӵ�num����
	}
	ListNode<int>* Front = NULL;
	ListNode<int>* Rear = NULL;
	for (int i = 0; i < 10; i++){
		if (queue[i].front != NULL){	//ĳ�����в�Ϊ��
			if (Front == NULL){	//�ܵ�ͷ���
				Front = (queue[i].front);
				Rear = (queue[i].rear);
			}
			else{
				Rear->succ = queue[i].front;
				Rear = queue[i].rear;
			}
		}
	}
	cout << "ƴ�����\n";
	ListNode<int>* Temp = Front;
	while (Temp != NULL){
		cout << (Temp->data) << " ";
		Temp = Temp->succ;
	}
	cout << "�������\n";
}