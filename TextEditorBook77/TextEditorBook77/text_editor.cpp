#include"text_editor.h"

int main() {

	TextEditor text;
	cout << "����������,���������ı�\n";
	for (int ii = 0; ii < 3; ii++) 
		cin >> text;
	cout << "���������\n";
	cout << text;
	cout << "���Լ���\n";
	int a1, a2, a3, a4, a5;
	text.WordStat(a1, a2, a3, a4, a5);
	cout << "���� ��ĸ ���� �ո� ���\n";
	cout << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << "\n";
	cout << "�ַ����� " << text.total << "\n";
	text.cursor.line = text.article.size();
	list<string>::iterator itt = text.article.end();
	itt--;
	text.cursor.offset = (*itt).length();
	cout << "���λ�� " << text.cursor.line << " " << text.cursor.offset << "\n";
	cout << "�����ƶ���꣬����ο�λ��(1,2,3)��ƫ����: ";
	int ori, off;
	cin >> ori >> off;
	text.MoveCursor(ori, off);
	cout << "���λ�� " << text.cursor.line << " " << text.cursor.offset << "\n";
	cout << "���������ı�\n";
	string s;
	cin >> s;
	text.InsertText(s);
	cout<<"�ı�\n" << text;
	cout << "������Ҳ�ɾ�����ı�\n";
	string ss;
	cout << "������ҵ��Ӵ�: ";
	cin >> ss;
	Cursor c(0, 0);
	bool b = text.FindText(ss, c);
	if (b == true) {
		cout << "��һ���Ӵ���λ��: ";
		cout << c.line << " " << c.offset;
		cout << "\nɾ��������Ӵ�\n";
		text.DeleteText(ss);
		cout << text;
	}
	cout << "����ɾ����λ��((1,0)��ʼ����ɾ���ĳ���\n";
	int cl, co;
	int le;
	cin >> cl >> co >> le;
	c.line = cl;
	c.offset = co;
	text.DeleteText(c, le+1);	//bug�����ò�le+1,ԭ����le
	cout << text;


	//TextEditor text;
	//string s = "qwe12er";
	//string s1 = "asd\nfs,,df zxc";
	//text.InsertText(s);
	//text.InsertText(s1);
	//list<string>::iterator Iterator = text.article.begin();
	//cout << (*Iterator)<<"\n";
	//Iterator++;
	//cout << (*Iterator) << "\n";
	//Iterator++;
	//cout << (*Iterator) << "\n";
	//cout << (text.total) << "\n";

	//int a1, a2, a3, a4, a5;
	//text.WordStat(a1, a2, a3, a4, a5);
	//cout << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << "\n";

	//text.MoveCursor(2, -12);	//�ĵ���������ǰ12
	//cout << (text.cursor.line) << " " << (text.cursor.offset);

	//cout << "\n��(1,2)��ʼɾ���ַ�����10\n";
	//Cursor c(1, 2);
	//text.DeleteText(c, 10);
	//cout << "����"<<(text.total) << "\n";
	//cout <<" ���ڹ��"<<(text.cursor.line) << " " << (text.cursor.offset) << "\n";
	//list<string>::iterator iterator1 = text.article.begin();
	////cout << (*iterator1) << "\n";
	//
	//list<string>::iterator IT1 = iterator1;
	//text.article.erase(++iterator1);	//bug���ڡ�ɾ��  \n
	//iterator1 = IT1;

	//Cursor c1;
	//string ss = "a";
	//string ss1 = "sad";
	//text.InsertText(ss);
	//text.InsertText(ss1);
	////cout << (*iterator1) << "\n";
	////text.InsertText(ss1);
	////iterator1++;
	////cout << (*iterator1) << "\n";
	////iterator1++;
	////cout << (*iterator1) << "\n";
	///*text.FindText(ss, c1);
	//cout<<"\n" << c1.line << " " << c1.offset << "\n";*/
	//cout << text;
	//cout << "�ٲ��뼸�����: ";
	//int nu;
	//cin >> nu;
	//for (int i = 0; i < nu; i++)
	//	cin >> text;
	//cout << "���ڵ��ı�\n";
	//cout << text;
	//cout << "������ҵ��Ӵ�: ";
	//cin >> ss;
	//bool b = text.FindText(ss, c);
	//if (b == true) {
	//	cout << "�Ӵ���λ��: ";
	//	cout << c.line << " " << c.offset;
	//	cout << "\nɾ��������Ӵ�\n";
	//	text.DeleteText(ss);
	//	cout << text;
	//}
	return 0;
}


