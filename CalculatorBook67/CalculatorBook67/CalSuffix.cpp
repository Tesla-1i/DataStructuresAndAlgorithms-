#include"Calculator.h"
#include<cmath>

string Calculator::infix_to_suffix(string InfixExp){
	Stack<char> OPTR;	
	string PostfixExp;// = NULL;��������ʱ����
	int i = 0;
	char item;
	while (InfixExp[i] != '\0'){
		if (InfixExp[i] == ' ')	//�����ո�
		{
			i++; continue;
		}
		//�����������ֱ�Ӽӵ���׺
		if (InfixExp[i] <= '9'&&InfixExp[i] >= '0'){
			PostfixExp += ' ';
			PostfixExp += InfixExp[i];
		}
		//���뿪���ţ�ֱ��ѹջ
		else if (InfixExp[i] == '('){
			OPTR.Push(InfixExp[i]);
		}
		//���������
		else if (InfixExp[i] == ')'){
			if (OPTR.IsEmpty()){
				cout << "���Ų�ƥ��\n"; exit(1);
			}
			else{//���ε�ջ��������Ԫ�ؼӵ���׺��ֱ������������(�����Ų��ӵ���׺)
				while (!OPTR.IsEmpty()){
					OPTR.Pop(item);
					if (item != '('){	//��������һ����֮ǰ����׷��
						PostfixExp += ' ';
						PostfixExp += item;
					}
					else{	//���򣬲��ٽ���׷��
						break;
					}
				}
				//���������ջ���޿����ţ�����ջ��Ԫ��ȫ���������϶�����
				if (OPTR.IsEmpty()){	//ȫ��������˵��û��������������ƥ�䲻�ɹ���
					cout << "����ƥ�䲻�ɹ�\n"; exit(1);
				}
			}
		}
		//���������
		else if (InfixExp[i] == '+' || InfixExp[i] == '-' || InfixExp[i] == '*' || InfixExp[i] == '/'){
			OPTR.Top(item);
			//ջ�ǿ�&&ջ�����ǿ�����&&��������ȼ�������ջ������������ȼ�.	�����������ӵ���׺
			//���ȼ��Ƚϣ���ջ����*��/ �� ��ǰ������� +��- ����������
			while (!OPTR.IsEmpty() && item != '(' && (item == '*' || item == '/' || InfixExp[i] == '+' || InfixExp[i] == '-')){
				OPTR.Pop(item); PostfixExp += ' '; PostfixExp += item;
				OPTR.Top(item);
			}
			OPTR.Push(InfixExp[i]);
		}
		i++;
	}
	while (!OPTR.IsEmpty()){	//ɨ������׺���ʽ��ջ�л���Ԫ�أ�׷�ӵ���׺���ʽ
		OPTR.Pop(item);
		if (item == '('){	//����δƥ���(˵���﷨����
			cout << "���Ų�ƥ��\n"; exit(1);
		}
		else{
			PostfixExp += ' ';
			PostfixExp += item;
		}
	}
	return PostfixExp;
}

double Calculator::cal(double num1, double num2, char op){
	switch (op){
	case '+': return (num1 + num2);
	case '-': return (num1 - num2);
	case '*': return (num1*num2);
	case '/': if (fabs(num2) < 1e-5){
				  cout << "����������0\n";
				  exit(1);
				  //return 10000;		//�����жϳ�����0
				}
			  else{
				  return (num1 / num2);
			  }
	}
}

double Calculator::cal_suffix(string PostfixExp){
	int i = 0;
	Stack<double> OPND;		//������ջ
	double num,num1,num2;
	while (PostfixExp[i] != '\0'){
		if (PostfixExp[i] == ' '){
			i++;
			continue;	//���Ժ�׺���ʽ�еĿո�
		}
		switch (PostfixExp[i]){
		case '1':OPND.Push(1); break;
		case '2':OPND.Push(2); break;
		case '3':OPND.Push(3); break;
		case '4':OPND.Push(4); break;
		case '5':OPND.Push(5); break;
		case '6':OPND.Push(6); break;
		case '7':OPND.Push(7); break; 
		case '8':OPND.Push(8); break;
		case '9':OPND.Push(9); break;
		case '0':OPND.Push(0); break;
		case '+':
			OPND.Pop(num2); OPND.Pop(num1);	//��һ���������ǵڶ���������
			 num=cal(num1, num2, '+');
			OPND.Push(num); break;
		case '-':
			OPND.Pop(num2); OPND.Pop(num1);
			 num= cal(num1, num2, '-'); 
			 OPND.Push(num); break;
		case '*':
			OPND.Pop(num2); OPND.Pop(num1);
			num=cal(num1, num2, '*'); 
			OPND.Push(num); break;
		case '/':
			OPND.Pop(num2); OPND.Pop(num1);
			num=cal(num1, num2, '/'); 
			OPND.Push(num); break;
		}
		i++;
	}
	double item;
	OPND.Top(item);
	return item;
}

int main(){
	Calculator calculator;
	string str = "10/";	//���ʽ�����пո�
	//double d=calculator.cal_suffix(str);
	//cout << d;
	string str1;
	cout << "������׺���ʽ\n";
	char* s = new char[20];
	gets(s);	//�����ַ���Ҳ�����пո�
	str1 = s;
	cout << str1;
	//cin >> str1;
	str = calculator.infix_to_suffix(str1);
	cout << str << endl;
	double d = calculator.cal_suffix(str);
	cout << d << endl;
}