#include <iostream>
#include <queue>
//利用队列求多项式的系数
using namespace std;
//参数是队列&和幂次数。每完成一轮遇到0，numof0++，判断是否到达幂次数，否，则压0
template <class T>void Polynomial(queue<T>& queue1, int n) {
	int numof0 = 0;   //队列中0的个数
	queue1.push(1); //起始处队列外的0和队列内1相加得1
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
	queue1.push(0); //压入0作为结束
	cout << "输入幂次数：";
	int n;  cin >> n;
	if (n < 1) {
		cout << "幂小于1\n"; return 0;
	}
	if (n == 1) {
		cout << "1 1\n"; return 0;
	}
	if (n == 2) {
		cout << "1 2 1\n"; return 0;
	}
	Polynomial(queue1, n - 2);   //四次方的系数
	queue1.pop();	//弹出队头的0（由于算法的缺陷）
	while (!queue1.empty()) {
		cout << queue1.front() << " ";
		queue1.pop();
	}
	return 0;
}