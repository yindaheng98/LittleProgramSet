#include "stdafx.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

char sdate[2][8];
unsigned date[2][3];
long diff = 0;

unsigned mdays[2][13] = { {0,31,28,31,30,31,30,31,31,30,31,30,31},{ 0,31,29,31,30,31,30,31,31,30,31,30,31 } };

unsigned atoi(char *a,short n)
{
	unsigned i = 0;
	for (short k = 0; k < n; k++)
		i = i * 10 + (a[k] - '0');
	return i;
}

int main()
{
	while (!cin.eof())
	{
		cin >> sdate[0] >> sdate[1];
		short c = atoi(sdate[0], 8) > atoi(sdate[1], 8) ? 1 : 0;
		date[c % 2][0] = atoi(&sdate[0][0], 4);
		date[c % 2][1] = atoi(&sdate[0][4], 2);
		date[c % 2][2] = atoi(&sdate[0][6], 2);
		c++;
		date[c % 2][0] = atoi(&sdate[1][0], 4);
		date[c % 2][1] = atoi(&sdate[1][4], 2);
		date[c % 2][2] = atoi(&sdate[1][6], 2);

		for (unsigned y = date[0][0]; y < date[1][0]; y++)
			diff += y % 400 == 0 || (y % 4 == 0 && y % 100 != 0) ? 366 : 365;

		for (unsigned m = 1; m < date[0][1]; m++)
			diff -= mdays[date[0][0] % 4 == 0][m];

		for (unsigned m = 1; m < date[1][1]; m++)
			diff += mdays[date[1][0] % 4 == 0][m];

		diff -= date[0][2];
		diff += date[1][2];
		cout << diff + 1;
	}
}

