// client.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")
#define DEFAULT_PORT 75


void main()
{
	int iport = DEFAULT_PORT;
	int ibind;
	WSADATA data;
	WORD w = MAKEWORD(2, 0);
	char sztext[] = "Welcome,everyone\r\n";
	WSAStartup(w, &data);
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in addr, addr2;
	int n = sizeof(addr2);
	char buff[1024] = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(iport);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	ibind = bind(s, (sockaddr*)&addr, sizeof(addr));
	if (ibind == SOCKET_ERROR)
		printf("bind() failed:%d\n", WSAGetLastError());
	else if (ibind == 0)
		printf("UDP server has worked.\r\n");
	while (true)
		if (recvfrom(s, buff, 1024, 0, (sockaddr*)&addr2, &n) != 0)
		{
			printf("Accept client IP:[%s],port:[%d]\r\n", inet_ntoa(addr2.sin_addr), ntohs(addr2.sin_port));
			printf("%s\r\n", buff);
			sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&addr2, n);
			break;
		}
	closesocket(s);
	WSACleanup();
	if (getchar())
		return;
	else
		Sleep(100);
}

