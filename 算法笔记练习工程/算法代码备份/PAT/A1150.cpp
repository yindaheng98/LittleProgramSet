#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<memory.h>
using std::cin;
using std::cout;
using std::endl;

int N, M, K;
int dists[200][200];
bool traveled[200];

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		memset(&dists[i][0], 0xff, N * sizeof(int));
		dists[i][i] = 0;
	}
	for (int i = 0; i < M; i++)
	{
		int from, to, dist;
		cin >> from >> to >> dist;
		from--; to--;
		dists[from][to] = dists[to][from] = dist;
	}
	cin >> K;
	int min = -1, mini;
	for (int k = 0; k < K; k++)
	{
		memset(&traveled[0], 0, N * sizeof(bool));
		bool isreachable = true, issimple = true;
		int n, total_length = 0;
		cin >> n;
		int first_city, last_city;
		cin >> last_city;
		last_city--;
		first_city = last_city;
		for (int i = 1; i < n; i++)
		{
			int curr_city;
			cin >> curr_city;
			curr_city--;
			if (!isreachable)continue;//一不可达全不可达
			if (dists[last_city][curr_city] < 0)
				isreachable = false;//不可达
			total_length += dists[last_city][curr_city];
			if (traveled[last_city])issimple = false;
			traveled[last_city] = true;
			last_city = curr_city;
		}
		if (!isreachable)
		{
			printf("Path %d: NA (Not a TS cycle)\n", k + 1);
			continue;
		}
		if (first_city != last_city)
		{
			printf("Path %d: %d (Not a TS cycle)\n", k + 1, total_length);
			continue;
		}
		bool isevery = true;
		for (int i = 0; i < N; i++)
			if (!traveled[i])
			{
				isevery = false;
				break;
			}
		if (!isevery)printf("Path %d: %d (Not a TS cycle)\n", k + 1, total_length);
		else if (!issimple)printf("Path %d: %d (TS cycle)\n", k + 1, total_length);
		else printf("Path %d: %d (TS simple cycle)\n", k + 1, total_length);

		if (isreachable&&isevery)
		{
			if (min == -1)
			{
				min = total_length;
				mini = k + 1;
			}
			else if (total_length < min)
			{
				min = total_length;
				mini = k + 1;
			}
		}
	}
	if (min == -1)printf("Shortest Dist(0) = NA\n");
	else printf("Shortest Dist(%d) = %d\n", mini, min);
	return 0;
}

/*正确*/