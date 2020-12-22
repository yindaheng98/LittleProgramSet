#include "stdafx.h"
#include<iostream>
#include<string.h>
using std::cin;
using std::cout;
using std::endl;

char s[2][110];
unsigned M[110][110];

unsigned max(unsigned a, unsigned b) { return a > b ? a : b; }

unsigned f(unsigned i, unsigned j)
{
	if (i == 0 || j == 0)return M[i][j] = (unsigned)(s[0][i] == s[1][j]);
	if (s[0][i] == s[1][j])return M[i][j] = M[i - 1][j - 1] + 1;
	return M[i][j] = max(M[i - 1][j], M[i][j - 1]);
}

int main()
{
	while (!cin.eof())
	{
		cin >> s[0] >> s[1];
		unsigned L[2] = { strlen(s[0]),strlen(s[1]) };
		unsigned max = 0;
		for (unsigned i = 0; i < L[0]; i++)
			for (unsigned j = 0; j < L[1]; j++)
			{
				unsigned c = f(i, j);
				max = max > c ? max : c;
			}
		cout << max << endl;
	}
	return 0;
}

/*
״̬ת�Ʒ��������ֹ�������
s[0][i]!=s[1][j]ʱ��M[i-1][j-1]������M[i][j]��ȡ�������ֵ
��s[0][i]!=s[1][j]��M[i][j]Ӧ�̳�M[i][j-1]��M[i-1][j]�еĽϴ�ֵ
*/
/*����ȷ��ԭ��δ֪*/
