#pragma once

#include"global.h"


class CBuffer{
	public:
		CBuffer( int nMySockFd );
	   ~CBuffer();
	
		int nReadOperator();
		int nWriteOperator( dealPackage * pDealPkg );
		
		int nSetDealPkgBuffToSendList( dealPackage * pDealPkg );
		dealPackage * pGetDealPkgBuff();
		int nAllocDealPkg();//【】
		int nFreeDealPackage();
		int nSetDealPackageNull();
		
		int nInitDealPkg();
		int nRecoverDealPkg();
		
		int nReadType();//【】
		int nReadHead();//【】
		int nReadData();//【】
		
		int nListInsertThis( dealPackage * pDealPkg );//【】		
		int nListDeleteThis( dealPackage * pDealPkg  ); //【】	
		list<dealPackage*>::iterator pGetDealPkgFromSendList();
				
		int nIsEmptySendList(); //【】
		dealPackage * pMakeLoginACK();
		
		int nAddDealPkgToBufferSendList( dealPackage * pDealPkg );
		
	private:
		int nMySockFd;
		int nMyFriendSockFd;
		
		dealPackage * pDealPkgBuff;
		
		list<dealPackage*>lSendList;//发送队列
		// list<dealPackage*>::iterator ilist;//发送队列的迭代器
		
		int nPackageLength;//记录readHead()函数中，读到的头的长度结果		
		int nReadHeadCount;//记录readHead()函数中，已经读到的头的长度
		char * pchReadHeadPtr;////++++important####指向已读的头的指针
		
		int nType;
		int nReadTypeCount;
		char * pchReadTypePtr;
		
};