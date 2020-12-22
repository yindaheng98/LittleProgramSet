#include "stdafx.h"
#include<iostream>
#include<string.h>
using std::cin;
using std::cout;
using std::endl;

char s[5011];
char S[5011];
unsigned P[5011];
bool M[5010][5010];
unsigned L = 0;

void restruct()
{
	unsigned j = 0;
	for (unsigned i = 0; i < L; i++)
		if (s[i] >= 'a'&&s[i] <= 'z')
		{
			S[j] = s[i];
			P[j] = i;
			j++;
		}
		else if (s[i] >= 'A'&&s[i] <= 'Z')
		{
			S[j] = s[i] - 'A' + 'a';
			P[j] = i;
			j++;
		}
	S[j] = '\0';
	L = strlen(S);
}

bool f(unsigned i, unsigned j)
{
	if (i == j)return M[i][j] = true;
	if (S[i] != S[j])return M[i][j] = false;
	return M[i][j] = j - i > 1 ? M[i + 1][j - 1] : true;
}

int main()
{
	char c = getchar();
	while (c != '\n'&&c != EOF)
	{
		s[L++] = c;
		c = getchar();
	}
	s[L] = '\0';
	restruct();
	unsigned max = 0;
	unsigned ii = 0, jj = 0;
	for (unsigned l = 0; l < L; l++)
		for (unsigned i = 0; i < L - l; i++)
			if (f(i, i + l) && l > max)
			{
				ii = i;
				jj = i + l;
			}
	s[P[jj] + 1] = '\0';
	cout << &s[P[ii]] << endl;
	return 0;
}

/*出现过一次运行错误*/
/*原因是缺少c != EOF导致程序不能停止*/
/*正确*/
