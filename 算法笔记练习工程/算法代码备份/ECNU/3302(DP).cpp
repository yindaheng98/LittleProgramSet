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

unsigned long long dp(unsigned long long n)
{
	if (n <= 0)return t[n] = 0;
	if (n == 1)return t[n] = x;
	unsigned long long t_min = t[n - 1] + x;
	if (n % 2 == 0)t_min = min(t[n / 2] + y, t_min);
	else t_min = min(t[(n + 1) / 2] + x + y, t_min);
	return t[n] = t_min;
}

int main()
{
	cin >> N >> x >> y;
	for (unsigned long long i = 0; i <= N; i++)
		dp(i);
	cout << t[N];
	return 0;
}

/*��ȷ*/
/*��̬�滮��������˼·����˼·������ȫ��ȷ��ֻ����Ŀ����û�п����������*/
/*��ȡ��ѵ���´ο���˼·���ڸ��ӵ�ʱ�򣬾�����������϶�һ��*/
/*��һ���ύ���˸�����*/