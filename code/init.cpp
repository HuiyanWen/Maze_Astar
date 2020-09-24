#include "stdafx.h"
#include "init.h"


CParseIniFile::CParseIniFile()
{
}

CParseIniFile::~CParseIniFile()
{

}

bool CParseIniFile::ReadConfig(const string& filename, map<string, string>& mContent, const char* section)
{
	mContent.clear();
	ifstream infile(filename.c_str());
	if (!infile)
	{
		cout << "Ini open error" << endl;
		return false;
	}
	string line, key, value;
	int pos = 0;
	string Tsection = string("[") + section + "]";
	bool flag = false;
	while (getline(infile, line))
	{
		if (!flag)
		{
			pos = line.find(Tsection, 0);
			if (-1 == pos)
			{
				continue;
			}
			else
			{
				flag = true;
				getline(infile, line);
			}
		}
		if (0 < line.length() && '[' == line.at(0))
		{
			break;
		}
		if (0 < line.length() && AnalyseLine(line, key, value))
		{

			if (value.length() > 0)
			{
				if (value[value.size() - 1] == '\r')
				{
					value[value.size() - 1] = '\0';
				}
			}
			mContent[key] = value;
		}
	}
	infile.close();
	return true;
}

bool CParseIniFile::AnalyseLine(const string & line, string & key, string & val)
{
	if (line.empty())
	{
		return false;
	}
	int start_pos = 0, end_pos = line.size() - 1, pos = 0;
	if ((pos = line.find(COMMENT_CHAR)) != -1)
	{
		if (0 == pos)
		{//行的第一个字符就是注释字符
			return false;
		}
		end_pos = pos - 1;
	}
	string new_line = line.substr(start_pos, start_pos + 1 - end_pos);  // 预处理，删除注释部分

	if ((pos = new_line.find('=')) == -1)
	{
		return false;  // 没有=号
	}

	key = new_line.substr(0, pos);
	val = new_line.substr(pos + 1, end_pos + 1 - (pos + 1));

	Trim(key);
	if (key.empty())
	{
		return false;
	}
	Trim(val);
	return true;
}

void CParseIniFile::Trim(string & str)
{
	if (str.empty())
	{
		return;
	}
	int i, start_pos, end_pos;
	for (i = 0; i < str.size(); ++i)
	{
		if (!IsSpace(str[i]))
		{
			break;
		}
	}
	if (i == str.size())
	{ //全部是空白字符串
		str = "";
		return;
	}

	start_pos = i;

	for (i = str.size() - 1; i >= 0; --i)
	{
		if (!IsSpace(str[i]))
		{
			break;
		}
	}
	end_pos = i;

	str = str.substr(start_pos, end_pos - start_pos + 1);
}

bool CParseIniFile::IsSpace(char c)
{
	if (' ' == c || '\t' == c)
	{
		return true;
	}
	return false;
}

bool CParseIniFile::IsCommentChar(char c)
{
	switch (c)
	{
	case COMMENT_CHAR:
		return true;
	default:
		return false;
	}
}

void CParseIniFile::PrintConfig(const map<string, string> & mContent)
{
	map<string, string>::const_iterator mite = mContent.begin();
	for (; mite != mContent.end(); ++mite)
	{
		cout << mite->first << "=" << mite->second << endl;
	}
}