// server.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")

#define DEFAULT_PORT 5050
#define DATA_BUFFER 1024

void main()
{
	char addr[DATA_BUFFER];
	char buf[DATA_BUFFER];
	printf("Input server IP address:");
	scanf("%s", addr);
	WSADATA wsaData;
	SOCKET sClient;
	int iPort = DEFAULT_PORT, iLen, iSend;
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = inet_addr(addr);
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock.\n");
		return;
	}
	sClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sClient == INVALID_SOCKET)
	{
		printf("socket() Failed :%d.\n", WSAGetLastError());
		return;
	}
	if (connect(sClient, (struct sockaddr*)&ser, sizeof(ser)) == INVALID_SOCKET)
	{
		printf("connect() Failed: %d.\n", WSAGetLastError());
		return;
	}

	do
	{
		memset(buf, 0, sizeof(buf));
		printf("Input the message you wanna send:");
		scanf("%s", buf);
		iSend = send(sClient, buf, sizeof(buf), 0);
		if (iSend == SOCKET_ERROR)
		{
			printf("send() Failed: %d\n", WSAGetLastError());
			continue;
		}
		iLen = recv(sClient, buf, sizeof(buf), 0);
		if (iLen == SOCKET_ERROR)
		{
			printf("recv() Failed: %d.\n", WSAGetLastError());
			continue;
		}
		printf("recv() data from server: %s.\n", buf);
	} while (buf[0] != '0');
	closesocket(sClient);
	WSACleanup();
	system("pause");
}