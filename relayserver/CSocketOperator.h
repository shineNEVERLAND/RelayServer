#pragma once

#include"global.h"

class CSocketOperator{
	public:
		CSocketOperator();
	   ~CSocketOperator();
	    int nSocketCreate();
		int nSetNonBlock( int fd );//���ص������ú÷��������׽���fd
		int nAcceptNonBlock();//���ص����������׽���connfd
	private:
		int nSockFd;

};