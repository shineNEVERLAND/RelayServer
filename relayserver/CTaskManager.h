#pragma once

#include"global.h"

class CMessageTask;
class CTaskManager{
	public:
		vector<CMessageTask*>g_vecMessageTask;
		
		CTaskManager();
	   ~CTaskManager();
		CMessageTask * pNewMessageTask();	
		
		int nDeleteMessageTask( int nSockFd );
		
		CMessageTask * pGetMessageTask( int nSockFd );
		
		int nSetMessageTask( int nSockFd, CMessageTask * cMessageTaskArgue );
		
};