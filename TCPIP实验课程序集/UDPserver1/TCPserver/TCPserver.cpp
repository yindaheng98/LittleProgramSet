// client.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<windows.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib")
#define DEFAULT_PORT 9000
#define BUFFER_LENGTH 1024

void main()
{
	int iPort = DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sSocket;
	int iLen;
	int iSend;
	int iRecv;
	int recvcount = 5;
	char recv_buf[BUFFER_LENGTH];
	struct sockaddr_in ser, cli;
	printf("-------------------------\n");
	printf("Server waiting\n");
	printf("-------------------------\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock.\n");
		return;
	}
	sSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (sSocket == INVALID_SOCKET)
	{
		printf("socket()Failed:%d\n", WSAGetLastError());
		return;
	}
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sSocket, (sockaddr*)&ser, sizeof(ser)) == SOCKET_ERROR)
	{
		printf("bind()Failed:%d\n", WSAGetLastError());
		return;
	}
	iLen = sizeof(cli);
	memset(recv_buf, 0, sizeof(recv_buf));
	while (recvcount>0)
	{
		iRecv = recvfrom(sSocket, recv_buf, BUFFER_LENGTH, 0, (SOCKADDR*)&cli, &iLen);
		if (iRecv == SOCKET_ERROR)
		{
			printf("recvfrom() Failed:%d", WSAGetLastError());
			break;
		}
		else if (iRecv == 0) break;
		else
		{
			printf("recvfrom():%s\n", recv_buf);
			printf("Accepted client IP:[%s],port:[%d]\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
		}
		iSend = sendto(sSocket, recv_buf, sizeof(recv_buf), 0, (SOCKADDR*)&cli, sizeof(cli));
		if (iSend == SOCKET_ERROR)
		{
			printf("sendto Failed:%d\n", WSAGetLastError());
			printf("------------------------------\n");
			break;
		}
		else if (iSend == 0)break;
		else
		{
			printf("return to client succeeded!\n");
			printf("------------------------------\n");
		}
		memset(recv_buf, 0, sizeof(recv_buf));
		recvcount--;
	}
	closesocket(sSocket);
	WSACleanup();
	system("pause");
}