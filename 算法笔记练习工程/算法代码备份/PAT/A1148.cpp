#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int N;
struct Assert
{
	int who;
	bool iswolf;
};

Assert asserts[100];
short wolf[100];//1狼-1人0不确定
vector<int*>v = vector<int*>();

bool try_lie(int lie[2])
{
	for (int i = 0; i < N; i++)wolf[i] = 0;
	for (int i = 0; i < 2; i++)
		wolf[asserts[lie[i]].who] = asserts[lie[i]].iswolf ? -1 : 1;
	for (int i = 0; i < N; i++)
		if (i != lie[0] && i != lie[1])
		{
			Assert a = asserts[i];
			if (wolf[a.who] == 0)wolf[a.who] = a.iswolf ? 1 : -1;
			else if (wolf[a.who] != (a.iswolf ? 1 : -1))return false;
		}
	int totalwolf = 0;
	bool wolflie = false;
	for (int i = 0; i < N; i++)
		if (wolf[i] == 1)
		{
			if (i == lie[0] || i == lie[1])
				wolflie = true;
			totalwolf++;
		}
	if (totalwolf > 2 || !wolflie)return false;
	for (int i = 0; i < N; i++)
		if (wolf[i] == 0)
		{
			if (i == lie[0] || i == lie[1])
				wolflie = true;
			totalwolf++;
		}
	if (totalwolf < 2 || !wolflie)return false;
	return true;
}

void getwolf(int whoiswolf[2])
{
	int w = 0;
	for (int i = 0; i < N; i++)
	{
		if (wolf[i] > 0)whoiswolf[w++] = i;
		if (w >= 2)
			return;
	}
	for (int i = 0; i < N; i++)
	{
		if (wolf[i] == 0)whoiswolf[w++] = i;
		if (w >= 2)
		{
			if (whoiswolf[0] > whoiswolf[1])
			{
				int t = whoiswolf[0];
				whoiswolf[0] = whoiswolf[1];
				whoiswolf[1] = t;
			}
			return;
		}
	}
}

int main()
{
	cin >> N;
	getchar();
	for (int i = 0; i < N; i++)
	{
		char c;
		cin >> c;
		asserts[i] = { 0,c == '-' };
		cin >> asserts[i].who;
		asserts[i].who--;
		getchar();
	}
	
	v.clear();
	for(int i=0;i<N;i++)
		for (int j = i + 1; j < N; j++)
		{
			int lie[2] = { i, j };
			if (try_lie(lie))
			{
				int* whoiswolf=new int[2];
				getwolf(whoiswolf);
				v.push_back(whoiswolf);
			}
		}
	if (v.empty())
	{
		cout << "No Solution" << endl;
		return 0;
	}
	int whoiswolf[2] = { v[0][0],v[0][1] };
	for(int* w:v)
		if (w[0] <= whoiswolf[0])
		{
			whoiswolf[0] = w[0];
			if(w[1]<=whoiswolf[1])
				whoiswolf[1] = w[1];
		}
	cout << whoiswolf[0] + 1 << ' ' << whoiswolf[1] + 1 << endl;
	return 0;
}

/*部分正确*/