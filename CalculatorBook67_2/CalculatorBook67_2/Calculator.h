#include<string>
#include"Stack.h"

//计算器初级阶段，仅仅计算一位整数数的加减乘除。
//直接计算中缀表达式(没有处理空格)

#ifndef CALCULATOR
#define CALCULATOR

class Calculator{
public:
	double calculate(string InfixExp);
	//string infix_to_suffix(string InfixExp);
	//double cal_suffix(string PostfixExp);
	double cal(double num1, double num2, char op);
	//double cal(double num1, char op);
};

#endif