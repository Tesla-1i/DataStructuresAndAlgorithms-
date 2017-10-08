#include<stack>
#include<iostream>
using namespace std;

//将输入行以相反顺序打印出来

//利用stack将非尾递归转为迭代
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
