#pragma once
extern "C" _declspec(dllexport)void _stdcall INIT(int num, int initdata[][2]);
extern "C" _declspec(dllexport)void _stdcall RUN(int status[][5]);
extern "C" _declspec(dllexport)void _stdcall ISFINISH(bool&isf);