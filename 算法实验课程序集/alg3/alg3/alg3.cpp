// alg3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using std::cout;
using std::endl;

int d[8] = { 2,4,6,8,10,13,16,19 };
int n = 8;

int main()
{
	int t = 0;
	int s = 1;
	for (int i = 0; i < n; i++)
	{
		if (d[i] > d[t] + 8)
		{
			t=i;
			s++;
		}
	}
	cout << "���ݾ��룺";
	for (int i = 0; i < n; i++)
		cout << d[i] <<",";
	cout << endl << "��վ������" << s << endl;
	system("pause");
    return 0;
}

