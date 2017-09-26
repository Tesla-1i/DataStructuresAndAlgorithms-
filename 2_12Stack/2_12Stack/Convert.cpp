#include"Stack.h"
//十进制n转换为base进制的数
void convert(Stack<char>& S,unsigned int n, int base){
	char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'
		, 'D', 'E', 'F' };
	while (n){
		int remainder = (int)(n%base);
		S.Push(digit[remainder]);
		n /= base;
	}
}

int main(){
	Stack<char> S;
	cout << "输入十进制整数n和进制base ";
	unsigned int n; int base;
	cin >> n >> base;
	
	convert(S, n, base);

	bool b = S.IsEmpty();
	if (b == false)
		cout << "不空";
	else
		cout << "空";

	char c;
	while (S.top != -1){
		S.Pop(c);
		cout << c;
	}
	
	/*Stack<int> stack;
	cout << "输入5个整数\n";
	for (int i = 0; i < 5; i++){
		int n;  cin >> n;
		stack.Push(n);
	}
	cout << "栈顶元素是： ";
	int item;
	stack.Top(item);
	cout << item << "\n";
	cout << "弹栈\n";
	stack.Pop(item);
	cout << "新栈顶： ";
	stack.Top(item);
	cout << item << "\n";*/
}

//ttp://www.myexception.cn/cpp/1907738.html
//将数字转为无符号数字，则可以转换负数

//下面是只转换正整数
//void convert(Stack<char>& S, int n, int base){
//	char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'
//		, 'D', 'E', 'F' };
//	while (n>0){
//		int remainder = (int)(n%base);
//		S.Push(digit[remainder]);
//		n /= base;
//	}
//}