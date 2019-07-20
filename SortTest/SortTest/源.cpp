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

long long TimeCount(void(*fun)(int s[], int n), int n)//输入排序函数和数据量返回平均运行时间*3000000000.
{
	srand(read_time_stamp_counter());//随机数种
	int*s = new int[n];//测试用临时数组
	long long sum = 0;//测试总频度
	for (int i = 0; i < TEST_LOOP; i++)//测试循环TEST_LOOP次
	{
		for (int i = 0; i < n; i++)s[i] = rand();//输入一组随机数据
		long long start = read_time_stamp_counter();//计时开始
		fun(s, n);//运行
		long long end = read_time_stamp_counter();//计算结束
		sum += (end - start);//加上时间
	}
	return sum / TEST_LOOP;
}

vector<long long>TimeTest(void(*fun)(int s[], int n))//测试排序函数并存入一维向量
{
	vector<long long>data(DATA_COUNT);
	for (int i = 0; i < DATA_COUNT; i++)
		data[i] = TimeCount(fun, i*DATA_SIZE);
	return data;
}

/*只需在此添加要测试的函数即可*/

void store(vector<Algo>&data)//存入数据
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