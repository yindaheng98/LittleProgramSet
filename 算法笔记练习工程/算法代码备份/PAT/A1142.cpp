#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::set;

int Nv,Ne,M;
bool E[201][201];

int main()
{
	cin >> Nv >> Ne;
	for (int i = 1; i <= Nv; i++)
	{
		memset(&E[i][1], 0, Nv * sizeof(bool));
		E[i][i] = true;
	}
	for (int i = 0; i < Ne; i++)
	{
		int from, to; cin >> from >> to;
		E[from][to] = E[to][from] = true;
	}
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		int K; cin >> K;
		set<int>s = set<int>();
		bool isClique = true;
		bool include[201];
		memset(&include[0], 0, Nv * sizeof(bool));
		for (int k = 0; k < K; k++)
		{
			int v; cin >> v;
			if (isClique)
				for (int vo : s)
					if (!E[vo][v])
						isClique = false;
			s.insert(v);
			include[v] = true;
		}
		if (!isClique)
		{
			cout << "Not a Clique" << endl;
			continue;
		}
		bool isMax = true;
		for (int v = 1; v <= Nv; v++)
		{
			if (include[v])continue;
			bool can_insert = true;
			for (int vo : s)
				if (!E[vo][v])
				{
					can_insert = false;
					break;
				}
			if (can_insert)
			{
				isMax = false;
				break;
			}
		}
		if (!isMax)
		{
			cout << "Not Maximal" << endl;
			continue;
		}
		cout << "Yes" << endl;
	}
	return 0;
}

/*部分正确*/
/*在memset邻接矩阵E时从0开始导致出错*/
/*遍历判断maximal循环的Nv<=误打成<导致出错*/