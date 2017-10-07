#include<cmath>
#include"Calculator.h"

///////////////////////////////////判断运算符优先级
#define N_OPTR 7	//运算符总数
typedef enum{ADD,SUB,MUL,DIV,L_P,R_P,EOE}Operator;//运算符集合
//+ - * / ^ ! ( ) \0既是起始符和终止符
char pri[N_OPTR][N_OPTR] = {//运算符优先级[栈顶][当前]
	/*              |------- 当 前 运 算 符 -----------| */
	/*              +    -    *    /     (    )     \0 */
	/* --  + */    '>', '>', '<', '<',  '<', '>',  '>',
	/* |   - */    '>', '>', '<', '<',  '<', '>',  '>',
	/* 栈  * */    '>', '>', '>', '>',  '<', '>',  '>',
	/* 顶  / */    '>', '>', '>', '>',  '<', '>',  '>',
	/* 符  ( */    '<', '<', '<', '<',  '<', '=',  ' ',
	/* |   ) */    ' ', ' ', ' ', ' ',  ' ', ' ',  ' ',
	/* -- \0 */    '<', '<', '<', '<',  '<', ' ',  '='
};
Operator optr2rank(char op){
	switch (op){
	case '+': return ADD;
	case '-': return SUB;
	case '*': return MUL;
	case '/': return DIV;
	case '(': return L_P;
	case ')': return R_P;
	case '\0': return EOE;	//起始符与终止符
	default: exit(-1);	//其他未知运算符
	}
}
char orderBetween(char op1, char op2){//比较运算符间的优先级
	return pri[optr2rank(op1)][optr2rank(op2)];
}
////////////////////////////////////////////////////////////




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



double Calculator::calculate(string InfixExp){
	Stack<double> OPND; Stack<char> OPTR;	//运算数栈，运算符栈
	OPTR.Push('\0');	//‘\0’头哨兵入栈
	char item;
	int i = 0;
	while (!OPTR.IsEmpty()){
		//操作数直接压入,字符型转数字
		if (InfixExp[i] >= '0'&&InfixExp[i] <= '9'){
			OPND.Push(InfixExp[i] - '0');
			//double d; OPND.Top(d); cout << d << " ";
			i++;
		}
		//操作符与栈顶操作符优先级进行比较
		else{
			OPTR.Top(item);	//取运算符栈顶，不弹栈
			switch (orderBetween(item, InfixExp[i])){
			case '<':OPTR.Push(InfixExp[i]); i++; break;
				//栈顶运算符优先级低，当前运算符入栈
			case '=':OPTR.Pop(item); i++; break;
				//优先级相等，当前运算符是右括号或尾部'\0'，弹出栈顶
			case '>': //栈顶运算符优先级高，进行计算，结果再入栈
				OPTR.Pop(item);//弹栈
				double num1, num2;
				OPND.Pop(num2); OPND.Pop(num1);//先弹出的是第二个操作数
				OPND.Push(cal(num1, num2, item));
				break;
			default: cout << "语法错误\n"; exit(-1);
			}
		}
	}
	double num; OPND.Top(num);
	return num;
}

int main(){
	Calculator calculator;
	string str;
	cout << "输入中缀表达式\n";
	cin >> str;
	//str += '\0';
	cout << str << endl;
	double d = calculator.calculate(str);
	cout << d << endl;
}

//string类结尾可以没有'\0'?????????????????