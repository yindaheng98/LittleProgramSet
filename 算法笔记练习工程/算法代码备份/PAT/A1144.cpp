#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<memory.h>
using std::cin;
using std::cout;
using std::endl;

int N;
bool nums[100010];

int main()
{
	cin >> N;
	memset(&nums[0], 0, (N + 10) * sizeof(bool));
	for (int i = 0; i < N; i++)
	{
		int n;
		cin >> n;
		if (n > 0 && n < 100010)nums[n] = true;
	}
	for (int i = 1; i < 100010; i++)
		if (!nums[i])
		{
			cout << i << endl;
			break;
		}
	return 0;
}

/*正确*/
/*第一次提交时在第二个循环处的终止条件写的i<N，但是实际上可能N个数直接从1到N，导致出错*/