#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

char num_str[1001];

class Number
{
private:
	string str;
public:
	Number(string num_str)
	{
		str = num_str;
	}

	Number operator+(const Number& b)
	{
		string str_a = str, str_b = b.str;
		string str_t = "";
		int na = str_a.size();
		int nb = str_b.size();
		int carry = 0;
		while (na > 0 || nb > 0)
		{
			na--; nb--;
			int num = carry;
			if (na >= 0)num += str_a[na] - '0';
			if (nb >= 0)num += str_b[nb] - '0';
			carry = num / 10;
			str_t = string({ (char)(num % 10 + '0') }) + str_t;
		}
		if (carry > 0)str_t = string({ (char)(carry % 10 + '0') }) + str_t;
		return Number(str_t);
	}

	Number operator~()
	{
		string str_b = "";
		int n = str.size();
		while (n-- > 0)
			str_b += str[n];
		return Number(str_b);
	}

	bool isPalindromic()
	{
		int i = 0, j = str.size() - 1;
		bool yes = true;
		while (i < j)
		{
			if (str[i] != str[j])
			{
				yes = false;
				break;
			}
			i++; j--;
		}
		return yes;
	}

	const char* c_str()
	{
		return str.c_str();
	}
};
int main()
{
	cin >> num_str;
	Number n(num_str);
	bool ok = false;
	for (int i = 0; i < 10; i++)
	{
		if (n.isPalindromic())
		{
			ok = true;
			cout << n.c_str() << " is a palindromic number." << endl;
			break;
		}
		Number nr = ~n;
		Number nn = n + nr;
		cout << n.c_str() << " + " << nr.c_str() << " = " << nn.c_str() << endl;
		n = nn;
	}
	if (!ok)cout << "Not found in 10 iterations." << endl;
	return 0;
}

/*正确*/
/*第一次提交没有考虑到只有一个字符的情况*/