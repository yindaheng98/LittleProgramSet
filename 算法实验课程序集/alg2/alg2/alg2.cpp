// alg2.cpp : 定义控制台应用程序的入口点。
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
	cout << "输入时间t：" << endl;
	cin >> t;
	cout << "输入物品总数m：" << endl;
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		cout << "第"<<i<<"个物品的时间w和价值c：" << endl;
		cin >> w[i] >> c[i];//体积//价值
	}
	for (int i = 1; i <= m; i++)
	{
		f[i][0] = 0;
		for (int j = 1; j <= t; j++)
			if (j >= w[i])//背包容量够大
				f[i][j] = max(f[i - 1][j - w[i]] + c[i], f[i - 1][j]);
			else//背包容量不足
				f[i][j] = f[i - 1][j];
	}
	cout << "最大价值：" << endl;
	cout << f[m][t] << endl;
	system("pause");
}