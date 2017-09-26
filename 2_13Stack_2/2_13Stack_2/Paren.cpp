#include"Stack.h"
#include<cstring>

//正确，没问题
bool paren(const char exp[], int lo, int hi){	//lo,hi均为秩
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
	cout << "输入表达式\n";
	cin >> exp;
	int hi = strlen(exp);
	bool b = paren(exp, 0, hi-1);
	if (b == false)
		cout << "不匹配";
	else
		cout << "匹配";

}