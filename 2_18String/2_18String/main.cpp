#include<iostream>
#include<cstring>
using namespace std;

int NaiveStrMatching(char* T, char* P){
	int p = 0, t = 0, x=-1;
	int plen = strlen(P);
	int tlen = strlen(T);
	if (tlen < plen)
		return -1;	//Ŀ�괮��ģʽ����
	//������ģʽƥ�䲻ͬ���ǣ�ɨ������Ŀ�괮����ʹƥ���˻���������ɨ��
	//ÿ�Ƚ�һ���ַ��󣬾��ж�ģʽ���Ƿ�ƥ��ɹ����ɹ�һ�Σ��͸���һ�γɹ���λ��
	//ɨ����Ŀ�괮��ֱ�ӷ������µĳɹ�λ�ã�һ�㲻�ں��棬һ�㵽�����ƥ�䲻���ˣ����ɣ�
	//��Ϊx��ʼ��-1����һ��Ҳûƥ��ɹ�ʱ��x��Ȼ��-1.
	while (t < tlen){
		if (T[t] == P[p]){
			t++; p++;
		}
		else{
			t = t - p + 1;
			p = 0;
		}
		//�ؼ���ÿ�ζ�����Ƿ�ƥ���ˣ����Ҹ���ƥ��λ��
		if (p == plen){
			x = t - p + 1;
		}
	}
	return x;
}

int main(){
	char* T = new char[20];
	char* P = new char[20];
	cout << "����T ";
	gets(T);
	cout << "����P ";
	gets(P);
	int flag = NaiveStrMatching(T, P);
	cout << "ƥ������λ���� " << flag << endl;
}