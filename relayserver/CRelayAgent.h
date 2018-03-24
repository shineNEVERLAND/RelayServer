#pragma once

#include"global.h"
#include"CAgent.h"

class CMessageTask;
class CBuffer;
class CRelayAgent:public CAgent{
	public:
		CRelayAgent();//【】
	   ~CRelayAgent();//【】
	   
	    virtual void vReadOperator();
		virtual void vWriteOperator();
		
		int nSetSockFd( int nSockFd );//【】
		int nGetSockFd();//【】
		struct epoll_event * pGetEv();//【】
		
		CBuffer * pGetBuffer();
		
		
		// int nSetDealPkgFromBuffer( dealPackage * pDealPkgBuff );
		dealPackage * pGetDealPkgBuffer();
		// int nAllocDealPkg();//【】
		
		int nNewMessageTask();//【】
		int nNewBuffer();//【】
		
		int nSetDealPkgToBuffer( dealPackage * pDealPkg );
		// int nSetDealPkgRelayToSelfBuffer( dealPackage * pDealPkg );
		
		int nDeleteDealPkg();
		
	private:
		CMessageTask * pMessageTask;
		CBuffer * pBuffer;
		
		// dealPackage * pDealPkgRelay;
		
		int nMyFriendSockFd;		
		struct epoll_event * pEv;
		
};