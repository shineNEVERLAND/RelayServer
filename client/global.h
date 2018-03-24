#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>//socket()
#include<sys/socket.h>//socket()
#include<unistd.h>//close()
#include<errno.h>
#include<netinet/in.h>
#include<sys/time.h>
#include<signal.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>

#define ERROR -1
#define SUCCESS 1
#define ECONTINUE -2

#define LOGIN_MESSAGE 2
#define NORMAL_MESSAGE 3
#define LOGIN_ACK 8

#define FALSE -4
#define TRUE  4

#define ADD_ALL_AGENT 5

#define CLI_NUM 2000
#define SERV_PORT 6130
#define PKGNUMPERCLI 2000

#define DATA_SIZE 1024

typedef struct _package{
	int nMessageType;
	int nPackageLength;
	char pchPackageData[0];
}package;

typedef struct _dealPackage{
	int nMySockFd;
	
	int bAlreadyAlloc;
	int bAlreadyType;
	
	int nMessageType;
	
	int nReadCount;
	int nWriteCount;
	
	char * pchReadPtr;
	char * pchWritePtr;
	package * pPkg;
}dealPackage;

typedef struct _EpollPtr {
	dealPackage *INdealPackage;
	dealPackage *OUTdealPackage;
}EpollPtr;

extern EpollPtr * g_EpollPtr[CLI_NUM];
extern int alreadyRecordCliNum;
extern long timeAll;

extern long long timeWhole;
extern long long HandleCount;
extern struct timeval dwStart;
extern struct timeval dwEnd;

extern int g_numLOGINACK;



void EpollDo( int epollFd );
