#pragma once
extern "C" _declspec(dllexport)void _stdcall SetTimePiece(double timepiece);
//设定时间片大小

extern "C" _declspec(dllexport)void _stdcall SetCPUMaxtime(double maxtime);
//设定CPU时间

extern "C" _declspec(dllexport)void _stdcall Init(int nn, double processes[][4]);
//初始化作业块：process[]到达时间/CPU时间/IO时间/优先级，n：作业数量

extern "C" _declspec(dllexport)void _stdcall Priority();
//运行出结果

extern "C" _declspec(dllexport)int _stdcall GetPathLength();
//返回工作路线的长度

extern "C" _declspec(dllexport)void _stdcall GetResult(double res[][4]);
//开始/结束/周转/带权周转

extern "C" _declspec(dllexport)void _stdcall GetWorkingPath(int ID[], int isFinish[], double info[][3]);
//ID，是否完成，当前时间片/已运行时间/剩余时间