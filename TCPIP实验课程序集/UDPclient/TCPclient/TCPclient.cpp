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

void main(int argc, char *argv[]) {
	while (true)
	{
		printf("Input server IP address: ");
		scanf("%s", *argv);
		WSADATA data;
		WORD w = MAKEWORD(2, 0);
		char sztext[] = "Server,how are you.\r\n";
		WSAStartup(w, &data);
		SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
		sockaddr_in addr, addr2;
		int n = sizeof(addr2);
		char buff[1024] = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(75);
		addr.sin_addr.S_un.S_addr = inet_addr(argv[0]);
		printf("UDP server has been opened.\r\n");
		if (sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&addr, n) != 0)
		{
			recvfrom(s, buff, 1024, 0, (sockaddr*)&addr2, &n);
			printf("Server says:%s\r\n", buff);
			closesocket(s);
			WSACleanup();
		}
	}
}