#include<iostream>
#include<queue>
#include<vector>
#include<Windows.h>
using namespace std;

#ifndef USER
#define USER

int serveTime = 4;	//����ʱ�� 4s
int timeInterval = 2;	//ʱ����

class User{
public:
	int id;
	int waitTime;
	int arriveTime;
	int serverTime;
	char* type;
	User(){ type = NULL; }
	User(int i, int w, int a, int s, char* t){
		id = i;	waitTime = w; arriveTime = a; serverTime = s;
		type = t;
	}
	void getServed(){
		cout << type << id << "����������뿪����\n";
	}
};
class NormalUser :public User{
public:
	NormalUser():User(){}
	NormalUser(int i, int w, int a, int s) :User(i, w, a, s, "��ͨ�û�"){}
};
class VIPUser :public User{
public:
	VIPUser():User(){}
	VIPUser(int i, int w, int a, int s) :User(i, w, a, s, "VIP�û�"){}
};
class OfficialUser :public User{
public:
	OfficialUser():User(){}
	OfficialUser(int i, int w, int a, int s) :User(i, w, a, s, "�Թ��û�"){}
};

class BankWindow{
public:
	int id;
	bool isBusy;
	User client;
	char* type;
	BankWindow(){ type = NULL; }
	BankWindow(int i, bool b, User& c, char* t){
		id = i; isBusy = b; client = c; type = t;
	}
	void handleUser(){
		cout << type << id << "����Ϊ" << (client.type) << (client.id) << "����\n";
	}
};
class NormalBankWindow :public BankWindow{
public:
	NormalBankWindow() :BankWindow(){}
	NormalBankWindow(int i, bool b, User& c) :BankWindow(i, b, c, "��ͨ����"){}
};
class VIPBankWindow :public BankWindow{
public:
	VIPBankWindow() :BankWindow(){}
	VIPBankWindow(int i, bool b, User& c) :BankWindow(i, b, c, "VIP����"){}
};
class OfficialBankWindow :public BankWindow{
public:
	OfficialBankWindow() :BankWindow(){}
	OfficialBankWindow(int i, bool b, User& c) :BankWindow(i, b, c, "�Թ�����"){}
};

#endif