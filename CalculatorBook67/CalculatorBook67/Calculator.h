#include<string>
#include"Stack.h"

//�����������׶Σ���������һλ�������ļӼ��˳���

#ifndef CALCULATOR
#define CALCULATOR

class Calculator{
public:
	//double calculate(string InfixExp);
	string infix_to_suffix(string InfixExp);
	double cal_suffix(string PostfixExp);
	double cal(double num1, double num2, char op);
};

#endif
