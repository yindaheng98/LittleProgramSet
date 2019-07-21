#pragma pack(1)
#define ICMP_ECHOREPLY 0
#define ICMP_ECHOREQ 8
typedef struct tagIPHDR
{
	u_char VIHL;
	u_char TOS;
	short TotLen;
	short ID;
	short FlagOff;
	u_char TTL;
	u_char Protocol;
	u_short Checksum;
	struct in_addr iaSrc;
	struct in_addr iaDst;
}IPHDR, *PIPHDR;

typedef struct tagICMPHDR
{
	u_char TYpe;
	u_char Code;
	u_short Checksum;
	u_short ID;
	u_short Seq;
	char Data;
}ICMPHDR, *PICMPHDR;

#define REQ_DATASIZE 32

typedef struct tagECHOREQUEST
{
	ICMPHDR icmpHdr;
	DWORD dwTime;
	char cData[REQ_DATASIZE];
}ECHOREQUEST, *PECHOREQUEST;

typedef struct tagECHOREPLY
{
	IPHDR ipHdr;
	ECHOREQUEST echoRequest;
	char cFiller[256];
}ECHOREPLY, *PECHOREPLY;
#pragma pack()