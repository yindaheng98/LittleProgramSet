#include "stdafx.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

unsigned N, a[1000];
unsigned M[1000];

unsigned max(unsigned k)
{
	M[k] = 1;
	for (unsigned i = 0; i < k; i++)
		if (a[i] < a[k])M[k] = M[k] > (M[i] + 1) ? M[k] : (M[i] + 1);
	return M[k];
}

int main()
{
	unsigned m = 0;
	cin >> N;
	for (unsigned k = 0; k < N; k++)
	{
		cin >> a[k];
		unsigned c = max(k);
		m = m > c ? m : c;
	}
	cout << m;
	return 0;
}

/*ÕıÈ·*/
