#include<iostream>
#include<list>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

#ifndef TEXTEDITOR
#define TEXTEDITOR

//�����(ʵ����λ����)�������У�ƫ����
class Cursor {
public:
	int line;	
	int offset;
	Cursor() { line = 1; offset = 0; }
	Cursor(int l,int o):line(l),offset(o){}
};
//�ı��༭����
class TextEditor {
public:
	list<string> article;	//�ı��ý����string������洢��ÿһ����Ϊһ�����
	Cursor cursor;	//һ���༭��ֻһ�����
	int total;	//�ı�������
	string name;	//�ı�����
public:
	TextEditor() { total = 0; }
	~TextEditor() { article.clear(); }
	string& GetName() { return name; }
	void SetName(string& name) { this->name = name; }
	int GetTotalBeforeCursor();

	friend ostream& operator<<(ostream& out, TextEditor& editor);
	friend istream& operator>>(istream& in, TextEditor& editor);
	
	//��������������������ĸ�������������ո������������
	void WordStat(int &pTotal, int &pLetter, int &pDigit, int &pSpace, int &pQuot);

	//�õ������ã��ƶ����λ��
	void GetCursor(int &pLine, int &pOffset) { pLine = cursor.line; pOffset = cursor.offset; }
	void SetCursor(int line, int offset) { cursor.line = line; cursor.offset = offset; }
	//origin�ǲο�λ�ã��ֱ����ĵ���ʼ���ĵ��������ĵ���ǰ���λ�ã�offset��ƫ����
	//origin={1,2,3}֮һ
	void MoveCursor(int origin, int offset);

	//׷�ӣ������ı��������ı���ɾ���ı�
	//void AddText(string &text);
	void InsertText(string& text);	//�ڹ�괦�����ı�,(����ʵ�������ĩ�������)
	bool FindText(string& text,Cursor& cursor);
	bool DeleteText(string& text);	//�Ȳ���ƥ�����ɾ��
	bool DeleteText(Cursor origin,int length);	//�Ӹ�����꣨λ��,�����ĵ��Ĺ�꣩��ɾ��length���ַ�
};

#endif // !TEXTEDITOR

//ȡ�õ�ǰ���֮�ĵ���ͷ��ƫ������
int TextEditor::GetTotalBeforeCursor() {
	list<string>::iterator Iterator = article.begin();	//������,������ָ��
	int tempTotalBeforeCursor = 0;	//��ʼ0
	for (int i = 1; i < cursor.line; i++) {
		tempTotalBeforeCursor += (*Iterator).length();	//����string��length()����
		Iterator++;
	}
	tempTotalBeforeCursor += cursor.offset;
	return tempTotalBeforeCursor;
}

//�ƶ���꣨λ�ã�
void TextEditor::MoveCursor(int origin, int offset) {
	//��ʱ��֮���ĵ���ͷ��ƫ����TempOffset,TempLine��󸳸�cursor.line,���Գ�ʼΪ1.
	int TempOffset = 0, TempLine = 1;
	switch (origin)
	{
	case 1:TempOffset = offset; break;	//�ĵ���ʼ��
	case 2:TempOffset = total + offset; break;	//�ĵ���������offset�����Ǹ���
	case 3:TempOffset = GetTotalBeforeCursor() + offset; break;	//��ǰ��괦
	default: cout << "�ο�λ�ó���\n"; exit(-1);
	}
	if (TempOffset < 0) {
		TempOffset = 0;	cout << "֮���ĵ���ͷƫ����С��0��������Ϊ0\n";
	}
	//list<string>::reverse_iterator rIterator = article.rbegin();
	list<string>::iterator Iterator = article.begin();
	while (1) {
		if (TempOffset > (*Iterator).length()) {	//ƫ�������ڱ��г���
			TempOffset -= (*Iterator).length();
			TempLine++;
		}
		if (Iterator == (--article.end())) break;	//���������һ��
		Iterator++;	//ȡ��һ��
	}
	cursor.line = TempLine;
	cursor.offset = TempOffset;
}

//ͳ���ַ���������ĸ�����֣��ո񣬱������
void TextEditor::WordStat(int & pTotal, int & pLetter, int & pDigit, int & pSpace, int & pQuot)
{
	pTotal = 0; pLetter = 0; pDigit = 0; pSpace = 0; pQuot = 0;
	list<string>::iterator Iterator = article.begin();
	while (Iterator!=article.end())
	{
		for (int i = 0; i < (*Iterator).length(); pTotal++,i++) {
			//<=97 ��Bug
			if ((*Iterator)[i] >= 65 && (*Iterator)[i] <= 90 || (*Iterator)[i] >= 97 && (*Iterator)[i] <= 122)
				pLetter++;
			else if ((*Iterator)[i] >= 48 && (*Iterator)[i] <= 57)
				pDigit++;
			else if ((*Iterator)[i] == 32)
				pSpace++;
			else
				pQuot++;
		}
		//��Bug
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
	if (backNum != 0) {	//�ı��а������з�
		s = new string[backNum + 1];	//�м�һ���ո񣬷�Ϊ������
		for (k = 0; k < backNum; k++) {
				s[k] = text.substr(n, backAddress[k] - n);
				n = backAddress[k] + 1;
		}
		s[k] = text.substr(n, text.length() - n);
		cout << "*****\n";
	}
	else {	//���������з�
		 s1 = text;
		 //cout << "2";
	}
	///////////////////////////////
	if (backNum != 0) {
		for (int m = 0; m < backNum + 1; m++) {
			article.push_back(s[m]);	//����s[k]
			total += s[m].length();		//������
		}
		cursor.line += (backNum + 1);
		cursor.offset = s[backNum].length();
		//cout << "3";
	}
	else {
		article.push_back(s1);
		total += s1.length();	//������
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
	int eraseLine = 0, tempOffset = 0;	//ɾ����������ɾ�������һ�е�ʣ��ƫ����
	if ((*Iterator).length() >= length) {	//ɾ��һ���еĲ���
		(*Iterator).erase(origin.offset, length);
		SetCursor(origin.line, origin.offset);
		//total -= length;
		return true;
	}
	else {	//ɾ������
		list<string>::iterator IteratorTemp = Iterator;
		length -= ((*Iterator).length() - origin.offset);
		Iterator++;
		while (1) {
			if ((*Iterator).length() >= length)	break;
			length -= (*Iterator).length();
			eraseLine++;
			Iterator++;	//ָ����һ��
			
		}
		tempOffset = length;
		//��ʼɾ��,��ƴ�ӣ���ɾ��
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

//����û�л��з�,û�пո�����һ������Ϊһ�����
istream & operator>>(istream & in, TextEditor & editor)
{
	string s;
	in >> s;
	editor.article.push_back(s);
	return in;
}

//��ÿ���ڵ����ƥ��
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

//�Ȳ���ƥ����ɾ����������ÿһ����ƥ�䣬�����ܿ���
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





