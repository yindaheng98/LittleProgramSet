#include "stdafx.h"
#include<memory.h>
#include<iostream>
#include<unordered_map>
using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;
using std::pair;

unsigned long long a, b;
unsigned T;

short one_num(unsigned long long n)
{
	short r = 0;
	while (n > 0)
	{
		n = n >> 1;
		r++;
	}
	return r;
}

unsigned long long number(short n_one, short p_zero)
{
	unsigned long long n = ((unsigned long long)1 << (n_one + 1)) - 1;
	return n&(~((unsigned long long)1 << p_zero));
}

short diff_num(unsigned long long a,unsigned long long b)
{
	return one_num(a^b);
}

int main()
{
	cin >> T;
	for (unsigned t = 1; t <= T; t++)
	{
		cin >> a >> b;
		short diff_n = diff_num(a, b);
		unsigned long long mask = ((unsigned long long)1 << diff_n) - 1;
		unsigned long long result = a&~mask;
		if (result + mask <= b)result += mask;
		else result += mask >> 1;
		cout << "Case " << t << ": " << result << endl;
	}
	return 0;
}

/*正确*/
/*第一次提交没有考虑b的最后几位是全1的情况*/