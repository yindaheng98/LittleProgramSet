#include "stdafx.h"
#include<iostream>
#include<string.h>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::sort;

int DP[10000], S[10000];
unsigned K, begin;

int dp(unsigned k)
{
	if (k == 0)
		return begin = 0, DP[k] = S[k];
	if (DP[k - 1] >= 0)
		return DP[k] = DP[k - 1] + S[k];
	begin = k;
	return  DP[k] = S[k];
}

int main()
{
	cin >> K;
	bool nega = true;
	for (unsigned k = 0; k < K; k++)
	{
		cin >> S[k];
		if (S[k] >= 0)nega = false;
	}
	if (nega)
	{
		cout << 0 << ' ' << S[0] << ' ' << S[K - 1];
		return 0;
	}
	int start = 0, end = 0, max = S[0];
	for (unsigned k = 0; k < K; k++)
	{
		int c=dp(k);
		if (c > max)
		{
			start = S[begin];
			end = S[k];
			max = c;
		}
	}
	cout << max << ' ' << start << ' ' << end;
	return 0;
}

/*正确*/
/*有一个测试点不通过，不知何故*/
