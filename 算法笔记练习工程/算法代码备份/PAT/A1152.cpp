#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<math.h>
using std::cin;
using std::cout;
using std::endl;

#define MAX 100000

int L, K;
char N[1001];

bool notPrime[MAX];
void initPrime()
{
	memset(notPrime, 0, MAX * sizeof(bool));
	for (int i = 2; i < MAX; i++)
		if (!notPrime[i])
			for (int j = i * 2; j < MAX; j += i)
				notPrime[j] = true;
}

bool isPrime(long n)
{
	if (n < 2)return false;
	int rest = n % 6;
	if (rest != 1 && rest != 5)return false;
	if (n < MAX)return !notPrime[n];
	long sq = (long)ceil(sqrt(n)) + 10;
	for (int i = 2; i < (sq < MAX ? sq : MAX); i++)
		if (!notPrime[i] && (n%i == 0))
			return false;
	for (int i = MAX - (MAX % 6); i < sq; i += 6)
		if ((n != (i + 1) && n % (i + 1) == 0) || (n != i - 1 && n % (i - 1) == 0))
			return false;
	return true;
}

long atoi(char*n,int K)
{
	long i = 0;
	for (int k = 0; k < K; k++)
		i = i * 10 + n[k] - '0';
	return i;
}

int findPrime(char N[1001], int L, int K)
{
	int P = 0;
	while (N[P] == '0')P++;
	while (P <= L - K)
	{
		if (isPrime(atoi(&N[P], K)))
			break;
		P++;
	}
	return P;
}

int main()
{
	initPrime();
	cin >> L >> K;
	cin >> N;
	int P = findPrime(N, L, K);
	if (P > L - K)cout << "404";
	else
	{
		for (int i = 0; i < K; i++)
			cout << N[P + i];
	}
	return 0;
}

/*部分正确，应该是大于和大于等于的问题*/
/*prime：质数*/
/*"the leading zeroes are not in the original number."*/