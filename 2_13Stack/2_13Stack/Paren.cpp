#include"Stack.h"
#include<cstring>

//表达式括号匹配检查，兼顾三种括号
bool paren(char *exp, int lo, int hi){
	Stack<char> S;
	char item;
	for (int i = lo; i <= hi; i++){
		switch (exp[i]){
		case '(':case '[':case '{':S.Push(exp[i]);	break;
		/*case ')':if (S.IsEmpty()) return false;
			S.Pop(item); if ( ('(' != item)) return false; break;*/
		case ')'://不能先弹，再比较是否空
			S.Top(item); if (S.IsEmpty() || ('(' != item)) return false; S.Pop(item); break;
		case ']'://不能先弹，再比较是否空
			S.Top(item); if (S.IsEmpty() || ('[' != item)) return false; S.Pop(item); break;
		case '}'://不能先弹，再比较是否空
			S.Top(item); if (S.IsEmpty() || ('{' != item)) return false; S.Pop(item); break;
		default:break;
		}
	}
	//返回假，表示不匹配
	return S.IsEmpty();
}

int main(){
	char *exp = new char[20];
	cout << "输入表达式： \n";
	cin >> exp;
	int hi = strlen(exp);
	cout << hi << endl;
	
	bool b = paren(exp, 0, hi - 1);
	cout << exp << endl;
	if (b == false)
		cout << "不匹配\n";
	if (b == true)
		cout << "匹配\n";
}