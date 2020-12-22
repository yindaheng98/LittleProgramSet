#include "stdafx.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

char sdate[2][8];
unsigned date[2][3];
unsigned A, B;
short D;

int main()
{
	cin >> A >> B >> D;
	unsigned C = A + B;
	char E[300];
	E[299] = '\0';
	short e = 298;
	do
	{
		E[e--] = C%D+'0';
		C /= D;
	} while (C > 0);
	E[e] = '\0';
	cout << &E[e + 1];
}

