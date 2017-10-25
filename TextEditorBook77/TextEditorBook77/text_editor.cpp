#include"text_editor.h"

int main() {

	TextEditor text;
	cout << "测试输入流,输入三行文本\n";
	for (int ii = 0; ii < 3; ii++) 
		cin >> text;
	cout << "测试输出流\n";
	cout << text;
	cout << "测试计数\n";
	int a1, a2, a3, a4, a5;
	text.WordStat(a1, a2, a3, a4, a5);
	cout << "总数 字母 数字 空格 标点\n";
	cout << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << "\n";
	cout << "字符总数 " << text.total << "\n";
	text.cursor.line = text.article.size();
	list<string>::iterator itt = text.article.end();
	itt--;
	text.cursor.offset = (*itt).length();
	cout << "光标位置 " << text.cursor.line << " " << text.cursor.offset << "\n";
	cout << "测试移动光标，输入参考位置(1,2,3)和偏移量: ";
	int ori, off;
	cin >> ori >> off;
	text.MoveCursor(ori, off);
	cout << "光标位置 " << text.cursor.line << " " << text.cursor.offset << "\n";
	cout << "输入插入的文本\n";
	string s;
	cin >> s;
	text.InsertText(s);
	cout<<"文本\n" << text;
	cout << "输入查找并删除的文本\n";
	string ss;
	cout << "输入查找的子串: ";
	cin >> ss;
	Cursor c(0, 0);
	bool b = text.FindText(ss, c);
	if (b == true) {
		cout << "第一个子串的位置: ";
		cout << c.line << " " << c.offset;
		cout << "\n删除输入的子串\n";
		text.DeleteText(ss);
		cout << text;
	}
	cout << "输入删除的位置((1,0)开始）及删除的长度\n";
	int cl, co;
	int le;
	cin >> cl >> co >> le;
	c.line = cl;
	c.offset = co;
	text.DeleteText(c, le+1);	//bug，不得不le+1,原来是le
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

	//text.MoveCursor(2, -12);	//文档结束处向前12
	//cout << (text.cursor.line) << " " << (text.cursor.offset);

	//cout << "\n从(1,2)开始删除字符长度10\n";
	//Cursor c(1, 2);
	//text.DeleteText(c, 10);
	//cout << "总数"<<(text.total) << "\n";
	//cout <<" 现在光标"<<(text.cursor.line) << " " << (text.cursor.offset) << "\n";
	//list<string>::iterator iterator1 = text.article.begin();
	////cout << (*iterator1) << "\n";
	//
	//list<string>::iterator IT1 = iterator1;
	//text.article.erase(++iterator1);	//bug所在。删除  \n
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
	//cout << "再插入几个结点: ";
	//int nu;
	//cin >> nu;
	//for (int i = 0; i < nu; i++)
	//	cin >> text;
	//cout << "现在的文本\n";
	//cout << text;
	//cout << "输入查找的子串: ";
	//cin >> ss;
	//bool b = text.FindText(ss, c);
	//if (b == true) {
	//	cout << "子串的位置: ";
	//	cout << c.line << " " << c.offset;
	//	cout << "\n删除输入的子串\n";
	//	text.DeleteText(ss);
	//	cout << text;
	//}
	return 0;
}


