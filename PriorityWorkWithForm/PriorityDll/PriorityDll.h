#pragma once
extern "C" _declspec(dllexport)void _stdcall SetTimePiece(double timepiece);
//�趨ʱ��Ƭ��С

extern "C" _declspec(dllexport)void _stdcall SetCPUMaxtime(double maxtime);
//�趨CPUʱ��

extern "C" _declspec(dllexport)void _stdcall Init(int nn, double processes[][4]);
//��ʼ����ҵ�飺process[]����ʱ��/CPUʱ��/IOʱ��/���ȼ���n����ҵ����

extern "C" _declspec(dllexport)void _stdcall Priority();
//���г����

extern "C" _declspec(dllexport)int _stdcall GetPathLength();
//���ع���·�ߵĳ���

extern "C" _declspec(dllexport)void _stdcall GetResult(double res[][4]);
//��ʼ/����/��ת/��Ȩ��ת

extern "C" _declspec(dllexport)void _stdcall GetWorkingPath(int ID[], int isFinish[], double info[][3]);
//ID���Ƿ���ɣ���ǰʱ��Ƭ/������ʱ��/ʣ��ʱ��