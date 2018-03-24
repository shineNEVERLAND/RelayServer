#pragma once

#include"global.h"
#include"CTask.h"

// class CBuffer;
class CLoginTask:public CTask{
	public:
		CLoginTask();
	   ~CLoginTask();
	    virtual int nNext( int nMySockFd );
};