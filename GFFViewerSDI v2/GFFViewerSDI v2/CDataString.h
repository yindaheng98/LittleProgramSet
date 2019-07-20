#pragma once
#include<fstream>
#include<string>
#include<vector>
using std::ifstream;
using std::string;

class CDataString
{
	
public:
	string str[9];
	
	CDataString(ifstream &file)
	{
		for (int j = 0; j < 9; j++)
		{
			file >> str[j];
		}
	}
};


