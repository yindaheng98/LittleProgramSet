#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<map>
#include<string>
#include<vector>
#include<math.h>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;
using std::sort;

int P, M, N;
struct Grade
{
	string id;
	int p;
	int mid_term;
	int final;
	int G;
};
map<string, Grade*>students;
vector<Grade*>order_list;

int main()
{
	cin >> P >> M >> N;
	char StudentID[21];
	for (int i = 0; i < P; i++)
	{
		int p;
		cin >> StudentID >> p;
		string id = string(StudentID);
		Grade* grade = new Grade({ id, p,-1,-1 });
		order_list.push_back(grade);
		students.insert(pair<string, Grade*>(id, grade));
	}
	for (int i = 0; i < M; i++)
	{
		int mid_term;
		cin >> StudentID >> mid_term;
		string id = string(StudentID);
		auto student = students.find(id);
		if (student == students.end())
		{
			Grade* grade = new Grade({ id,-1,mid_term,-1 });
			order_list.push_back(grade);
			students.insert(pair<string, Grade*>(id, grade));
		}
		else student->second->mid_term = mid_term;
	}
	for (int i = 0; i < N; i++)
	{
		int final;
		cin >> StudentID >> final;
		string id = string(StudentID);
		auto student = students.find(id);
		if (student == students.end())
		{
			Grade* grade = new Grade({ id, -1,-1,final });
			order_list.push_back(grade);
			students.insert(pair<string, Grade*>(id, grade));
		}
		else student->second->final = final;
	}
	for (Grade* s : order_list)
		s->G = (s->mid_term) > (s->final) ? (int)round(s->mid_term*0.4 + s->final*0.6) : s->final;
	sort(
		order_list.begin(),
		order_list.end(),
		[](Grade*a, Grade*b) {
		if (a->G != b->G)
			return a->G > b->G;
		return a->id < b->id;
	});
	for (Grade*s : order_list)
		if (s->p >= 200 && s->G >= 60)
			printf("%s %d %d %d %d\n", s->id.c_str(), s->p, s->mid_term, s->final, s->G);
	return 0;
}

/*ÕıÈ·*/