#include<iostream>
#include<cstring>
using namespace std;

int NaiveStrMatching(char* T, char* P){
	int p = 0, t = 0, x=-1;
	int plen = strlen(P);
	int tlen = strlen(T);
	if (tlen < plen)
		return -1;	//目标串比模式串短
	//与朴素模式匹配不同的是，扫描整个目标串，即使匹配了还继续向下扫描
	//每比较一个字符后，就判断模式串是否匹配成功，成功一次，就更新一次成功的位置
	//扫描完目标串后，直接返回最新的成功位置（一般不在后面，一般到后面就匹配不上了）即可，
	//因为x初始是-1，当一次也没匹配成功时，x仍然是-1.
	while (t < tlen){
		if (T[t] == P[p]){
			t++; p++;
		}
		else{
			t = t - p + 1;
			p = 0;
		}
		//关键是每次都检查是否匹配了，并且更新匹配位置
		if (p == plen){
			x = t - p + 1;
		}
	}
	return x;
}

int main(){
	char* T = new char[20];
	char* P = new char[20];
	cout << "输入T ";
	gets(T);
	cout << "输入P ";
	gets(P);
	int flag = NaiveStrMatching(T, P);
	cout << "匹配的最后位置是 " << flag << endl;
}