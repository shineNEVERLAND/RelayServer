#pragma once

#include"global.h"
#include"CAgent.h"

class CSocketOperator;
class CListenAgent:public CAgent{
	public:
		CListenAgent();//【】
	   ~CListenAgent();
	   
	    int nGetSockFd();//【】
		int nSetSockFd( int nSockFd );//【】
		
		int nInitCSocketOperator();
	    CSocketOperator * pGetSockOperator();//【】
		
	    virtual void vReadOperator();//【】
		virtual void vWriteOperator();//【】 
		
	private:	
		CSocketOperator * pSockOperator;

};