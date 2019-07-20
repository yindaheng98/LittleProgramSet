#pragma once
#include<fstream>
#include<string>
using std::wifstream;
using std::wstring;

class CDataString
{
	
public:
	wstring str[9];
	
	CDataString(wifstream &file)
	{
		for (int j = 0; j < 9; j++)
		{
			file >> str[j];//读取每行9项数据
		}
	}
};


