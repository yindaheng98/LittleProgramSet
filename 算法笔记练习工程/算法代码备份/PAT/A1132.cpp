#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int N;
unsigned long num;

int dig(unsigned long n)
{
	if (n == 0)return 0;
	int d = 0;
	do d++;
	while (n /= 10);
	return d;
}

unsigned long pow10(int d)
{
	unsigned long pow = 1;
	while (d--)pow *= 10;
	return pow;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> num;
		int d = dig(num);
		int p10 = pow10(d / 2);
		int div = (num / p10) * (num%p10);
		if (div != 0 && num % div == 0)
			cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}

/*ÕýÈ·*/
/*×¢Òâ0*/