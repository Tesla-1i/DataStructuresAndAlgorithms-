#include"Calculator.h"
#include<cmath>

string Calculator::infix_to_suffix(string InfixExp){
	Stack<char> OPTR;	
	string PostfixExp;// = NULL;否则运行时错误
	int i = 0;
	char item;
	while (InfixExp[i] != '\0'){
		if (InfixExp[i] == ' ')	//跳过空格
		{
			i++; continue;
		}
		//读入操作数，直接加到后缀
		if (InfixExp[i] <= '9'&&InfixExp[i] >= '0'){
			PostfixExp += ' ';
			PostfixExp += InfixExp[i];
		}
		//读入开括号，直接压栈
		else if (InfixExp[i] == '('){
			OPTR.Push(InfixExp[i]);
		}
		//读入闭括号
		else if (InfixExp[i] == ')'){
			if (OPTR.IsEmpty()){
				cout << "括号不匹配\n"; exit(1);
			}
			else{//依次弹栈，弹出的元素加到后缀，直到遇到开括号(开括号不加到后缀)
				while (!OPTR.IsEmpty()){
					OPTR.Pop(item);
					if (item != '('){	//在遇到第一个（之前进行追加
						PostfixExp += ' ';
						PostfixExp += item;
					}
					else{	//否则，不再进行追加
						break;
					}
				}
				//可能情况是栈中无开括号，导致栈中元素全部弹出，肯定错了
				if (OPTR.IsEmpty()){	//全部弹出，说明没有遇到（，括号匹配不成功。
					cout << "括号匹配不成功\n"; exit(1);
				}
			}
		}
		//读入运算符
		else if (InfixExp[i] == '+' || InfixExp[i] == '-' || InfixExp[i] == '*' || InfixExp[i] == '/'){
			OPTR.Top(item);
			//栈非空&&栈顶不是开括号&&运算符优先级不高于栈顶运算符的优先级.	反复弹出并加到后缀
			//优先级比较：当栈顶是*或/ 或 当前运算符是 +或- 就满足条件
			while (!OPTR.IsEmpty() && item != '(' && (item == '*' || item == '/' || InfixExp[i] == '+' || InfixExp[i] == '-')){
				OPTR.Pop(item); PostfixExp += ' '; PostfixExp += item;
				OPTR.Top(item);
			}
			OPTR.Push(InfixExp[i]);
		}
		i++;
	}
	while (!OPTR.IsEmpty()){	//扫描完中缀表达式，栈中还有元素，追加到后缀表达式
		OPTR.Pop(item);
		if (item == '('){	//还有未匹配的(说明语法错误
			cout << "括号不匹配\n"; exit(1);
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
				  cout << "除数不能是0\n";
				  exit(1);
				  //return 10000;		//进行判断除数是0
				}
			  else{
				  return (num1 / num2);
			  }
	}
}

double Calculator::cal_suffix(string PostfixExp){
	int i = 0;
	Stack<double> OPND;		//操作数栈
	double num,num1,num2;
	while (PostfixExp[i] != '\0'){
		if (PostfixExp[i] == ' '){
			i++;
			continue;	//忽略后缀表达式中的空格
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
			OPND.Pop(num2); OPND.Pop(num1);	//第一个弹出的是第二个操作数
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
	string str = "10/";	//表达式不能有空格
	//double d=calculator.cal_suffix(str);
	//cout << d;
	string str1;
	cout << "输入中缀表达式\n";
	char* s = new char[20];
	gets(s);	//输入字符串也可以有空格
	str1 = s;
	cout << str1;
	//cin >> str1;
	str = calculator.infix_to_suffix(str1);
	cout << str << endl;
	double d = calculator.cal_suffix(str);
	cout << d << endl;
}