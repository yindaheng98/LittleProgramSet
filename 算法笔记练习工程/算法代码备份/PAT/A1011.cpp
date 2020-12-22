#include "stdafx.h"
#include<iostream>
#include<stdio.h>
using std::cin;
using std::cout;
using std::endl;

double games[3][3];
char g[3] = { 'W','T','L' };

int main()
{
	double total = 0.65;
	for (int i = 0; i < 3; i++)
	{
		double max = 0;
		int maxj = 0;
		for (int j = 0; j < 3; j++)
		{
			double c;
			cin >> c;
			if (c > max)
			{
				max = c;
				maxj = j;
			}
		}
		cout << g[maxj] << ' ';
		total *= max;
	}
	printf("%.2f", (total - 1) * 2);
	return 0;
}

/*ÕýÈ·*/