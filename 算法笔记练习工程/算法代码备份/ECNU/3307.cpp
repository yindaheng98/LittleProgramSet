#include "stdafx.h"
#include<memory.h>
#include<iostream>
#include<unordered_set>
using std::cin;
using std::cout;
using std::endl;
using std::unordered_set;

unsigned N, Q;
unsigned long a[500000];

template <typename BaseType> class BitMap
{
private:
	unordered_set<unsigned long>I = unordered_set<unsigned long>(500000);
	BaseType* bits;
	unsigned long N;

public:
	void setbit(unsigned long a)
	{
		unsigned long i = a / (sizeof(BaseType) * 8);
		unsigned long j = a % (sizeof(BaseType) * 8);
		bits[i] |= 1 << j;
		I.insert(i);
	}

	bool getbit(unsigned long a)
	{
		unsigned long i = a / (sizeof(BaseType) * 8);
		unsigned long j = a % (sizeof(BaseType) * 8);
		return (bits[i] & (1 << j)) > 0;
	}

	void clearbits()
	{
		for (unsigned long i : I)
			bits[i] = 0;
		I.clear();
	}

	BitMap(unsigned long n)
	{
		N = n / (sizeof(BaseType) * 8) + 1;
		bits = new BaseType[N];
		memset(bits, 0, N * sizeof(BaseType));
	}
	~BitMap()
	{
		delete bits;
	}
};

int main()
{
	cin >> N >> Q;
	for (unsigned i = 0; i < N; i++)
		cin >> a[i];

	BitMap<unsigned> exists1 = BitMap<unsigned>(1000000000);
	BitMap<unsigned> exists2 = BitMap<unsigned>(1000000000);
	BitMap<unsigned> exists3 = BitMap<unsigned>(1000000000);
	for (unsigned q = 0; q < Q; q++)
	{
		exists1.clearbits();
		exists2.clearbits();
		exists3.clearbits();
		unsigned L, R, total = 0;
		cin >> L >> R;
		L--; R--;
		for (unsigned i = L; i <= R; i++)
		{
			unsigned long A = a[i];
			if (!exists1.getbit(A))exists1.setbit(A);
			else if (!exists2.getbit(A)) { exists2.setbit(A); total++; }
			else if (!exists3.getbit(A)) { exists3.setbit(A); total--; }
		}
		cout << total << endl;
	}
	return 0;
}

/*部分正确*/
/*超时，不知如何进一步优化*/
