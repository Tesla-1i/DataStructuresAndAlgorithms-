#include<iostream>
#include<queue>
#include<vector>
#include<Windows.h>
using namespace std;

#ifndef USER
#define USER

int serveTime = 4;	//服务时间 4s
int timeInterval = 2;	//时间间隔

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
		cout << type << id << "接受完服务，离开银行\n";
	}
};
class NormalUser :public User{
public:
	NormalUser():User(){}
	NormalUser(int i, int w, int a, int s) :User(i, w, a, s, "普通用户"){}
};
class VIPUser :public User{
public:
	VIPUser():User(){}
	VIPUser(int i, int w, int a, int s) :User(i, w, a, s, "VIP用户"){}
};
class OfficialUser :public User{
public:
	OfficialUser():User(){}
	OfficialUser(int i, int w, int a, int s) :User(i, w, a, s, "对公用户"){}
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
		cout << type << id << "正在为" << (client.type) << (client.id) << "服务\n";
	}
};
class NormalBankWindow :public BankWindow{
public:
	NormalBankWindow() :BankWindow(){}
	NormalBankWindow(int i, bool b, User& c) :BankWindow(i, b, c, "普通窗口"){}
};
class VIPBankWindow :public BankWindow{
public:
	VIPBankWindow() :BankWindow(){}
	VIPBankWindow(int i, bool b, User& c) :BankWindow(i, b, c, "VIP窗口"){}
};
class OfficialBankWindow :public BankWindow{
public:
	OfficialBankWindow() :BankWindow(){}
	OfficialBankWindow(int i, bool b, User& c) :BankWindow(i, b, c, "对公窗口"){}
};

#endif