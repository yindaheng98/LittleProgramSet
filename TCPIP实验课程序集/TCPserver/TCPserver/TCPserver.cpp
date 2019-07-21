// client.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")
#define DEFAULT_PORT 5050
#define DATA_BUFFER 1024

void main()
{
	int iPort = DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sListen, sAccept;
	int iLen, iSend;
	char buf[DATA_BUFFER];
	sockaddr_in	ser, cli;
	printf("Server waiting.\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("Failed to load Winsock.\n");
		return;
	}

	sListen = socket(AF_INET, SOCK_STREAM, 0);
	if (sListen == INVALID_SOCKET)
	{
		printf("Socket() Failed:%d\n", WSAGetLastError());
		return;
	}

	ser.sin_family = AF_INET;
	ser.sin_port = htons(DEFAULT_PORT);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sListen, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR)
	{
		printf("bind() Failed:%d\n", WSAGetLastError());
		return;
	}
	if (listen(sListen, 5) == SOCKET_ERROR)
	{
		printf("listen() Failed:%d\n", WSAGetLastError());
		return;
	}
	iLen = sizeof(cli); sAccept = accept(sListen, (sockaddr*)&cli, &iLen);
	if (sAccept == INVALID_SOCKET)
	{
		printf("accept() Failed: %d\n", WSAGetLastError());
		return;
	}
	printf("Client from:%s:%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

	do
	{
		iLen = recv(sAccept, buf, sizeof(buf), 0);
		if (iLen == SOCKET_ERROR)
		{
			printf("recv() Failed: %d.\n", WSAGetLastError());
			continue;
		}
		printf("recv():[%s],port:[%d]\r\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
		printf("%s\r\n", buf);

		iSend = send(sAccept, buf, sizeof(buf), 0);
		if (iSend == SOCKET_ERROR)
		{
			printf("send() Failed: %d\n", WSAGetLastError());
			continue;
		}
		printf("send() byte:%d\n", iSend);
	} while (buf[0] != '0');
	closesocket(sAccept);
	closesocket(sListen);
	WSACleanup();
	system("pause");
}

