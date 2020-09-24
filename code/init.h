#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

#define COMMENT_CHAR '#'

using namespace std;

class CParseIniFile
{
public:
	CParseIniFile();
	~CParseIniFile();
	bool ReadConfig(const string& filename, map<string, string>& mContent, const char* section);
	bool AnalyseLine(const string & line, string & key, string & val);
	void Trim(string & str);
	bool IsSpace(char c);
	bool IsCommentChar(char c);
	void PrintConfig(const map<string, string> & mContent);
private:
};