#include "stdafx.h"
#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
string words[80];
int w = 0;

int main()
{
	while (!cin.eof())
		cin >> words[w++];
	w -= 2;
	while (w > 0)cout << words[w--].c_str() << ' ';
	cout << words[w].c_str();
}

