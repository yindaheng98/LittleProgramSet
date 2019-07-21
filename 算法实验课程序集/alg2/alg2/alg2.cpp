// alg2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>

#define M 100
#define T 1000

using std::cin;
using std::cout;
using std::endl;

int c[M];
int w[M];
int f[M][T];

int max(int a, int b)
{
	return a > b ? a : b;
}

void main()
{
	int m, t;
	cout << "����ʱ��t��" << endl;
	cin >> t;
	cout << "������Ʒ����m��" << endl;
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		cout << "��"<<i<<"����Ʒ��ʱ��w�ͼ�ֵc��" << endl;
		cin >> w[i] >> c[i];//���//��ֵ
	}
	for (int i = 1; i <= m; i++)
	{
		f[i][0] = 0;
		for (int j = 1; j <= t; j++)
			if (j >= w[i])//������������
				f[i][j] = max(f[i - 1][j - w[i]] + c[i], f[i - 1][j]);
			else//������������
				f[i][j] = f[i - 1][j];
	}
	cout << "����ֵ��" << endl;
	cout << f[m][t] << endl;
	system("pause");
}