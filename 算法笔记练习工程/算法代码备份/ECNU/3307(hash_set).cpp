#include "stdafx.h"
#include<memory.h>
#include<iostream>
#include<unordered_set>
using std::cin;
using std::cout;
using std::endl;
using std::unordered_set;

unsigned N, Q;
unsigned long a[500000];
unordered_set<unsigned long>as1 = unordered_set<unsigned long>();
unordered_set<unsigned long>as2 = unordered_set<unsigned long>();
unordered_set<unsigned long>as3 = unordered_set<unsigned long>();

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
			if (as1.find(A) == as1.end())as1.insert(A);
			else if (as2.find(A) == as2.end()) { as2.insert(A); total++; }
			else if (as3.find(A) == as3.end()) { as3.insert(A); total--; }
		}
		cout << total << endl;
		as1.clear(); as2.clear(); as3.clear();
	}
	return 0;
}

/*部分正确*/
/*超时，不知如何进一步优化*/
