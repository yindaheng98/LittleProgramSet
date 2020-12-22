#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<memory.h>
using std::cin;
using std::cout;
using std::endl;

int MSize, N, M;
int Hash[20000];
bool seted[20000];
bool not_prime[20000];

void primeInit(int n)
{
	for (int i = 2; i < n+1000; i++)
	{
		if (not_prime[i])continue;
		for (int j = i * 2; j < n+1000; j += i)
			not_prime[j] = true;
	}
}

int HashID(int n)
{
	int place = n%MSize;
	if (seted[place])
	{
		bool find = false;
		int tplace = -1;
		for (int i = 1; i < MSize; i++)
		{
			tplace = (place + i*i) % MSize;
			if (!seted[tplace]) { find = true; break; }
		}
		if (find)place = tplace;
		else place = -1;
	}
	return place;
}

void HashSet(int n)
{
	int id = HashID(n);
	if (id >= 0) { Hash[id] = n; seted[id] = true; }
	else printf("%d cannot be inserted.\n", n);
}

int HashFind(int n)
{
	int time = 1;
	int place = n%MSize;
	if (seted[place] && Hash[place] != n)
	{
		for (int i = 1; i <= MSize; i++)
		{
			time++;
			int tplace = (place + i*i) % MSize;
			if (!seted[tplace] || Hash[tplace] == n)break;
		}
	}
	return time;
}

int main()
{
	cin >> MSize >> N >> M;
	primeInit(MSize);
	while (not_prime[MSize])MSize++;
	for (int i = 0; i < N; i++)
	{
		int n;
		cin >> n;
		HashSet(n);
	}
	int total_time = 0;
	for (int i = 0; i < M; i++)
	{
		int n;
		cin >> n;
		total_time += HashFind(n);
	}
	printf("%.1f", ((double)total_time) / M);
	return 0;
}

/*��ȷ*/
/*��Ŀ���ᵽ with positive increments only ��������ֻ��Ҫ��������������*/
/*����q<=�� - 1*/
/*�������������10000����ô��С��������10007�����������10000*/
/*MSize���˴���10000��Hash��Ҳ�������10000*/