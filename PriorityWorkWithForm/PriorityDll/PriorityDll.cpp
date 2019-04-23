// PriorityDll.cpp : ���� DLL Ӧ�ó���ĵ���������
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
	string ID;                                       //��ҵ��
	int priority;                                            //���ȼ�
	double begin_time;                               //�ύʱ��
	double rtime;                                    //�Ѿ�����ʱ��
	double turnaround_time;                          //��תʱ��
	double cpu_service_time;                         //ռ��CPU��ʱ��
	double io_time;                                  //����I/O��ʱ��
	double finish_time;                              //���ʱ��
	double Wturnaround_time;                         //��Ȩ��תʱ��
	Box& operator = (const Box& p2)                 //���� = ���������������
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
vector<Runtime>runningpath;//��������

void _stdcall SetTimePiece(double timepiece)//�趨ʱ��Ƭ��С
{
	index = timepiece;
}

void _stdcall SetCPUMaxtime(double maxtime)//�趨CPUʱ��
{
	CPU = maxtime;
}

void _stdcall GetWorkingPath(int ID[], int isFinish[], double info[][3])//ID���Ƿ���ɣ���ǰʱ��Ƭ/������ʱ��/ʣ��ʱ��
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

void _stdcall GetResult(double res[][4])//��ʼ/����/��ת/��Ȩ��ת
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

void _stdcall Init(int nn, double processes[][4])//��ʼ����ҵ�飺process[]����ʱ��/CPUʱ��/IOʱ��/���ȼ���n����ҵ����
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

	for (int i = 0; i<n - 1; i++)//�������ȼ��Ӵ�С��������ѡ������
	{
		for (int j = i + 1; j<n; j++)
		{
			if (jcb.data[i].priority < jcb.data[j].priority)
				swap(jcb.data[i], jcb.data[j]);
		}
	}
	for (int i = 0; i<n - 1; i++)//���յ���ʱ������һ�Σ�Ҳ��ѡ������
	{
		for (int j = i + 1; j<n; j++)
		{
			if (jcb.data[i].begin_time == jcb.data[j].begin_time && jcb.data[i].ID > jcb.data[j].ID)
				swap(jcb.data[i], jcb.data[j]);
		}
	}
}

void _stdcall Priority()//���г����
{
	int j = 0;
	double running = CPU;
	double bt = jcb.data[0].begin_time;
	double gtt = 0;//�ܵ���תʱ��
	double gwtt = 0;//�ܵĴ�Ȩ��תʱ��
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
		jcb.data[j].rtime += index;//�������������һ��ʱ��Ƭ
		runningpath[j].ID = atoi(jcb.data[j].ID.c_str());
		runningpath[j].curtime = j*index;
		runningpath[j].hastime = jcb.data[j].rtime;
		runningpath[j].isFinish = false;
		runningpath[j].needtime = jcb.data[j].cpu_service_time - jcb.data[j].rtime;
		record += index;//ʱ��+1
		if (running >= 0)
		{
			if (jcb.data[j].rtime >= jcb.data[j].cpu_service_time)//���������������
			{
				runningpath[j].isFinish = true;
				real_begin = bt;
				jcb.data[j].finish_time = record + jcb.data[j].io_time;//�����������ʱ��
				jcb.data[j].turnaround_time = jcb.data[j].finish_time - jcb.data[j].begin_time;//������תʱ��
				jcb.data[j].Wturnaround_time = jcb.data[j].turnaround_time / jcb.data[j].rtime;//�����Ȩ��תʱ��

				int id = atoi(jcb.data[j].ID.c_str());
				result[id][0] = real_begin;
				result[id][1] = jcb.data[j].begin_time;
				result[id][2] = jcb.data[j].turnaround_time;
				result[id][3] = jcb.data[j].finish_time;
				result[id][4] = jcb.data[j].Wturnaround_time;
				//������

				n--;//δ�������-1
				running -= jcb.data[j].cpu_service_time;//ʣ��CPUʱ���һ��ʱ��Ƭ
				bt = record;

				gtt += jcb.data[j].turnaround_time;//��������תʱ��
				gwtt += jcb.data[j].Wturnaround_time;//�����ܴ�Ȩ��תʱ��
			}
			else
			{
				num++;
				swap(jcb.data[num], jcb.data[j]);//���������ŵ��������ȥ
			}
		}
		else
		{
			running += jcb.data[j].cpu_service_time;

			num++;
			swap(jcb.data[num], jcb.data[j]);//���������ŵ��������ȥ
		}
		if (n == 0)//û������������˳�
			break;
		j++;
	}
	average_of_turnaround_time = gtt / number;
	average_of_wighted_turnaround_time = gwtt / number;
}

