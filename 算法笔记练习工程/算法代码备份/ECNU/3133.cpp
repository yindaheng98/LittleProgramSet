#include<iostream>
#include<string.h>
using std::cin;
using std::cout;
using std::endl;

char s[201];
bool M[200][200];
short L = 0;

bool f(short i, short j)
{
	if (i == j)return M[i][j] = true;
	if (s[i] != s[j])return M[i][j] = false;
	return M[i][j] = j - i > 1 ? M[i + 1][j - 1] : true;
}

int main()
{
	unsigned T = 0;
	cin >> T;
	for (unsigned t = 0; t < T; t++)
	{
		cin >> s;
		L = strlen(s);
		short max = 0;
		for (short l = 0; l < L; l++)
			for (short i = 0; i < L - l; i++)
				max = f(i, i + l) ? l : max;
		cout << "case #" << t << ':' << endl << max + 1 << endl;
	}
	return 0;
}

/*ÕýÈ·*/
