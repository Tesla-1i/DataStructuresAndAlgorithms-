#include"Stack.h"
//ʮ����nת��Ϊbase���Ƶ���
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
	cout << "����ʮ��������n�ͽ���base ";
	unsigned int n; int base;
	cin >> n >> base;
	
	convert(S, n, base);

	bool b = S.IsEmpty();
	if (b == false)
		cout << "����";
	else
		cout << "��";

	char c;
	while (S.top != -1){
		S.Pop(c);
		cout << c;
	}
	
	/*Stack<int> stack;
	cout << "����5������\n";
	for (int i = 0; i < 5; i++){
		int n;  cin >> n;
		stack.Push(n);
	}
	cout << "ջ��Ԫ���ǣ� ";
	int item;
	stack.Top(item);
	cout << item << "\n";
	cout << "��ջ\n";
	stack.Pop(item);
	cout << "��ջ���� ";
	stack.Top(item);
	cout << item << "\n";*/
}

//ttp://www.myexception.cn/cpp/1907738.html
//������תΪ�޷������֣������ת������

//������ֻת��������
//void convert(Stack<char>& S, int n, int base){
//	char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'
//		, 'D', 'E', 'F' };
//	while (n>0){
//		int remainder = (int)(n%base);
//		S.Push(digit[remainder]);
//		n /= base;
//	}
//}