#include "stdafx.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

short a[1000][1000];
unsigned sum[1000][1000];
unsigned zer[1000][1000];
unsigned temp[1000];
unsigned DP[1000];
unsigned n, m;

unsigned dp(unsigned k)
{
	if (k <= 0)return DP[0] = temp[0];
	if (temp[k] <= 0)return DP[0] = 0;
	return DP[k] = (temp[k - 1] <= 0) ? temp[k] : (DP[k - 1] + temp[k]);
}

unsigned findmax(unsigned i1)
{
	unsigned max = 0;
	for (unsigned j = 0; j < m; j++)
	{
		temp[j] = zer[i1][j] <= 0 ? sum[i1][j] : 0;
		unsigned c = dp(j);
		max = max > c ? max : c;
	}
	return max;
}

unsigned findmax(unsigned i1,unsigned i2)
{
	unsigned max = 0;
	for (unsigned j = 0; j < m; j++)
	{
		temp[j] = zer[i2][j] - zer[i1][j] <= 0 ? sum[i2][j] - sum[i1][j] : 0;
		unsigned c= dp(j);
		max = max > c ? max : c;
	}
	return max;
}

int main()
{
	cin >> n >> m;
	for (unsigned j = 0; j < m; j++)
	{
		cin >> a[0][j];
		sum[0][j] = a[0][j];
		zer[0][j] = (unsigned)(a[0][j] <= 0);
	}
	for (unsigned i = 1; i < n; i++)
		for (unsigned j = 0; j < m; j++)
		{
			cin >> a[i][j];
			sum[i][j] = sum[i - 1][j] + a[i][j];
			zer[i][j] = zer[i - 1][j] + (unsigned)(a[i][j] <= 0);
		}


	unsigned max = DP[0] = temp[0];
	for (unsigned i2 = 0; i2 < n; i2++)
	{
		unsigned c = findmax(i2);
		max = max > c ? max : c;
		for (unsigned i1 = 0; i1 < i2; i1++)
		{
			unsigned c = findmax(i1, i2);
			max = max > c ? max : c;
		}
	}
	cout << max;
	return 0;
}

/*ÕýÈ·*/
