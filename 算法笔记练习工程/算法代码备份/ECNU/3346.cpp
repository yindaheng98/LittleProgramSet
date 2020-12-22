#include "stdafx.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

unsigned long row[100000], col[100000], edge_l[200000], edge_r[200000];
unsigned long N;


unsigned long isdep(unsigned long x, unsigned long y)
{
	unsigned long depn = 0;

	depn += row[x]++ + col[y]++;

	unsigned long edgex, edgey, diff, loc;

	diff = x < y ? x : y;
	edgex = x - diff;
	edgey = y - diff;
	loc = (unsigned long)(edgex != 0)*N + edgex + edgey;
	depn += edge_l[loc]++;

	x = N - x;
	diff = x < y ? x : y;
	edgex = x - diff;
	edgey = y - diff;
	loc = (unsigned long)(edgex != 0)*N + edgex + edgey;
	depn += edge_r[loc]++;

	return depn;
}

int main()
{
	cin >> N;
	unsigned long depn = 0;
	for (unsigned long i = 0; i < N; i++)
	{
		unsigned long x, y;
		cin >> x >> y;
		x--, y--;
		unsigned long t = isdep(x, y);
		depn += t;
	}
	cout << depn;
}

/*��ȷ*/
/*���β�ͨ��*/
/*��һ�������С��10000������100000�����ݵĲ��Ե㴦Runtime Error->����Ĵ�*/
/*�ڶ�����Ϊunsigned�������->��unsigned long��*/
