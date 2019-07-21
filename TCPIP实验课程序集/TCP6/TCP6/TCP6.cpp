// TCP6.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#pragma comment(lib,"ws2_32.lib")
void main()
{
	WSADATA wsaData;
	int n;
	char hostname[256];
	hostent *pHostent;
	protoent *pProtoent, *pProtoent1;
	struct sockaddr_in sa;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	gethostname(hostname, sizeof(hostname));
	printf("--------------");
	printf("gethostname()::::\n");
	printf("Local host name :%s\n", hostname);
	printf("gethostbyname()::::\n");
	pHostent = gethostbyname(hostname);
	printf("name:%s\n aliases:%s \n addrtype:%d\n length:%d\n", pHostent->h_name,
		pHostent->h_aliases, pHostent->h_addrtype, pHostent->h_length);
	for (n = 0; pHostent->h_addr_list[n]; n++) {
		memcpy(&sa.sin_addr.s_addr, pHostent->h_addr_list[n], pHostent->h_length);
		printf("Address:%s\n", inet_ntoa(sa.sin_addr));
	}
	pProtoent = getprotobyname("udp");
	printf("getprotobyname()::::\n");
	printf("name:%s\n proto:%d\n", pProtoent->p_name, pProtoent->p_proto);
	for (n = 0; pProtoent->p_aliases[n]; n++) {
		printf("aliases:%s\n", pProtoent->p_aliases[n]);
	}
	int proto_number[] = { 0,1,6 };
	int proto_count = sizeof(proto_number) / sizeof(proto_number[0]);
	int i;
	for (i = 0; i<proto_count; i++) {
		pProtoent1 = getprotobynumber(proto_number[i]);
		printf("getprotobynumber()::::\n");
		printf("name:%s\n proto:%d\n", pProtoent1->p_name, pProtoent1->p_proto);
		for (n = 0; pProtoent1->p_aliases[n]; n++) {
			printf("aliases:%s\n", pProtoent1->p_aliases[n]);
		}
	}
	WSACleanup();
	system("pause");
}
