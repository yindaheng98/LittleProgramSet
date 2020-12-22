#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<algorithm>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;
using std::sort;

int N;
struct School
{
	int Rank;
	string Name;
	double TWS;
	int Ns;

};
map<string, School*>schools;
vector<School*> school_list;

bool comp(const School* a, const School* b)
{
	if ((int)a->TWS != (int)b->TWS)
		return (int)a->TWS > (int)b->TWS;
	if (a->Ns != b->Ns)
		return a->Ns < b->Ns;
	if (a->Name != b->Name)
		return a->Name < b->Name;
	return false;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		char id[20], school_name[20];
		double score;
		cin >> id >> score >> school_name;
		if (id[0] == 'B')score /= 1.5;
		else if (id[0] == 'T')score *= 1.5;
		string school_str = string(school_name);
		transform(school_str.begin(), school_str.end(), school_str.begin(), ::tolower);
		auto school_find = schools.find(school_str);
		if (school_find == schools.end())
		{
			School*schoolp = new School({ 0,school_str,score,1 });
			schools.insert(pair<string, School*>(school_str, schoolp));
			school_list.push_back(schoolp);
		}
		else
		{
			school_find->second->TWS += score;
			school_find->second->Ns++;
		}
	}
	sort(school_list.begin(), school_list.end(), comp);
	for (int i = 0; i < school_list.size(); i++)
	{
		int TWS = (int)(school_list[i]->TWS);
		if (i > 0 && TWS == (int)(school_list[i - 1]->TWS))
			school_list[i]->Rank = school_list[i - 1]->Rank;
		else school_list[i]->Rank = i + 1;
	}
	cout << school_list.size() << endl;
	for (School*schoolp : school_list)
		cout << schoolp->Rank << ' ' << schoolp->Name << ' ' << (int)schoolp->TWS << ' ' << schoolp->Ns << endl;
	return 0;
}

/*ÕýÈ·*/