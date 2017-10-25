#include <iostream>
#include <queue>
//���ö��������ʽ��ϵ��
using namespace std;
//�����Ƕ���&���ݴ�����ÿ���һ������0��numof0++���ж��Ƿ񵽴��ݴ���������ѹ0
template <class T>void Polynomial(queue<T>& queue1, int n) {
	int numof0 = 0;   //������0�ĸ���
	queue1.push(1); //��ʼ���������0�Ͷ�����1��ӵ�1
	T f = queue1.front();
	queue1.pop();
	while (1) {
		int value = f + queue1.front();
		queue1.push(value);
		if (queue1.front() == 0) {
			numof0++;
			if (numof0 == n)
				return;
			queue1.push(0);
		}
		f = queue1.front();
		queue1.pop();
	}
}

int main() {
	queue<int> queue1;
	queue1.push(1);
	queue1.push(2);
	queue1.push(1);
	queue1.push(0); //ѹ��0��Ϊ����
	cout << "�����ݴ�����";
	int n;  cin >> n;
	if (n < 1) {
		cout << "��С��1\n"; return 0;
	}
	if (n == 1) {
		cout << "1 1\n"; return 0;
	}
	if (n == 2) {
		cout << "1 2 1\n"; return 0;
	}
	Polynomial(queue1, n - 2);   //�Ĵη���ϵ��
	queue1.pop();	//������ͷ��0�������㷨��ȱ�ݣ�
	while (!queue1.empty()) {
		cout << queue1.front() << " ";
		queue1.pop();
	}
	return 0;
}