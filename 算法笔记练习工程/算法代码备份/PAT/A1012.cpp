#include "stdafx.h"
#include<iostream>
#include<math.h>
#include<stdio.h>
#include<vector>
#include<map>
#include<algorithm>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::pair;
using std::sort;
using std::string;

int M, N;
char course[4] = { 'A','C','M','E' };

struct Student{
	char id[7];
	int grade[4];
	int rank[4];
};
vector<Student>v = vector<Student>();
map<string, int*>m = map<string, int*>();
int j;

int argmax(int s[4],int n)
{
	int min = N;
	int mini = n;
	while(n-->0)
		if (s[n] <= min)
		{
			mini = n;
			min = s[n];
		}
	return mini;
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		Student s = {};
		cin >> s.id;
		double total = 0;
		for (int j = 1; j <= 3; j++)
		{
			cin >> s.grade[j];
			total += s.grade[j];
		}
		s.grade[0] = (int)round(total / 3);
		v.push_back(s);
	}
	for (j = 0; j < 4; j++)
	{
		sort(v.begin(), v.end(), [](Student a, Student b)->bool {return a.grade[j] > b.grade[j]; });
		for (int i = 0; i < N; i++)
		{
			if (i > 0 && v[i].grade[j] == v[i - 1].grade[j])
				v[i].rank[j] = v[i - 1].rank[j];
			else v[i].rank[j] = i + 1;
		}
	}
	for (int i = 0; i < N; i++)
		m.insert(pair<string, int*>(string(v[i].id), v[i].rank));
	for (int i = 0; i < M; i++)
	{
		char idc[7];
		cin >> idc;
		auto s = m.find(string(idc));
		if (s == m.end())
		{
			cout << "N/A" << endl;
			continue;
		}
		int* rank = s->second;
		int mini = argmax(rank, 4);
		cout <<rank[mini] << ' ' << course[mini] << endl;
	}
	return 0;
}

/*正确*/
/*A表示平均成绩，不是列出来的*/