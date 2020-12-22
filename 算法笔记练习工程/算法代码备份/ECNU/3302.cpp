#include "stdafx.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

unsigned long long N, x, y;
unsigned long long t[20000000];


template<typename T>T min(T a, T b)
{
	return a < b ? a : b;
}

bool changed[20000000];

unsigned long long dp(unsigned long long n)
{
	if (n <= 0)return 0;
	unsigned long long t_min = t[n - 1] + x;
	if (n % 2 == 0)t_min = min(t[n / 2] + y, t_min);
	return t[n] = t_min;
}

void DFS(unsigned long long n, unsigned long long time)
{
	if (time > t[n])return;
	if (time == t[n] && changed[n])return;
	t[n] = time;
	changed[n] = true;

	if (n > N && t[N] <= time + (n - N)*x)return;

	if (n > 0)
		DFS(n - 1, time + x);
	DFS(n + 1, time + x);
	DFS(n * 2, time + y);
}

int main()
{
	cin >> N >> x >> y;
	for (unsigned long long i = 0; i <= N; i++)
		dp(i);
	DFS(0, 0);
	cout << t[N];
	return 0;
}

/*不正确*/
/*这不是动态规划，主要算法是DFS*/
/*第一次提交运行错误，数组要设大一点*/