#include "stdafx.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
int A[10000];

int tags[10000][2];
int M[10000];

void max(unsigned k)
{
	if (k <= 0)
	{
		tags[0][0] = tags[0][1] = M[0] = A[0];
		return;
	}
	if (M[k - 1] > 0)
	{
		M[k] = M[k - 1] + A[k];
		tags[k][0] = tags[k - 1][0];
		tags[k][1] = A[k];
	}
	else M[k] = tags[k][0] = tags[k][1] = A[k];
}

int main()
{
	int K;
	for (cin >> K; K > 0; cin >> K)
	{
		bool negative = true;
		for (unsigned k = 0; k < K; k++)
		{
			cin >> A[k];
			if (A[k] >= 0)negative = false;
		}
		if (negative)
		{
			cout << 0 << ' ' << A[0] << ' ' << A[K - 1];
			continue;
		}

		for (unsigned k = 0; k < K; k++)
			max(k);

		unsigned mk = 0;
		for (unsigned k = 0; k < K; k++)
			if (M[mk] < M[k])
				mk = k;

		cout << M[mk] << ' ' << tags[mk][0] << ' ' << tags[mk][1] << endl;
	}
	return 0;
}

/*ÕıÈ·*/
