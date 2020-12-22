#include "stdafx.h"
#include<memory.h>
#include<iostream>
#include<unordered_map>
using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;
using std::pair;

unsigned N, Q;
unsigned long a[500000];
unordered_map<unsigned long, unsigned>ac = unordered_map<unsigned long, unsigned>();

int main()
{
	cin >> N >> Q;
	for (unsigned i = 0; i < N; i++)
		cin >> a[i];

	for (unsigned q = 0; q < Q; q++)
	{
		unsigned L, R, total = 0;
		cin >> L >> R;
		L--; R--;
		for (unsigned i = L; i <= R; i++)
		{
			unsigned long A = a[i];
			auto c = ac.find(A);
			if (c == ac.end())
				ac.insert(pair<unsigned long, unsigned>(A, 1));
			else
			{
				if (c->second == 1)total++;
				if (c->second == 2)total--;
				c->second++;
			}
		}
		cout << total << endl;
		ac.clear();
	}
	return 0;
}

/*部分正确*/
/*超时，不知如何进一步优化*/
