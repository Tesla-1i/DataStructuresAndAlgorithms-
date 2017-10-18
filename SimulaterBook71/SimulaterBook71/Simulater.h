#include"User_BankWindow.h"

#ifndef SIMULATER
#define SIMULATER

class Simulater{
public:
	queue<NormalUser> NormalUserQueue;
	queue<VIPUser> VIPUserQueue;
	queue<OfficialUser> OfficialUserQueue;
	vector<NormalBankWindow> nbw;
	vector<VIPBankWindow> vbw;
	vector<OfficialBankWindow> obw;
	Simulater(){}
	bool isServed(int time, User user){
		if (time - user.serverTime >= serveTime)
			return true;
		return false;
	}
	void simulaterCustomerEnter(User user); 

	void callCustomer(User& user, BankWindow& bankWindow, int time);
	void simulaterCallCustomer(int time);

	void initialize();
	void simulate();
};

#endif

void Simulater::simulaterCustomerEnter(User user){
	if (user.type == "普通用户"){
		this->NormalUserQueue.push((NormalUser&)user);
	}
	else if (user.type == "VIP用户"){
		this->VIPUserQueue.push((VIPUser&)user);
	}
	else{
		this->OfficialUserQueue.push((OfficialUser&)user);
	}
	cout << user.type << user.id << "进入银行（队列）\n";
}

void Simulater::callCustomer(User& user, BankWindow& bankWindow, int time){
	if (bankWindow.isBusy)	return;
	else{
		bankWindow.client = user;
		bankWindow.isBusy = true;
		user.serverTime = time;
		user.waitTime = time - user.arriveTime;
		cout << "请" << user.type << user.id << "到" << bankWindow.type << bankWindow.id << "办理业务\n";
	}
}
void Simulater::simulaterCallCustomer(int time){
	for (int i = 0; i < nbw.size(); i++){
		if ((nbw[i].isBusy&&this->isServed(time, nbw[i].client)) || !(nbw[i].isBusy)){
			if (nbw[i].isBusy&&this->isServed(time, nbw[i].client)){
				nbw[i].client.getServed();
			}
			nbw[i].isBusy = false;
			nbw[i].client.id = -1;
			if (!this->NormalUserQueue.empty()){
				NormalUser nuser = this->NormalUserQueue.front();
				this->NormalUserQueue.pop();
				this->callCustomer(nuser, nbw[i], time);
			}
		}
		else{
			nbw[i].handleUser();
		}
	}
	for (int i = 0; i < vbw.size(); i++){
		if ((vbw[i].isBusy&&this->isServed(time, vbw[i].client)) || !(vbw[i].isBusy)){
			if (vbw[i].isBusy&&this->isServed(time, vbw[i].client)){
				vbw[i].client.getServed();
			}
			vbw[i].isBusy = false;
			vbw[i].client.id = -1;
			if (this->VIPUserQueue.empty()){
				if (!this->NormalUserQueue.empty()){
					NormalUser nuser = this->NormalUserQueue.front();
					this->NormalUserQueue.pop();
					this->callCustomer(nuser, vbw[i], time);
				}
			}
			else{
				VIPUser vuser = this->VIPUserQueue.front();
				this->VIPUserQueue.pop();
				this->callCustomer(vuser, vbw[i], time);
			}
		}
		else{
			vbw[i].handleUser();
		}
	}
	for (int i = 0; i < obw.size(); i++){
		if ((obw[i].isBusy&&this->isServed(time, obw[i].client)) || !(obw[i].isBusy)){
			if (obw[i].isBusy&&this->isServed(time, obw[i].client)){
				obw[i].client.getServed();
			}
			obw[i].isBusy = false;
			obw[i].client.id = -1;
			if (this->OfficialUserQueue.empty()){
				if (!this->NormalUserQueue.empty()){
					NormalUser nuser = this->NormalUserQueue.front();
					this->NormalUserQueue.pop();
					this->callCustomer(nuser, obw[i], time);
				}
			}
			else{
				OfficialUser ouser = this->OfficialUserQueue.front();
				this->OfficialUserQueue.pop();
				this->callCustomer(ouser, obw[i], time);
			}
		}
		else{
			obw[i].handleUser();
		}
	}
}

void Simulater::initialize(){
	NormalUser nuser(-1, 0, 0, 0);
	NormalBankWindow nbw1(1, false, nuser);
	NormalBankWindow nbw2(2, false, nuser);
	NormalBankWindow nbw3(3, false, nuser);
	VIPBankWindow vbw1(4, false, nuser);
	OfficialBankWindow obw1(5, false, nuser);
	nbw.push_back(nbw1);
	nbw.push_back(nbw2);
	nbw.push_back(nbw3);
	vbw.push_back(vbw1);
	obw.push_back(obw1);
}
void Simulater::simulate(){
	int id = 1;	//真正用户的id
	initialize();
	for (int i = 0; i <= 12; i += timeInterval){
		cout << i << "s: \n";
		if (i == 0){
			for (int j = 0; j < 3; j++){
				NormalUser nu(id++, 0, i, 0);
				this->simulaterCustomerEnter(nu);
			}
			VIPUser vu(id++, 0, 0, 0);
			this->simulaterCustomerEnter(vu);
			OfficialUser ou(id++, 0, 0, 0);
			this->simulaterCustomerEnter(ou);
		}
		if (i == 2){
			for (int j = 0; j < 5; j++){
				NormalUser nu(id++, 0, i, 0);
				this->simulaterCustomerEnter(nu);
			}
		}
		if (i == 6){
			for (int j = 0; j < 5; j++){
				NormalUser nu(id++, 0, i, 0);
				this->simulaterCustomerEnter(nu);
			}
			VIPUser vu(id++, 0, i, 0);
			this->simulaterCustomerEnter(vu);
		}

		simulaterCallCustomer(i);

		if (NormalUserQueue.empty() && VIPUserQueue.empty() && OfficialUserQueue.empty()){
			cout << "没有用户正在排队\n";
		}
		else{
			cout << "有" << NormalUserQueue.size() + VIPUserQueue.size() + OfficialUserQueue.size() << "个用户在排队\n";
		}
		Sleep(2000);
	}
}
