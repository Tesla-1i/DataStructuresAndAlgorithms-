//������Ϸ������˳��ջʵ��
#include"Stack.h"
#include<cstring>
//scanf��cin�Ⱦ��Կո񣬻س���Ϊ������
//gets�����Իس���Ϊ������

int main(){
	char* str = new char[20];
	cout << "�����ַ���\n";
	gets(str);	//�����ַ��������Կո���Ϊ������
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
				cout << "���ǻ���\n";
				return 0;
			}
		}
	}
	cout << "�ǻ���\n";
	return 0;
	
}