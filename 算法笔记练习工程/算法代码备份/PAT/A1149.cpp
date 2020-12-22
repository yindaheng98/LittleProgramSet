#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<set>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::map;
using std::pair;
using std::vector;

int N, M;
map<int, set<int>>incompatibles;

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		int inc[2];
		cin >> inc[0] >> inc[1];
		for (int j = 0; j < 2; j++)
			if (incompatibles.find(inc[j]) == incompatibles.end())
				incompatibles.insert(pair<int, set<int>>(inc[j], set<int>()));
		incompatibles.find(inc[1])->second.insert(inc[0]);
		incompatibles.find(inc[0])->second.insert(inc[1]);
	}
	for (int i = 0; i < M; i++)
	{
		int K;
		cin >> K;
		set<int>goods;
		for (int k = 0; k < K; k++)
		{
			int good;
			cin >> good;
			if (incompatibles.find(good) != incompatibles.end())
				goods.insert(good);
		}
		vector<int>goodv;
		for (int good : goods)
			goodv.push_back(good);

		if (goodv.empty())
		{
			cout << "Yes" << endl;
			continue;
		}

		bool okok = false;
		for (int i = 0; i < goodv.size(); i++)
		{
			set<int>incset = incompatibles.find(goodv[i])->second;
			bool ok = false;
			for (int j = i + 1; j < goodv.size(); j++)
				if (incset.find(goodv[j]) != incset.end())
				{
					cout << "No" << endl;
					ok = true;
					okok = true;
					break;
				}
			if (ok)break;
		}
		if (okok)continue;
		cout << "Yes" << endl;
	}
	return 0;
}

/*ÕýÈ·*/