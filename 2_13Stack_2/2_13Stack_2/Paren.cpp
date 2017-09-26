#include"Stack.h"
#include<cstring>

//��ȷ��û����
bool paren(const char exp[], int lo, int hi){	//lo,hi��Ϊ��
	Stack<char> S;
	for (int i = lo; i <= hi; i++){
		switch (exp[i]){
		case '(': case '{': case '[': S.push(exp[i]); break;
		case ')':if (S.empty() || ('(' != S.pop())) return false; break;
		case ']':if (S.empty() || ('[' != S.pop())) return false; break;
		case '}':if (S.empty() || ('{' != S.pop())) return false; break;
		default: break;
		}
	}
	return S.empty();
}

int main(){
	char *exp = new char[20];
	cout << "������ʽ\n";
	cin >> exp;
	int hi = strlen(exp);
	bool b = paren(exp, 0, hi-1);
	if (b == false)
		cout << "��ƥ��";
	else
		cout << "ƥ��";

}