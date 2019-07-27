#pragma once
#include"stdafx.h"
#include<fstream>
#include<string>
#include<vector>
using std::wifstream;
using std::wstring;
using std::vector;

class CData//数据元素类
{
public:
	CData(wifstream&file)//构造：读入数据
	{
		for (int i = 1; i <= 9; i++)
		{
			wstring temp;
			switch (i)//读文件
			{
			case 2:case 6:case 8:file >> temp; break;
			case 1:file >> chr; break;	//读基因号
			case 3:file >> type; break;	//读类型
			case 4:file >> start; break;//读起点
			case 5:file >> end; break;	//读终点
			case 7:file >> temp;
				strand = (temp == L"+");
				break;					//读正负链
			case 9:file >> note; break;	//读备注
			}
		}
	}
	wstring chr;	//基因号
	wstring type;	//类型
	int start;		//起点
	int end;		//终点
	bool strand;	//正负链
	wstring note;	//备注
};

class CDataString//数据类
{
public:
	vector<CData>data;//数据元素类集合
	CDataString() {}
	CDataString(CString filepath)//输入路径
	{
		wifstream file(filepath);//打开文件
		while (!file.eof())				//读到文件尾
		{
			data.push_back(CData(file));//读文件
		}
	}
};


