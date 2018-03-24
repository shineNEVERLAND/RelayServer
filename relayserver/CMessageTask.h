#pragma once

#include"global.h"
#include"CTask.h"

class CBuffer;
class CMessageTask:public CTask{
	public:
		CMessageTask();
	   ~CMessageTask();
	    virtual int nNext( int nMySockFd );//message task的这个函数，函数的是对端的sockfd
		
		int nDeliverMessageBetweenTask( int nMySockFd , int nMyFriendSockFd );
		
		int nSendMessageToAnotherTask( int nMySockFd, dealPackage * pDealPkg, CMessageTask * pMessageTask );
		
		// int nReceiveMessageFromAnotherTask( dealPackage * pDealPkg );
		
		int nDeliverDealPkgToSelfAgent( int nMySockFd, dealPackage * pDealPkg );
		
		// int nSetDealPkgMessageTask( dealPackage * pDealPkg );
	private:
		// dealPackage * pDealPkgTask;
};