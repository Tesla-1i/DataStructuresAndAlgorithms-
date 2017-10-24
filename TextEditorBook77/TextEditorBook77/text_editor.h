#include<iostream>
#include<list>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

#ifndef TEXTEDITOR
#define TEXTEDITOR

//光标类(实际是位置类)，所在行，偏移量
class Cursor {
public:
	int line;	
	int offset;
	Cursor() { line = 1; offset = 0; }
	Cursor(int l,int o):line(l),offset(o){}
};
//文本编辑器类
class TextEditor {
public:
	list<string> article;	//文本用结点是string的链表存储，每一行作为一个结点
	Cursor cursor;	//一个编辑器只一个光标
	int total;	//文本总字数
	string name;	//文本名字
public:
	TextEditor() { total = 0; }
	~TextEditor() { article.clear(); }
	string& GetName() { return name; }
	void SetName(string& name) { this->name = name; }
	int GetTotalBeforeCursor();

	friend ostream& operator<<(ostream& out, TextEditor& editor);
	friend istream& operator>>(istream& in, TextEditor& editor);
	
	//计数函数，（总数，字母数，数字数，空格数，标点数）
	void WordStat(int &pTotal, int &pLetter, int &pDigit, int &pSpace, int &pQuot);

	//得到，设置，移动光标位置
	void GetCursor(int &pLine, int &pOffset) { pLine = cursor.line; pOffset = cursor.offset; }
	void SetCursor(int line, int offset) { cursor.line = line; cursor.offset = offset; }
	//origin是参考位置，分别是文档开始，文档结束，文档当前光标位置；offset是偏移量
	//origin={1,2,3}之一
	void MoveCursor(int origin, int offset);

	//追加，插入文本；查找文本；删除文本
	//void AddText(string &text);
	void InsertText(string& text);	//在光标处插入文本,(现在实际情况行末插入多行)
	bool FindText(string& text,Cursor& cursor);
	bool DeleteText(string& text);	//先查找匹配后，再删除
	bool DeleteText(Cursor origin,int length);	//从给定光标（位置,不是文档的光标）处删除length个字符
};

#endif // !TEXTEDITOR

//取得当前光标之文档开头的偏移总量
int TextEditor::GetTotalBeforeCursor() {
	list<string>::iterator Iterator = article.begin();	//迭代器,泛化的指针
	int tempTotalBeforeCursor = 0;	//初始0
	for (int i = 1; i < cursor.line; i++) {
		tempTotalBeforeCursor += (*Iterator).length();	//调用string的length()函数
		Iterator++;
	}
	tempTotalBeforeCursor += cursor.offset;
	return tempTotalBeforeCursor;
}

//移动光标（位置）
void TextEditor::MoveCursor(int origin, int offset) {
	//临时的之于文档开头的偏移量TempOffset,TempLine最后赋给cursor.line,所以初始为1.
	int TempOffset = 0, TempLine = 1;
	switch (origin)
	{
	case 1:TempOffset = offset; break;	//文档开始处
	case 2:TempOffset = total + offset; break;	//文档结束处，offset可能是负数
	case 3:TempOffset = GetTotalBeforeCursor() + offset; break;	//当前光标处
	default: cout << "参考位置出错\n"; exit(-1);
	}
	if (TempOffset < 0) {
		TempOffset = 0;	cout << "之于文档开头偏移量小于0，已重置为0\n";
	}
	//list<string>::reverse_iterator rIterator = article.rbegin();
	list<string>::iterator Iterator = article.begin();
	while (1) {
		if (TempOffset > (*Iterator).length()) {	//偏移量大于本行长度
			TempOffset -= (*Iterator).length();
			TempLine++;
		}
		if (Iterator == (--article.end())) break;	//本行是最后一行
		Iterator++;	//取下一行
	}
	cursor.line = TempLine;
	cursor.offset = TempOffset;
}

//统计字符总数，字母，数字，空格，标点总数
void TextEditor::WordStat(int & pTotal, int & pLetter, int & pDigit, int & pSpace, int & pQuot)
{
	pTotal = 0; pLetter = 0; pDigit = 0; pSpace = 0; pQuot = 0;
	list<string>::iterator Iterator = article.begin();
	while (Iterator!=article.end())
	{
		for (int i = 0; i < (*Iterator).length(); pTotal++,i++) {
			//<=97 大Bug
			if ((*Iterator)[i] >= 65 && (*Iterator)[i] <= 90 || (*Iterator)[i] >= 97 && (*Iterator)[i] <= 122)
				pLetter++;
			else if ((*Iterator)[i] >= 48 && (*Iterator)[i] <= 57)
				pDigit++;
			else if ((*Iterator)[i] == 32)
				pSpace++;
			else
				pQuot++;
		}
		//大Bug
		Iterator++;
	}
}

void TextEditor::InsertText(string &text) {
	bool b = false;
	int backNum = 0;
	int backAddress[20];
	for (int i = 0,j=0; i < text.length(); i++) {
		if (text[i] == '\n') {
			b = true; backNum++;
			backAddress[j] = i; j++;
		}
	}
	string *s;
	string s1;
	int k, n = 0;
	if (backNum != 0) {	//文本中包含换行符
		s = new string[backNum + 1];	//中间一个空格，分为两个串
		for (k = 0; k < backNum; k++) {
				s[k] = text.substr(n, backAddress[k] - n);
				n = backAddress[k] + 1;
		}
		s[k] = text.substr(n, text.length() - n);
		cout << "*****\n";
	}
	else {	//不包含换行符
		 s1 = text;
		 //cout << "2";
	}
	///////////////////////////////
	if (backNum != 0) {
		for (int m = 0; m < backNum + 1; m++) {
			article.push_back(s[m]);	//不是s[k]
			total += s[m].length();		//总字数
		}
		cursor.line += (backNum + 1);
		cursor.offset = s[backNum].length();
		//cout << "3";
	}
	else {
		article.push_back(s1);
		total += s1.length();	//总字数
		cursor.line++;
		cursor.offset = s1.length();
		//cout << "4";
		//list<string>::iterator Iterator = article.begin();
		//for (int i = 0; i < cursor.line; i++)
		//	Iterator++;
		//if ((*Iterator).length() == cursor.offset+1) {
		//	
		//}
	}	
}


bool TextEditor::DeleteText(Cursor origin, int length)
{
	total -= length;
	list<string>::iterator Iterator = article.begin();
	for (int i = 0; i < origin.line-1; i++) {
		Iterator++;
	}
	int eraseLine = 0, tempOffset = 0;	//删除的行数，删除的最后一行的剩余偏移量
	if ((*Iterator).length() >= length) {	//删除一行中的部分
		(*Iterator).erase(origin.offset, length);
		SetCursor(origin.line, origin.offset);
		//total -= length;
		return true;
	}
	else {	//删除多行
		list<string>::iterator IteratorTemp = Iterator;
		length -= ((*Iterator).length() - origin.offset);
		Iterator++;
		while (1) {
			if ((*Iterator).length() >= length)	break;
			length -= (*Iterator).length();
			eraseLine++;
			Iterator++;	//指向下一行
			
		}
		tempOffset = length;
		//开始删除,先拼接，再删除
		//total -= ((*IteratorTemp).length() - origin.offset);
		(*IteratorTemp).erase(origin.offset);
		//cout << (*IteratorTemp) << "\n";
		string st = (*Iterator).substr(tempOffset-1);
		(*IteratorTemp) += st;
		(*Iterator).erase(0);
		//cout << (*IteratorTemp) << "\n";
		list<string>::iterator IT2 = IteratorTemp;
		for (int i = 0; i < eraseLine; i++) {
			//total -= (*IT2).length();
			article.erase(++IT2);
		}

		SetCursor(origin.line, origin.offset);

		return true;
	}
	return false;
}

ostream & operator<<(ostream & out, TextEditor & editor)
{
	list<string>::iterator it = editor.article.begin();
	while (it != editor.article.end())
	{
		out << (*it) << endl;	it++;
	}
	return out;
}

//暂且没有换行符,没有空格，输入一个就作为一个结点
istream & operator>>(istream & in, TextEditor & editor)
{
	string s;
	in >> s;
	editor.article.push_back(s);
	return in;
}

//在每个节点查找匹配
bool TextEditor::FindText(string & text, Cursor& c)
{

	list<string>::iterator Iterator = article.begin();
	for (int i = 0; i < article.size(); i++) {
		int j = (*Iterator).find(text);
		if (j != -1) {
			c.line = i;
			c.offset = j;
			return true;
		}
		Iterator++;
	}
	return false;
}

//先查找匹配再删除，暂且在每一行中匹配，不接受跨行
bool TextEditor::DeleteText(string & text)
{
	int l = text.length();
	Cursor c(0, 0);
	bool b = FindText(text, c);
	if (b == false)
		return false;
	else
	{
		list<string>::iterator Iterator = article.begin();
		for (int i = 0; i < c.line; i++)
			Iterator++;
		string tempstr = (*Iterator).substr(c.offset + l);
		(*Iterator).erase(c.offset);
		(*Iterator) += tempstr;
		return true;
	}
}





