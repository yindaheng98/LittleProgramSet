// PriorityDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include<string>
#include<vector>

using std::string;
using std::endl;
using std::swap;
using std::to_string;
using std::vector;

struct Box
{
	string ID;                                       //作业号
	int priority;                                            //优先级
	double begin_time;                               //提交时间
	double rtime;                                    //已经运行时间
	double turnaround_time;                          //周转时间
	double cpu_service_time;                         //占用CPU的时间
	double io_time;                                  //用于I/O的时间
	double finish_time;                              //完成时间
	double Wturnaround_time;                         //带权周转时间
	Box& operator = (const Box& p2)                 //重载 = 运算符，方便排序
	{
		this->priority = p2.priority;
		this->begin_time = p2.begin_time;
		this->rtime = p2.rtime;
		this->finish_time = p2.finish_time;
		this->cpu_service_time = p2.cpu_service_time;
		this->io_time = p2.io_time;
		this->ID = p2.ID;
		this->turnaround_time = p2.turnaround_time;
		this->Wturnaround_time = p2.Wturnaround_time;
		return *this;
	}
};

typedef struct
{
	vector<Box>data;

} JCB;

typedef struct
{
	int ID;
	double hastime;
	double curtime;
	double needtime;
	bool isFinish;
}Runtime;

double CPU = 10.0;
double index = 0.5;
JCB jcb, jcb_1;
int n, number;
vector<vector<double>> result;
double average_of_turnaround_time;
double average_of_wighted_turnaround_time;
vector<Runtime>runningpath;//工作序列

void _stdcall SetTimePiece(double timepiece)//设定时间片大小
{
	index = timepiece;
}

void _stdcall SetCPUMaxtime(double maxtime)//设定CPU时间
{
	CPU = maxtime;
}

void _stdcall GetWorkingPath(int ID[], int isFinish[], double info[][3])//ID，是否完成，当前时间片/已运行时间/剩余时间
{
	for (int i = 0; i < (int)runningpath.size(); i++)
	{
		ID[i] = runningpath[i].ID;
		isFinish[i] = runningpath[i].isFinish;
		info[i][0] = runningpath[i].curtime;
		info[i][1] = runningpath[i].hastime;
		info[i][2] = runningpath[i].needtime;
	}
}

void _stdcall GetResult(double res[][4])//开始/结束/周转/带权周转
{
	for (int i = 0; i < number; i++)
	{
		res[i][0] = result[i][1];
		res[i][1] = result[i][3];
		res[i][2] = result[i][2];
		res[i][3] = result[i][4];
	}
}

int _stdcall GetPathLength()
{
	return runningpath.size();
}

void _stdcall Init(int nn, double processes[][4])//初始化作业块：process[]到达时间/CPU时间/IO时间/优先级，n：作业数量
{
	double totaltime = 0;

	n = nn;
	number = n;
	result.resize(n);
	jcb.data.resize(n);
	jcb_1.data.resize(n);
	runningpath.resize(1);
	for (int i = 0; i < n; i++)
		result[i].resize(5, 0);
	for (int i = 0; i<n; i++)
	{
		jcb.data[i].ID = to_string(i);
		jcb.data[i].begin_time = processes[i][0];
		jcb.data[i].cpu_service_time = processes[i][1];
		jcb.data[i].io_time = processes[i][2];
		jcb.data[i].priority = (int)processes[i][3];
		jcb.data[i].rtime = 0;
		totaltime += jcb.data[i].begin_time > totaltime ? jcb.data[i].begin_time : totaltime + jcb.data[i].cpu_service_time + 1;
	}

	jcb.data.resize((int)(totaltime / index + 1));
	jcb_1.data.resize((int)(totaltime / index + 1));

	for (int i = 0; i<n - 1; i++)//按照优先级从大到小排序，这是选择排序
	{
		for (int j = i + 1; j<n; j++)
		{
			if (jcb.data[i].priority < jcb.data[j].priority)
				swap(jcb.data[i], jcb.data[j]);
		}
	}
	for (int i = 0; i<n - 1; i++)//按照到达时间再排一次，也是选择排序
	{
		for (int j = i + 1; j<n; j++)
		{
			if (jcb.data[i].begin_time == jcb.data[j].begin_time && jcb.data[i].ID > jcb.data[j].ID)
				swap(jcb.data[i], jcb.data[j]);
		}
	}
}

void _stdcall Priority()//运行出结果
{
	int j = 0;
	double running = CPU;
	double bt = jcb.data[0].begin_time;
	double gtt = 0;//总的周转时间
	double gwtt = 0;//总的带权周转时间
	double real_begin;
	double record = jcb.data[0].begin_time;
	int num = n - 1;
	while (1)
	{
		if (jcb.data[j].cpu_service_time > CPU)
		{
			throw "over running range!!!";
			exit(0);
		}
		runningpath.resize(j + 1);
		jcb.data[j].rtime += index;//把这个任务运行一个时间片
		runningpath[j].ID = atoi(jcb.data[j].ID.c_str());
		runningpath[j].curtime = j*index;
		runningpath[j].hastime = jcb.data[j].rtime;
		runningpath[j].isFinish = false;
		runningpath[j].needtime = jcb.data[j].cpu_service_time - jcb.data[j].rtime;
		record += index;//时间+1
		if (running >= 0)
		{
			if (jcb.data[j].rtime >= jcb.data[j].cpu_service_time)//如果这个任务完成了
			{
				runningpath[j].isFinish = true;
				real_begin = bt;
				jcb.data[j].finish_time = record + jcb.data[j].io_time;//计算最终完成时间
				jcb.data[j].turnaround_time = jcb.data[j].finish_time - jcb.data[j].begin_time;//计算周转时间
				jcb.data[j].Wturnaround_time = jcb.data[j].turnaround_time / jcb.data[j].rtime;//计算带权周转时间

				int id = atoi(jcb.data[j].ID.c_str());
				result[id][0] = real_begin;
				result[id][1] = jcb.data[j].begin_time;
				result[id][2] = jcb.data[j].turnaround_time;
				result[id][3] = jcb.data[j].finish_time;
				result[id][4] = jcb.data[j].Wturnaround_time;
				//输出结果

				n--;//未完成任务-1
				running -= jcb.data[j].cpu_service_time;//剩余CPU时间减一个时间片
				bt = record;

				gtt += jcb.data[j].turnaround_time;//计入总周转时间
				gwtt += jcb.data[j].Wturnaround_time;//记入总带权周转时间
			}
			else
			{
				num++;
				swap(jcb.data[num], jcb.data[j]);//把这个任务放到队列最后去
			}
		}
		else
		{
			running += jcb.data[j].cpu_service_time;

			num++;
			swap(jcb.data[num], jcb.data[j]);//把这个任务放到队列最后去
		}
		if (n == 0)//没有任务可做就退出
			break;
		j++;
	}
	average_of_turnaround_time = gtt / number;
	average_of_wighted_turnaround_time = gwtt / number;
}

