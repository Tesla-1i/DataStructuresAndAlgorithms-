#include"Stack.h"
#include<cstring>

//表达式括号匹配检查，兼顾三种括号。秩在[lo,hi]区间进行匹配检测
bool paren(char *exp, int lo, int hi){
	Stack<char> S;
	char item;
	for (int i = lo; i <= hi; i++){
		switch (exp[i]){
		case '(':case '[':case '{':S.Push(exp[i]);	break;
		/*case ')':if (S.IsEmpty()) return false;
			S.Pop(item); if ( ('(' != item)) return false; break;*/
		//先取栈顶检查匹配，不匹配直接返回false，匹配则弹出
		case ')'://不能先弹，再比较是否空。应该先判断，再弹出
			S.Top(item); if (S.IsEmpty() || ('(' != item)) return false; S.Pop(item); break;
		case ']'://不能先弹，再比较是否空
			S.Top(item); if (S.IsEmpty() || ('[' != item)) return false; S.Pop(item); break;
		case '}'://不能先弹，再比较是否空
			S.Top(item); if (S.IsEmpty() || ('{' != item)) return false; S.Pop(item); break;
		default:break;
		}
	}
	//返回假，表示栈不空，表示匹配不完全。
	return S.IsEmpty();	//如果是空的，返回真，表示完全匹配
}

int main(){
	char *exp = new char[20];
	cout << "输入表达式： \n";
	cin >> exp;		//输入字符串
	int hi = strlen(exp);
	cout << hi << endl;
	
	bool b = paren(exp, 0, hi - 1);
	cout << exp << endl;
	if (b == false)
		cout << "不匹配\n";
	if (b == true)
		cout << "匹配\n";
}