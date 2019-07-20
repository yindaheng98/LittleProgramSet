//归并排序已完成
#pragma once
void Merge(int s1[], int s2[], int m, int n)
{
	int*r = new int[m + n];
	int i = 0, j = 0;
	int k = 0;
	while (i < m&&j < n)
		r[k++] = s1[i] < s2[j] ? s1[i++] : s2[j++];
	if (i < m)while (i < m)r[k++] = s1[i++];
	if (j < n)while (j < n)r[k++] = s2[j++];
	for (int i = 0; i < m + n; i++)
		s1[i] = r[i];
	delete[]r;
}

void MergeSort(int s[], int n)
{
	if (n <= 1)return;
	else
	{
		MergeSort(&s[0], n / 2);
		MergeSort(&s[n / 2], n / 2 + n % 2);
		Merge(&s[0], &s[n / 2], n / 2, n / 2 + n % 2);
	}
}