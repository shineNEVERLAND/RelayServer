#pragma once

#ifndef _GLOBAL__
#define _GLOBAL__

#include<iostream>
#include<string>

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<errno.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>


#include<vector>
#include<list>
#include<algorithm>

using namespace std;

#define OFF_LINE -3
#define ON_LINE 9

#define ECONTINUE -2
#define ERROR -1
#define SUCCESS 1

#define LOGIN_MESSAGE 2
#define NORMAL_MESSAGE 3
#define LOGIN_ACK 8

#define READ_OVER 4
#define WRITE_OVER 5

#define EMPTY 6
#define NON_EMPTY 7

#define FD_NUM 1000

#define CLI_NUM 2000
#define LISTENQ 1024
#define SERV_PORT 6130



// #define FALSE -1

typedef struct _package{
	int nMessageType;
	int nPackageLength;	
	char pchPackageData[0];
}package;

typedef struct _dealPackage{
	int nMySockFd;
	int nMyFriendSockFd;
	bool bAlreadyAlloc;
	bool bAlreadyType;
	int nMessageType;
	int nReadCount;
	int nWriteCount;
	char * pchReadPtr;
	char * pchWritePtr;
	package * pPkg;
}dealPackage;

class CEpoll;
class CListenAgent;

class COffLineManager;
class CBufferManager;
class CAgentManager;
class CTaskManager;


extern CEpoll cEp;
extern CListenAgent cLisAgt;

extern COffLineManager g_OffLineManager;
extern CBufferManager g_BufferManager;
extern CAgentManager g_RelayAgentManager;
extern CTaskManager g_MessageTaskManager;


extern int nMallocPkg;
extern int nFreePkg;


#endif




