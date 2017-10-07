#include<cmath>
#include"Calculator.h"

///////////////////////////////////�ж���������ȼ�
#define N_OPTR 7	//���������
typedef enum{ADD,SUB,MUL,DIV,L_P,R_P,EOE}Operator;//���������
//+ - * / ^ ! ( ) \0������ʼ������ֹ��
char pri[N_OPTR][N_OPTR] = {//��������ȼ�[ջ��][��ǰ]
	/*              |------- �� ǰ �� �� �� -----------| */
	/*              +    -    *    /     (    )     \0 */
	/* --  + */    '>', '>', '<', '<',  '<', '>',  '>',
	/* |   - */    '>', '>', '<', '<',  '<', '>',  '>',
	/* ջ  * */    '>', '>', '>', '>',  '<', '>',  '>',
	/* ��  / */    '>', '>', '>', '>',  '<', '>',  '>',
	/* ��  ( */    '<', '<', '<', '<',  '<', '=',  ' ',
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
	case '\0': return EOE;	//��ʼ������ֹ��
	default: exit(-1);	//����δ֪�����
	}
}
char orderBetween(char op1, char op2){//�Ƚ������������ȼ�
	return pri[optr2rank(op1)][optr2rank(op2)];
}
////////////////////////////////////////////////////////////




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



double Calculator::calculate(string InfixExp){
	Stack<double> OPND; Stack<char> OPTR;	//������ջ�������ջ
	OPTR.Push('\0');	//��\0��ͷ�ڱ���ջ
	char item;
	int i = 0;
	while (!OPTR.IsEmpty()){
		//������ֱ��ѹ��,�ַ���ת����
		if (InfixExp[i] >= '0'&&InfixExp[i] <= '9'){
			OPND.Push(InfixExp[i] - '0');
			//double d; OPND.Top(d); cout << d << " ";
			i++;
		}
		//��������ջ�����������ȼ����бȽ�
		else{
			OPTR.Top(item);	//ȡ�����ջ��������ջ
			switch (orderBetween(item, InfixExp[i])){
			case '<':OPTR.Push(InfixExp[i]); i++; break;
				//ջ����������ȼ��ͣ���ǰ�������ջ
			case '=':OPTR.Pop(item); i++; break;
				//���ȼ���ȣ���ǰ������������Ż�β��'\0'������ջ��
			case '>': //ջ����������ȼ��ߣ����м��㣬�������ջ
				OPTR.Pop(item);//��ջ
				double num1, num2;
				OPND.Pop(num2); OPND.Pop(num1);//�ȵ������ǵڶ���������
				OPND.Push(cal(num1, num2, item));
				break;
			default: cout << "�﷨����\n"; exit(-1);
			}
		}
	}
	double num; OPND.Top(num);
	return num;
}

int main(){
	Calculator calculator;
	string str;
	cout << "������׺���ʽ\n";
	cin >> str;
	//str += '\0';
	cout << str << endl;
	double d = calculator.calculate(str);
	cout << d << endl;
}

//string���β����û��'\0'?????????????????