#include "stdafx.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

char s[10000];
bool in[10000];

int main()
{
	char c = getchar();
	unsigned n = 0;
	while (c != '\n')
	{
		s[n++] = c;
		c = getchar();
	}
	c = getchar();
	while (c != '\n')
	{
		in[(unsigned)c] = true;
		c = getchar();
	}
	n = 0;
	unsigned k = 0;
	while (s[k] != '\0')
	{
		if (!in[s[k]])
			s[n++] = s[k];
		k++;
	}
	s[n] = '\0';
	cout << s;
}

/*ÕýÈ·*/
