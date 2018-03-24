#include"global.h"

int allocDealPackage( int clifd, int position)
{
	g_EpollPtr[position] = ( EpollPtr* )malloc( sizeof(EpollPtr) );
	if( NULL == g_EpollPtr[position]  )
	{
		printf("malloc g_EpollPtr error\n");
		return ERROR;
	}
	g_EpollPtr[position]->INdealPackage = (dealPackage *)malloc(sizeof(dealPackage));
	g_EpollPtr[position]->OUTdealPackage = (dealPackage *)malloc(sizeof(dealPackage));
	
	/////////////////////////////////////////
	
	g_EpollPtr[position]->INdealPackage->nMySockFd = clifd;
	// g_EpollPtr[position]->INdealPackage->nMyFriendSockFd = -1;
	
	g_EpollPtr[position]->INdealPackage->bAlreadyAlloc = FALSE;//还未给数据包分配空间
	g_EpollPtr[position]->INdealPackage->bAlreadyType = FALSE;//还未设置消息类型
	g_EpollPtr[position]->INdealPackage->nMessageType = -1;//还未设置消息类型
	
	g_EpollPtr[position]->INdealPackage->nReadCount = 0;
	g_EpollPtr[position]->INdealPackage->nWriteCount = 0;
	
	g_EpollPtr[position]->INdealPackage->pchReadPtr = NULL;
	g_EpollPtr[position]->INdealPackage->pchWritePtr = NULL;
	
	g_EpollPtr[position]->INdealPackage->pPkg = NULL;
	
	/////////////////////////////
	
	g_EpollPtr[position]->OUTdealPackage->nMySockFd = clifd;
	// g_EpollPtr[position]->OUTdealPackage->nMyFriendSockFd = -1;
	
	g_EpollPtr[position]->OUTdealPackage->bAlreadyAlloc = FALSE;//还未给数据包分配空间
	g_EpollPtr[position]->OUTdealPackage->bAlreadyType = FALSE;//还未设置消息类型
	g_EpollPtr[position]->OUTdealPackage->nMessageType = -1;//还未设置消息类型
	
	g_EpollPtr[position]->OUTdealPackage->nReadCount = 0;
	g_EpollPtr[position]->OUTdealPackage->nWriteCount = 0;
	
	g_EpollPtr[position]->OUTdealPackage->pchReadPtr = NULL;
	g_EpollPtr[position]->OUTdealPackage->pchWritePtr = NULL;
	
	g_EpollPtr[position]->OUTdealPackage->pPkg = NULL;
	
	
	
	return SUCCESS;
}