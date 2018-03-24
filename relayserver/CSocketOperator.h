#pragma once

#include"global.h"

class CSocketOperator{
	public:
		CSocketOperator();
	   ~CSocketOperator();
	    int nSocketCreate();
		int nSetNonBlock( int fd );//返回的是设置好非阻塞的套接字fd
		int nAcceptNonBlock();//返回的是已连接套接字connfd
	private:
		int nSockFd;

};