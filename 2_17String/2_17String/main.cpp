#include<iostream>
#include<cstdio>
using namespace std;

int Strcmp(char* s1, char* s2){
	int count = 0;
	while (s1[count] != '\0'&&s2[count] != '\0'){
		if (s1[count] > s2[count])
			return 1;
		else if (s1[count] < s2[count])
			return -1;
		count++;
	}
	if (s1[count] == '\0'&&s2[count] != '\0')
		return -1;
	else if (s1[count] != '\0'&&s2[count] == '\0')
		return 1;
	return 0;
}

int main(){
	char* s = new char[10];
	char* t = new char[10];
	cout << "ÊäÈë×Ö·û´®s\n";
	gets(s);
	cout << "ÊäÈë×Ö·û´®t\n";
	gets(t);
	int flag = Strcmp(s, t);
	switch (flag){
	case -1:cout << "s<t\n"; break;
	case 1:cout << "s>t\n"; break;
	case 0:cout << "s==t\n"; break;
	}
	return 0;
}