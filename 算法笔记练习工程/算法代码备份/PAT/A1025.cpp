#include "stdafx.h"
#include<iostream>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::sort;
struct Testee
{
	long long regnum;
	unsigned score;
	unsigned local_numb;
	unsigned local_rank = 0;
};

Testee* testees[40000];
unsigned locations[200];
unsigned K[200], N;

bool cmp(Testee*a, Testee*b)
{
	if (a->score == b->score)
		return a->regnum < b->regnum;
	return a->score > b->score;
}

int main()
{
	cin >> N;
	locations[0] = 0;
	for (unsigned n = 0; n < N; n++)
	{
		cin >> K[n];
		locations[n + 1] = locations[n];
		for (unsigned k = 0; k < K[n]; k++)
		{
			Testee* testee = new Testee();
			cin >> testee->regnum >> testee->score;
			testee->local_numb = n + 1;
			testees[locations[n + 1]] = testee;
			locations[n + 1]++;
		}
		sort(&testees[locations[n]], &testees[locations[n + 1]], cmp);
		Testee*testee_last = testees[locations[n]];
		testee_last->local_rank = 1;
		for (unsigned k = 1; k < K[n]; k++)
		{
			Testee* testee = testees[locations[n] + k];
			if (testee->score == testee_last->score)
				testee->local_rank = testee_last->local_rank;
			else testee->local_rank = k + 1;
			testee_last = testee;
		}
	}
	sort(&testees[locations[0]], &testees[locations[N]], cmp);

	cout << locations[N] - locations[0] << endl;
	Testee*testee_last = testees[locations[0]];
	unsigned rank = 1;
	for (unsigned location = locations[0]; location < locations[N]; location++)
	{
		Testee*testee = testees[location];
		if (testee->score != testee_last->score)
			rank = location + 1;
		testee_last = testee;
		cout << testee->regnum << ' ' << rank << ' ' << testee->local_numb << ' ' << testee->local_rank << endl;
	}
}

/*初次测试时最后一个算例没有通过*/
/*原因目前未知*/
