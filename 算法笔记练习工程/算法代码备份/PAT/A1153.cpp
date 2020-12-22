#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;
using std::sort;

int N, M;
struct Score
{
	string id;
	int score;
};
map<string, Score*>List;

map<char, vector<Score*>>mapOutputLevel;
void OutputLevel(char level)
{
	vector<Score*>list = vector<Score*>();
	if (mapOutputLevel.find(level) != mapOutputLevel.end())
		list = mapOutputLevel[level];
	else
	{
		for (auto l : List)
			if (l.first[0] == level)
				list.push_back(l.second);
		sort(list.begin(), list.end(),
			[](Score*a, Score*b) {if (a->score != b->score)return a->score > b->score; return a->id < b->id; });
		mapOutputLevel[level] = list;
	}
	if (list.size() <= 0)
	{
		cout << "NA" << endl;
		return;
	}
	for (Score*s : list)
		cout << s->id.c_str() << ' ' << s->score << endl;
}

map<string, int>map_total_n;
map<string, int>map_total_score;
void OutputSite(char* site_number)
{
	string site = string(site_number);
	int total_n = 0, total_score = 0;
	if (map_total_n.find(site) != map_total_n.end() && map_total_score.find(site) != map_total_score.end())
	{
		total_n = map_total_n[site];
		total_score = map_total_score[site];
	}
	else
	{
		for (auto l : List)
			if (l.first.substr(1, 3) == site)
			{
				total_n++;
				total_score += l.second->score;
			}

		map_total_n[site] = total_n;
		map_total_score[site] = total_score;
	}
	if (total_n <= 0)
	{
		cout << "NA" << endl;
		return;
	}
	cout << total_n << ' ' << total_score << endl;
}

struct Site
{
	string site;
	int count;
};

map<string, vector<Site*>>mapOutputDate;
void OutputDate(char*date_str)
{
	string date = string(date_str);
	vector<Site*>sites;
	if (mapOutputDate.find(date) != mapOutputDate.end())
		sites = mapOutputDate[date];
	else
	{
		map<string, Site*>site_map = map<string, Site*>();
		for (auto l : List)
		{
			string t = l.first.substr(4, 6);
			if (l.first.substr(4, 6) == date)
			{
				string site = l.first.substr(1, 3);
				auto find = site_map.find(site);
				if (find == site_map.end())
				{
					Site*new_site = new Site({ site,1 });
					site_map.insert(pair<string, Site*>(site, new_site));
					sites.push_back(new_site);
				}
				else find->second->count++;
			}
		}
		sort(sites.begin(), sites.end(), [](Site*a, Site*b) {if (a->count != b->count)return a->count > b->count; return a->site < b->site; });
		mapOutputDate[date] = sites;
	}
	if (sites.size() <= 0)
	{
		cout << "NA" << endl;
		return;
	}
	for (Site*s : sites)
		cout << s->site.c_str() << ' ' << s->count << endl;
}

int main()
{
	cin >> N >> M;
	for (int n = 0; n < N; n++)
	{
		char id[100];
		int score;
		cin >> id >> score;
		string ids = string(id);
		List[ids] = new Score({ ids,score });
	}
	for (int m = 1; m <= M; m++)
	{
		int type;
		char term[100];
		cin >> type >> term;
		cout << "Case " << m << ": " << type << ' ' << term << endl;
		switch (type)
		{
		case 1:OutputLevel(term[0]); break;
		case 2:OutputSite(term); break;
		case 3:OutputDate(term); break;
		}
	}
	return 0;
}

/*正确*/
/*！！！仔细校对输出格式！！！*/
/*暂存结果防止超时*/