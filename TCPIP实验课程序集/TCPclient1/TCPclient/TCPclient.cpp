// server.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<stdio.h>
#include<Winsock2.h>
#include<stdlib.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")
#define DEFAULT_PORT 5555
#define DATA_BUFFER 1024

void main(int argc, char *argv[])
{
	char ip_str[100];
	int iPort = DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sClient;
	int iLen;
	char buf[DATA_BUFFER];
	struct sockaddr_in ser;
	printf("Input IP address:");
	scanf("%s",ip_str);
	memset(buf, 0, sizeof(buf));

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock.\n");
		return;
	}
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = inet_addr(ip_str);
	sClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sClient == INVALID_SOCKET)
	{
		printf("socket()Failed:%d\n", WSAGetLastError());
		return;
	}
	if (connect(sClient, (struct sockaddr*)&ser, sizeof(ser)) == INVALID_SOCKET)
	{
		printf("connect()Failed:%d\n", WSAGetLastError());
		return;
	}
	else
	{
		iLen = recv(sClient, buf, sizeof(buf), 0);
		if (iLen == 0)return;
		else if (iLen == SOCKET_ERROR)
		{
			printf("recv()Failed:%d\n", WSAGetLastError());
			return;
		}
		printf("recv()data from server:%s\n", buf);
	}
	closesocket(sClient);
	WSACleanup();
	system("pause");
}