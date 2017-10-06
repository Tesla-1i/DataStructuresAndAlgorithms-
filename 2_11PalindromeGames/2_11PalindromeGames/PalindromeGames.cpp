//回文游戏，利用顺序栈实现
#include"Stack.h"
#include<cstring>
//scanf，cin等均以空格，回车作为结束符
//gets仅仅以回车作为结束符

int main(){
	char* str = new char[20];
	cout << "输入字符串\n";
	gets(str);	//输入字符串，不以空格作为结束符
	cout << str << endl;
	Stack<char> S;
	int sizeOfStr = strlen(str);
	for (int i = 0; i < sizeOfStr; i++){
		if (str[i] != ' '){
			S.Push(str[i]);
		}
	}
	char item;
	for (int i = 0; i < sizeOfStr; i++){
		if (str[i] != ' '){
			S.Pop(item);
			if (item != str[i]){
				cout << "不是回文\n";
				return 0;
			}
		}
	}
	cout << "是回文\n";
	return 0;
	
}