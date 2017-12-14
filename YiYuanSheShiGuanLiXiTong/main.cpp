/*
* ҽԺ��ʩ����ϵͳ
* ��ҽԺ�ĸ�����ʩ�Ĺ�ϵ����������ͳ�ƺ���ʾ
* �����в����µ���ʩ��ͳ����ʩ����������ʾ��ʩ�ȹ���
*/
#include<iostream>
#include<queue>
#include<string>
#include<stack>
using namespace std;

//ҽԺ��ʩ��
class HosPartNode{
private:
	int num;
	string name;
public:
	HosPartNode(string n="null", int number=1){
		name=n;
		num=number;
	}
	int getNum(){
		return num;
	}
	void setNum(int number){
		num=number;
	}
	string getName(){
		return name;
	}
	void setName(string n){
		name=n;
	}
	friend ostream &operator<< (ostream& out,HosPartNode &node){
		out << node.getName()<<":"<<node.getNum();
		return out;
	}
};

//����-�ֵܱ�ʾ�����������ڵ���
class TreeNode{
private:
	HosPartNode m_value;
	TreeNode *FirstLeftChild;
	TreeNode *RightBrother;
public:
	TreeNode(HosPartNode value,TreeNode *FLChild=NULL,TreeNode *RBrother=NULL){
		m_value.setName(value.getName());
		m_value.setNum(value.getNum());
		FirstLeftChild=FLChild;
		RightBrother=RBrother;
	}
	HosPartNode getValue(){
		return m_value;
	}
	TreeNode *getChild(){
		return FirstLeftChild;
	}
	TreeNode *getBrother(){
		return RightBrother;
	}
	void setValue(HosPartNode value){
		m_value.setName(value.getName());
		m_value.setNum(value.getNum());
	}
	void setChild(TreeNode *pointer){
		FirstLeftChild=pointer;
	}
	void setBrother(TreeNode *pointer){
		RightBrother=pointer;
	}
	void InsertFirst(TreeNode *node){
		FirstLeftChild=node;
	}
	void InsertBrother(TreeNode *node){
		RightBrother=node;
	}
	void printNode(){
		stack<TreeNode*>s;
		TreeNode *pointer=FirstLeftChild;
		cout<<m_value<<endl;
		while(!s.empty() || pointer)
		{
			if(pointer)
			{
				cout<<(pointer->getValue().getName())<<endl;
				//pointer->getValue();
				if(pointer->getBrother()!=NULL)
					s.push(pointer->getBrother());
				pointer=pointer->getChild();
			}
			else
			{
				pointer=s.top();
				s.pop();
			}
		}
	}
};

// ��ʩ����
class Tree{
private:
	TreeNode *root;
public:
	Tree(){
		root=NULL;
	}
	Tree(TreeNode *node){
		root=node;
	}
	TreeNode *getRoot(){
		return root;
	}
	//��ȡ��ǰ�ڵ�ĸ��ڵ�
	TreeNode *Parent(TreeNode *current){
		queue<TreeNode *> aQueue;
		TreeNode *pointer=root,*parent=NULL;
		if(!current)                                //Ŀ��ڵ�Ϊ��
			return NULL;
		else if(pointer==current)                   //Ŀ��ڵ��Ǹ��ڵ�
			return NULL;
		else                                        //Ŀ��ڵ���ڲ��Ҳ��Ǹ��ڵ�
		{
			aQueue.push(pointer);
			while(!aQueue.empty())
			{
				parent=aQueue.front();
				pointer=parent->getChild();
				while(pointer)
				{
					if(pointer==current)
					{
						return parent;
					}
					aQueue.push(pointer);
					pointer=pointer->getBrother();
				}
				aQueue.pop();
			}
		}
	}
	//����ֵΪcurrent�Ľڵ�
	TreeNode *Find(string current){
		queue<TreeNode *> aQueue;
		TreeNode *pointer=root;
		if(current=="\0")
			return NULL;
		else{
			while(pointer){
				if(pointer->getValue().getName()==current)
					return pointer;
				else{
					aQueue.push(pointer);
					pointer=pointer->getBrother();
				}
			}
			while(!aQueue.empty()){
				pointer=aQueue.front()->getChild();
				aQueue.pop();
				while(pointer){
					if(pointer->getValue().getName()==current)
						return pointer;
					else{
						aQueue.push(pointer);
						pointer=pointer->getBrother();
					}
				}
			}
			return NULL;
		}
	}
	//����ڵ�
	void Insert(string parent,HosPartNode rootVlaue){
		HosPartNode h(parent);
		if(!root){
			root=new TreeNode(h);
			root->setChild(new TreeNode(rootVlaue));
		}
		else{
			TreeNode *temp=Find(parent);
			if(temp->getChild()){
				temp=temp->getChild();
				while(temp->getBrother())
				{
					temp=temp->getBrother();
				}
				temp->setBrother(new TreeNode(rootVlaue));
			}
			else
				temp->setChild(new TreeNode(rootVlaue));
		}
	}
	//�ȸ�����
	void RootFirstTraverse(TreeNode *root){
		if(root!=NULL)
		{
			cout<<root->getValue().getName()<<endl;
			RootFirstTraverse(root->getChild());
			RootFirstTraverse(root->getBrother());
		}
	}
	//�������
	void RootLastTraverse(TreeNode *root){
		if(root!=NULL)
		{
			RootLastTraverse(root->getChild());
			cout<<root->getValue().getName()<<endl;
			RootLastTraverse(root->getBrother());
		}
	}
	//������ȱ���
	void WithTraverse(TreeNode *root){
		queue<TreeNode *>q;
		TreeNode *pointer=root;
		if(pointer)
			q.push(pointer);
		while(!q.empty())
		{
			pointer=q.front();
			cout<<pointer->getValue().getName()<<endl;
			q.pop();
			pointer=pointer->getChild();
			while(pointer)
			{
				q.push(pointer);
				pointer=pointer->getBrother();
			}
		}
	}
	//ͳ��parent����child������
	int Count(string parent,string child){
		TreeNode *p=Find(parent),*c=Find(child);
		if(!p||!c)
			return 0;
		else{
			int Num=1;
			TreeNode *direParent=Parent(c);
			if(!direParent)
				return 0;
			else{
				Num*=c->getValue().getNum();
				while(parent!=direParent->getValue().getName()){
					Num*=direParent->getValue().getNum();
					direParent=Parent(direParent);
				}
				return Num;
			}
		}
	}
};

int main(){
	Tree Hospital;
	// ����ҽԺ�ڵ㣬����ӵ�ҽԺ����
	HosPartNode h0("ҽԺ");
	HosPartNode h1("¥��",10);
	HosPartNode h2("�������",1);
	HosPartNode h3("��¥",4);
	HosPartNode h4("����",1);
	HosPartNode h5("ɳ��",2);
	HosPartNode h6("������",2);
	HosPartNode h7("��������",1);
	HosPartNode h8("����",21);
	HosPartNode h9("�ⷿ",5);
	HosPartNode h10("������",1);
	HosPartNode h11("����",4);
	HosPartNode h12("����",2);
	HosPartNode h13("ϴ����",1);
	HosPartNode h14("������",1);
	HosPartNode h15("���",2);
	HosPartNode h16("���",1);
	Hospital.Insert(h0.getName(),h1);
	Hospital.Insert(h1.getName(),h2);
	Hospital.Insert(h1.getName(),h3);
	Hospital.Insert(h2.getName(),h4);
	Hospital.Insert(h2.getName(),h5);
	Hospital.Insert(h3.getName(),h6);
	Hospital.Insert(h3.getName(),h7);
	Hospital.Insert(h6.getName(),h8);
	Hospital.Insert(h7.getName(),h9);
	Hospital.Insert(h8.getName(),h10);
	Hospital.Insert(h8.getName(),h11);
	Hospital.Insert(h8.getName(),h12);
	Hospital.Insert(h10.getName(),h13);
	Hospital.Insert(h10.getName(),h14);
	Hospital.Insert(h11.getName(),h15);
	Hospital.Insert(h11.getName(),h16);
	TreeNode *result=NULL;
	int select;
	string s1,s2;
	while(1)
	{
		cout<<"---------------------ҽԺ��ʩ����ϵͳ---------------------"<<endl;
		cout<<"1.��������ʩ  2.ͳ������  3.������ʩ  4.���ȫ��  0.�˳�ϵͳ"<<endl;
		cin>>select;
		switch(select)
		{
		case 0: return 0;
		case 1:{
			int num;
			cout<<"���븸��λ����"<<endl;
			cin>>s1;
			cout<<"������ʩ����"<<endl;
			cin>>s2;
			cout<<"������ʩ����"<<endl;
			cin>>num;
			HosPartNode newNode(s2,num);
			Hospital.Insert(s1,newNode);
			break;
			   }
		case 2:{
			cout<<"���븸��λ����"<<endl;
			cin>>s1;
			cout<<"������ʩ����"<<endl;
			cin>>s2;
			cout<<s1<<"�а���"<<s2<<"������Ϊ"<<Hospital.Count(s1,s2)<<endl;
			break;
			   }
		case 3:{
			cout<<"���������ʩ���ƣ�"<<endl;
			cin>>s1;
			result=Hospital.Find(s1);
			cout<<"���ҽ��Ϊ��"<<endl;
			if(!result)
				cout<<"δ�ҵ���"<<endl;
			else
				result->printNode();
			break;
			   }
		case 4:{
			cout<<"������ȱ�����"<<endl;
			Hospital.WithTraverse(Hospital.getRoot());
			break;
			   }
		}
	}

}

