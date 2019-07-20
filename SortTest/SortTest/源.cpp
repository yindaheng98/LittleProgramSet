#include"stdafx.h"
#include"InsertSort.h"
#include"BubbleSort.h"
#include"SelectSort.h"
#include"MergeSort.h"
#include<stdlib.h>

vector<Algo>data;

#define DATA_SIZE DATA_WIDTH/DATA_COUNT
#define TEST_LOOP 20
__int64 __declspec(naked) read_time_stamp_counter()
{
	__asm cpuid;
	__asm rdtsc;
	__asm ret;
}

long long TimeCount(void(*fun)(int s[], int n), int n)//����������������������ƽ������ʱ��*3000000000.
{
	srand(read_time_stamp_counter());//�������
	int*s = new int[n];//��������ʱ����
	long long sum = 0;//������Ƶ��
	for (int i = 0; i < TEST_LOOP; i++)//����ѭ��TEST_LOOP��
	{
		for (int i = 0; i < n; i++)s[i] = rand();//����һ���������
		long long start = read_time_stamp_counter();//��ʱ��ʼ
		fun(s, n);//����
		long long end = read_time_stamp_counter();//�������
		sum += (end - start);//����ʱ��
	}
	return sum / TEST_LOOP;
}

vector<long long>TimeTest(void(*fun)(int s[], int n))//����������������һά����
{
	vector<long long>data(DATA_COUNT);
	for (int i = 0; i < DATA_COUNT; i++)
		data[i] = TimeCount(fun, i*DATA_SIZE);
	return data;
}

/*ֻ���ڴ����Ҫ���Եĺ�������*/

void store(vector<Algo>&data)//��������
{
	data.push_back(Algo{ CString("MergeSort"),TimeTest(MergeSort) });
	data.push_back(Algo{ CString("InsertSort") ,TimeTest(InsertSort) });
	data.push_back(Algo{ CString("BinInsertSort") ,TimeTest(BinInsertSort) });
	data.push_back(Algo{ CString("ShellSort"),TimeTest(ShellSort) });
	data.push_back(Algo{ CString("SelectSort"),TimeTest(SelectSort) });
	data.push_back(Algo{ CString("HeapSort"),TimeTest(HeapSort) });
	data.push_back(Algo{ CString("BubbleSort"),TimeTest(BubbleSort) });
	data.push_back(Algo{ CString("QuickSort"),TimeTest(QuickSort) });
}