#include"Stack.h"
#include<cstring>

//���ʽ����ƥ���飬�����������
bool paren(char *exp, int lo, int hi){
	Stack<char> S;
	char item;
	for (int i = lo; i <= hi; i++){
		switch (exp[i]){
		case '(':case '[':case '{':S.Push(exp[i]);	break;
		/*case ')':if (S.IsEmpty()) return false;
			S.Pop(item); if ( ('(' != item)) return false; break;*/
		case ')'://�����ȵ����ٱȽ��Ƿ��
			S.Top(item); if (S.IsEmpty() || ('(' != item)) return false; S.Pop(item); break;
		case ']'://�����ȵ����ٱȽ��Ƿ��
			S.Top(item); if (S.IsEmpty() || ('[' != item)) return false; S.Pop(item); break;
		case '}'://�����ȵ����ٱȽ��Ƿ��
			S.Top(item); if (S.IsEmpty() || ('{' != item)) return false; S.Pop(item); break;
		default:break;
		}
	}
	//���ؼ٣���ʾ��ƥ��
	return S.IsEmpty();
}

int main(){
	char *exp = new char[20];
	cout << "������ʽ�� \n";
	cin >> exp;
	int hi = strlen(exp);
	cout << hi << endl;
	
	bool b = paren(exp, 0, hi - 1);
	cout << exp << endl;
	if (b == false)
		cout << "��ƥ��\n";
	if (b == true)
		cout << "ƥ��\n";
}