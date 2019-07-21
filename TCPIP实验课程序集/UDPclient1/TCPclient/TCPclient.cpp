// server.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
//#include<windows.h>
#pragma comment(lib,"ws2_32.lib")

#define DEFAULT_PORT 9000
#define DATA_BUFFER 1024

void main(int argc, char *argv[]) {
	printf("Input server IP address: ");
	scanf("%s", *argv);
	WSADATA wsaData;
	SOCKET sClient;
	int iPort = DEFAULT_PORT;
	int iLen;
	int iSend;
	int iRecv;
	int recvcount = 5;
	char recv_buf[DATA_BUFFER];
	char charRecv[DATA_BUFFER] = { 0 };
	char send_buf[DATA_BUFFER] = { 0 };
	sockaddr_in ser;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock");
		return;
	}
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.S_un.S_addr = inet_addr(argv[0]);
	sClient = socket(AF_INET, SOCK_DGRAM, 0);
	if (sClient == INVALID_SOCKET)
	{
		printf("socket() Failed");
		return;
	}
	iLen = sizeof(ser);
	int recvNum = 0;
	memset(charRecv, 0, 1024);
	memset(recv_buf, 0, sizeof(recv_buf));

	while (recvcount > 0)
	{
		memset(charRecv, 0, 1024);
		memset(recv_buf, 0, sizeof(recv_buf));
		printf("To:");
		scanf("%s", send_buf);
		iSend = sendto(sClient, send_buf, sizeof(send_buf), 0, (sockaddr*)&ser, iLen);
		if (iSend == SOCKET_ERROR)
		{
			printf("sendto() Failed");
			break;
		}
		else if (iSend == 0)
		{
			printf("nothing send");
			break;
		}
		else printf("send to server succeeded\n");
		iRecv = recvfrom(sClient, recv_buf, sizeof(recv_buf), 0, (sockaddr*)&ser, &iLen);
		if (iRecv == SOCKET_ERROR)
		{
			printf("recvfrom() Failed");
			break;
		}
		else if (iRecv == 0)
		{
			printf("nothing return");
			break;
		}
		else
		{
			printf("return from server:%s\n", recv_buf);
			printf("-------------------------------\n");
		}
		recvcount--;
	}
	closesocket(sClient);
	WSACleanup();
	system("pause");
}