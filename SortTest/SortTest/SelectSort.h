//选择排序已完成
#pragma once
void SelectSort(int s[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int k = i;
		for (int j = i + 1; j < n; j++)if (s[j] < s[k])k = j;
		if (k != i)
		{
			s[k] = s[k] ^ s[i];
			s[i] = s[k] ^ s[i];
			s[k] = s[k] ^ s[i];
		}
	}
}
//堆排序已完成
void HeapSort(int s[], int n)
{
	if (n <= 1)return;
	else
	{
		for (int i = n - 1; i >= 0; i--)
		{
			if (s[i / 2]>s[i])
			{
				s[i / 2] = s[i / 2] ^ s[i];
				s[i] = s[i / 2] ^ s[i];
				s[i / 2] = s[i / 2] ^ s[i];
			}
		}
	}
	HeapSort(&s[1], n - 1);
}

