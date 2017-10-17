#pragma once

#include<iostream>
#include <queue>
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
using namespace std;

//每个用户的服务时间
int serveTime = 4;

//时间间隔
int timeInterval = 2;

#ifndef USERBANK
#define USERBANK

//用户类
class User {
public:

	//用户ID
	int id;
	//等待时间
	int isWait;
	//到达时间
	int arriveTime;
	//开始服务时间
	int serveTime;
	//用户类型
	char *type;
	//构造函数
	User() { type = NULL; }
	User(int id, int isWait, int arriveTime, int serveTime, char *type) {

		this->id = id;
		this->isWait = isWait;
		this->arriveTime = arriveTime;
		this->serveTime = serveTime;
		this->type = type;
	}

	//服务完毕
	void getServed() { cout << this->type << this->id << "已经被服务完毕，离开银行。" << endl; }
};

//普通用户
class NormalUser : public User {
public:
	NormalUser() {}
	NormalUser(int id, int isWait, int arriveTime, int serveTime) :User(id, isWait, arriveTime, serveTime, "普通用户")
	{}
	void getServed() { cout << this->type << this->id << "已经被服务完毕，离开银行。" << endl; }
};

//VIP用户
class VIPUser : public User {
public:
	VIPUser() :User() {}
	VIPUser(int id, int isWait, int arriveTime, int serveTime) :User(id, isWait, arriveTime, serveTime, "VIP用户") {}
	void getServed() {
		cout << this->type << this->id << "已经被服务完毕，离开银行。" << endl;
	}
};

//公用用户
class OfficialUser : public User {
public:
	OfficialUser() :User() {}
	OfficialUser(int id, int isWait, int arriveTime, int serveTime) :User(id, isWait, arriveTime, serveTime, "公用用户") {}
	void getServed() { cout << this->type << this->id << "已经被服务完毕，离开银行。" << endl; }
};

//窗口类
class BankWindow {
public:
	//窗口是否繁忙
	bool isBusy;
	//窗口ID
	int id;
	//用户
	User client;
	//窗口类型
	char *type;
	//构造函数
	BankWindow() { type = NULL; }
	BankWindow(bool isBusy, int id, User client, char *type) {
		this->isBusy = isBusy;
		this->id = id;
		this->client = client;
		this->type = type;
	}
	//处理用户服务
	void HandleUser() { cout << this->type << this->id << "正在为" << this->client.type << this->client.id << "服务" << endl; }
};

//普通窗口
class NormalBankWindow : public BankWindow {
public:
	NormalBankWindow() :BankWindow() {}
	NormalBankWindow(bool isBusy, int id, User client) :BankWindow(isBusy, id, client, "普通窗口") {}
	void HandleUser() {
		cout << this->type << this->id << "正在为" << this->client.type << this->client.id << "服务" << endl;
	}
};

//VIP窗口
class VIPBankWindow : public BankWindow {
public:
	VIPBankWindow() :BankWindow() {}
	VIPBankWindow(bool isBusy, int id, User client) :BankWindow(isBusy, id, client, "VIP窗口") {}
	void HandleUser() {
		cout << this->type << this->id << "正在为" << this->client.type << this->client.id << "服务" << endl;
	}
};

//公用窗口
class OfficialBankWindow : public BankWindow {
public:
	OfficialBankWindow() :BankWindow() {}
	OfficialBankWindow(bool isBusy, int id, User client) :BankWindow(isBusy, id, client, "公用窗口") {}
	void HandleUser() {
		cout << this->type << this->id << "正在为" << this->client.type << this->client.id << "服务" << endl;
	}
};

#endif