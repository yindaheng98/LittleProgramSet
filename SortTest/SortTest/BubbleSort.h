//√∞≈›≈≈–Ú“—ÕÍ≥…
#pragma once
void BubbleSort(int s[], int n)
{
	bool ex = true;
	while (ex)
	{
		ex = false;
		for (int i = 1; i < n; i++)
		{
			if (s[i] < s[i - 1])
			{
				s[i - 1] = s[i - 1] ^ s[i];
				s[i] = s[i - 1] ^ s[i];
				s[i - 1] = s[i - 1] ^ s[i];
				ex = true;
			}
		}
	}
}

/*int Partition(int s[], int low, int high)
{
	while (low < high)
	{
		if (s[low] > s[high])
		{
			s[low] = s[low] ^ s[high];
			s[high] = s[low] ^ s[high];
			s[low] = s[low] ^ s[high];
		}
		low++;
		high--;
	}
}*/

void change(int&x, int&y)
{
	if (x != y)
	{
		x = x ^ y;
		y = x ^ y;
		x = x ^ y;
	}
}

int Partition(int s[], int low, int high)
{
	int key = s[low];
	while (low < high)
	{
		while (low<high&&s[high]>=key)high--;
		change(s[low], s[high]);
		while (low<high&&s[low]<=key)low++;
		change(s[low], s[high]);
	}
	return low;
}

void Sort(int s[], int low, int high)
{
	if (low < high)
	{
		int tag = Partition(s, low, high);
		Sort(s, low, tag - 1);
		Sort(s, tag + 1, high);
	}
}

void QuickSort(int s[], int n)
{
	Sort(s, 0, n - 1);
}
