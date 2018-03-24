#pragma once

#include"global.h"

class CTask{
	public:
		CTask();
	    virtual ~CTask();
	    virtual int nNext( int nMySockFd ){};
};