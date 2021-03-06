#include "stdafx.h"
#include <Winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include "ping.h"
#pragma comment(lib,"ws2_32.lib")
//函数声明
void Ping(LPCSTR pstrHost);
void ReportError(LPCSTR pstrFrom);
int WaitForEchoReply(SOCKET s);
u_short in_cksum(u_short*addr, int len);
//ICMP回送请求和应答函数申明
int SendEchoRequest(SOCKET, LPSOCKADDR_IN);
DWORD RecvEchoReply(SOCKET, LPSOCKADDR_IN, u_char*);
//主程序
void main(int argc, char**argv)
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(1, 1);//Winsock1.1
	int nRet;
	//命令行参数检查
	if (argc != 2)
	{
		fprintf(stderr, "\nUsage:ping hostname\n");
		return;
	}
	//初始化
	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (nRet)
	{
		fprintf(stderr, "\nError initializing Winsock\n");
		return;
	}
	if (wsaData.wVersion != wVersionRequested)
	{
		fprintf(stderr, "\nWinsock version not supported\n");
		return;
	}
	//调用Ping函数
	Ping(argv[1]);
	//释放Winsock
	WSACleanup();
}
////////////////
//Ping()函数
//调用Send。。。和Recv。。。函数
//并输出结果
void Ping(LPCSTR pstrHost)
{
	SOCKET rawSocket;
	LPHOSTENT lpHost;
	struct sockaddr_in saDest;
	struct sockaddr_in saSrc;
	DWORD dwTimeSent;
	DWORD dwElapsed;
	u_char cTTL;
	int nLoop;
	int nRet;
	//创建一个原始套接口
	rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (rawSocket == SOCKET_ERROR)
	{
		ReportError("socket()");
		return;
	}
	//根据主机名查询主机地址
	lpHost = gethostbyname(pstrHost);
	if (lpHost == NULL)
	{
		fprintf(stderr, "\nHost not found:%s\n", pstrHost);
		return;
	}
	saDest.sin_addr.s_addr = *((u_long FAR*)(lpHost->h_addr));
	saDest.sin_family = AF_INET;
	saDest.sin_port = 0;
	printf("\nPinging %s [%s] with %d bytes of data:\n",
		pstrHost,
		inet_ntoa(saDest.sin_addr),
		REQ_DATASIZE);
	for (nLoop = 0; nLoop<4; nLoop++)
	{
		SendEchoRequest(rawSocket, &saDest);
		nRet = WaitForEchoReply(rawSocket);
		if (nRet == SOCKET_ERROR)
		{
			ReportError("select()");
			break;
		}
		if (!nRet)
		{
			printf("\nTimeout");
			break;
		}
		dwTimeSent = RecvEchoReply(rawSocket, &saSrc, &cTTL);
		dwElapsed = GetTickCount() - dwTimeSent;
		printf("\nReply from:%s:bytes=%d time=%ldms TTL=%d",
			inet_ntoa(saSrc.sin_addr),
			REQ_DATASIZE,
			dwElapsed,
			cTTL);
	}
	printf("\n");
	nRet = closesocket(rawSocket);
	if (nRet == SOCKET_ERROR) {
		ReportError("closesocket()");
	}
}
///////////////////////////////////////////
int SendEchoRequest(SOCKET s, LPSOCKADDR_IN lpstToAddr)
{
	static ECHOREQUEST echoReq;
	static int nld = 1;
	static int nSeq = 1;
	int nRet;
	//填写会送请求信息
	echoReq.icmpHdr.TYpe = ICMP_ECHOREQ;
	echoReq.icmpHdr.Code = 0;
	echoReq.icmpHdr.Checksum = 0;
	echoReq.icmpHdr.ID = nld++;
	echoReq.icmpHdr.Seq = nSeq++;
	//填写要发送的数据
	for (nRet = 0; nRet < REQ_DATASIZE; nRet++) {
		echoReq.cData[nRet] = ' ' + nRet;
	}
	//保存发送时间
	echoReq.dwTime = GetTickCount();
	//数据存入包中并计算。。。
	echoReq.icmpHdr.Checksum = in_cksum((u_short *)&echoReq,
		sizeof(ECHOREQUEST));
	//发送会送请求
	nRet = sendto(s,
		(LPSTR)&echoReq,
		sizeof(ECHOREQUEST),
		0,
		(LPSOCKADDR)lpstToAddr,
		sizeof(SOCKADDR_IN));
	if (nRet == SOCKET_ERROR) {
		ReportError("sendto()");
	}
	return(nRet);
}
//RecvEchoReply()
DWORD RecvEchoReply(SOCKET s, LPSOCKADDR_IN lpsaForm, u_char*pTTL)
{
	ECHOREPLY echoReply;
	int nRet;
	int nAddrLen = sizeof(struct sockaddr_in);
	nRet = recvfrom(s,
		(LPSTR)&echoReply,
		sizeof(ECHOREPLY),
		0,
		(LPSOCKADDR)lpsaForm,
		&nAddrLen);
	if (nRet == SOCKET_ERROR)
		ReportError("recvfrom()");
	*pTTL = echoReply.ipHdr.TTL;
	return(echoReply.echoRequest.dwTime);
}
void ReportError(LPCSTR pWhere)
{
	fprintf(stderr, "\n%s error:%d\n",
		WSAGetLastError());
}
int WaitForEchoReply(SOCKET s)
{
	struct timeval Timeout;
	fd_set readfds;
	readfds.fd_count = 1;
	readfds.fd_array[0] = s;
	Timeout.tv_sec = 5;
	Timeout.tv_usec = 0;
	return(select(1, &readfds, NULL, NULL, &Timeout));
}
///////////////////////////////////
//in_cksum()
//计算校验和
u_short in_cksum(u_short *addr, int len)
{
	register int nleft = len;
	register u_short *w = addr;
	register u_short answer;
	register int sum = 0;
	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}
	if (nleft == 1) {
		u_short u = 0;
		*(u_char *)(&u) = *(u_char*)w;
		sum += u;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return (answer);
}