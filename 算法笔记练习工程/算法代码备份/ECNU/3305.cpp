#include "stdafx.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

char a[18];

unsigned long long atoi()
{
	unsigned long long res = a[0] - '0';
	for (short i = 2; i < 17; i++)
		res = res * 10 + a[i] - '0';
	return res;
}

template<typename T> T GCD(T a, T b)
{
	while (a % b != 0)
	{
		T t = a;
		a = b;
		b = t%b;
	}
	return b;
}

bool process(unsigned long long p, unsigned long long q)
{
	unsigned long long G = GCD(p, q);
	if (q / G < 1000000000)
	{
		cout << p / G << ' ' << q / G;
		return true;
	}
	return false;
}

int main()
{
	cin >> a;
	unsigned long long p = atoi(), q = 999999999999999;
	if (p - q == 1)cout << 1 << ' ' << 1 << endl;
	if (process(p, q))
		return 0;
	for (unsigned t1 = 1; t1 <= 4; t1++)
	{
		unsigned long long pp = p * 10 + t1, qq = q * 10 + 9;
		if (process(pp, qq))
			return 0;
		for (unsigned t2 = 1; t2 <= 4; t2++)
		{
			unsigned long long ppp = pp * 10 + t2, qqq = qq * 10 + 9;
			if (process(ppp, qqq))
				return 0;
		}
	}
	return 0;
}

/*部分正确*/
/*这个题目的题干问题很大*/