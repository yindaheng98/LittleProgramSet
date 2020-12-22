#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<map>
#include<vector>
#include<algorithm>
#include<set>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::vector;
using std::sort;
using std::set;
using std::string;

int N, M, K;
struct People
{
	int id;
	bool sex;
	vector<People*>friends;
	set<int>friend_ids;
};
map<int, People*>network;

inline int abs(int n)
{
	return n > 0 ? n : -n;
}

inline int atoi(char a[6])
{
	int bias = (a[0] == '-' ? 1 : 0);
	int result = 0;
	for (int i = 0; i < 4; i++)
		result = result * 10 + a[i + bias] - '0';
	return result + bias * 10000;
}

int main()
{
	cin >> N >> M;
	for (int m = 0; m < M; m++)
	{
		char id[2][6];
		cin >> id[0] >> id[1];
		People*ps[2];
		for (int i = 0; i < 2; i++)
		{
			int ida = atoi(id[i]);
			auto find = network.find(ida);
			if (find == network.end())
			{
				ps[i] = new People({ ida,(id[i][0] == '-') });
				network.insert(pair<int, People*>(ida, ps[i]));
			}
			else ps[i] = find->second;
		}
		for (int i = 0; i < 2; i++)
		{
			People*p = ps[(i + 1) % 2];
			if (ps[i]->friend_ids.find(p->id) == ps[i]->friend_ids.end());
			{
				ps[i]->friends.push_back(p);
				ps[i]->friend_ids.insert(p->id);
			}
		}
	}
	for (auto find = network.begin(); find != network.end(); find++)
		sort(find->second->friends.begin(), find->second->friends.end(),
			[](People*a, People*b) {return a->id < b->id; });
	cin >> K;
	for (int k = 0; k < K; k++)
	{
		char id[2][6];
		cin >> id[0] >> id[1];
		int A = atoi(id[0]), B = atoi(id[1]);
		auto Afind = network.find(A), Bfind = network.find(B);
		if (Afind == network.end() || Bfind == network.end())
		{
			cout << 0 << endl;
			continue;
		}
		vector<People*>Afriends;
		for (People*Afriend : Afind->second->friends)
			if (Afriend->sex == Afind->second->sex)
				Afriends.push_back(Afriend);
		set<int>Bfriends;
		for (People*Bfriend : Bfind->second->friends)
			if (Bfriend->sex == Bfind->second->sex)
				Bfriends.insert(Bfriend->id);
		vector<int*>results;
		for (People*Afriend : Afriends)
		{
			int Afsex = (Afriend->sex ? 1 : 0) * 10000;
			for (People*Aff : Afriend->friends)
			{
				int Affsex = (Aff->sex ? 1 : 0) * 10000;
				if (Aff->id != A&&Bfriends.find(Aff->id) != Bfriends.end())
					results.push_back(new int[2]{ Afriend->id - Afsex,Aff->id - Affsex });
			}
		}
		cout << results.size() << endl;
		for (int*result : results)
			printf("%04d %04d\n", result[0], result[1]);
	}
	return 0;
}

/*������ȷ��ԭ��δ֪*/
/*�����ʱ��ֻ����string����ΪID������-0000������int�Ļ����žͿ���������*/
/*�����ʱ��������4λ*/
/*��Ů��ž���ֵ����һ��*/
/*Ҫ��֤����ĺ��Ѳ������Լ�*/
/*���ѻ�Ҫȥ��*/