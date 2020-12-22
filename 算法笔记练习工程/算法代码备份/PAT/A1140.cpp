#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<queue>
using std::cin;
using std::cout;
using std::endl;
using std::queue;

int D, N;
queue<int>q;

int main()
{
	cin >> D >> N;
	q.push(D);
	for (int i = 0; i < N - 1; i++)
	{
		queue<int>q_next = queue<int>();
		int last = q.front(), count = 1; q.pop();
		while (q.size() > 0)
		{
			if (q.front() == last)count++;
			else
			{
				q_next.push(last);
				q_next.push(count);
				count = 1;
				last = q.front();
			}
			q.pop();
		}
		q_next.push(last);
		q_next.push(count);
		q = q_next;
	}
	while (q.size() > 0)
	{
		cout << q.front();
		q.pop();
	}
	return 0;
}

/*ÕýÈ·*/