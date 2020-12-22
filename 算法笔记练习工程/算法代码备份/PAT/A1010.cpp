#include "stdafx.h"
#include<iostream>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

char sN[2][11];
unsigned N[2];

unsigned atoi(char*a, unsigned radix)
{
	unsigned i = 0;
	unsigned N = strlen(a);
	for (unsigned n = 0; n < N; n++)
	{
		if (a[n] >= '0'&&a[n] <= '9')i = i*radix + a[n] - '0';
		else if (a[n] >= 'a'&&a[n] <= 'z')i = i*radix + a[n] - 'a' + 10;
	}
	return i;
}

char* itoa(unsigned i, unsigned radix)
{
	vector<char>vs = vector<char>();
	if (i == 0)vs.push_back('0');
	while (i > 0)
	{
		unsigned c = i%radix;
		if (c < 10)vs.push_back(c + '0');
		else vs.push_back(c - 10 + 'a');
		i /= radix;
	}
	unsigned l = vs.size();
	char*s = new char[l+1];
	for (unsigned i = 0; i < l; i++)
		s[i] = vs[l - i - 1];
	s[l] = '\0';
	return s;
}

int main()
{
	unsigned tag, radix;
	cin >> sN[0] >> sN[1] >> tag >> radix;
	tag=(tag-1)%2;
	N[tag] = atoi(sN[tag], radix);
	for(radix=2;radix<36;radix++)
		if (strcmp(sN[(tag + 1) % 2], itoa(N[tag], radix)) == 0)
		{
			cout << radix;
			return 0;
		}
	cout << "Impossible";
	return 0;
}

/*部分正确*/
/*radix要考虑溢出的情况*/
