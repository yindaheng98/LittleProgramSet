#pragma once
#include"stdafx.h"
#include<fstream>
#include<string>
#include<vector>
using std::wifstream;
using std::wstring;
using std::vector;

class CData//����Ԫ����
{
public:
	CData(wifstream&file)//���죺��������
	{
		for (int i = 1; i <= 9; i++)
		{
			wstring temp;
			switch (i)//���ļ�
			{
			case 2:case 6:case 8:file >> temp; break;
			case 1:file >> chr; break;	//�������
			case 3:file >> type; break;	//������
			case 4:file >> start; break;//�����
			case 5:file >> end; break;	//���յ�
			case 7:file >> temp;
				strand = (temp == L"+");
				break;					//��������
			case 9:file >> note; break;	//����ע
			}
		}
	}
	wstring chr;	//�����
	wstring type;	//����
	int start;		//���
	int end;		//�յ�
	bool strand;	//������
	wstring note;	//��ע
};

class CDataString//������
{
public:
	vector<CData>data;//����Ԫ���༯��
	CDataString() {}
	CDataString(CString filepath)//����·��
	{
		wifstream file(filepath);//���ļ�
		while (!file.eof())				//�����ļ�β
		{
			data.push_back(CData(file));//���ļ�
		}
	}
};


