#include<stack>
#include<iostream>
using namespace std;

//�����������෴˳���ӡ����

//����stack����β�ݹ�תΪ����
void nonRecursiveReverse(){
	stack<char> st;
	char ch;
	cin.get(ch);
	while (ch != '\n'){
		st.push(ch);
		cin.get(ch);
	}
	while (!st.empty()){
		cout.put(st.top());
		st.pop();
	}
}

void reverse(){
	char ch;
	cin.get(ch);
	if (ch != '\n'){
		reverse();
		cout.put(ch);
	}
}

int main(){
	nonRecursiveReverse();
	cout << endl;
	reverse();
}
