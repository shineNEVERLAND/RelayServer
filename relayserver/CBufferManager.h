#pragma once

#include"global.h"

class CBuffer;
class CBufferManager{
	public:
		vector<CBuffer*>g_vecBufferManager;
		
		CBufferManager();
	   ~CBufferManager();
	    
		CBuffer * pNewBuffer( int nSockFd );
		
		int nDeleteBuffer( int nSockFd );
		
		CBuffer * pGetBuffer( int nSockFd );
		
		int nSetBuffer( int nSockFd, CBuffer * cBufferArgue );
};