#pragma once

#include<iostream>
#include <queue>
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
using namespace std;

//ÿ���û��ķ���ʱ��
int serveTime = 4;

//ʱ����
int timeInterval = 2;

#ifndef USERBANK
#define USERBANK

//�û���
class User {
public:

	//�û�ID
	int id;
	//�ȴ�ʱ��
	int isWait;
	//����ʱ��
	int arriveTime;
	//��ʼ����ʱ��
	int serveTime;
	//�û�����
	char *type;
	//���캯��
	User() { type = NULL; }
	User(int id, int isWait, int arriveTime, int serveTime, char *type) {

		this->id = id;
		this->isWait = isWait;
		this->arriveTime = arriveTime;
		this->serveTime = serveTime;
		this->type = type;
	}

	//�������
	void getServed() { cout << this->type << this->id << "�Ѿ���������ϣ��뿪���С�" << endl; }
};

//��ͨ�û�
class NormalUser : public User {
public:
	NormalUser() {}
	NormalUser(int id, int isWait, int arriveTime, int serveTime) :User(id, isWait, arriveTime, serveTime, "��ͨ�û�")
	{}
	void getServed() { cout << this->type << this->id << "�Ѿ���������ϣ��뿪���С�" << endl; }
};

//VIP�û�
class VIPUser : public User {
public:
	VIPUser() :User() {}
	VIPUser(int id, int isWait, int arriveTime, int serveTime) :User(id, isWait, arriveTime, serveTime, "VIP�û�") {}
	void getServed() {
		cout << this->type << this->id << "�Ѿ���������ϣ��뿪���С�" << endl;
	}
};

//�����û�
class OfficialUser : public User {
public:
	OfficialUser() :User() {}
	OfficialUser(int id, int isWait, int arriveTime, int serveTime) :User(id, isWait, arriveTime, serveTime, "�����û�") {}
	void getServed() { cout << this->type << this->id << "�Ѿ���������ϣ��뿪���С�" << endl; }
};

//������
class BankWindow {
public:
	//�����Ƿ�æ
	bool isBusy;
	//����ID
	int id;
	//�û�
	User client;
	//��������
	char *type;
	//���캯��
	BankWindow() { type = NULL; }
	BankWindow(bool isBusy, int id, User client, char *type) {
		this->isBusy = isBusy;
		this->id = id;
		this->client = client;
		this->type = type;
	}
	//�����û�����
	void HandleUser() { cout << this->type << this->id << "����Ϊ" << this->client.type << this->client.id << "����" << endl; }
};

//��ͨ����
class NormalBankWindow : public BankWindow {
public:
	NormalBankWindow() :BankWindow() {}
	NormalBankWindow(bool isBusy, int id, User client) :BankWindow(isBusy, id, client, "��ͨ����") {}
	void HandleUser() {
		cout << this->type << this->id << "����Ϊ" << this->client.type << this->client.id << "����" << endl;
	}
};

//VIP����
class VIPBankWindow : public BankWindow {
public:
	VIPBankWindow() :BankWindow() {}
	VIPBankWindow(bool isBusy, int id, User client) :BankWindow(isBusy, id, client, "VIP����") {}
	void HandleUser() {
		cout << this->type << this->id << "����Ϊ" << this->client.type << this->client.id << "����" << endl;
	}
};

//���ô���
class OfficialBankWindow : public BankWindow {
public:
	OfficialBankWindow() :BankWindow() {}
	OfficialBankWindow(bool isBusy, int id, User client) :BankWindow(isBusy, id, client, "���ô���") {}
	void HandleUser() {
		cout << this->type << this->id << "����Ϊ" << this->client.type << this->client.id << "����" << endl;
	}
};

#endif