#include"Stack.h"
#include<cstring>

//���ʽ����ƥ���飬����������š�����[lo,hi]�������ƥ����
bool paren(char *exp, int lo, int hi){
	Stack<char> S;
	char item;
	for (int i = lo; i <= hi; i++){
		switch (exp[i]){
		case '(':case '[':case '{':S.Push(exp[i]);	break;
		/*case ')':if (S.IsEmpty()) return false;
			S.Pop(item); if ( ('(' != item)) return false; break;*/
		//��ȡջ�����ƥ�䣬��ƥ��ֱ�ӷ���false��ƥ���򵯳�
		case ')'://�����ȵ����ٱȽ��Ƿ�ա�Ӧ�����жϣ��ٵ���
			S.Top(item); if (S.IsEmpty() || ('(' != item)) return false; S.Pop(item); break;
		case ']'://�����ȵ����ٱȽ��Ƿ��
			S.Top(item); if (S.IsEmpty() || ('[' != item)) return false; S.Pop(item); break;
		case '}'://�����ȵ����ٱȽ��Ƿ��
			S.Top(item); if (S.IsEmpty() || ('{' != item)) return false; S.Pop(item); break;
		default:break;
		}
	}
	//���ؼ٣���ʾջ���գ���ʾƥ�䲻��ȫ��
	return S.IsEmpty();	//����ǿյģ������棬��ʾ��ȫƥ��
}

int main(){
	char *exp = new char[20];
	cout << "������ʽ�� \n";
	cin >> exp;		//�����ַ���
	int hi = strlen(exp);
	cout << hi << endl;
	
	bool b = paren(exp, 0, hi - 1);
	cout << exp << endl;
	if (b == false)
		cout << "��ƥ��\n";
	if (b == true)
		cout << "ƥ��\n";
}