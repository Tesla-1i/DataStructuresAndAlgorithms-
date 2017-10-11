#include<iostream>
#include<string>
#include<cstring>
using namespace std;

int NaiveStrMatching(string &T, string &P){
	int p = 0;
	int t = 0;
	int plen = P.length();
	int tlen = T.length();
	if (tlen < plen)
		return -1;
	while (p < plen&&t < tlen){
		if (T[t] == P[p]){
			t++; p++;
		}
		else{
			t = t - p + 1;
			p = 0;
		}
	}
	if (p >= plen)
		return(t - plen + 1);
	else
		return -1;
}

int main(){
	string T;
	string P;
	cout << "����Ŀ�괮\n";
	cin >> T;
	cout << "����ģʽ��\n";
	cin >> P;
	int flag = NaiveStrMatching(T, P);
	cout << flag << endl;
}